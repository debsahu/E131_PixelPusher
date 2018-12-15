#include <ESP8266WiFi.h>
#include <ESPAsyncUDP.h>         //https://github.com/me-no-dev/ESPAsyncUDP
#include <ESPAsyncE131.h>        //https://github.com/forkineye/ESPAsyncE131
#ifdef ESP8266
#include <Hash.h>
#include <ESPAsyncTCP.h>         //https://github.com/me-no-dev/ESPAsyncTCP
#else
#include <AsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>   //https://github.com/me-no-dev/ESPAsyncWebServer
#include <ESPAsyncWiFiManager.h> //https://github.com/alanswx/ESPAsyncWiFiManager
#include <ESPAsyncDNSServer.h>   //https://github.com/devyte/ESPAsyncDNSServer
// #include <DNSServer.h>
//                               //https://github.com/me-no-dev/ESPAsyncUDP
#include <NeoPixelBus.h>
#include <pgmspace.h>

#define HOSTNAME "E131PixelPusher"
#define HTTP_PORT 80

#define UNIVERSE 1                        // First DMX Universe to listen for
#define UNIVERSE_COUNT 7                  // Total number of Universes to listen for, starting at UNIVERSE max 7 for multicast and 12 for unicast
uint16_t ledCount = UNIVERSE_COUNT * 170; // 170 LEDs per Universe

// ESPAsyncE131 instance with UNIVERSE_COUNT buffer slots
ESPAsyncE131 e131(UNIVERSE_COUNT);
AsyncWebServer server(HTTP_PORT);
AsyncDNSServer dns;
// DNSServer dns;

NeoEsp8266Dma800KbpsMethod dma = NeoEsp8266Dma800KbpsMethod(ledCount, 3);
uint8_t *pixel = (uint8_t *)malloc(dma.getPixelsSize());

#define SHOW_FPS_SERIAL //uncomment to see Serial FPS
#ifdef SHOW_FPS_SERIAL
uint64_t frameCt = 0;
uint64_t PM = 0;
float interval = 10 * 1000.0; // 10s
#endif

char update_html[] PROGMEM = R"=====(<!DOCTYPE html><html lang="en"><head><title>Firmware Update</title><meta http-equiv="Content-Type" content="text/html; charset=utf-8"><meta name="viewport" content="width=device-width"><link rel="shortcut icon" type="image/x-icon" href="favicon.ico"></head><body><h3>Update Firmware</h3><br><form method="POST" action="/update" enctype="multipart/form-data"><input type="file" name="update"> <input type="submit" value="Update"></form></body></html>)=====";

void setup()
{
    SPIFFS.begin();
    Serial.begin(115200);
    delay(10);

    char NameChipId[64] = {0};
    snprintf(NameChipId, sizeof(NameChipId), "%s_%06x", HOSTNAME, ESP.getChipId());

    WiFi.mode(WIFI_STA); // Make sure you're in station mode
    wifi_station_set_hostname(const_cast<char *>(NameChipId));
    AsyncWiFiManager wifiManager(&server, &dns); //Local intialization. Once its business is done, there is no need to keep it around
    wifiManager.setConfigPortalTimeout(180);     //sets timeout until configuration portal gets turned off, useful to make it all retry or go to sleep in seconds
    if (!wifiManager.autoConnect(NameChipId))
    {
        Serial.println("Failed to connect and hit timeout");
        ESP.restart();
    }
    Serial.println("");
    Serial.print(F("Connected with IP: "));
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Send E1.31 Multicast UDP Request to " + WiFi.localIP().toString());
    });
    server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", update_html);
        request->send(response);
    });
    server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request) {
        bool shouldReboot = !Update.hasError();
        AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", shouldReboot?"OK":"FAIL");
        response->addHeader("Connection", "close");
        response->addHeader("Access-Control-Allow-Origin", "*");
        request->send(response);
        if(shouldReboot) ESP.reset(); },
              [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
          if (!filename.endsWith(".bin")) {
                return;
            }
            if(!index){
                Serial.printf("Update Start: %s\n", filename.c_str());
                Update.runAsync(true);
                if(!Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000)) {
                Update.printError(Serial);
                }
            }
            if(!Update.hasError()){
                if(Update.write(data, len) != len) {
                Update.printError(Serial);
                }
            }
            if(final){
                if(Update.end(true)) 
                Serial.printf("Update Success: %uB\n", index+len);
                else {
                Update.printError(Serial);
                }
            } });

    server.begin();

    // Choose one to begin listening for E1.31 data
    //if (e131.begin(E131_UNICAST))                               // Listen via Unicast
    if (e131.begin(E131_MULTICAST, UNIVERSE, UNIVERSE_COUNT)) // Listen via Multicast
        Serial.println(F("Listening for data..."));
    else
        Serial.println(F("*** e131.begin failed ***"));
    delay(1000);
#ifdef SHOW_FPS_SERIAL
    Serial.end();
#endif
    dma.Initialize();
    memset(pixel, 0, sizeof(pixel));
}

void loop()
{
    if (!e131.isEmpty())
    {
        e131_packet_t packet;
        e131.pull(&packet); // Pull packet from ring buffer

        uint16_t universe = htons(packet.universe);
        uint8_t *data = packet.property_values + 1;

        if (universe < UNIVERSE || universe > UNIVERSE_COUNT)
            return; //async will take care about filling the buffer

        // Serial.printf("Universe %u / %u Channels | Packet#: %u / Errors: %u / CH1: %u\n",
        //               htons(packet.universe),                 // The Universe for this packet
        //               htons(packet.property_value_count) - 1, // Start code is ignored, we're interested in dimmer data
        //               e131.stats.num_packets,                 // Packet counter
        //               e131.stats.packet_errors,               // Packet error counter
        //               packet.property_values[1]);             // Dimmer data for Channel 1

        uint16_t multipacketOffset = (universe - UNIVERSE) * 170; //if more than 170 LEDs (510 channels), client will send in next higher universe
        if (ledCount <= multipacketOffset)
            return;
        uint16_t len = (170 + multipacketOffset > ledCount) ? (ledCount - multipacketOffset) * 3 : 510;
        memcpy(pixel + multipacketOffset * 3, data, len); // Burden on source to send in correct color order
    }

    if (dma.IsReadyToUpdate())
    {
        memcpy(dma.getPixels(), pixel, dma.getPixelsSize());
        dma.Update();
#ifdef SHOW_FPS_SERIAL
        frameCt++;
#endif
    }

#ifdef SHOW_FPS_SERIAL
    if (millis() - PM >= interval)
    {
        PM = millis();
        Serial.printf("FPS: %.2f\n", interval / frameCt);
        frameCt = 0;
    }
#endif
}
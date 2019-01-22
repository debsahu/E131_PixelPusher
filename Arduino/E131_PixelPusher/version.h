#define SKETCH_VERSION "1.2.0"

/*
* Dec 13, 2018 v1.0.0
* - Initial Release v1.0
* 
* Dec 14, 2018 v1.1.0
* - Trimmed and made it fast
* - RGB order is a burden on the source: must match RGB order of NeoPixels
*
* Dec 15, 2018 v1.1.1
* - Minor bug fixes
* - Add MDNS (new implementation on ESP8266 core v 2.5.0)
* - Remove dist folder, supply dist with release
*
* Dec 16,2018 v1.1.2
* - Changes to webserver reponses
* - no FPS drop from above change
*
* Jan 7, 2019 (commented by default so version remains same)
* - Added ESP32 support (check platformio.ini for compiling details)
* - APA102/DotStar relavent lines
*
* Jan 8, 2019 v1.1.2 (commented by default so version remains same)
* - Added Arduino IDE compatibility mode, DNS server is not Async for ArduinoIDE
*
* Jan 21, 2019 v1.2.0
* - Add web interface
* - user can choose starting universe, unicast/umulticast, total number of universe
*/
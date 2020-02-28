# E131_PixelPusher

[![Build Status](https://travis-ci.com/debsahu/E131_PixelPusher.svg?branch=master)](https://travis-ci.com/debsahu/E131_PixelPusher) [![License: MIT](https://img.shields.io/github/license/debsahu/E131_PixelPusher.svg)](https://opensource.org/licenses/MIT) [![version](https://img.shields.io/github/release/debsahu/E131_PixelPusher.svg)](https://github.com/debsahu/E131_PixelPusher/releases/tag/1.2.2) [![LastCommit](https://img.shields.io/github/last-commit/debsahu/E131_PixelPusher.svg?style=social)](https://github.com/debsahu/E131_PixelPusher/commits/master)

Minimalistic Async code around Async E131 for ESP8266/ESP32

- Completely Async
- Web-interface to set starting universe, unicast/umulticast, total number of universes
- WiFiManager Captive Portal to get WiFi credentials (Compile with `-DUSE_EADNS` for ESP8266)
- Subscribes to E131 multicast
- Connect RX/GPIO3 to DIN of NeoPixel strip, and any PIN (<GPIO32) specified for ESP32
- Upload included [firmware.bin](https://github.com/debsahu/E131_PixelPusher/releases/latest) at http://<IP_ADDRESS>/update for ESP8266, compile your own for ESP32
- Included relavent lines for APA102/Dotstar LED strip: Comment `//#define USE_NEOPIXELS xxx` and uncomment `#define USE_DOTSTAR`
  - ESP8266 Hardware SPI: Uses GPIO14(SCK) for CLOCK and GPIO13(MOSI) for DATA
  - ESP32 Hardware SPI: Uses GPIO18(SCK) for CLOCK and GPIO23(MOSI) for DATA

[![E131_PixelPusher](https://img.youtube.com/vi/lZ09GlO2_8s/0.jpg)](https://www.youtube.com/watch?v=lZ09GlO2_8s)

## Libraries Needed

[platformio.ini](https://github.com/debsahu/E131_PixelPusher/blob/master/platformio.ini) is included, use [PlatformIO](https://platformio.org/platformio-ide) and it will take care of installing the following libraries.

| Library                   | Link                                                       | Platform    |
|---------------------------|------------------------------------------------------------|-------------|
|ESPAsyncE131               |https://github.com/forkineye/ESPAsyncE131                   |ESP8266/32   |
|ESPAsyncUDP                |https://github.com/me-no-dev/ESPAsyncUDP                    |ESP8266      |
|ESPAsyncTCP                |https://github.com/me-no-dev/ESPAsyncTCP                    |ESP8266      |
|NeoPixelBus                |https://github.com/Makuna/NeoPixelBus                       |ESP8266/32   |
|ESPAsyncWiFiManager        |https://github.com/alanswx/ESPAsyncWiFiManager              |ESP8266/32   |
|ESPAsyncDNSServer          |https://github.com/devyte/ESPAsyncDNSServer                 |ESP8266      |
|ESP Async WebServer        |https://github.com/me-no-dev/ESPAsyncWebServer              |ESP8266/32   |
|AsyncTCP                   |https://github.com/me-no-dev/AsyncTCP                       |ESP32        |
|Adafruit's Dot Star        |https://github.com/debsahu/Adafruit_DotStar                 |ESP8266/32   |

## Pushing E1.31 UDP Data

### Jinx
- Download Jinx from [here](http://www.live-leds.de/downloads/)
- Setup instructions: see video

### LEDfx
- Download and installation instructions for LEDfx are [here](https://ahodges9.github.io/LedFx/)
- Setup instructions: see video

### xLights
- Download xLights from [here](https://xlights.org/releases/)
- Setup instructions: see video

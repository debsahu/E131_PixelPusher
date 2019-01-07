# E131_PixelPusher

[![Build Status](https://travis-ci.com/debsahu/E131_PixelPusher.svg?branch=master)](https://travis-ci.com/debsahu/E131_PixelPusher) [![License: MIT](https://img.shields.io/github/license/debsahu/E131_PixelPusher.svg)](https://opensource.org/licenses/MIT) [![version](https://img.shields.io/github/release/debsahu/E131_PixelPusher.svg)](https://github.com/debsahu/E131_PixelPusher/releases/tag/1.1.2) [![LastCommit](https://img.shields.io/github/last-commit/debsahu/E131_PixelPusher.svg?style=social)](https://github.com/debsahu/E131_PixelPusher/commits/master)

Minimalistic Async code around Async E131 for ESP8266/ESP32

- Completely Async
- WiFiManager Captive Portal to get WiFi credentials (Compile with `-DUSE_EADNS` for ESP8266)
- Subscribes to E131 multicast
- Connect RX/GPIO3 to DIN of NeoPixel strip, and any PIN (<GPIO32) specified for ESP32
- Upload included [firmware.bin](https://github.com/debsahu/E131_PixelPusher/releases/latest) at http://<IP_ADDRESS>/update for ESP8266, compile your own for ESP32
- Included relavent lines for APA102/Dotstar LED strip

[![E131_PixelPusher](https://img.youtube.com/vi/lZ09GlO2_8s/0.jpg)](https://www.youtube.com/watch?v=lZ09GlO2_8s)

## Libraries Needed

[platformio.ini](https://github.com/debsahu/E131_PixelPusher/blob/master/platformio.ini) is included, use [PlatformIO](https://platformio.org/platformio-ide) and it will take care of installing the following libraries.

| Library                   | Link                                                       |
|---------------------------|------------------------------------------------------------|
|ESPAsyncE131               |https://github.com/forkineye/ESPAsyncE131                   |
|ESPAsyncUDP                |https://github.com/me-no-dev/ESPAsyncUDP                    |
|ESPAsyncTCP                |https://github.com/me-no-dev/ESPAsyncTCP                    |
|NeoPixelBus                |https://github.com/Makuna/NeoPixelBus                       |
|ESPAsyncWiFiManager        |https://github.com/alanswx/ESPAsyncWiFiManager              |
|ESPAsyncDNSServer          |https://github.com/devyte/ESPAsyncDNSServer                 |
|ESP Async WebServer        |https://github.com/me-no-dev/ESPAsyncWebServer              |

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

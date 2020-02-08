/*************************
 * ArtNet FastLED
 * Edoardo Viviani <edoardo.viviani@gmail.com
 * 08/02/2020
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "ArtNet.h"
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

#define STASSID "wifi-ssid"
#define STAPSWD "wifi-passwd"

#define FIXTURE_UNIVERSE 0
#define FIXTURE_ADDRESS 1
#define FIXTURE_LEDS 30 // MUST BE <=170

#define LED_PIN     D4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

uint8_t packetBuffer[ARTNET_MAX_PACKET_SIZE];
WiFiUDP Udp;

CRGB *leds;

void setup() {  
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSWD);
  while (WiFi.status() != WL_CONNECTED) { delay(1); }
  Udp.begin(ARTNET_PORT);

  leds = (CRGB*)&packetBuffer[ARTNET_DATA + FIXTURE_ADDRESS - 1];
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, FIXTURE_LEDS).setCorrection( TypicalLEDStrip );
}

void loop() {
  uint16_t packetSize = Udp.parsePacket();
  if (packetSize) {
    Udp.read(packetBuffer, packetSize);

    if(packetBuffer[0] != 'A') // packet first bytes are 'Art-Net\0', just check A to make sure it is an ArtNet packet
      return;

    uint16_t universe = packetBuffer[ARTNET_UNIVERSE_LOW];
    universe |= packetBuffer[ARTNET_UNIVERSE_HIGH] << 8;

    if(universe != FIXTURE_UNIVERSE) // sorry, this data is not for me
      return;

    // IGNORED FOR NOW, TODO: DO NOT IGNORE THANKS otherwise RGB data may be corrupted due to FASTLed reading directly from packet buffer
    // uint16_t dataSize = packetBuffer[ARTNET_LENGTH_LOW];
    // dataSize |= packetBuffer[ARTNET_LENGTH_HIGH] << 8;

    FastLED.show();
  }
}

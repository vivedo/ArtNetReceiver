# ArtNet LED Strip controller

This software runs on an ESP8266 module (tested on a NodeMCU clone). Listens via WiFi for ArtNet packets and commands LED strips via the FASTLed library (tested with WS2802 strips).
Currently handles up to 170 RGB LEDs (one single DMX universe).

Compiled on Arduino IDE 1.8.11
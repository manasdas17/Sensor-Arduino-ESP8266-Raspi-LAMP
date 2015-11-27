# Sensor-Arduino-ESP8266-Raspi-LAMP
A web panel which plots some values like temperature and humidity using Raspberry Pi, Arduino and WiFi module ESP8266

* Details:
It is used an Arduino system based with the DHT22 temperature and humidity sensor. Arduino can introduce data into server using WiFi
communication through ESP8266 module.
Raspberry Pi has implemented a LAMP server which receive data values using a "GET" request.

* Considerations:
Some ESP8266 Firmware version have bugs. These bugs won't affect if they are connected to a WiFi Network which same would be like "Name12"
(name with some numbers and without space between characters).

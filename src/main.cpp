//
// Created by Gennadii Ilyashenko on 27.11.2025.
//

#include <Arduino.h>

#include "sensors.h"
#include "lcd_12864.h"

const uint8_t lcdQuarterFirst = 32;
const uint8_t lcdQuarterSecond = 64;
const uint8_t lcdQuarterThird = 96;

DeviceAddress airIn = {0x28, 0x61, 0x64, 0x35, 0xC6, 0x16, 0xA0, 0x46};
DeviceAddress airOut = {0x28, 0x61, 0x64, 0x35, 0xC6, 0x1E, 0x36, 0xFC};
DeviceAddress coolantIn = {0x28, 0x61, 0x64, 0x35, 0xC6, 0x25, 0x5B, 0x6A};
DeviceAddress coolantOut = {0x28, 0x61, 0x64, 0x35, 0xC6, 0x24, 0xF3, 0xC3};

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* CS=*/ 5, /* reset=*/
                                 22); // Feather HUZZAH ESP8266, E=clock=14, RW=data=13, RS=CS

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
uint8_t sensorsCount = 0;
const uint8_t charLenPix = 6;
const bool emulateTemp = true;

const uint8_t loopNum = 25;
uint8_t loopId = 0;

void setup() {
    Serial.begin(115200);

    sensors.begin();
    sensors.setResolution(TEMPERATURE_PRECISION);
    sensorsCount = getDeviceCount();
    if (sensorsCount == 0) {
        Serial.println("Wait 10 seconds");
        ESP.restart();
    }

    u8g2.begin();
    u8g2_prepare();
}

void loop() {
    if (loopId == 0 || loopId == loopNum) {
        printSensorsAddress(sensorsCount);
        loopId = 0;
    }

    sensors.requestTemperatures();

    u8g2.clearBuffer();

    drawThreeSections();

    u8g2.sendBuffer();

    delay(250);
    loopId++;
}
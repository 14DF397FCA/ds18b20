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

void setup() {
    Serial.begin(115200);

    sensors.begin();
    sensors.setResolution(TEMPERATURE_PRECISION);
    sensorsCount = getDeviceCount();
    if (sensorsCount == 0) {
        Serial.println("Wait 10 seconds");
        ESP.restart();
    }

    printSensorsAddress(sensorsCount);

    u8g2.begin();
}

void loop() {
    sensors.requestTemperatures();

    printSensorsAddress(sensorsCount);

    u8g2.clearBuffer();
    u8g2_prepare();

    //  Inflated air
    drawData(lcdQuarterSecond, 0, 0, "Inflated air");
    drawData(0, 10, 0,">>");
    drawData(-1, 10, 0,">>");
    u8g2.drawVLine(lcdQuarterSecond, 10, 10);
    drawData(lcdQuarterFirst, 10, 6, String(int(getTemperatureByDevice(airIn))));
    drawData(lcdQuarterThird, 10, -6, String(int(getTemperatureByDevice(airOut))));
    u8g2.drawHLine(0, 20, 128);

    //  Coolant
    drawData(lcdQuarterSecond, 21, 0, "Coolant");
    drawData(0, 31, 0,">>");
    drawData(-1, 31, 0,">>");
    u8g2.drawVLine(lcdQuarterSecond, 31, 10);
    drawData(lcdQuarterFirst, 31, 6, String(int(getTemperatureByDevice(coolantIn))));
    drawData(lcdQuarterThird, 31, -6, String(int(getTemperatureByDevice(coolantOut))));
    u8g2.drawHLine(0, 41, 128);

//    Extra
    drawData(lcdQuarterSecond, 42, 0, "Extra sensors");
    drawData(0, 52, 0, ">>");
    drawData(-1, 52, 0, ">>");
    u8g2.drawVLine(lcdQuarterSecond, 52, 10);
    drawData(lcdQuarterFirst, 52, 6, String(getRandTemp()));
    drawData(lcdQuarterThird, 52, -6, String(getRandTemp()));

    u8g2.sendBuffer();

    delay(250);
}
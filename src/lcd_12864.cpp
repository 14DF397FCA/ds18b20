//
// Created by Gennadii Ilyashenko on 27.11.2025.
//

#include "lcd_12864.h"

void u8g2_prepare() {
    u8g2.setFont(font);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
}

uint8_t sLengthPix(const String &t) {
    return t.length() * charLengthPix;
}

void drawData(const int8_t xBase, const uint8_t y, const uint8_t offset, const String &s) {
    uint8_t sLen = sLengthPix(s);
    uint8_t x = 0;
    if (xBase == -1) {
        x = 128 - sLen;
    } else if (xBase > 0) {
        x = (xBase - sLen / 2) + offset;
    }
    u8g2.drawStr(x, y, s.c_str());
}


uint8_t drawSection(const uint8_t y, const String &head, const float a, const float b) {
    uint8_t lastLine = y + (2 * charHeightPix);

    drawData(lcdQuarterSecond, y, 0, head.c_str());
    drawData(0, y + charHeightPix, 0, ">>");
    drawData(-1, y + charHeightPix, 0, ">>");
    u8g2.drawVLine(lcdQuarterSecond, y + charHeightPix, 10);
    drawData(lcdQuarterFirst, y + charHeightPix, 6, String(int(a)));
    drawData(lcdQuarterThird, y + charHeightPix, -6, String(int(b)));
    u8g2.drawHLine(0, lastLine, 128);
    return lastLine;
}

void drawThreeSections() {
    u8g2.clearBuffer();
    uint8_t lastLine = 0;
    lastLine = drawSection(lastLine, "Inflated air", getTemperatureByDevice(airIn),
                           getTemperatureByDevice(airOut));
    lastLine = drawSection(lastLine + 1, "Coolant", getTemperatureByDevice(coolantIn),
                           getTemperatureByDevice(coolantOut));
    if (font == u8g2_font_6x12_tf) {
        drawSection(lastLine + 1, "Extra sensors", getRandTemp(), getRandTemp());
    }
    u8g2.sendBuffer();
}

uint8_t drawRaw(const uint8_t xBase, const uint8_t y, const uint8_t offset, const String &head, const String& data) {
    uint8_t sLenPix = sLengthPix(head);
    u8g2.drawStr(xBase - sLenPix - offset, y, head.c_str());
    u8g2.drawStr(xBase + offset + 1, y, String(data).c_str());
    u8g2.drawHLine(0, charHeightPix + y, 128);
    return y + charHeightPix + 2;
}

void twoColumns() {
    u8g2.clearBuffer();
    uint8_t y = 0;
    uint8_t x = lcdQuarterThird - charLengthPix;
    uint8_t offset = 3;
    y = drawRaw(x, y, offset, "Intake in", String(int(getTemperatureByDevice(airIn))));
    y = drawRaw(x, y, offset, "Intake out", String(int(getTemperatureByDevice(airOut))));
    y = drawRaw(x, y, offset, "Coolant in", String(int(getTemperatureByDevice(coolantIn))));
    y = drawRaw(x, y, offset, "Coolant out", String(int(getTemperatureByDevice(coolantOut))));
    u8g2.drawVLine(x, 0, y -1);
    u8g2.sendBuffer();
}
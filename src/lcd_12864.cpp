//
// Created by Gennadii Ilyashenko on 27.11.2025.
//

#include "lcd_12864.h"

void u8g2_prepare() {
    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
}

uint8_t sLengthPix(const String &t) {
    return t.length() * charLenPix;
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


uint8_t drawSection(const uint8_t y, const uint8_t fontH, const String &head, const float a, const float b) {
    uint8_t lastLine = y + (2 * fontH);

    drawData(lcdQuarterSecond, y, 0, head.c_str());
    drawData(0, y + fontH, 0, ">>");
    drawData(-1, y + fontH, 0, ">>");
    u8g2.drawVLine(lcdQuarterSecond, y + fontH, 10);
    drawData(lcdQuarterFirst, y + fontH, 6, String(int(a)));
    drawData(lcdQuarterThird, y + fontH, -6, String(int(b)));
    u8g2.drawHLine(0, lastLine, 128);
    return lastLine;
}

void drawThreeSections() {
    uint8_t fontH = 10;
    uint8_t lastLine = 0;
    lastLine = drawSection(lastLine, fontH, "Inflated air", getTemperatureByDevice(airIn),
                           getTemperatureByDevice(airOut));
    lastLine = drawSection(lastLine + 1, fontH, "Coolant", getTemperatureByDevice(coolantIn),
                           getTemperatureByDevice(coolantOut));
    drawSection(lastLine + 1, fontH, "Extra sensors", getRandTemp(), getRandTemp());
}

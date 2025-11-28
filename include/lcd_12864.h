//
// Created by Gennadii Ilyashenko on 27.11.2025.
//

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include "sensors.h"

#ifndef DS18B20_LCD_12864_H
#define DS18B20_LCD_12864_H

extern U8G2_ST7920_128X64_F_SW_SPI u8g2;
extern const uint8_t charLenPix;
extern const uint8_t lcdQuarterFirst;
extern const uint8_t lcdQuarterSecond;
extern const uint8_t lcdQuarterThird;

void drawData(const int8_t xBase, const uint8_t y, const uint8_t offset, const String &s);
uint8_t sLengthPix(const String &t);
void u8g2_prepare();
uint8_t drawSection(const uint8_t y, const uint8_t fontH, const String &head, const float a, const float b);
void drawThreeSections();

#endif //DS18B20_LCD_12864_H

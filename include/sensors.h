//
// Created by Gennadii Ilyashenko on 27.11.2025.
//
#include <Arduino.h>
#include <Wire.h>
#include "OneWire.h"
#include "DallasTemperature.h"

#define ONE_WIRE_BUS 14
#define TEMPERATURE_PRECISION 9

extern OneWire oneWire;//(ONE_WIRE_BUS);
extern DallasTemperature sensors;//(&oneWire);
extern uint8_t sensorsCount;
extern const bool emulateTemp;

#ifndef DS18B20_SENSORS_H
#define DS18B20_SENSORS_H

uint8_t getDeviceCount();

void printSensorsAddress(uint8_t num);

void printAddress(DeviceAddress deviceAddress);

float getTemperatureByDevice(DeviceAddress deviceAddress);

void printTemperature(DeviceAddress deviceAddress);

void printData(DeviceAddress deviceAddress);

float getRandTemp();

#endif //DS18B20_SENSORS_H

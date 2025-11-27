//
// Created by Gennadii Ilyashenko on 27.11.2025.
//

#include "sensors.h"

uint8_t getDeviceCount() {
    Serial.print("Locating devices...");
    uint8_t c = sensors.getDeviceCount();
    if (c == 0) {
        Serial.println("No devices found.");
        return -1;
    }
    Serial.println("Found " + String(c) + " devices.");
    return c;
}

void printSensorsAddress(uint8_t num) {
    DeviceAddress t;
    for (uint8_t i; i < num; i++) {
        sensors.getAddress(t, i);
        printAddress(t);
    }
}

void printAddress(DeviceAddress deviceAddress) {
    uint8_t len = 8;
    for (uint8_t i = 0; i < len; i++) {
        if (i == 0) {
            Serial.print("0x");
        }
        // zero pad the address if necessary
        if (deviceAddress[i] < 16) {
            Serial.print("0");
        }
        Serial.print(deviceAddress[i], HEX);
        if (i < len - 1) {
            Serial.print(", 0x");
        }
    }
    Serial.println("");
}

float getTemperatureByDevice(DeviceAddress deviceAddress) {
    float tempC = sensors.getTempC(deviceAddress);
    if (emulateTemp) {
        return getRandTemp();
    }

    if (tempC == DEVICE_DISCONNECTED_C) {
        Serial.println("Error: Could not read temperature data");
        return -999.0;
    }
    return tempC;
}

void printTemperature(DeviceAddress deviceAddress) {
    Serial.print("Temp C: ");
    Serial.println(getTemperatureByDevice(deviceAddress));
}


void printData(DeviceAddress deviceAddress) {
    Serial.print("Device Address: ");
    printAddress(deviceAddress);
    Serial.print("; ");
    printTemperature(deviceAddress);
    Serial.println();
}

float getRandTemp() {
    return (float(random())/float (random())) * 10;
}
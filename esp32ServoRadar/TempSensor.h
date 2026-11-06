#pragma once
#include <cstdint>


class TempSensor {
private:
    const uint8_t pin;
    float lastTemp = 0;
public:
    explicit TempSensor(uint8_t p) : pin(p) {}

    void setReading(float t) {
        lastTemp = t;
    }

    float getReading() const {
        return lastTemp;
    }

    bool isOverHeated() const {
        return lastTemp > 100;

    }
};
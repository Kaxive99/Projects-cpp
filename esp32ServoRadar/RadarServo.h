#pragma once
#include <cstdint>

class RadarServo {
private:
    const uint8_t pin;
    uint32_t stepIntervalMs = 1;
    uint32_t lastStepMs = 0;
    uint8_t angle = 0;
    int8_t direction = 1;

public:
    RadarServo(uint8_t p, uint32_t step) : pin(p), stepIntervalMs(step) {}

    uint8_t update(uint32_t nowMs) {
        if (nowMs - lastStepMs >= stepIntervalMs) {
            angle += direction;
            lastStepMs = nowMs;
        }
    if (angle == 180) {
        direction = -1;
    } else if (angle == 0) {
        direction = 1;
    }
        return angle;
    }
    uint8_t getPin() const {return pin;}
};

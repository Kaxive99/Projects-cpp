#pragma once
#include <cstdint>

class Blinker {
private:
    uint32_t intervalMs;
    uint32_t lastToggleMs = 0;
    bool isOn = false;

public:
    explicit Blinker(uint32_t interval) : intervalMs(interval) {}

    bool update(uint32_t nowMs) {
        if (nowMs - lastToggleMs >= intervalMs) {
            lastToggleMs = nowMs;
            isOn = !isOn;
        }
        return isOn;

    }
        void setInterval(uint32_t ms) {
            intervalMs = ms;
        }
};
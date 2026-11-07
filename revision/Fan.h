#pragma once
#include <cstdint>
#include <iostream>

class Fan {

private:
    const uint8_t pin;
    bool running = false;
public:
    explicit Fan(uint8_t p) : pin(p) {}


    void turnOn() {
        running = true;
    }

    void turnOff() {
        running = false;
    }

    bool isRunning() const { return running;}

};

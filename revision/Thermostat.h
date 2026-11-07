#pragma once
#include "Fan.h"
#include <cstdint>

enum class ThermoState { Normal, Cooling, Overheat };

inline const char* nameThermoState(ThermoState s) {
    switch (s) {
        case ThermoState::Normal : return "Normal";
        case ThermoState::Cooling : return "Cooling";
        case ThermoState::Overheat : return "Overheat";
    }
}

class Thermostat {
private:
    Fan& fan;
    ThermoState state = ThermoState::Normal;

public:
    explicit Thermostat(Fan& f) : fan(f) {}
    ThermoState getState() const { return state; }
    void update(float temp) {
        switch (state) {
            case ThermoState::Normal: if (temp > 85) {
                    state = ThermoState::Cooling;
                }
                break;
            case ThermoState::Cooling: if (temp < 75) {
                    state = ThermoState::Normal;
                } else if (temp > 110) {
                    state = ThermoState::Overheat;
                }
                break;
            case ThermoState::Overheat: if (temp < 100) {
                    state = ThermoState::Cooling;
                }
                break;
        }
        if (state == ThermoState::Normal) {
            fan.turnOff();
        } else {
            fan.turnOn();
        }
    }
};

#pragma once
#include <cstdint>
#include <iostream>

enum class BatteryState { OK, Low, Critical, };

inline const char* batteryLevel(BatteryState s) {
    switch (s) {
        case BatteryState::OK : return "Ok";
        case BatteryState::Low : return "Low";
        case BatteryState::Critical : return "Critical";
    }
}

inline BatteryState nextBatteryState(BatteryState current, float voltage) {
    switch (current) {
        case BatteryState::OK : if (voltage < 11.1f) {return BatteryState::Low;} return current;
        case BatteryState::Low : if (voltage > 11.4f) {return BatteryState::OK;} else if (voltage < 10.5f) {return BatteryState::Critical;} return current;
        case BatteryState::Critical : if (voltage > 10.8f) {return BatteryState::Low;} return current;
    }
}
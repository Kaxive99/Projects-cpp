#pragma once
#include <cstdint>
#include <iostream>
#include <__fwd/string.h>

enum class RadarState {
    Scanning,
    Tracking,
    Alarm,
};


    inline const char* stateName(RadarState s) {
        switch (s) {
            case RadarState::Scanning:
                return "Scaning";
            case RadarState::Tracking:
                return "Tracking";
            case RadarState::Alarm:
                return "Alarm";
        }
        return "UNKNOWN";
    }


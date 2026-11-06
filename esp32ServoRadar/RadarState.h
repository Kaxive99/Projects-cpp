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


    inline RadarState nextState(RadarState current, float distanceCm) {
            switch (current) {
                case RadarState::Scanning:
                    if (distanceCm < 50) {
                        return RadarState::Tracking;
                    }
                    return current;

                case RadarState::Tracking:
                    if (distanceCm < 20) {
                        return RadarState::Alarm;
                    }
                    if (distanceCm > 60) {
                        return RadarState::Scanning;
                    }
                    return current;

                case RadarState::Alarm:
                    if (distanceCm > 25) {
                        return RadarState::Tracking;
                    }
                    return current;
            }
            return current;
        }
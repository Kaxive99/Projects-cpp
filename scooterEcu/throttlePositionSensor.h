#pragma once

class tps {

public:
    void rpmsToThrottle(float tps, float maxAllowedRPM) {
        float procentageThrottle = tps / 100;
        float currentRpm = maxAllowedRPM * procentageThrottle;
        std::cout << "[ECU] Current RPM: " <<currentRpm<< std::endl;
    }
};
#pragma once

enum class engineState {
    cold,
    optimal,
    warning,
    critical
};

class engineProtection {
private:
    float tempThresholdCold = 50;
    float tempThresholdOptimal = 90;
    float tempThresholdWarning = 110;
public:
    engineProtection() = default;
    int maxRPM = 0;

    engineState evaluateState(float currentTemp) const {
        if (currentTemp < tempThresholdCold) return engineState::cold;
        if (currentTemp < tempThresholdOptimal) return engineState::optimal;
        if (currentTemp < tempThresholdWarning) return engineState::warning;
        return engineState::critical;
    }

    int getMaxAllowedRPM(engineState state) {
        switch (state) {
            case engineState::cold: return 3500;
            case engineState::optimal: return 11000;
            case engineState::warning: return 8500;
            case engineState::critical: return 0;
        }
        return 0;
    }

    unsigned int maxRPMforState (int testTemp) {
            engineState currentState = evaluateState(testTemp);
            maxRPM = getMaxAllowedRPM(currentState);
            std::cout << "Status: ";

            switch (currentState) {
                case engineState::cold: std::cout << "[COLD] Max "; break;
                case engineState::optimal: std::cout << "[OK] Max "; break;
                case engineState::warning: std::cout << "[WARNING] Max "; break;
                case engineState::critical: std::cout << "[CRITICAL] Max "; break;
            }
            std::cout << maxRPM << " RPM" << std::endl;
        return maxRPM;
        }
};
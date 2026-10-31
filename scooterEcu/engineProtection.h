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

    engineState evaluateState(float currentTemp) const {
        if (currentTemp < tempThresholdCold) return engineState::cold;
        if (currentTemp < tempThresholdOptimal) return engineState::optimal;
        if (currentTemp < tempThresholdWarning) return engineState::warning;
        return engineState::critical;
    }

    int getMaxAllowedRPM(engineState state) {
        switch (state) {
            case engineState::cold: return 4000;
            case engineState::optimal: return 8500;
            case engineState::warning: return 11500;
            case engineState::critical: return 0;
        }
        return 0;
    }

    void maxRPMforState (int testTemp) {
            engineState currentState = evaluateState(testTemp);
            int maxRPM = getMaxAllowedRPM(currentState);
            std::cout << "Temp: " << testTemp << " °C | Status: ";

            switch (currentState) {
                case engineState::cold: std::cout << "[COLD] Max "; break;
                case engineState::optimal: std::cout << "[OK] Max "; break;
                case engineState::warning: std::cout << "[WARNING] Max "; break;
                case engineState::critical: std::cout << "[CRITICAL] Max "; break;
            }
            std::cout << maxRPM << " RPM" << std::endl;
        }
};
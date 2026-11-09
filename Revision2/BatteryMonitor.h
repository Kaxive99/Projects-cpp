#pragma once
#include <cstdint>
#include <string>

enum class BatteryState {Full, Ok, Low, Critical};

constexpr int kFullMv = 4100;
constexpr int kOkMv = 3700;
constexpr int kLowMv = 3400;

constexpr BatteryState voltageTopState(int voltageMv) {
        if (voltageMv >= kFullMv) return BatteryState::Full;
        if (voltageMv >= kOkMv) return BatteryState::Ok;
        if (voltageMv >= kLowMv) return BatteryState::Low;
        return BatteryState::Critical;
}

class BatteryMonitor {
private:
        const uint8_t pin_;
        BatteryState state_;

public:
        explicit BatteryMonitor(uint8_t p) : pin_(p), state_(BatteryState::Full) {}

        void update(int voltageMv) {
                if (state_ == BatteryState::Critical) {
                        return;
                }
                state_ = voltageTopState(voltageMv);

        }

        void reset() {
                state_ = BatteryState::Full;
        }

        BatteryState getState() const {return state_;}

        std::string stateName() const {
                BatteryState stateOfBattery = getState();
                switch (stateOfBattery) {
                        case BatteryState::Full : return "Full Battery";
                        case BatteryState::Ok : return "Ok Battery";
                        case BatteryState::Low : return "Low Battery";
                        case BatteryState::Critical : return "Critical Battery";
                }
                return "Unknown, system fail";
        }




};

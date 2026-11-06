#include <iostream>
#include <cstdint>

#include "BatteryState.h"

int main() {

    float voltages[] = {12.6f, 11.8f, 11.0f, 10.9f, 10.4f, 10.7f, 10.9f, 11.3f, 11.5f};
    BatteryState state = BatteryState::Low;
    for (auto voltage: voltages) {
    state = nextBatteryState(state, voltage);
    std::cout << "Poziom bateri: " << batteryLevel(state) << " Napięcie: " << voltage <<std::endl;
    }

}

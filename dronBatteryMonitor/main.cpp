#include <iostream>
#include <cstdint>

#include "BatteryState.h"
#include "CollisionRadar.h"

int main() {

    float voltages[] = {12.6f, 11.8f, 11.0f, 10.9f, 10.4f, 10.7f, 10.9f, 11.3f, 11.5f};
    BatteryState state = BatteryState::Low;
    for (auto voltage: voltages) {
    state = nextBatteryState(state, voltage);
    std::cout << "Poziom bateri: " << batteryLevel(state) << " Napięcie: " << voltage <<std::endl;
    }

    isCollisionRisk(320,280);

    int32_t intruderAltitudes[] = {500, 450, 380, 250, 300, 330, 410, 430, 470, 220, 201, 199, 100};

    for (int32_t intruderAltitude: intruderAltitudes) {

        std::cout << trajectoryName(updateTrajectory(flightTrjacetory::Cruise,300, intruderAltitude)) << std::endl;
    }
}

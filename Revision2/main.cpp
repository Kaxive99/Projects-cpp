#include <iostream>
#include <cstdint>
#include "BatteryMonitor.h"

int main() {

    constexpr uint8_t pin = 34;

    BatteryMonitor batteryMonitor(pin);

    int voltages[] = {4200, 3800, 3500, 3300, 3900, 3900};

    for (int i = 0; i < std::size(voltages); i++) {
        if (i == 5) {batteryMonitor.reset();}

        batteryMonitor.update(voltages[i]);
        std::cout<< voltages[i] << " mV ---> " << batteryMonitor.stateName() << "\n" ;
    }
}
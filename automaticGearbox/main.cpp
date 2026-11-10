#include <iostream>
#include <cstdint>
#include <thread>
#include "gearsEcu.h"
using namespace std::chrono;
using namespace std;

int main() {
    GeraboxEcu ecu(10);

    int tpss;
    int rpmss;
    std::cout << "Pozycja pedału gazu: \n";
    cin >> tpss;
    std::cout << "Obroty silnika: \n";
    cin >> rpmss;

    ecu.tpsSensor(tpss);
    ecu.rpmSensor(rpmss);



    auto tickPeriod = milliseconds(100);
    auto nextTick = std::chrono::steady_clock::now();
    while (ecu.isRunning()) {
        nextTick += tickPeriod;
        std::this_thread::sleep_until(nextTick);
        if (ecu.isNeutral()) {
            cout << "[Info] Gearbox is in neutral, put it in drive \n";
            break;
        }
        ecu.increasingRpm();
        std::cout << "Gear: " << ecu.getGearState() << " | RPM: " << ecu.getRpms() << std::endl;
    }

}
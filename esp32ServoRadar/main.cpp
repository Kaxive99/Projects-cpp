#include <iostream>
#include "Blinker.h"
#include "RadarServo.h"
#include "TempSensor.h"
#include "RadarState.h"

int main() {

    Blinker fast(1);

    RadarServo servo(13, 1);

    TempSensor tempS(4);

    for (int t = 0; t < 5; ++t) {
        bool fastOn = fast.update(t);
        std::cout << "T: " << t << " Wynik: " << fastOn << std::endl;

    }

     for (uint32_t t = 0; t < 5; ++t) {
        uint8_t a = servo.update(t);
        if (t % 1 == 0) {
            std::cout << t << " ms -> " << (int)a << std::endl;
        }
    }

    tempS.setReading(120);
    std::cout << tempS.getReading()<< "\n";
    std::cout << tempS.isOverHeated()<< "\n";

    std::cout << stateName(RadarState::Tracking) << "\n";





}

#include <iostream>
#include "Blinker.h"
#include "radarServo.h"

int main() {

    Blinker fast(150);

    RadarServo servo(13, 10);

    for (int t = 0; t < 2000; ++t) {
        bool fastOn = fast.update(t);
        std::cout << "T: " << t << " Wynik: " << fastOn << std::endl;

    }

    for (uint32_t t = 0; t < 4000; ++t) {
        uint8_t a = servo.update(t);
        if (t % 20 == 0) {
            std::cout << t << " ms -> " << (int)a << std::endl;
        }
    }



}
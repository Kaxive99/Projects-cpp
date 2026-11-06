#include <iostream>
#include "Blinker.h"

int main() {

    Blinker slow(500);
    Blinker fast(150);


    for (int t = 0; t < 2000; ++t) {
        bool fastOn = fast.update(t);
        std::cout << "T: " << t << " Wynik: " << fastOn << std::endl;

    }

}
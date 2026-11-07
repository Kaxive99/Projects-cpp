#include <iostream>
#include "Fan.h"
#include "Thermostat.h"


int main() {
    Fan fans(5);
    Thermostat thermostat(fans);

    float tablicaTemp [] {60, 90, 80, 72, 95, 115, 105, 98, 70};

    for (auto tablica_temp: tablicaTemp) {
       thermostat.update(tablica_temp);
        std::cout << tablica_temp << " --> " << nameThermoState(thermostat.getState()) << " | " <<std::endl;
    }


}
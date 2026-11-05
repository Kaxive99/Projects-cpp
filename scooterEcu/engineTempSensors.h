#pragma once
#include "engineProtection.h"

class engineTemp {
private:

public:
    unsigned int avgTemp;
    bool fansOn = false;
    bool serviceMode;
    engineProtection engine_protection;

    unsigned int tempSensor(unsigned int tempA, unsigned int tempB) {
        uint8_t tempDiff;
        if (tempA < tempB) {
            tempDiff = tempB - tempA;
        } else {tempDiff = tempA - tempB;}
        if (tempDiff >= 15) {
            std::cout << "[ECU] Czujniki nie działają poprawnie." << std::endl;
            return serviceMode = true;
        }
        avgTemp = (tempA + tempB) / 2;
        std::cout << "Średnia temperatura wynosi: " << avgTemp << " °C" << std::endl;
        return avgTemp;

    }

     bool criticalTempSensor() {
        if (avgTemp >= 125) {
            std::cout << "[ECU] Temperatura osiągneła krytyczny poziom: " << avgTemp << " °C." << std::endl;
            engine_protection.limpHomeMode(2000);
            return true;
        }
        return false;
    }

    void checkFans() {
        if (avgTemp > 95) {
            std::cout <<"[ECU] Włączenie wiatraków z powodu zbyt wysokiej temp. " << std::endl;
            fansOn = true;
        }
        if (fansOn == true && avgTemp < 85) {
            std::cout <<"[ECU] Wyłączenie wiatraków z powodu stabilizacji temp. " << std::endl;
            fansOn = false;
        }
    }
    };

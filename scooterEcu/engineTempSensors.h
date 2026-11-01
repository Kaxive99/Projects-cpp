#pragma once


class engineTemp {
private:

public:
    unsigned int avgTemp;
    bool fansOn = false;
    bool serviceMode = false;

    unsigned int tempSensor(unsigned int tempA, unsigned int tempB) {
        uint8_t tempDiff;
        if (tempA < tempB) {
            tempDiff = tempB - tempA;
        } else {tempDiff = tempA - tempB;}
        if (tempDiff >= 15) {
            std::cout << "[ECU] Czujniki nie działają poprawnie, udaj sie do serwisu w celu naprawienia usterki." << std::endl;
            serviceMode = true;
            return 0;
        }
        avgTemp = (tempA + tempB) / 2;
        std::cout << "Średnia temperatura wynosi: " << avgTemp << " °C" << std::endl;
        return avgTemp;

    }

     void criticalTempSensor() {
        if (avgTemp >= 120) {
            std::cout << "[ECU] Temperatura osiągneła krytyczny poziom: " << avgTemp << " °C zapłon zostaje wyłączony." << std::endl;
            serviceMode = true;
        }
    }

    void checkFans() {
        if (avgTemp > 95 && avgTemp < 119) {
            std::cout <<"[ECU] Włączenie wiatraków z powodu zbyt wysokiej temp. " << std::endl;
            fansOn = true;
        }
        if (fansOn == true && avgTemp < 85) {
            std::cout <<"[ECU] Wyłączenie wiatraków z powodu stabilizacji temp. " << std::endl;
            fansOn = false;
        }
    }
    };

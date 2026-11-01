#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <termios.h>
#include "engineProtection.h"
#include "engineTempSensors.h"
#include "throttlePositionSensor.h"




class monitor {
private:
    std::string ecuKey = "Eryczek123";

public:
    unsigned int ignition = 0;
    std::chrono::steady_clock::time_point startTime;

    void engineTimeStart() {
        startTime = std::chrono::steady_clock::now();
    }

    void engineTimeEnd() {
        std::chrono::steady_clock::time_point endTime;
        endTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsedSeconds = endTime - startTime;
        int seconds = (int)elapsedSeconds.count();
        if (seconds >= 60) {
            unsigned int minutes = seconds / 60;
            if (minutes == 1){
                std::cout << "Silnik pracował " << minutes << " minute" << std::endl;
            } else if  (minutes <= 4) {
                std::cout << "Silnik pracował " << minutes << " minuty" << std::endl;
            }
            else {
                std::cout << "Silnik pracował " << minutes << " minut" << std::endl;
        }
        } else if (seconds == 0) {
            std::cout << "Silnik pracował " << seconds << " sekund" << std::endl;
        }
        else if  (seconds <= 4) {
            std::cout << "Silnik pracował " << seconds << " sekundy" << std::endl;
        } else {
            std::cout << "Silnik pracował " << seconds << " sekund" << std::endl;
        }

    }

    void setIgnition(unsigned int state) {
        ignition = state;
        if (state == 1) {
        std::cout << "Zapłon włączony." << std::endl;
        } else {
        std::cout << "Zapłon wyłączony." << std::endl;
        }
    }
};


int main () {

    monitor ecuMonitor;
    engineProtection protection;
    engineTemp tempSensorClass;
    tps throttlePS;

    int tempUserA, tempUserB, tps;

    // Odpalenie zapłonu
    ecuMonitor.setIgnition(1);
    // Start liczenia czasu
    ecuMonitor.engineTimeStart();
    while (ecuMonitor.ignition == 1) {
        std::cout << "Podaj temp czujników: " << std::endl;
        std::cin >> tempUserA >> tempUserB;
        std::cout << "Podaj pozycje manetki w %: " << std::endl;
        std::cin >> tps;

        // Średnia temp
        tempSensorClass.tempSensor(tempUserA, tempUserB);
        // Awaryjne wyłączenie silnika
        if (tempSensorClass.serviceMode == 1) {
            ecuMonitor.setIgnition(0);
            break;
        }
        // Status silnika i maksymalne obroty
        protection.maxRPMforState(tempSensorClass.avgTemp);
        // Aktualne obroty liczone według procentu przekręcenia manetki
        throttlePS.rpmsToThrottle(tps, protection.maxRPM);
        // Wykrywanie krytycznej temperatury
        tempSensorClass.criticalTempSensor();
        // Awaryjne wyłączenie silnika
        if (tempSensorClass.serviceMode == 1) {
            ecuMonitor.setIgnition(0);
            break;
        }
        // Włączenie lub wyłączenie wiatraków
        tempSensorClass.checkFans();
        }
    // Koniec liczenia czasu
    ecuMonitor.engineTimeEnd();
}
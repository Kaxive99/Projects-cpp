#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <termios.h>
#include "engineProtection.h"


struct scooterEcu {
    unsigned int monitorA;
    unsigned int monitorB;
    unsigned int timeStamp = 0;

    bool monitorError = false;
};

class monitor {
private:
    std::string ecuKey = "Eryczek123";

public:
    unsigned int ignition = 0;
    unsigned int avgTemp = 0;
    bool fansOn = false;
    bool serviceMode = false;

    scooterEcu ecu;
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
    void tempSensor(unsigned int tempA, unsigned int tempB) {
        uint8_t tempDiff;
        if (tempA < tempB) {
            tempDiff = tempB - tempA;
        } else {tempDiff = tempA - tempB;}
        if (tempDiff >= 15) {
            std::cout << "[ECU] Czujniki nie działają poprawnie, udaj sie do serwisu w celu naprawienia usterki." << std::endl;
            serviceMode = true;
            setIgnition(0);
            return;
        }
        avgTemp = (tempA + tempB) / 2;
        std::cout << "Średnia temperatura wynosi: " << avgTemp << " °C" << std::endl;

    }

    void criticalTempSensor() {
        if (avgTemp >= 110) {
            std::cout << "[ECU] Temperatura osiągneła krytyczny poziom: " << avgTemp << " °C zapłon zostaje wyłączony." << std::endl;
            setIgnition(0);
            serviceMode = true;
        }
    }

    void checkFans() {
        if (avgTemp > 90 && avgTemp < 109) {
            std::cout <<"[ECU] Włączenie wiatraków z powodu zbyt wysokiej temp. " << std::endl;
            fansOn = true;
        }
        if (fansOn == true && avgTemp < 90) {
            std::cout <<"[ECU] Wyłączenie wiatraków z powodu stabilizacji temp. " << std::endl;
            fansOn = false;
        }
    }



};


int main () {
    monitor ecuMonitor;
    engineProtection protection;
    int tempUserA, tempUserB;
    // Testowe wywołanie

    ecuMonitor.setIgnition(1);
    ecuMonitor.engineTimeStart();
    while (ecuMonitor.ignition == 1) {
        std::cout << "Podaj testowe temp: " << std::endl;
        std::cin >> tempUserA >> tempUserB;
        ecuMonitor.tempSensor(tempUserA, tempUserB);
        if (ecuMonitor.serviceMode == true) {
            return 0;
        } else {
        protection.maxRPMforState(ecuMonitor.avgTemp);
        ecuMonitor.criticalTempSensor();
        ecuMonitor.checkFans();
        }
    }
    ecuMonitor.engineTimeEnd();
}
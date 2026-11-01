#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <termios.h>
#include "engineProtection.h"
#include "engineTempSensors.h"




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

    int tempUserA, tempUserB;

    ecuMonitor.setIgnition(1);
    ecuMonitor.engineTimeStart();
    while (ecuMonitor.ignition == 1) {
        std::cout << "Podaj testowe temp: " << std::endl;
        std::cin >> tempUserA >> tempUserB;

        tempSensorClass.tempSensor(tempUserA, tempUserB);
        if (tempSensorClass.serviceMode == 1) {
            ecuMonitor.setIgnition(0);
            break;
        }
        protection.maxRPMforState(tempSensorClass.avgTemp);

        tempSensorClass.criticalTempSensor();
        if (tempSensorClass.serviceMode == 1) {
            ecuMonitor.setIgnition(0);
            break;
        }
        tempSensorClass.checkFans();
        }
    ecuMonitor.engineTimeEnd();
}
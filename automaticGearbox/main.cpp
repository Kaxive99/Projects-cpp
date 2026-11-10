#include <iostream>
#include <cstdint>
#include <thread>
#include "gearsEcu.h"
using namespace std::chrono;
using namespace std;

int main() {
    GeraboxEcu ecu(10);




    // auto tickPeriod = milliseconds(100);
    // auto nextTick = std::chrono::steady_clock::now();
    // bool running = true;
    // while (running) {
    //     nextTick += tickPeriod;
    //     std::this_thread::sleep_until(nextTick);
    //     std::cout << "aaa \n    ";
    // }

}
#include <iostream>
#include <cstdint>
#include <thread>
using namespace std::chrono;

int main() {


    auto tickPeriod = milliseconds(100);
    auto nextTick = std::chrono::steady_clock::now();
    bool running = true;
    while (running) {
        nextTick += tickPeriod;
        std::this_thread::sleep_until(nextTick);
        std::cout << "aaa \n    ";
    }

}
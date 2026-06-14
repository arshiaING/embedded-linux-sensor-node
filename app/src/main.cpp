#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "FakeSensor.hpp"



int main()
{
    srand(time(nullptr)); // Seed the random number generator

    std::cout << "Starting sensor prototype..." << std::endl;

    for (int i = 0; i < 5; i++) {
        double temperature = readFakeTemperature();

        std::cout << "Temperature: " << temperature << " C" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Program finished." << std::endl;

    return 0;
}
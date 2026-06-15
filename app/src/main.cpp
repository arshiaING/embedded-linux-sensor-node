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
    std::cout << "Press Ctrl + C to stop the program." << std::endl; // Inform the user how to stop the program real sensor would run indefinitely, but for testing we will run it a few times and then exit with ctrl + c
    while (true) {
        double temperature = readFakeTemperature();

        std::cout << "Temperature: " << temperature << " C" << std::endl;
        

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Program finished." << std::endl;

    return 0;
}
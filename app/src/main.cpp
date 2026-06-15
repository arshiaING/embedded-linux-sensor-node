#include <chrono>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

#include "FakeSensor.hpp"

volatile std::sig_atomic_t running = 1;

void handleSignal(int signal)
{
    if (signal == SIGINT) {
        running = 0;
    }
}

int main()
{
    srand(time(nullptr));

    std::signal(SIGINT, handleSignal);

    std::cout << "Starting sensor prototype..." << std::endl;
    std::cout << "Press Ctrl + C to stop the program." << std::endl;

    while (running) {
        double temperature = readFakeTemperature();

        std::cout << "Temperature: "
                  << temperature
                  << " C"
                  << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\nStopping sensor prototype..." << std::endl;

    return 0;
}
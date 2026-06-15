#include <chrono>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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

int main(int argc, char* argv[])
{
    int readingIntervalSeconds = 1;

    if (argc > 1) {
        readingIntervalSeconds = std::atoi(argv[1]);
    }

    if (readingIntervalSeconds <= 0) {
        std::cout << "Invalid interval. Using 1 second." << std::endl;
        readingIntervalSeconds = 1;
    }

    srand(time(nullptr));

    std::signal(SIGINT, handleSignal);

    std::cout << "Starting sensor prototype..." << std::endl;
    std::cout << "Reading interval: "
              << readingIntervalSeconds
              << " second(s)"
              << std::endl;

    std::cout << "Press Ctrl + C to stop the program." << std::endl;

    while (running) {
        double temperature = readFakeTemperature();

        std::cout << std::fixed
                  << std::setprecision(2)
                  << "Temperature: "
                  << temperature
                  << " C"
                  << std::endl;

        std::this_thread::sleep_for(
            std::chrono::seconds(readingIntervalSeconds)
        );
    }

    std::cout << "\nStopping sensor prototype..." << std::endl;

    return 0;
}
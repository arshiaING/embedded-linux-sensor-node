#include "CsvLogger.hpp"
#include "FakeSensor.hpp"
#include "TimeUtils.hpp"

#include <chrono>
#include <csignal>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

volatile std::sig_atomic_t running = 1;

// This function runs when the user presses Ctrl+C.
void handleSignal(int signal)
{
    if (signal == SIGINT) {
        running = 0;
    }
}

int main(int argc, char* argv[])
{
    // Default reading interval
    int intervalSeconds = 1;

    // Read interval from command-line argument
    if (argc > 1) {
        intervalSeconds = std::atoi(argv[1]);

        if (intervalSeconds <= 0) {
            std::cerr
                << "Invalid interval. Using default value of 1 second."
                << std::endl;

            intervalSeconds = 1;
        }
    }

    // Connect Ctrl+C to the signal handler
    std::signal(SIGINT, handleSignal);

    const std::string csvFileName = "temperature_readings.csv";
    std::ofstream csvFile;

    if (!openCsvFile(csvFile, csvFileName)) {
        std::cerr
            << "Could not open "
            << csvFileName
            << " for writing."
            << std::endl;

        return 1;
    }

    std::cout
        << "Sensor daemon started. Press Ctrl+C to stop."
        << std::endl;

    std::cout
        << "Saving readings to "
        << csvFileName
        << std::endl;

    while (running) {
        double temperature = readFakeTemperature();

        // Use the same timestamp in the terminal and CSV file
        std::string timestamp = getCurrentTimestamp();

        std::cout
            << timestamp
            << " - Temperature: "
            << std::fixed
            << std::setprecision(2)
            << temperature
            << " C"
            << std::endl;

        if (!writeCsvReading(csvFile, timestamp, temperature)) {
            std::cerr
                << "Could not write to "
                << csvFileName
                << ". Stopping program."
                << std::endl;

            csvFile.close();

            return 1;
        }

        std::this_thread::sleep_for(
            std::chrono::seconds(intervalSeconds)
        );
    }

    csvFile.close();

    std::cout
        << "\nStopping sensor daemon..."
        << std::endl;

    return 0;
}

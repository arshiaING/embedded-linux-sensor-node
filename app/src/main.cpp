#include "FakeSensor.hpp"

#include <chrono>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

// Flag to control the main loop, set to 0 when SIGINT is received
volatile std::sig_atomic_t running = 1;

// Signal handler for SIGINT (Ctrl+C)
void handleSignal(int signal)
{
    if (signal == SIGINT) {
        running = 0;
    }
}

// Function to get the current timestamp as a string
std::string getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();

    std::time_t currentTime =
        std::chrono::system_clock::to_time_t(now);

    std::tm* localTime = std::localtime(&currentTime);

    std::ostringstream timestamp;

    timestamp << std::put_time(
        localTime,
        "%Y-%m-%d %H:%M:%S"
    );

    return timestamp.str();
}

int main(int argc, char* argv[])
{
    // Default reading interval is 1 second
    int intervalSeconds = 1;

    // Read the interval from the command-line argument if it is provided
    if (argc > 1) {
        intervalSeconds = std::atoi(argv[1]);

        // Use the default interval if the value is invalid
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

    // Check if the CSV file is new or empty
    std::ifstream existingFile(
        csvFileName,
        std::ios::binary | std::ios::ate
    );

    bool writeHeader =
        !existingFile.is_open() || existingFile.tellg() == 0;

    existingFile.close();

    // Open the CSV file and add new readings at the end
    std::ofstream csvFile(csvFileName, std::ios::app);

    if (!csvFile.is_open()) {
        std::cerr
            << "Could not open "
            << csvFileName
            << " for writing."
            << std::endl;

        return 1;
    }

    // Write the CSV header only once
    if (writeHeader) {
        csvFile << "timestamp,temperature" << std::endl;
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

        // Use the same timestamp for the terminal and the CSV file
        std::string timestamp = getCurrentTimestamp();

        std::cout
            << timestamp
            << " - Temperature: "
            << std::fixed
            << std::setprecision(2)
            << temperature
            << " C"
            << std::endl;

        csvFile
            << timestamp
            << ","
            << std::fixed
            << std::setprecision(2)
            << temperature
            << std::endl;

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

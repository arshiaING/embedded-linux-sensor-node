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
    // default interval 
    int intervalSeconds = 1;

  
    if (argc > 1) {
        intervalSeconds = std::atoi(argv[1]);

        
        if (intervalSeconds <= 0) {
            std::cerr
                << "Invalid interval. Using default value of 1 second."
                << std::endl;

            intervalSeconds = 1;
        }
    }

    // Connects Ctrl+C to the handleSignal function.
    std::signal(SIGINT, handleSignal);

    const std::string csvFileName = "temperature_readings.csv";

    // Check if the file already exists and if it is empty.
    // This is used so the CSV header is not written many times.
    std::ifstream existingFile(
        csvFileName,
        std::ios::binary | std::ios::ate
    );

    bool writeHeader =
        !existingFile.is_open() || existingFile.tellg() == 0;

    existingFile.close();

    // std::ios::app means new readings are added at the end of the file.
    std::ofstream csvFile(csvFileName, std::ios::app);

    if (!csvFile.is_open()) {
        std::cerr
            << "Could not open "
            << csvFileName
            << " for writing."
            << std::endl;

        return 1;
    }

    // The header is only written if the file is new or empty.
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

        // Make the timestamp once, so the terminal and CSV file
        // get exactly the same time value.
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

#include <iostream>
#include <thread>
#include <chrono>

double readFakeTemperature()
{
    double base = 20.0;
    return base + (rand() % 1000) / 100.0; // Simulate a temperature reading between 20.0 and 30.0 degrees Celsius

}

int main()
{
    std::cout << "Starting sensor prototype..." << std::endl;

    for (int i = 0; i < 5; i++) {
        double temperature = readFakeTemperature();

        std::cout << "Temperature: " << temperature << " C" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Program finished." << std::endl;

    return 0;
}
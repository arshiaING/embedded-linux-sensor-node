#include <cstdlib>

#include "FakeSensor.hpp"

double readFakeTemperature() // Simulate reading a temperature value from a sensor
{
    static double currentTemperature =
        10.0 + (rand() % 1001) / 100.0; // Initial temperature between 10.00 and 20.00 degrees Celsius

    double change = ((rand() % 41) - 20) / 100.0; // Random change between -0.20 and +0.20 degrees Celsius

    currentTemperature = currentTemperature + change; // Update the current temperature with the random change 

    return currentTemperature;
}
#include "FakeSensor.hpp"
#include <cstdlib>

double readFakeTemperature()
{
    // Simulate reading a temperature value from a sensor this is base on norwegian weather data in the summer months, which typically ranges from 10.0 to 20.0 degrees Celsius.
    
    double base = 10.0; // Base temperature
    double randomPart = (rand() % 1000) / 100.0; // Simulate a random value between 0.0 and 10.0
    return base + randomPart; // Simulate a temperature reading between 10.0 and 20.0 degrees Celsius

}
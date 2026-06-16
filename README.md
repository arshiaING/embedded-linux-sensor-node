# Embedded Linux Sensor Node

This is a student project where I am learning embedded Linux, C++, Yocto and sensor communication.

The final goal is to build a custom Linux image for a Raspberry Pi 5 and run a C++ program that reads data from an I2C sensor.

## Current stage

My Raspberry Pi is used for another project, so I am starting with a simple C++ prototype on my Mac.

The first version uses a fake temperature function that returns a temperature between 20 and 30 degrees.

This lets me practice:

- Basic C++
- CMake
- Git and GitHub
- Project documentation

The fake sensor will later be replaced with a real I2C sensor.

## Choose the reading interval

The program can take the reading interval as a command-line argument.

For example, this reads the sensor every three seconds:

```bash
./build/sensor-daemon 3
```

## Build the program

```bash
cmake -S . -B build
cmake --build build
```

Run the program:

```bash
./build/sensor-daemon
```

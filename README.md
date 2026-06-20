# Embedded Linux Sensor Node

This is a student project where I am learning embedded Linux, C++, Yocto and sensor communication.

The final goal is to build a custom Linux image for a Raspberry Pi 5 and run a C++ program that reads data from an I2C sensor.

## Current stage

My Raspberry Pi is used for another project, so I am starting with a simple C++ prototype on my Mac.

The current version uses a fake temperature sensor. It starts with a value between 10 and 20 degrees and then changes slowly for each reading.

I have also started preparing the hardware so I can later collect real sensor data.

This lets me practice:

- Basic C++
- CMake
- Git and GitHub
- Project documentation
- Simple file handling

The fake sensor will later be replaced with a real I2C sensor.

The program now prints each reading with a timestamp and also saves the readings to a CSV file.

The CSV file is called:

```text
temperature_readings.csv
```

If the file cannot be opened or written to, the program prints an error message and stops.

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

Example output:

```text
2026-06-20 12:30:01 - Temperature: 17.42 C
```

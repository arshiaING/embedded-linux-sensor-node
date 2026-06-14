cat > README.md <<'EOF'
# Embedded Linux Sensor Node

This is a student project where I am learning embedded Linux, C++, Yocto and sensor communication.

The final goal is to build a custom Linux image for a Raspberry Pi 5 and run a C++ program that reads data from an I2C sensor.

## Current stage

my Raspberry Pi is used for another project, so I am starting with a simple C++ prototype on my Mac.

The first version uses a fake temperature function that will retrun a tempeture between 20 and 30 degrees.

This lets me practice:

- Basic C++
- CMake
- Git and GitHub
- Project documentation

The fake sensor will later be replaced with a real I2C sensor.

## Build the program

```bash
cmake -S . -B build
cmake --build build
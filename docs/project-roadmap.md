# Project Roadmap

## What this plan is for

This plan shows how to build the Embedded Linux Sensor Node project from start to finish.


## Status

- [x] Completed
- [ ] Planned
- [~] In progress

---

## Phase 1 – First C++ version on Mac

### Goal

Make a simple C++ program that works without Raspberry Pi hardware.

### Tasks

- [x] Create the project folder
- [x] Create `README.md`
- [x] Create `CMakeLists.txt`
- [x] Create `main.cpp`
- [x] Generate a fake temperature
- [x] Build the program with CMake
- [x] Run the program in Terminal
- [x] Create the first Git commit


---

## Phase 2 – Improve FakeSensor

### Goal

Make the fake temperature behave more like a real sensor.

### Tasks

- [x] Check that the starting temperature is between 10 and 20 °C
- [x] Check that the temperature remembers the previous value
- [x] Check that it changes gradually
- [x] Move the FakeSensor code into separate files
- [x] Check that the program runs continuously
- [x] Check that Ctrl+C stops the program correctly
- [x] Add a configurable reading interval

---

## Phase 3 – Save and organize readings

### Goal

Make the output easier to understand and save the measurements.

### Tasks

- [x] Add timestamps
- [x] Save readings to a CSV file
- [ ] Handle simple file errors
- [ ] Improve terminal messages
- [ ] Add a simple config file



---

## Phase 4 – Better code structure and tests

### Goal

Prepare the program for both fake and real sensors.

### Tasks

- [ ] Create an `ISensor` interface
- [ ] Make `FakeSensor` use `ISensor`
- [ ] Add basic validation of temperature values
- [ ] Add GoogleTest
- [ ] Add program version information
- [ ] Add GitHub Actions
- [ ] Add sanitizer checks



---

## Phase 5 – Raspberry Pi and real sensor

### Goal

Move the project from the Mac to a Raspberry Pi and use a real I2C sensor.

### Tasks

- [ ] Install Raspberry Pi OS
- [ ] Enable I2C
- [ ] Connect AHT21 or BMP280
- [ ] Check the sensor with `i2cdetect`
- [ ] Create `I2CSensor`
- [ ] Read data from `/dev/i2c-1`
- [ ] Convert raw data into temperature
- [ ] Choose fake or real sensor from config

---

## Phase 6 – Linux service and monitoring

### Goal

Make the program run automatically and send data to the monitoring system.

### Tasks

- [ ] Create a `systemd` service
- [ ] Start the program automatically at boot
- [ ] Restart it if it crashes
- [ ] Send logs to `journald`
- [ ] Publish readings to MQTT
- [ ] Store the data in InfluxDB
- [ ] Show the data in Grafana



---

## Phase 7 – Yocto image

### Goal

Build my own embedded Linux image for the Raspberry Pi.

### Tasks

- [ ] Set up Yocto
- [ ] Add the Raspberry Pi layer
- [ ] Create `meta-sensor-node`
- [ ] Create a BitBake recipe
- [ ] Install the daemon, service and config
- [ ] Build the image
- [ ] Boot the Raspberry Pi with the image



---

## Phase 8 – Mender OTA

### Goal

Update the device through the network without manually flashing the SD card again.

### Tasks

- [ ] Add Mender to the Yocto image
- [ ] Build version 1.0.0
- [ ] Build version 1.1.0
- [ ] Send the update with Mender
- [ ] Check that the new version runs
- [ ] Document the update
- [ ] Test rollback if I have enough time


---

## Phase 9 – Final documentation

### Goal

Make the project easy for other people to understand.

### Tasks

- [ ] Finish the main README
- [x] Add the architecture diagram
- [x] Explain the architecture and data flow
- [x] Add this project roadmap
- [ ] Add wiring documentation
- [ ] Add build and test instructions
- [ ] Add screenshots from Grafana
- [ ] Add screenshots from Mender
- [ ] Measure CPU and memory usage
- [ ] Record a short demo video
- [ ] Write a final reflection

---



This roadmap can change during the project if I find a better or simpler way to solve something.

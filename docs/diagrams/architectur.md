# System Architecture

> This diagram shows how I plan to build the final system. Right now I only have the C++ prototype and the FakeSensor. The other parts will be added step by step.



## Main idea

I divided the system into three main parts:

- Hardware
- Raspberry Pi / Yocto Linux
- External services

I did this because it makes the system easier to understand. It also shows clearly where the data starts, how it is processed and where it ends up.

The data flow is:

```text
I2C Sensor
    ↓
Linux I2C Interface
    ↓
C++ Sensor Daemon
    ↓
MQTT Broker
    ↓
InfluxDB
    ↓
Grafana
```

The support parts are placed next to the main flow. They help control the program.

## How the data moves through the system

The sensor, BMP280, measures temperature from the environment.

It communicates with the Raspberry Pi through I2C. The main I2C connections are:

```text
SDA  = data
SCL  = clock
3.3V = power
GND  = ground
```

Linux makes the I2C bus available through:

```text
/dev/i2c-1
```

The `I2CSensor` class will later use this device file to communicate with the real sensor.

The sensor normally sends raw data, not a ready temperature value. The C++ code must therefore read the raw bytes and convert them into a temperature.

After that, the Sensor Daemon checks that the value looks valid before it is used.

A valid reading can be:

- printed or logged
- saved locally
- published to MQTT as JSON

Example:

```json
{
  "temperature": 21.42,
  "timestamp": "2026-06-16T14:30:01Z",
  "version": "1.0.0"
}
```

The MQTT Broker receives the message and sends it further to the monitoring system.

InfluxDB stores the measurements over time, and Grafana shows the data in graphs and dashboards.

The full flow is:

```text
Physical temperature
        ↓
I2C sensor
        ↓
Linux /dev/i2c-1
        ↓
C++ Sensor Daemon
        ↓
MQTT message
        ↓
InfluxDB
        ↓
Grafana
```

## Sensor interface

The project will later use a common interface called `ISensor`.

Both `FakeSensor` and `I2CSensor` will use the same interface:

```text
             ISensor
             ▲     ▲
             │     │
    FakeSensor     I2CSensor
```

The reason for this is that the main program should not need to know how the temperature was created.

It should only ask the active sensor for a reading:

```cpp
double temperature = sensor->readTemperature();
```



!! Imortant if the real sensor fails, the program should show an error instead of silently creating fake data.

## C++ Sensor Daemon

The Sensor Daemon is the main program in the system.

Its job will be to:

```text
Read configuration
Select the sensor
Open the sensor
Read temperature
Check the value
Write logs
Publish data to MQTT
Wait
Repeat
```

The daemon is the part that connects the physical sensor to the external services.

## Configuration

The program will later use a configuration file.

Example:

```ini
[general]
reading_interval = 2
sensor_mode = fake

[sensor]
i2c_device = /dev/i2c-1
i2c_address = 0x38

[mqtt]
enabled = true
broker = localhost
port = 1883
topic = sensors/embedded-linux/temperature
```

This file can control:

- reading interval
- fake or real sensor
- I2C device
- I2C address
- MQTT broker
- MQTT topic

The main reason for using a config file is that settings can be changed without editing and rebuilding the C++ code.

## systemd and logging

On the Raspberry Pi, `systemd` will start the daemon automatically when the device boots.

It can also restart the daemon if it crashes.

```text
systemd
    ↓ starts / restarts
Sensor Daemon
```

The daemon will later send logs to `journald`.

Example log messages:

```text
Sensor daemon started
Using I2CSensor on /dev/i2c-1
Temperature reading: 21.42 C
Failed to read sensor
Sensor daemon stopped
```

The logs can be viewed with:

```bash
journalctl -u sensor-daemon
```

## External services

The external services have different jobs:

```text
MQTT Broker → receives and forwards messages
InfluxDB    → stores measurements
Grafana     → shows graphs and dashboards
Mender      → updates the Yocto image
```

The daemon does not send data directly to Grafana.

MQTT is used to move the data, InfluxDB stores it, and Grafana displays it.

I chose this structure because each part then has one clear job.

## Mender OTA

Mender will later be used to update the complete Yocto image over the network.

The planned flow is:

```text
Build a new Yocto image
        ↓
Send the update with Mender
        ↓
Install it on the other partition
        ↓
Restart the device
        ↓
Check the new version
```

The A/B setup means that the device has two system partitions.

If the new version does not work, the system can go back to the previous working version.

Mender therefore updates the complete system image, not only the C++ program.

#
cmake_minimum_required(VERSION 3.16)

project(embedded_linux_sensor_node LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sensor-daemon
    app/src/main.cpp
    app/src/FakeSensor.cpp
)

target_include_directories(sensor-daemon PRIVATE
    app/include
)
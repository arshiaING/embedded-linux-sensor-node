# Learning Log

## Random temperature values

The first fake sensor always returned the same temperature.

I changed the function so that it now returns a random temperature between approximately 10 and 20 degrees.

I used `srand()` with the current time so that the program does not produce the same sequence every time it starts.




## Separating the fake sensor code

The first version of the project had all the code inside main.cpp.

I moved the fake temperature function into separate files:

- FakeSensor.hpp contains the function declaration.
- FakeSensor.cpp contains the function implementation.
- main.cpp controls the main program.

This made main.cpp easier to read.

I also updated CMakeLists.txt so that CMake compiles both C++ source files and can find the header file inside app/include.


## Continuous sensor loop

The first version only read the temperature five times.

I changed the for loop to a while loop so that the program continues reading the fake sensor until I stop it with Ctrl + C.

This makes the program behave more like a sensor daemon because it can run continuously.

The program still uses one thread, so sleep_for pauses the whole program for one second between each reading.

## Graceful shutdown

The program previously used an endless while loop and stopped immediately when I pressed Ctrl + C.

I added simple signal handling for SIGINT.

When Ctrl + C is pressed, the signal handler changes a running variable from 1 to 0. The while loop then stops, and the program prints a shutdown message before exiting.

This gives the program a cleaner shutdown and will be useful later when the program needs to close hardware resources.

 ## Reading interval and output formatting

I moved the reading interval into a named constant instead of writing the number directly inside sleep_for.

This makes the code easier to understand and makes the interval easier to change later.

I also used iomanip to display the temperature with two decimal places.
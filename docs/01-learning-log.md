## Random temperature values

The first fake sensor always returned the same temperature.

I changed the function so that it now returns a random temperature between approximately 10 and 20 degrees.

I used `srand()` with the current time so that the program does not produce the same sequence every time it starts.



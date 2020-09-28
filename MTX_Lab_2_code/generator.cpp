/* This file contains the functions used by the Arduino to generate sine waves
using the R2R ladder DAC connected to pins 0-7

19.08.20
C Jones
*/

#include <Arduino.h>
#include "generator.h"

void init_generator(void)
{
    DDRD = B11111111; // Port D at Arduino Uno (pin 0-7), set as outputs
}

void generate_sine_wave(float frequency, uint32_t currentTime, 
                                        uint8_t lookup_table[])
{
    static uint32_t phase;        // phase of the wave (one wave is 100 steps)
    static uint32_t previousTime; // variable to store prev time

    /* Calculates the delay (us) between each point to reach desired frequency  
     the factor of 100 is beacause the lookup table has 100 points */
    static const uint32_t TIME_DELAY = lroundf(1000000 / (50 * frequency*1.1));

    // check if it's time to output next number from table
    if (currentTime - previousTime >= TIME_DELAY)
    {
        // write the output to the DAC pins
        PORTD = lookup_table[phase % 50];
        previousTime = currentTime; // update prev time variable
        phase++;                    // increment phase
    }
}

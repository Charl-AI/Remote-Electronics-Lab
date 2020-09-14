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

void generate_sine_wave(float frequency, uint32_t currentTime)
{
    static uint32_t phase;        // phase of the wave (one wave is 100 steps)
    static uint32_t previousTime; // variable to store prev time

    /* Calculates the delay (us) between each point to reach desired frequency  
     the factor of 100 is beacause the lookup table has 100 points */
    static const uint32_t TIME_DELAY = lroundf(1000000 / (100 * frequency*1.1));

    #ifdef EXERCISE_1 
    /*  Here we have a lookup table to generate a single sine wave from 100 
    points, ranging from 0 to 255 */
    static const uint8_t SINE_LOOKUP_TABLE[] =
    {
        128, 136, 143, 151, 159, 167, 174, 182,
        189, 196, 202, 209, 215, 220, 226, 231,
        235, 239, 243, 246, 249, 251, 253, 254,
        255, 255, 255, 254, 253, 251, 249, 246,
        243, 239, 235, 231, 226, 220, 215, 209,
        202, 196, 189, 182, 174, 167, 159, 151,
        143, 136, 128, 119, 112, 104, 96, 88,
        81, 73, 66, 59, 53, 46, 40, 35,
        29, 24, 20, 16, 12, 9, 6, 4,
        2, 1, 0, 0, 0, 1, 2, 4,
        6, 9, 12, 16, 20, 24, 29, 35,
        40, 46, 53, 59, 66, 73, 81, 88,
        96, 104, 112, 119, 128
    };
    #endif
    #ifndef EXERCISE_1
    #ifdef EXERCISE_2

    static const uint8_t SINE_LOOKUP_TABLE[] =
    {
        64,68,72,76,80,84,88,91,
        95,98,102,105,108,111,113,116,
        118,120,122,124,125,126,127,127,
        128,128,128,127,127,126,125,124,
        122,120,118,116,113,111,108,105,
        102,98,95,91,88,84,80,76,
        72,68,64,60,56,52,48,44,
        40,37,33,30,26,23,20,17,
        15,12,10,8,6,4,3,2,
        1,1,0,0,0,1,1,2,
        3,4,6,8,10,12,15,17,
        20,23,26,30,33,37,40,44,
        48,52,56,60,64,
    };
    #endif
    #endif

    // check if it's time to output next number from table
    if (currentTime - previousTime >= TIME_DELAY)
    {
        // write the output to the DAC pins
        PORTD = SINE_LOOKUP_TABLE[phase % 100];
        previousTime = currentTime; // update prev time variable
        phase++;                    // increment phase
    }
}
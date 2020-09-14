/*
This code can be uploaded to the Arduino as part of MTX Lab 2: Analogue Filters.

The purpose of this code is to allow the Arduino to act as both a function 
generator and an oscilloscope. We use an 8-bit R2R ladder as a DAC to create a 
sine wave and then measure it before and after it is filtered using the
analogue inputs. The Arduino IDE serial plotter acts as a scope to visualise the
signal.

13.08.20
C Jones
 */

/******************************************************************************/
// Import statements and boilerplate code
#include <Arduino.h>
#include "scope.h"
#include "generator.h"
/******************************************************************************/
// These variables are for the student to change

/* Changes which code is compiled depending on the exercise being completed.
When moving onto the next exercise, comment out the previous one and
uncomment the next one*/
//#define EXERCISE_1
#define EXERCISE_2
//#define EXERCISE_3

/* Frequency of sine wave generated. Vary me between 5-200 Hz in lab 1 & 2 
This does nothing in lab 3*/
const float SINE_WAVE_FREQUENCY = 5; // (Hz)
/******************************************************************************/
// Setup function, runs when device is started
void setup()
{
  init_generator(); // intialises function generator
  init_scope(); // initialises scope
}
/******************************************************************************/
// Main loop, runs forever
void loop()
{
  uint32_t currentTime = micros(); // reads current time in microseconds

  #ifdef EXERCISE_1 
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

  #elif defined(EXERCISE_2)
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
    48,52,56,60,64
  };
  #endif

  #ifndef EXERCISE_3
  generate_sine_wave(SINE_WAVE_FREQUENCY, currentTime, SINE_LOOKUP_TABLE);
  oscilloscope(currentTime);
  #else
  #error not written exercise 3 yet
  #endif
}
/******************************************************************************/
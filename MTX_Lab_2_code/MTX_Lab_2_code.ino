/*
This code can be uploaded to the Arduino as part of MTX Lab 2: Analogue Filters.

The purpose of this code is to allow the Arduino to act as both a function 
generator and an oscilloscope. We use an 8-bit R2R ladder as a DAC to create a 
sine wave and vary the frequency whilst measuring the peak to peak voltage
by using the Serial Plotter as a scope.

13.08.20
C Jones
 */

/******************************************************************************/
// Import statements
#include <Arduino.h>
#include "scope.h"
#include "generator.h"
/******************************************************************************/
// These variables are for the student to change

/* Changes which code is compiled depending on the exercise being completed.
Once you get to exercise 3, uncomment the line below by removing the two
forward slashes*/

//#define EXERCISE_3

/* Frequency of sine wave generated. Vary me between 2-250 Hz in exercise 
1 & 2. This does nothing in exercise 3*/
const float SINE_WAVE_FREQUENCY = 250; // (Hz)
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

  #ifndef EXERCISE_3
    static const uint8_t SINE_LOOKUP_TABLE[] =
  {
    128,143,159,174,189,202,215,226,235,243,
    249,253,255,255,253,249,243,235,226,215,
    202,189,174,159,143,128,112,96,81,66,
    53,40,29,20,12,6,2,0,0,2,
    6,12,20,29,40,53,66,81,96,112,
  };
    static const uint8_t TABLE_SIZE = 50;
  #else
  static const uint8_t SINE_LOOKUP_TABLE[] =
  {
   127, 132, 138, 146, 158, 170, 180, 183, 184, 192,
        91, 196,  90, 211,  95, 144, 187, 144, 179,  93,
        90,  98, 167, 117,  89, 101, 197, 107,  92,  92,
       195,  93, 141,  91, 200, 198,  91, 193, 142,  98,
        91,  92,  94,  97, 100, 101, 101, 101, 102, 100,
       100, 101, 103, 104, 106, 107, 107, 109, 110, 111,
       112, 113, 113, 115, 116, 117, 118, 118, 119, 120,
       120, 122, 122, 122, 123, 124, 125, 125, 125, 126,
       126, 126, 127, 128, 129, 130, 130, 131, 131, 131,
       132, 132, 133, 133, 134, 134, 135, 135, 135, 136
  };
  static const uint8_t TABLE_SIZE = 100;
  static const float SINE_WAVE_FREQUENCY = 15; // (Hz)
  #endif

  generate_sine_wave(SINE_WAVE_FREQUENCY, currentTime, SINE_LOOKUP_TABLE, TABLE_SIZE);
  oscilloscope(currentTime);
}
/******************************************************************************/

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

#define EXERCISE_3

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
    116, 139, 129, 119, 141, 164, 153, 143, 164, 187,
    175, 164, 184, 206, 193, 181, 200, 221, 206, 193,
    211, 230, 214, 199, 216, 233, 216, 199, 214, 230,
    211, 193, 206, 221, 200, 181, 193, 206, 184, 164,
    175, 187, 164, 143, 153, 164, 141, 119, 129, 139,
    116,  94, 103, 114,  91,  69,  79,  90,  68,  46,
    57,  69,  48,  27,  39,  52,  32,  12,  26,  40,
    21,   3,  18,  34,  16,   0,  16,  34,  18,   3,
    21,  40,  26,  12,  32,  52,  39,  27,  48,  69,
    57,  46,  68,  90,  79,  69,  91, 114, 103,  94
  };
  static const uint8_t TABLE_SIZE = 100;
  static const float SINE_WAVE_FREQUENCY = 10; // (Hz)
  #endif

  generate_sine_wave(SINE_WAVE_FREQUENCY, currentTime, SINE_LOOKUP_TABLE, TABLE_SIZE);
  oscilloscope(currentTime);
}
/******************************************************************************/

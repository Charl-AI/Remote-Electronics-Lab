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
Once you get to exercise 3, comment out the first line and uncomment the
the 'EXERCISE_3' line*/
#define EXERCISE_1_AND_2
//#define EXERCISE_3

/* Frequency of sine wave generated. Vary me between 2-200 Hz in exercise 
1 & 2. This does nothing in lab 3*/
const float SINE_WAVE_FREQUENCY = 20; // (Hz)
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

  #ifdef EXERCISE_1_AND_2
  static const uint8_t SINE_LOOKUP_TABLE[] =
  {
    128,143,159,174,189,202,215,226,235,243,
    249,253,255,255,253,249,243,235,226,215,
    202,189,174,159,143,128,112,96,81,66,
    53,40,29,20,12,6,2,0,0,2,
    6,12,20,29,40,53,66,81,96,112,
  };

  #elif defined(EXERCISE_3)
  static const uint8_t SINE_LOOKUP_TABLE[] =
  {
    120, 120, 120, 120, 126, 144, 150, 150, 150, 138,
    138, 138, 126, 126, 138, 144, 150, 156, 156, 162,
    162, 150, 138, 132, 126, 120, 126, 132, 144, 162,
    162, 156, 144, 126, 126, 120, 126, 126, 138, 144,
    156, 156, 156, 156, 150, 150, 138, 132, 138, 144,
    150, 144, 144, 138, 138, 144, 144, 144, 144, 138,
    132, 132, 132, 138, 156, 162, 162, 174, 168, 162,
    156, 156, 162, 162, 156, 150, 156, 150, 132, 120,
    102,  78,  66,  54,  48,  54,  66,  72,  78,  84,
    96, 102, 114, 132, 144, 144, 144, 156, 168, 174
  };
  static const float SINE_WAVE_FREQUENCY = 8; // (Hz)
  #else
  #error I am an automated error message Beep Boop. If you see me it means you have done something naughty
  #error Please select an exercise by uncommenting either exercise 1 or 3. Thanks :)
  #endif

  generate_sine_wave(SINE_WAVE_FREQUENCY, currentTime, SINE_LOOKUP_TABLE);
  oscilloscope(currentTime);
}
/******************************************************************************/

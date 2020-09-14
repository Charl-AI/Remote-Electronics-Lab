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
#define EXERCISE_1
/******************************************************************************/
// Import statements and boilerplate code
#include <Arduino.h>
#include "scope.h"
#include "generator.h"
/******************************************************************************/
// These variables are for the student to change

/* Changes which code is compiled depending on the exercise being completed
When moving onto the next exercise, comment out the previous one and
uncomment the next one*/

//#define EXERCISE_2
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

  generate_sine_wave(SINE_WAVE_FREQUENCY, currentTime);
  oscilloscope(currentTime);
}
/******************************************************************************/
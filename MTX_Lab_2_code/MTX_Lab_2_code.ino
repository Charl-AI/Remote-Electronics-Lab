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
// Define global variables

/* These variables control the frequency of the sine wave generated and the
sampling frequency of the scope. The generator frequency is accurate to 10% of
the specified value up to 50 Hz.The sampling frequency is 2.5x generator
frequency to avoid aliasing*/

// vary me between
const uint16_t SINE_WAVE_FREQUENCY = 50; // (Hz)

// Do not change
const uint16_t SCOPE_SAMPLING_FREQUENCY = roundf(2.5 * SINE_WAVE_FREQUENCY); // (Hz)
/******************************************************************************/
// Setup function, runs when device is started
void setup()
{
  init_generator();
  init_scope();
}
/******************************************************************************/
// Main loop, runs forever
void loop()
{
  generate_sine_wave(SINE_WAVE_FREQUENCY);
  oscilloscope(SCOPE_SAMPLING_FREQUENCY);
}
/******************************************************************************/
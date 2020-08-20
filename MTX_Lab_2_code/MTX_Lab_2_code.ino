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
sampling frequency of the scope. It is recommended to leave the scope frequency
unchanged (at 500). Do not increase the sine wave freqency over 250*/
const uint16_t SINE_WAVE_FREQENCY = 10 // (Hz)
const uint16_t SCOPE_SAMPLING_FREQUENCY = 500 // (Hz)
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
  generate_sine_wave(SINE_WAVE_FREQENCY);
  oscilloscope(SCOPE_SAMPLING_FREQUENCY);

}
/******************************************************************************/
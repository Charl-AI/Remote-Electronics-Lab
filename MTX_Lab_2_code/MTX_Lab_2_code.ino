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

// Give analog pins meaningful names
#define rawPin A0      // raw data collected from A0
#define filteredPin A1 // filtered data collected from A1

// initialise sampling interval and previous sampling time
const int sampling_interval = 1; // 1  milisecond sampling rate (1000 Hz)
unsigned long previoustime = 0;
/******************************************************************************/
// Setup function, runs when device is started
void setup()
{

  // set up serial port to send data to PC
  Serial.begin(115200);
}
/******************************************************************************/
// Main loop, runs forever
void loop()
{

  // check to see if its time to take another sample
  unsigned long currentTime = millis();
  if (currentTime - previoustime >= sampling_interval)
  {

    previoustime = currentTime; // save time of sample

    int raw = analogRead(rawPin);
    int filtered = analogRead(filteredPin);
  }
}
/******************************************************************************/
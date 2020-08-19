/* This file contains the functions used by the Arduino to generate sine waves
using the R2R ladder DAC connected to pins 0-7

19.08.20
C Jones
*/

#include <Arduino.h>
#include "generator.h"

void init_generator(void){
 DDRD = B11111111;  // Port D at Arduino Uno (pin 0-7), set as outputs
}
/* This file contains the functions used by the Arduino to act as a scope, using
pins A0 and A1

20.08.20
C Jones
*/

#include <Arduino.h>
#include "scope.h"

void init_scope(void)
{
    Serial.begin(2000000);
}

void oscilloscope(uint16_t sampling_freq, uint32_t currentTime)
{
    static uint32_t previousTime;

    static const uint32_t time_delay = roundf(1000000 / (2 * sampling_freq));

    static uint16_t rawArray[250];
    static uint16_t filteredArray[250];
    static uint8_t sampleNumber;

    if ((currentTime - previousTime >= time_delay) && (sampleNumber < 250))
    {
        static int pin;
        if (pin == 0)
        {
            rawArray[sampleNumber] = analogRead(rawPin);
            pin = 1;
        }
        else
        {
            filteredArray[sampleNumber] = analogRead(filteredPin);
            pin = 0;
        }

        sampleNumber ++;
        previousTime = currentTime;
    }
    else
    {
        for(i=0;i<250;i++){
            Serial.print(rawArray[i]);
            Serial.print(",");
            Serial.println(filteredArray[i]);
        }
        while(!Serial.available() ){
        }
        sampleNumber = 0;
    }
    
}


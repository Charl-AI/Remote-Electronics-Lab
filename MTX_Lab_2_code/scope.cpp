/* This file contains the functions used by the Arduino to act as a scope, using
pins A0 and A1

20.08.20
C Jones
*/

#include <Arduino.h>
#include "scope.h"

void init_scope(void)
{
    Serial.begin(9600);
}

void oscilloscope(uint16_t sampling_freq)
{
    static uint32_t previousTime;
    const uint32_t currentTime = millis();

    const uint32_t time_delay = roundf(1000 / (2 * sampling_freq));

    if (currentTime - previousTime >= time_delay)
    {
        static uint16_t raw;
        static uint16_t filtered;
        static int pin;
        if (pin == 0)
        {
            raw = analogRead(rawPin);
            pin = 1;
        }
        else
        {
            filtered = analogRead(filteredPin);
            pin = 0;
        }

        Serial.print(raw);
        Serial.print(",");
        Serial.println(filtered);

        previousTime = currentTime;
    }
}
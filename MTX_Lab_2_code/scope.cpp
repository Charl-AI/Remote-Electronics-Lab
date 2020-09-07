/* This file contains the functions used by the Arduino to act as a scope, using
pins A0 and A1

20.08.20
C Jones
*/

#include <Arduino.h>
#include "scope.h"

void init_scope(void)
{
    Serial.begin(115200);
    ADCSRA = 0;             // clear ADCSRA register
    ADCSRB = 0;             // clear ADCSRB register
    ADMUX |= (1 << MUX0);    // set A0 analog input pin ****
    ADMUX |= (1 << REFS0);  // set reference voltage
    ADMUX &= ~(1 << ADLAR);  // Conversion Result = ADCL | ADCH << 8

    // sampling rate is [ADC clock] / [prescaler] / [conversion clock cycles]
    // for Arduino Uno ADC clock is 16 MHz and a conversion takes 13 clock cycles
    ADCSRA |= (1 << ADPS2) | (1 << ADPS0);    // 32 prescaler for 38.5 KHz
    //ADCSRA |= (1 << ADPS2);                     // 16 prescaler for 76.9 KHz
    //ADCSRA |= (1 << ADPS1) | (1 << ADPS0);    // 8 prescaler for 153.8 KHz

    ADCSRA |= (1 << ADATE); // enable auto trigger
    ADCSRA |= (1 << ADIE);  // enable interrupt when a measurement is completed
    ADCSRA |= (1 << ADEN);  // enable ADC
    ADCSRA |= (1 << ADSC);  // start ADC measurements
}

void oscilloscope(uint16_t sampling_freq, uint32_t currentTime, int au0,int au1)
{
    int raw = au0
    int filtered = au1

    Serial.print(raw);
    Serial.print(",");
    Serial.println(filtered);

       
    
}
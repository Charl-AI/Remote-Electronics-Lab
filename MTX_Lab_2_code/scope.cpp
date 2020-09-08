/* This file contains the functions used by the Arduino to act as a scope, using
pins A0 and A1

20.08.20
C Jones
*/

#include <Arduino.h>
#include "scope.h"

void init_scope(void)
{
    Serial.begin(9600); // initialise serial connection

    // Set ADC prescaler to 16 to speed it up (as opposed to 128 normally)
    sbi(ADCSRA,ADPS2) ;
    cbi(ADCSRA,ADPS1) ;
    cbi(ADCSRA,ADPS0) ;
}

void oscilloscope(uint32_t currentTime)
{   
    // stores time when previous measurement was taken
    static uint32_t previousTime; 

    // Time delay of 500 microseconds between measurements
    static const uint32_t time_delay = 500;

    // These variables store the data in the RAM (holding 300 samples each)
    static uint16_t rawArray[300];
    static uint16_t filteredArray[300];
    static uint8_t sampleNumber; // stores which sample number we're on

    // check it's time to take a sample and we haven't filled out arrays
    if ((currentTime - previousTime >= time_delay) && (sampleNumber < 300))
    {
        static int pin; // stores which pin was read last
        if (pin == 0)
        {
            rawArray[sampleNumber] = analogRead(rawPin); // read from raw pin
            pin = 1; // next reading will be from filtered pin
        }
        else
        {
            // read from filtered pin
            filteredArray[sampleNumber] = analogRead(filteredPin);
            pin = 0; // next reading will be from raw pin

            sampleNumber ++; // increment sample number
        }
        previousTime = currentTime; // store when sample was taken
    }
    
    // if we have filled up our storage arrays, send results to PC
    else if(sampleNumber == 300)
    {
        // Send data over serial port
        for(int i=0;i<300;i++){
            Serial.print("Raw:");
            Serial.print(rawArray[i]);
            Serial.print(",");
            Serial.print("Filtered:");
            Serial.println(filteredArray[i]);
            delay(1);
        }

        // wait for any user input
        while(!Serial.available() ){
        }
    
        sampleNumber = 0; // reset sample number
        char throwaway = Serial.read(); // clear serial buffer
    }
}


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
    static const uint32_t TIME_DELAY = 500;

    // These variables store the data in the RAM (holding 300 samples each)
    static const uint16_t SAMPLES = 300;
    static uint16_t rawArray[SAMPLES];
    static uint16_t filteredArray[SAMPLES];
    static uint16_t sampleNumber; // stores which sample number we're on

    // check it's time to take a sample and we haven't filled out arrays
    if ((currentTime - previousTime >= TIME_DELAY) && (sampleNumber < SAMPLES))
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
    else if(sampleNumber == SAMPLES)
    {
        // Send data over serial port
        send_data(rawArray,filteredArray,SAMPLES);

        // wait for any user input
        while(!Serial.available() ){
        }
    
        sampleNumber = 0; // reset sample number
        char throwaway = Serial.read(); // clear serial buffer
    }
}

void send_data(uint16_t rawArray[], uint16_t filteredArray[], uint16_t SAMPLES)
{
    uint16_t rawMaximum = 0;
    uint16_t rawMinimum = 1023;
    uint16_t filteredMaximum = 0;
    uint16_t filteredMinimum = 1023;
    
    for(int i=0;i<SAMPLES;i++){
        if(rawArray[i]>rawMaximum){
            rawMaximum = rawArray[i];
        }
        else if(rawArray[i] < rawMinimum){
            rawMinimum = rawArray[i];
        }
        if(filteredArray[i]>filteredMaximum){
            filteredMaximum = filteredArray[i];
        }
        else if(filteredArray[i] < filteredMinimum){
            filteredMinimum = filteredArray[i];
        }
    }

    uint16_t rawVPP = rawMaximum - rawMinimum;
    uint16_t filteredVPP = filteredMaximum - filteredMinimum;

    char rawBuf[20];
    char filteredBuf[20];

    sprintf(rawBuf,"Raw_Vpp=%d:",rawVPP);
    sprintf(filteredBuf,"Filtered_Vpp=%d:",filteredVPP);
    

    // Send data over serial port
        for(int i=0;i<SAMPLES;i++){
            Serial.print(rawBuf);
            Serial.print(rawArray[i]);
            Serial.print(",");
            Serial.print(filteredBuf);
            Serial.println(filteredArray[i]);
            //delay(1);
        } 
}
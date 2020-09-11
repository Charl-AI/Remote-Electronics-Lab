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
    static const uint16_t SAMPLES = 500;
    static uint16_t dataArray[SAMPLES];
    static uint16_t sampleNumber; // stores which sample number we're on

    // check it's time to take a sample and we haven't filled out arrays
    if ((currentTime - previousTime >= TIME_DELAY) && (sampleNumber < SAMPLES))
    {
        dataArray[sampleNumber] = analogRead(dataPin); // read from data pin
        previousTime = currentTime; // store when sample was taken
        sampleNumber ++; // increment sample number
    }
    
    // if we have filled up our storage arrays, send results to PC
    else if(sampleNumber == SAMPLES)
    {
        // Send data over serial port
        send_data(dataArray,SAMPLES);

        // wait for any user input
        while(!Serial.available() ){
        }
    
        sampleNumber = 0; // reset sample number
        char throwaway = Serial.read(); // clear serial buffer
    }
}

void send_data(uint16_t array[], uint16_t SAMPLES)
{
    // These variables store the max and min values of the data
    uint16_t maximum = 0;
    uint16_t minimum = 1023;
    
    // Here we loop through the data to find the max and min values
    for(int i=0;i<SAMPLES;i++){
        if(array[i]>maximum){
            maximum = array[i];
        }
        else if(array[i] < minimum){
            minimum = array[i];
        }
    }

    // calculate Vpp based off max and min values
    uint16_t vpp = maximum - minimum;
   
    // buffers to store strings
    char buf[20];

    // create strings with data labels and Vpp numbers
    sprintf(buf,"Vpp=%d:",vpp);

    // Send data and labels over serial port
        for(int i=0;i<SAMPLES;i++){
            Serial.print(buf);
            Serial.println(array[i]);
        } 
}
/*
This script can be uploaded to the Arduino as part of ME2 MTX Lab 2. It simply reads the analog data
from A0 and A1 corresponding to the input signal unfiltered and filtered. The data is sent through the
serial port where it can be visualised on the serial plotter

13.08.20
C Jones
 */

// Give analog pins meaningful names
#define rawPin A0 // raw data collected from A0
#define filteredPin A1 // filtered data collected from A1

// initialise sampling interval and previous sampling time
const int sampling_interval = 1; // 1  milisecond sampling rate (1000 Hz)
unsigned long previoustime = 0;

void setup() {

// set up serial port to send data to PC
Serial.begin(115200);

}

void loop() {

// check to see if its time to take another sample
  unsigned long currentTime = millis();
  if (currentTime - previoustime >= sampling_interval) {

    previoustime = currentTime; // save time of sample

    int raw = analogRead(rawPin);
    int filtered = analogRead(filteredPin);

  }
}

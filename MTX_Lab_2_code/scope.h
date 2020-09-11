/* This header file defines the functions that will be used in the project for
the signal acquisition and sensing part of the lab

19.08.20
C Jones
*/

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef scope_H
#define	scope_H

// give analogue pins meaningful names
#define dataPin A0

// this allows us to change the ADC prescaler
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// define function prototypes
void init_scope(void); // initialise scope
void oscilloscope(uint32_t currentTime);
void send_data(uint16_t rawArray[], uint16_t filteredArray[], uint16_t SAMPLES);


#ifdef	__cplusplus
}
#endif

#endif
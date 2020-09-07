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

#define rawPin A0
#define filteredPin A1

// define function prototypes
void init_scope(void); // initialise scope
void oscilloscope(uint16_t sampling_freq, uint32_t currentTime, int au0,int au1)


#ifdef	__cplusplus
}
#endif

#endif
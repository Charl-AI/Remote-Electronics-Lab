/* This header file defines the functions that will be used in the project for
the function generation part of the lab

19.08.20
C Jones
*/

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef generator_H
#define	generator_H

// define function prototypes
void init_generator(void); // intialise function generator
void generate_sine_wave(float frequency, uint32_t currentTime);

#ifdef	__cplusplus
}
#endif

#endif
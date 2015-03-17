/* 
 * File:   Leds.h
 * Author: Zachary Lenenberg
 *
 * Created on February 16, 2015, 10:11 AM
 */

#ifndef LEDS_H
#define	LEDS_H

#include <xc.h>

enum LEDS {
LD1 = 0x1,
LD2 = 0x2,
LD3 = 0x4,
LD4 = 0x8,
LD5 = 0x10,
LD6 = 0x20,
LD7 = 0x40,
LD8 = 0x80,
};
/**
 * This macro will initialize leds 1-8 to be set as outputs
 */
#define LEDS_INIT() do {\
TRISE = 0x00;\
LATE = 0x00;\
} while(0)

/**
 * This macro will return the value of the LATE register, with 1's corresponding
 * to which LEDs are illuminated.
 */
#define LEDS_GET() PORTE

/**
 * This macro will set or clear all 8 LEDS as a group
 */
#define LEDS_SET(x) LATE = x

#endif	/* LEDS_H */


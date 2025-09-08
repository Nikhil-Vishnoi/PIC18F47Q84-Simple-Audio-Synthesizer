/* 
 * File:   DAC_Utils.c
 * Author: nikhil
 *
 * Created on August 18, 2025, 7:05 PM
 */
#include "DAC_Utils.h"

/**
 * 
 * @param RA2 1 means outputs to RA2 0 means outputs to RB7 
 * @param posRef 0 = Vdd, 1 = Vref+, 2 = FVR Buffer 2 
 * @param negRef 1 = Vref-, 0 = Vss 
 */
void initializeDAC(uint8_t RA2, uint8_t posRef, uint8_t negRef) {
    uint8_t set = 0x80;  // DAC1EN = 1

    // Output select
    if (RA2 == 1) {
        set |= 0x20;  // DAC1OE1 = 1 (RA2)
        set &= ~0x10; // ensure DAC1OE2 = 0
    } else {
        set |= 0x10;  // DAC1OE2 = 1 (RB7)
        set &= ~0x20; // ensure DAC1OE1 = 0
    }

    // Positive reference select (PSS1:PSS0)
    switch(posRef) {
        case 0: set &= ~0x0C; break;       // 00 = VDD
        case 1: set = (set & ~0x0C) | 0x04; break;  // 01 = VREF+
        case 2: set = (set & ~0x0C) | 0x08; break;  // 10 = FVR Buffer 2
        default: set &= ~0x0C; break;     // default to VDD
    }

    // Negative reference select (NSS)
    if (negRef == 1) {
        set |= 0x01;  // VREF-
    } else {
        set &= ~0x01; // VSS
    }

    DAC1CON = set;  // Write configuration to DAC1CON
}

void setDAC(uint8_t data){
    DAC1DAT = data; 
}

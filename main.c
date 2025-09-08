/* 
 * File:   newmain1.c
 * Author: nikhil
 *
 * Created on August 16, 2025, 3:38 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Configuration.h"0

#pragma config FEXTOSC = OFF
#pragma config RSTOSC  = HFINTOSC_64MHZ
#pragma config WDTE = OFF
#pragma config MCLRE = EXTMCLR


#include <stdint.h>
#include <xc.h>
#include "PIC18F47Q84_Register.h"
#include "DAC_Utils.h"
#include "shared.h"
#include "mcc_generated_files/system/system.h"
#define _XTAL_FREQ 64000000

// ADC read
uint16_t readADC(void) {
    ADCON0bits.GO = 1; //Start conversion
    while (ADCON0bits.GO); //Wait for conversion done
    uint16_t adc_result = ((uint16_t)ADRESH << 8) | ADRESL;
    return adc_result; 
    
}

void main(void) {
    
    TRISCbits.TRISC4 = 0;   // RC4 as output
    RC4PPS = 0x0C;          // PWM1_16BIT Slice1 Output1 to RC4 (check PPS table)

    PWM1CLK = 0x02;  // FOSC
    PWM1LDS = 0x00;  // immediate load
    PWM1PR = 3199;   // PWM period (register may be 16-bit in header)
    PWM1S1P1 = 0;    // 0% duty
    PWM1CON = 0x80;  // enable PWM
    PWM1CONbits.LD = 1;

   // DAC init
   initializeDAC(1,0,0);
   //Setup ADC
   ADCON0bits.FM = 1; //right justify
   ADCON0bits.CS = 1; //ADCRC Clock
   ADPCH = 0x00; //RA0 is Analog channel
   TRISAbits.TRISA0 = 1; //Set RA0 to input
   ANSELAbits.ANSELA0 = 1; //Set RA0 to analog
   ADCON0bits.ON = 1; //Turn ADC On
   __delay_ms(2);

   // Timer0 init
   TMR0H = 0; TMR0L = 0;
   T0CON1 = (3<<_T0CON1_T0CS_POSN) | (0<<_T0CON1_T0CKPS_POSN) | (1<<_T0CON1_T0ASYNC_POSN);
   T0CON0 = (0<<_T0CON0_T0OUTPS_POSN) | (1<<_T0CON0_T0EN_POSN) | (1<<_T0CON0_T0MD16_POSN);
   
    // Wave option mode select 
    TRISDbits.TRISD1 = 1;   // 1 = input
    ANSELDbits.ANSELD1 = 0; // 0 = digital mode


       
   PIR3bits.TMR0IF = 0;
   PIE3bits.TMR0IE = 1;

   INTCON0bits.GIEH = 1; // global high-priority interrupts

   const uint16_t base_freq = 440;
   const uint8_t samples = 50;
   uint8_t prev_ind = -1; 
   uint8_t debouncer = PORTDbits.RD1; 
   while(1) {
       uint16_t adc_val = readADC();
       float voltage = ((float)adc_val / 4095.0f)*3 ; // 0..3 V

       uint8_t ind = (voltage/3.0)*9;
       if (voltage < 0.3) 
            ind = 0; 
       else if (voltage < .5) 
           ind = 1; 
       else if (voltage < .8) 
           ind = 2; 
       else if (voltage < .5) 
           ind = 3; 
       else if (voltage < .8) 
           ind = 4; 
       else if (voltage < 1.2) 
           ind = 5; 
       else if (voltage < 1.6) 
           ind = 6; 
       else if (voltage < 2) 
           ind = 7; 
       else if (voltage < 2.3) 
           ind = 8; 
       else 
           ind = 9; 
       uint16_t duty = (uint16_t)((ind+1)/10.0*3199);
    PWM1S1P1 = duty;
    PWM1CONbits.LD = 1;

       float fout = freq_lookup[ind]; 

       uint32_t counts = (_XTAL_FREQ)/(samples*fout);
       preload = 65536 - (uint16_t)counts;
        
        uint8_t rd1_value = PORTDbits.RD1; // read RD1 
        if (rd1_value == 0 && debouncer == 1) {
            mode = (mode+1)%3; 
        }
              
        debouncer = rd1_value; 
        
        prev_ind = ind; 
   }
}
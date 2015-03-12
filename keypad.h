/* 
 * File:   keypad.h
 * Author: user
 *
 * Created on February 5, 2015, 11:42 AM
 */
#include "p24FJ64GA002.h"
#ifndef KEYPAD_H
#define	KEYPAD_H

#define TRIS_ROW1 TRISAbits.TRISA0//pin 2
#define TRIS_ROW2 TRISBbits.TRISB3//pin 7
#define TRIS_ROW3 TRISBbits.TRISB2//pin 6
#define TRIS_ROW4 TRISAbits.TRISA1//pin 3

//TRISBbits.TRISB0//pin 4
//TRISBbits.TRISB1//pin 5

#define TRIS_COL1 TRISBbits.TRISB7//pin 16
#define TRIS_COL2 TRISBbits.TRISB6//pin 15
#define TRIS_COL3 TRISBbits.TRISB8//pin 17

#define PU_COL1 CNPU2bits.CN23PUE
#define PU_COL2 CNPU2bits.CN24PUE
#define PU_COL3 CNPU2bits.CN22PUE

#define CNEN_COL1 CNEN2bits.CN23IE
#define CNEN_COL2 CNEN2bits.CN24IE
#define CNEN_COL3 CNEN2bits.CN22IE

#define ODC_ROW1 ODCAbits.ODA0
#define ODC_ROW2 ODCBbits.ODB3
#define ODC_ROW3 ODCBbits.ODB2
#define ODC_ROW4 ODCAbits.ODA1

#define ROW1 LATAbits.LATA0
#define ROW2 LATBbits.LATB3
#define ROW3 LATBbits.LATB2
#define ROW4 LATAbits.LATA1

#define COL1 PORTBbits.RB7
#define COL2 PORTBbits.RB6
#define COL3 PORTBbits.RB8

#define PRESSED 0
#define RELEASED 1//backwards because inputs are pull up resistors

#define ROW_ON 0
#define ROW_OFF 1
//For the rows (outputs):
//LOW Z is putting ODC latch to 0
//HIGH Z is opening the circuit with the ODC, latch is 1
//ROW_ON is 0 because we want low Z so that there's a change when the button is pressed

void initKeypad(void);
char scanKeypad(void);

#endif	/* KEYPAD_H */


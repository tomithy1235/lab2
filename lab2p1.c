// ******************************************************************************************* //
// File:         lab2p1.c
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include <stdio.h>

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

typedef enum statesEnum {

    listenForPress,
    pressHandle,
    waitForRelease
            
} states;

volatile states state = listenForPress;

int main(void)
{
    char printChar;
    int printNum = 0;
    initTimer2();
    initKeypad();
    initLCD();
    clearLCD();
    moveCursorLCD(0,0);

    while(1){
        switch(state){
            
            case listenForPress:
                //nothing needs to be done
                break;

                
            case pressHandle:
                printChar = scanKeypad();
                if(printChar != -1)
                {
                    if(printNum <= 7)
                        moveCursorLCD(printNum,0);
                    else
                        moveCursorLCD(printNum%8,1);

                    printNum++;
                    if(printNum == 16)
                        printNum = 0;

                    printCharLCD(printChar);
                }
                state = waitForRelease;
                break;

            case waitForRelease:
                //nothing needs to be done here
                break;
        }
    }
    
    return 0;
}


void _ISR _CNInterrupt(void){
    
    IFS1bits.CNIF = 0;//put flag down
    delayUs(5000);//to debounce

    if(state == listenForPress){
        if(COL1 == PRESSED || COL2 == PRESSED || COL3 == PRESSED)
            state = pressHandle;
    }
    
    else if (state == waitForRelease)
        state = listenForPress;
    

    
}
/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"
#include "lcd.h"
#define ONE_SECOND F_CY/256.0 - 1
#define TEN_MS .01*F_CY/256.0 - 1

void delayUs(unsigned int delay)
{
    PR2 = (unsigned int) (delay*14.7456);
    
    IFS0bits.T2IF = 0;
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF == 0){ }
    IFS0bits.T2IF = 0;
}


/*
//NOTE: I changed this to just state being 1 or 2, to follow with the change in
//the main function as well. 2 should be run, 1 should be stop
//Before, states 1 and 2 were stop states, 3 and 4 were run states
void turnOn(int state){
    if(state == 1){
        stopTimer1();
    }

    else if(state == 2){
        startTimer1();
    }
    else if (state == 3){
        clearTimer1();
    }
    
}
 * */

void delay2Sec(){
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 1;
    while(IFS0bits.T1IF == 0){ }
    IFS0bits.T1IF = 0;
    while(IFS0bits.T1IF == 0){ }
    IFS0bits.T1IF = 0;
    //This just delays 1 second twice
}

void initTimer1()
{
    //enables interrupt and sets PR value
    PR1 = ONE_SECOND;
    TMR1 = 0;
    T1CONbits.TCKPS = 0b11;
    //IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 0;
}

void initTimer2()
{
    T2CONbits.TCKPS = 0b00;
    TMR2 = 0;
    T2CONbits.TON = 0;
    IFS0bits.T2IF = 0;
    //we don't need interrupts for switch 2
}
/*
void clearTimer1()
{
    //TODO: actually finish clearing the time off the LCD!
    clearLCD();
    moveCursorLCD(0,0);
    printStringLCD("STOPPED:");
    TMR1 = 0;//dump timer register
}

void startTimer1()
{
    //update LCD to say "RUNNING:"
    moveCursorLCD(0,0);
    printStringLCD("RUNNING:");

    //change LEDs and turn on timer
    LATAbits.LATA0 = OFF;
    LATAbits.LATA1 = ON;
    T1CONbits.TON = 1;
    //T2CONbits.TON = 1;
   
}

void stopTimer1()
{
    //update LCD to say "STOPPED:"
    moveCursorLCD(0,0);
    printStringLCD("STOPPED:");

    //change LEDs and turn on timer:
    LATAbits.LATA0 = ON;
    LATAbits.LATA1 = OFF;
    T1CONbits.TON = 0;
   // T2CONbits.TON = 0;

    
}
 * */
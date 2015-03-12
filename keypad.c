#include "p24FJ64GA002.h"
#include "keypad.h"
#include "timer.h"

//typedef enum buttonsEnum{
//    none, pound, star, one, two, three,
//    four, five, six, seven, eight, nine, zero
//} buttons;


//TODO: confirm pin 17 can be used as output!

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
 //Other considerations: explicitly defining pins to be digital input (instead of analog)


void initKeypad(void){
    //Rows as outputs:
    TRIS_ROW1 = 0;
    TRIS_ROW2 = 0;
    TRIS_ROW3 = 0;
    TRIS_ROW4 = 0;
    
    //Columns as inputs:
    TRIS_COL1 = 1;
    TRIS_COL2 = 1;
    TRIS_COL3 = 1;

//    AD1PCFGbits.PCFG0 = 1;
//    AD1PCFGbits.PCFG2 = 1;
  //  AD1PCFGbits. = 1;//set as digital input

    //ODC outputs:
    ODC_ROW1 = 1;
    ODC_ROW1 = 1;
    ODC_ROW1 = 1;
    ODC_ROW1 = 1;
    
    //Pull up resistor inputs:
    PU_COL2 = 1;
    PU_COL1 = 1;
    PU_COL3 = 1;

    //enable interrupts for each pin:
    CNEN_COL1 = 1;
    CNEN_COL2 = 1;
    CNEN_COL3 = 1;
    
    IEC1bits.CNIE = 1;//overall interrupt enable
    IFS1bits.CNIF = 0;

    //Set each row to High Z (So everything is logic high)
    ROW1 = ROW_ON;
    ROW2 = ROW_ON;
    ROW3 = ROW_ON;
    ROW4 = ROW_ON;

}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
char scanKeypad(void){
    char key = -1;
    
    int listenCol = 0;
    
    if(COL1 == PRESSED)
        listenCol = 1;
    else if (COL2 == PRESSED)
        listenCol = 2;
    else if (COL3 == PRESSED)
        listenCol = 3;
    
    //Turn everything off (except row 1)
    
    ROW2 = ROW_OFF;
    ROW3 = ROW_OFF;
    ROW4 = ROW_OFF;
    ROW1 = ROW_ON;
    
    //ROW1 scan:
    if(listenCol == 1 && COL1 == PRESSED)
        key = '1';
    else if (listenCol == 2 && COL2 == PRESSED)
        key = '2';
    else if (listenCol == 3 && COL3 == PRESSED)
        key = '3';

    else{
        
        ROW1 = ROW_OFF;//turn row1 off

        //ROW2 scan:
        ROW2 = ROW_ON;//turn row2 on

        if(listenCol == 1 && COL1 == PRESSED)
            key = '4';
        else if (listenCol == 2 && COL2 == PRESSED)
            key = '5';
        else if (listenCol == 3 && COL3 == PRESSED)
            key = '6';

        else{
            
            ROW2 = ROW_OFF;//turn row2 off

            //ROW3 scan:
            ROW3 = ROW_ON;
            if(listenCol == 1 && COL1 == PRESSED)
                key = '7';
            else if (listenCol == 2 && COL2 == PRESSED)
                key = '8';
            else if (listenCol == 3 && COL3 == PRESSED)
                key = '9';
            
            else {

                ROW3 = ROW_OFF;

                //ROW4 scan:
                ROW4 = ROW_ON;
                if(listenCol == 1 && COL1 == PRESSED)
                    key = '*';
                else if (listenCol == 2 && COL2 == PRESSED)
                    key = '0';
                else if (listenCol == 3 && COL3 == PRESSED)
                    key = '#';
            }
        }
    }

    
    //Turn everything back on:
    ROW1 = ROW_ON;
    ROW2 = ROW_ON;
    ROW3 = ROW_ON;
    ROW4 = ROW_ON;
    return key;
}

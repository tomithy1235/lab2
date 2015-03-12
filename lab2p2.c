// ******************************************************************************************* //
// File:         lab2p1.c
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include "part2helper.h"
#include <stdio.h>

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

typedef enum statesEnum {

    waitForPass,
    listenForPress,
    pressHandle,
    waitForRelease,
    checkChar,
    invalidPress,
    enterNewPassStart,
    validPassEntered,
    validNewPass,
    invalidNewPassEntered
            
} states;

volatile states state = waitForPass;


int main(void)
{
        //char currChar;
	char pass[4];
	int numPasses = 0;
	int newPassEnter = 0;
	char passDB[][4] = { {'a','a','a','a'}, {'a','a','a','a'}, {'a','a','a','a'}, {'a','a','a','a'} };
        //int printNum = 0;
	int charNum = 0;
        initTimer1();
        initTimer2();
        initKeypad();
        initLCD();
        int i=0;
        char currChar = 'a';

    while(1){
        switch(state){
            
            case waitForPass:
                for(i = 0; i < 4; i++)
                    pass[i] = 'a';
                newPassEnter = 0;
		clearLCD();
                charNum = 0;
		moveCursorLCD(0,0);
		printStringLCD("Enter");
		state = listenForPress;
            break;
			
			
            case listenForPress:
                //nothing needs to be done
                break;

                
            case pressHandle:
		currChar = scanKeypad();
                pass[charNum] = currChar;
                if(newPassEnter == 1)
                {
                    if(checkValidChar(currChar) == 0){
                        state = invalidNewPassEntered;//erases set state and current pass
                        break;
                    }
                }

                moveCursorLCD(charNum,1);//sets cursor to second row
                printCharLCD(pass[charNum]);//prints current button press

                charNum++;
                
                if(charNum == 4){//then reset it, and handle the valid chars
                //charNum being 4 means we made it through 4 valid key presses
                    charNum = 0;
                    if(newPassEnter == 1){
                        state = validNewPass;
                    }
                    else{
                        if(checkPass(passDB, pass) == 1)
                            state = validPassEntered;
                        else
                            state = invalidPress;
                    }
                }
                
                if(numPasses == 4)
                    numPasses = 0;
                
                if(state == pressHandle)//just in case it was changed elsewhere already
                    state = waitForRelease;
                
                    break;


            case waitForRelease:
                //nothing needs to be done here
                break;


            case checkChar:
                if (pass[0] == '*'){//then we are heading for a new passcode entry
                    if (pass[1] == '*')//then new passcode entry
                    {
                        state = enterNewPassStart;
                        charNum = 0;
                    }
                    else if ((pass[0] == '*') && (checkValidChar(pass[1]) == 1))
                        state = invalidPress;
                }
                //otherwise we will be doing nothing for a star being first
                
                //we need the else so that a '*','X' (X = number) is noticed
                if(newPassEnter != 1){
                    //always invalid:
                    if(pass[0] == '#' || pass[1] == '#' || pass[2] == '#' ||
                            pass[3] == '#' || pass[2] == '*' || pass[3] == '*'
                            || ((pass[0] != '*') && (pass[1] == '*')))
                        state = invalidPress;
                }

                if(state == checkChar){
                    state = listenForPress;
                }

                break;

            case invalidNewPassEntered:
                clearLCD();
                moveCursorLCD(0,0);
                printStringLCD("Invalid");
                delay2Sec();
                state = waitForPass;
                break;

            case validPassEntered:
                clearLCD();
                moveCursorLCD(0,0);
                printStringLCD("Good");
                delay2Sec();
                state = waitForPass;
                break;

            case invalidPress:
                clearLCD();
                moveCursorLCD(0, 0);
                printStringLCD("Bad");
                delay2Sec();
                state = waitForPass; //this state will reset pass array
                break;

            case enterNewPassStart:
                clearLCD();
                moveCursorLCD(0, 0);
                printStringLCD("Set Mode");
                newPassEnter = 1;
                state = listenForPress;
                break;

            case validNewPass:
                placeNewPassword(passDB,pass,numPasses);
                numPasses++;
                clearLCD();
                moveCursorLCD(0, 0);
                printStringLCD("Valid");
                delay2Sec();
                state = waitForPass;
                break;
        }
    }
    
    return 0;
}


void _ISR _CNInterrupt(void){
    
    IFS1bits.CNIF = 0;//put flag down
    delayUs(5000);//to debounce
    
    if(state == listenForPress){
        //this next if statement might not be necessary:
        if(COL1 == PRESSED || COL2 == PRESSED || COL3 == PRESSED)
            //then a button is being pressed
            state = pressHandle;
    }
    
    else if (state == waitForRelease){
        state = checkChar;
    }
    
}

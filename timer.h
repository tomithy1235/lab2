#ifndef INITTIMER_H
#define	INITTIMER_H
#define F_CY 14745600.0
#define ON 0
#define OFF 1

void delayUs(unsigned int delay);
void initTimer2();
void initTimer1();
void delay2Sec();
/*
void clearTimer1();
void startTimer1();
void stopTimer1();
void turnOn(int state);
*/
#endif	/* INITTIMER_H */


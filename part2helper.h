/* 
 * File:   part2helper.h
 * Author: Timothy
 *
 * Created on March 10, 2015, 2:55 PM
 */

#ifndef PART2HELPER_H
#define	PART2HELPER_H

void placeNewPassword(char passDB[][4], char newPass[], int pos);
int checkValidChar(char c);
int checkPass(char passDB[][4],char pass[]);

#endif	/* PART2HELPER_H */


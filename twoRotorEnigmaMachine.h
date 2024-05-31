// Author: Basim Khokhar
// Date: October 2023
// Description: This twoRotorEnigmaMachine.h file contains forward declarations 
//              for all the functions that are listed and programmed in
//              the twoRotorEnigmaMachine.c file.     

#include <stdio.h>
#include <stdlib.h>

#ifndef TWOROTORENIGMAMACHINE_H // extra pre-processing step for safety
#define TWOROTORENIGMAMACHINE_H // .h file must have the same name as its .c counterpart.

// Each function definition below is listed in the twoRotorEnigmaMachine.c file, including
// the return types and parameters expected.
void setUpIni(char *);
void createRotors(int[28], int[28]);  
void turnRotorRight(int[28]);
void turnRotorLeft(int[28]);
void configureRotor1(int[28], int);
void configureRotor2(int[28], int);
int charToIndex(char);
char indexToChar(int);
void encryptFile(FILE*, FILE*, int rotor1[28], int rotor2[28]);
void decryptFile(FILE*, FILE*, int rotor1[28], int rotor2[28]);
void showUsageStatements();
char checkFlags(char[3]);

#endif // closes the #ifndef ("if not defined").

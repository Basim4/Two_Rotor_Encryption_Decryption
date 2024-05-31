/*
Author: Basim Khokhar
Date: October 2023
Description: This twoRotorEnigmaMachine.c file encases all the functions required to create and
             utilize a 2 Rotor Encryption Machine. All these functions have been 
             preprocessed by each function's forward declarations in the twoRotorEnigmaMachine.h
             file. All the functions that this file provides - setUpIni, createRotors, 
             turnRotorRight, turnRotorLeft, configureRotor1, configureRotor2, charToIndex, indexToChar, 
             encryptFile, decryptFile, showUsageStatements, and checkFlags - are all used my the 
             main() function to build/set rotors and encrypt/decrypt files.
*/

#include "twoRotorEnigmaMachine.h" // all functions below are forward declared in this .h file
#include <stdio.h>
#include <ctype.h> // for toUppercase() fucntion

// This setUpIni function takes a char pointer which will eventually 
// be opened and have each value XOR-ed with 42. Those new values will
// be stored in a "rotors.ini" file, which will be used to fill both rotors.
void setUpIni (char *fileName) {
  int buffer[56]; // will store the contents from the file
  int i;
  int xorVal;

  FILE *openedConFile;
  openedConFile= fopen(fileName, "r"); // creates a FILE pointer to allow reading into fileName
  FILE *rotFile;
  rotFile = fopen("rotors.ini", "w");

  if (openedConFile == NULL){ // File given was not properly given. Displays an error and exits the program
    printf("rotors.ini was not initialized. Run with -i option and provide an appropriate configuration file.\n");
    exit(0);
  } 
  else { // File was properly given and its contents will be XOR-ed for rotors.ini
    for (i = 0; i < 56; i++){ // 56 values are in the configuration file.
      xorVal = 0;
      fscanf(openedConFile, "%d", buffer); // reading from the open file. Results are placed in buffer
      xorVal = (*buffer) ^ 42;
      fprintf(rotFile, "%d\n", xorVal); // XOR-ed value is writted to rotors.ini
    }
  }
  fclose(openedConFile); // both input and output files are closed.
  fclose(rotFile);
}

// This build Rotors function populates two integer arrays usuing an already exisitng
// "rotors.ini" file. If the file does not exist, an error will occur and the program
// will exit.
void createRotors(int rotor1[28], int rotor2[28]) {
  FILE *rotFile;
  int i;
  int buffer[56]; // will store the contents from the file
  int xorVal;

  rotFile = fopen("rotors.ini", "r"); // opens rotors.ini for reading
  if (rotFile == NULL) {
    printf("Error: Rotor machine not initialized. Run with -i option and provide an appropriate configuration file.");
    exit(0);
  }
  else { // file is given properly
    for (i = 0; i < 56; i++) { // iterates though entire rotors.ini file
      xorVal = 0;
      fscanf(rotFile, "%d", buffer); //reads integeer value from rotors.ini
      xorVal = (*buffer) ^ 42; // XOR-ed value is stored
      if (i < 28){ // values 1-28 are stored in Rotor1 and 29-56 are stored in Rotor 2
	      rotor1[i] = xorVal;
      } 
      else {
	      rotor2[i - 28] = xorVal;
      }  
    }
  }
  fclose(rotFile); // closes the rotors.ini file
}

// This turnRotorRight function primarily handles Rotor1. Each value of rotor1 is
// shifted to the right, with the previously last value being sent to the beginning.
void turnRotorRight(int rotor[28]) {
  int lastVal = rotor[27]; // stores the initial final value
  int i;
  
  for (i = 27; i >= 0; i--) { //iterates through list backwards.
    if (i < 1){
      // all elements have been shifted and initial final value is placed in the beginning.
      rotor[0] = lastVal;
    }
    else {
      rotor[i] = rotor[i-1]; // previous element is stored in the current i index. 
    }
  }
} 

// This turnRotorLeft function primarily handles Rotor2. Each value of rotor2 is
// shifted to the left, with the previously first value being sent to the end.
void turnRotorLeft(int rotor[28]) {
  int firstVal = rotor[0]; // stores the initial first value
  int i;

  for (i = 0; i < 28; i++) {
    if (i >= 27){
      // all elements have been shifted and initial first value is placed in the end.
      rotor[27] = firstVal;
    } 
    else {
      rotor[i] = rotor[i+1]; // subsequent element is stored in the current i index.
    }
  }
}

// This configureRotor1 function shifts rotor1 to its initial position by shifting the rotor
// right. The number of rotations is given by the user through the arguments.   
void configureRotor1(int rotor[28], int rotations){
  int i;
  // for loop rotates the rotor right a number of times determined by the rotations variable
  for (i = 0; i < rotations; i++) {
    turnRotorRight(rotor);
  }
}

// This configureRotor2 function shifts rotor2 to its initial position by shifting the rotor
// left. The number of rotations is given by the user through the arguments.
void configureRotor2(int rotor[28], int rotations){
  int i;
  // for loop rotates the rotor left a number of times determined by the rotations variable
  for (i = 0; i < rotations; i++) { 
    turnRotorLeft(rotor);
  }
}

// This charToIndex function takes a character and converts it to an Index value to be used
// in the encryptionFile / decriptionFile functions. 
int charToIndex(char convert) {
  int charIndex;

  if (convert == ' ') { //returns an index of 26 if a space is given
    return 26;
  } 
  else if (convert == '.') { //returns an index of 27 if a period is given
    return 27;
  }
  else { 
    convert = toupper(convert); // ensures that the given char is workable
    charIndex = (int)convert - 65; // Subtracts 65 to represent value in index range.
    return charIndex; 
  }
}

// This indexToChar function takes a an index (integer) and returns a cooresponding char 
// to be used in the encryptionFile / decriptionFile functions.
char indexToChar(int convert) {
  char returnedChar;

  if (convert == 26){ //returns a space if an index of 26 is given
    return ' ';
  } else if (convert == 27) { //returns a period if an index of 27 is given
    return '.';
  } else {
    returnedChar = (char)(convert + 65); // Adds 65 to represent its respective char's ASCII value.
    return returnedChar;
  }
}

// This encryptFile encrypts the contents inside a suitable input file and outputs the result into
// another file of the user's choosing. Two built rotors are sent to this function, and each index
// cooresponds to a respective English letter, with _ (index 26) and . (index 27) included. A letter
// is read from the input file, checks its respective rotor1 index, checks the element inside the index,
// finds that same number in rotor2, converts the value's matching index to a character, outputs it
// into the user's output file, and then both rotors are rotated for the next character.
void encryptFile(FILE* infile, FILE* outfile, int rotor1[28], int rotor2[28]) {
  int i, k;
  int asciiVal;
  int rot2Index;
  int newLetter, compareVal;
  char buffer[256]; // will store the to-be-analyzed line contents

  while (fgets(buffer, 256, infile) != NULL) { // continue iterating until there are no more lines.
    i = 0;
    while (buffer[i] != '\0'){
      if (buffer[i] == '\n') {  //NEW LINE FOUND
	      fprintf(outfile, "\n");
	      break;
      } 
      else {  //CHAR FOUND
	      asciiVal = charToIndex(buffer[i]); //getting index of char that will be checked in R1
       	compareVal = rotor1[asciiVal]; //uses the letter index from above to get number from R1 to check R2
	      for(k = 0; k < 28; k++) { //searching R2 for compareVal recieved from R1
	        if (rotor2[k] == compareVal) {
	        rot2Index = k;
	        break;  
	        }
	      }
	      newLetter = indexToChar(rot2Index); //Encrypted Letter is determined. Now need to write in file.
        fprintf(outfile, "%c", newLetter); //new encrypted letter is written to output file.
      }
      i = i + 1;
      //Rotate both rotors in thier respective directions
      turnRotorRight(rotor1);
      turnRotorLeft(rotor2);
    }
  } // iterate again (if needed) to scan new line and repeat.

  fclose(infile); //both input and output files are closed.
  fclose(outfile);
}

// This decryptFile decrypts the contents inside a suitable input file and outputs the result into
// another file of the user's choosing. Two built rotors are sent to this function, and each index
// corresponds to a respective English letter, with _ (index 26) and . (index 27) included. A letter
// is read from the input file, checked with its respective rotor2 index, checks the element inside the 
// index finds that same number in rotor1, converts the value's matching index to a character, outputs
// it into the user's output file, and then both rotors are rotated for the next character.
void decryptFile(FILE* infile, FILE* outfile, int rotor1[28], int rotor2[28]) {
  int i, k;
  int asciiVal;
  int rot1Index;
  int newLetter, compareVal;
  char buffer[256]; // will store the to-be-analyzed line contents

  while (fgets(buffer, 256, infile) != NULL) { // continue iterating until there are no more lines.
    i = 0;
    while (buffer[i] != '\0'){ // continue iterating unntil the end of the string.
      if (buffer[i] == '\n') { //NEW LINE FOUND
	      fprintf(outfile, "\n");
	      break;
      } 
      else { //CHAR FOUND
	      asciiVal = charToIndex(buffer[i]); // getting index of char that will be checked in R1
      	compareVal = rotor2[asciiVal]; // uses the letter index from above to get number from R1 to check R2
	      for(k = 0; k < 28; k++) { // searching R2 for compareVal recieved from R1
	        if (rotor1[k] == compareVal) {
	          rot1Index = k; // keeps the index if a match is found.
	          break;  
	        }
	      }

	    newLetter = indexToChar(rot1Index); // Encrypted Letter is determined. Now need to write in file.
	    fprintf(outfile, "%c", newLetter); // new encrypted letter is written to output file.
      }

      i = i + 1; // i is incremented to analyze next character
      // Rotate both rotors in thier respective directions
      turnRotorRight(rotor1);
      turnRotorLeft(rotor2);
    }
  } // iterate again (if needed) to scan new line and repeat.

  fclose(infile); // close both input and output files
  fclose(outfile);
} 

// This showUsageStatements function is invoked when the user has not properly given the arguments
// needed to two_rotor_machine.execute this 2 Motor Encryption Machine program. The function prints the five
// proper ways to two_rotor_machine.execute the function.
void showUsageStatements(){
  printf("usage\n");
  printf("./two_rotor_machine.exe -i <file>\n");
  printf("./two_rotor_machine.exe -e <file1> <file2> -r <r1> <r2>\n");
  printf("./two_rotor_machine.exe -d <file1> <file2> -r <r1> <r2>\n");
  printf("./two_rotor_machine.exe -e <file1> <file2> -r <r1> <r2> -i <file>\n");
  printf("./two_rotor_machine.exe -d <file1> <file2> -r <r1> <r2> -i <file>\n");
}

// This checkFlags function is used to determine if the user has properly given the 
// "-i", "-e", "-d", and "-r" flags in the arguments. If the flag is valid, the function
// returns the character (i/e/d/r) to be processed. If invalid, the usage statements are
// displayed and the program exits.
char checkFlags(char flag[3]) {
  //checks if first char is a "-" and if it ends after where a letter should be (through \0)
  if ((flag[0] == '-') && (flag[2] == '\0')) {
    // Checks all possible valid flags and returns the letter if found. 
    if (flag[1] == 'i') {
      return 'i';
    } 
    else if (flag[1] == 'e') {
      return 'e';
    } 
    else if (flag[1] == 'd') {
      return 'd';
    } 
    else if (flag[1] == 'r') {
      return 'r';
    } 
    else { // flag letter was not valid - Usage statements are displayed and the program exits.
      showUsageStatements();
      exit(0);
      return ' ';
    }
  }
  return ' ';
}
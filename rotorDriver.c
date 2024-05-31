/*
Author: Basim Khokhar
Date: October 2023
Description: This rotorDriver.c file stores the main() to the
             2 Rotor Encryption machine. This main function will 
             determine how many arguments are provided and carry out
             the necessary operations through the included rotorMachine
             functions. The arguments given to the main() are being 
             pulled from the char *argv[] array parameter. Each parameter will
             be vetted before use to ensure the user provided proper information.
*/
#include <stdio.h>
#include <stdlib.h>
#include "twoRotorEnigmaMachine.h" // This allows for the twoRotorEnigmaMachine.c functions to be called and used

int main (int argc, char *argv[]) {
  int rotor1[28]; // Integer array that stores all Rotor 1 numbers
  int rotor2[28]; // Integer array that stores all Rotor 2 numbers
  FILE *inputFile;
  FILE *outputFile;

  switch (argc) { // There can only be three correct argument count values: 3, 7, or 9.

  // Case 3 simply creates the rotors.ini for future rotor building
  case 3:
    if(checkFlags(argv[1]) == 'i'){  // Will only create the rotors.ini file with proper flag
      setUpIni(argv[2]);  // Sends the configuaration file to make the rotors.ini file
    } 
    else{  // displays usage and exits due to the -_ flag being incorrect
      showUsageStatements(); 
      exit(0);
    }
    break;

  // Case 7 primarily encrypts and decrypts the files through the use of the functions
  // from twoRotorEnigmaMachine.c. Before that, the rotors are set up using an already existing
  // rotors.ini file.  
  case 7: 
    if(((checkFlags(argv[1]) == 'e') || (checkFlags(argv[1]) == 'd')) && (checkFlags(argv[4]) == 'r')) {
	if ((argv[2] != NULL) && (argv[3] != NULL)) {
	  inputFile = fopen(argv[2], "r"); //opening the input and output files
	  outputFile = fopen(argv[3], "w");
	  createRotors(rotor1, rotor2); // building rotors
	  configureRotor1(rotor1, atoi(argv[5])); // setting the rotors to thier inital positions
	  configureRotor2(rotor2, atoi(argv[6]));
	  if (checkFlags(argv[1]) == 'e') { // "e" signals for encryption
	    encryptFile(inputFile, outputFile, rotor1, rotor2);
	  } 
	  else { // only other option (proven by earlier if statement) is "d" for decryption
	    decryptFile(inputFile, outputFile, rotor1, rotor2);
	  }
	} 
	else { // displays the usage and exits when the given files are invalid.
	  showUsageStatements();
	  exit(0);
	}
    }
    else { // displays the usage and exits when the "-_" flag is invalid
      showUsageStatements();
      exit(0);
    }
    break;
    
  // Case 9 is very similar to case 7. The only difference is that there is
  // an extra check for the two added parameters (-i and <file>). The rotors.ini
  // file will be created by this and then the same process as case 7 will occur.
  case 9:
    // checks if ALL proper flags exist and are given properly.
    if(((checkFlags(argv[1]) == 'e') || (checkFlags(argv[1]) == 'd')) && (checkFlags(argv[4]) == 'r') && (checkFlags(argv[7]) == 'i')) {
	if ((argv[2] != NULL) && (argv[3] != NULL)) {
	  inputFile = fopen(argv[2], "r"); //opening the input and output files
	  outputFile = fopen(argv[3], "w");
	  setUpIni(argv[8]);  // creating the rotors.ini needed for encryption/decryption
	  createRotors(rotor1, rotor2); // building rotors
	  configureRotor1(rotor1, atoi(argv[5])); // setting the rotors to thier inital positions
	  configureRotor2(rotor2, atoi(argv[6]));
	  if (checkFlags(argv[1]) == 'e') { // "e" signals for encryption
	    encryptFile(inputFile, outputFile, rotor1, rotor2);
	  }
	  else { // only other option (proven by earlier if statement) is "d" for decryption 
	    decryptFile(inputFile, outputFile, rotor1, rotor2);
	  }
	} 
	else { // displays the usage and exits when the file parameters are invalid
	  showUsageStatements();
	  exit(0);
	}
    }
    else { // displays the usage and exits when the -_ flag is invalid.
      showUsageStatements();
      exit(0);
    }
    break;

  default: // displays the usage and exits when the argument count is invalid
    showUsageStatements();
    exit(0);
  }
   return 0;
}

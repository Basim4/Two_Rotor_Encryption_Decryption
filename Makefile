# Author: Basim Khokhar
# Date: October 2023
# Description: This Makefile allows for the comilation and linkage 
#              of multiple .c file to create a full program written
#              in the C language. Each .c file is compiled alongside
#              a needed .h file (collection of forward declarations)
#              to create its respective .o file. Then, the .o files
#              are compiled together to create the executable aOut.

# The "make" command will see which .o files are needed to be compiled
# and will compile them. Then, the two_rotor_machine.exe executable 
# will be compiled by the listed .o files.
two_rotor_machine.exe: rotorDriver.o twoRotorEnigmaMachine.o
	gcc -g -Wall rotorDriver.o twoRotorEnigmaMachine.o -o two_rotor_machine.exe

# Will compile main().  
rotorDriver.o: rotorDriver.c
	gcc -g -Wall -c rotorDriver.c

# Will compile twoRotorEnigmaMachine.c alongside using the forward declarations
# provided from twoRotorEnigmaMachine.h.
twoRotorEnigmaMachine.o: twoRotorEnigmaMachine.c twoRotorEnigmaMachine.h
	gcc -g -Wall -c twoRotorEnigmaMachine.c

# "make clean" will remove all previously existing .o, .ini, and
# executable files.
clean:
	rm *.o *ini two_rotor_machine.exe

# Two_Rotor_Encryption_Decryption
C program written for the terminal. This is a Two Rotor Enigma Machine used to encrypt and decrypt text files. A configuration file must be provided
after the -i flag in the below usage statements. A configuration file has two lists of integers ranging from [0, 27]. Each number in this range must
be listed once per list and on thier own line. The two lists are separated by a blank line. See sampleConfig.rtr as an example. 

USAGE (after calling "make")
-----
 ./two_rotor_machine.exe -i (configurationFile)
 
 ./two_rotor_machine.exe -e (decryptedFile) (encryptedFileOutput) -r (turnRotor1XIntegertimes) (turnRotor2XIntegertimes)
 
 ./two_rotor_machine.exe -d (encryptedFile) (decryptedFileOutput) -r (turnRotor1XIntegertimes) (turnRotor2XIntegertimes)
 
 ./two_rotor_machine.exe -e (decryptedFile) (encryptedFileOutput) -r (turnRotor1XIntegertimes) (turnRotor2XIntegertimes) -i (configurationFile)
 
 ./two_rotor_machine.exe -d (encryptedFile) (decryptedFileOutput) -r (turnRotor1XIntegertimes) (turnRotor2XIntegertimes) -i (configurationFile)

In the order shown above, here is what each usage statement does: 
----

Creating only a rotors.ini file

encrypting a text file with an existing rotors.ini file in the current directory. Set how mnay times each respective rotors will turn before encryption.

decrypting a text file with an existing rotors.ini file in the current directory. Set how mnay times each respective rotors will turn before encryption.

encrypting a text file WITH NO existing rotors.ini file in the current directory. Set how mnay times each respective rotors will turn before encryption.

decrypting a text file WITH NO existing rotors.ini file in the current directory. Set how mnay times each respective rotors will turn before encryption.

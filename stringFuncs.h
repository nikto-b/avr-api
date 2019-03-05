
//#define bool uint8_t		//define for bool var because C has not bool or boolean variable
//#define byte uint8_t		//define for 8 bit var
#ifndef byte
	//#define byte uint8_t		//define for 8 bit var
#endif //ifndef byte

#ifndef bool
	//#define bool uint8_t		//define for bool var because C has not bool or boolean variable
#endif //ifndef bool

#include "stringFuncs.c"

byte getCountsOfDigits(int __number__); //get count of digits for int
byte getCountsOfDigits(long __number__); //get count of digits for long
byte getCountsOfDigits(byte __number__); //get count of digits for byte

int getCountsOfBits(int __in__);//get count if digits for int
    
char* dec2bin(int __in__);//convert dec num to bin C-string

int bin2dec(char* __in__);//convert bin num to dec int

int str2int(char* __in__);//convert C-string to int
long str2long(char* __in__);//convert C-string to long
byte str2byte(char* __in__);//convert C-string to byte

char* int2str(int __in__);//convert int var to char array
char* long2str(long __in__);//convert long var to char array
char* byte2str(byte __in__);//convert byte var to char array
char* bool2str(bool __in__);//convert bool var to char array


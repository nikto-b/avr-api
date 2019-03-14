#pragma once

#include "base.h"

//#define bool uint8_t		//define for bool var because C has not bool or boolean variable
//#define byte uint8_t		//define for 8 bit var
#ifndef byte
	#define byte uint8_t		//define for 8 bit var
#endif //ifndef byte

#ifndef bool
	#define bool uint8_t		//define for bool var because C has not bool or boolean variable
#endif //ifndef bool


byte getCountsOfDigits(int __number); //get count of digits for int
byte getCountsOfDigits(long __number); //get count of digits for long
byte getCountsOfDigits(byte __number); //get count of digits for byte

int getCountsOfBits(uint64_t __in);//get count if digits for int
    
char* dec2bin(uint64_t __in);//convert dec num to bin C-string

int bin2dec(char* __in);//convert bin num to dec int

int str2int(char* __in);//convert C-string to int
long str2long(char* __in);//convert C-string to long
byte str2byte(char* __in);//convert C-string to byte

char* int2str(int __in);//convert int var to char array
char* long2str(long __in);//convert long var to char array
char* byte2str(byte __in);//convert byte var to char array
char* bool2str(bool __in);//convert bool var to char array



bool contains(const char* _inbuf, uint16_t _len, char _ch);
bool contains(const char* _inbuf, char _ch);
uint16_t indexOf(const char* _in, char _c);
uint16_t indexOf(const char* _in, uint16_t _len, char _c);
char* strCut(const char* _in, uint16_t start, uint16_t end);
char* strSplit(const char* _in, char _opening, char _closing);
char* strSplit(const char* _in, uint16_t _len, char _opening, char _closing);

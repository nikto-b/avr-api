#pragma once

#include "settings.hpp"

#define USART_TX_BUF_LEN 100

#ifndef DEC
	#define DEC 0
#endif //ifndef DEC

#ifndef BIN
	#define BIN 1
#endif //ifndef DEC

#ifndef EOL
	#pragma message The EOL not defined! Using NULL
	#define EOL 0
#endif

	


//set bit settings of USART, mode on input
void USART0SetBitSettings(uint8_t __bitness);
//init function, baudrate on input
void USART0Begin(uint64_t __baud);


#pragma message "using USART output"

//send one char function
void USART0Send(unsigned char __data);

//send char array function
void USART0Print(const char* __data);
void USART0Print(int);
void USART0Print(long);
void USART0Print(unsigned long);
void USART0Print(int, int);
void USART0Println(int __data, byte __mode);

void USART0Println();
void USART0Println(const char* __data);
void USART0Println(int);
void USART0Println(long);
void USART0Println(unsigned long);
void USART0Println(int data, int mode);



#pragma message "using USART input"

//get recieved data
char USART0Read(void);
//get is any data recieved
bool USART0Available(void);
//remove all recieved data
void USART0Flush(void);

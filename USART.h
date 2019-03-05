#if USE_USART0 == 1

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
	
	#include "stringFuncs.h"
	#include "USARTModes.h"
	#include "USART.c"
		
	//set bit settings of USART, mode on input
	void USART0SetBitSettings(uint8_t);
	//init function, baudrate on input
	void USARTBegin(uint64_t);
	
	
	#if USE_USART0_OUTPUT == 1//if using output
		#pragma message "using USART output"
		
		//send one char function
		void USARTSend(unsigned char);
		
		//send char array function
		void USARTPrint(const char*);
		void USARTPrint(int);
		void USARTPrint(int, int);
		void USARTPrint(int, byte);
	#endif //if USE_USART0_OUTPUT == 1
	
	
	#if USE_USART0_INPUT == 1//if using input
		#pragma message "using USART input"
		
		//get recieved data
		char USARTRead(void);
		//get is any data recieved
		bool USART0Available(void);
		//remove all recieved data
		void USART0Flush(void);

	#endif //if USE_USART0_INPUT == 1


	
#endif //if USE_USART0 == 1



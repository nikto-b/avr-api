#if USE_USART0 == 1

	#ifndef DEC
		#define DEC 0
	#endif //ifndef DEC
	
	#ifndef BIN
		#define BIN 1
	#endif //ifndef DEC
	
	#include "stringFuncs.h"
	#include "USART.c"
	
	//init function, baudrate on input
	void USARTBegin(uint64_t _baud);
	
	
	#if USE_USART0_OUTPUT == 1//if using output
		#pragma message "using USART output"
		
		//send one char function
		void USARTSend(unsigned char);
		
		//send char array function
		void USARTPrint(char*);
		void USARTPrint(int);
		void USARTPrint(int, int);
		void USARTPrint(int, byte);
	#endif //if USE_USART0_OUTPUT == 1
	
	
	#if USE_USART0_INPUT == 1//if using input
		#pragma message "using USART input"
		
		//get recieved data
		char USARTRead(void);
	#endif //if USE_USART0_INPUT == 1


	
#endif //if USE_USART0 == 1



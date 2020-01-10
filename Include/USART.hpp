#pragma once

#include "settings.hpp"

#ifndef EOL
	#pragma message The EOL not defined! Using NULL
	#define EOL 0
#endif

namespace usart
{
	

	const uint8_t TX_BUF_LEN = 100;
	const uint8_t MAX_BUF_SIZE = 254;

	extern char txbuf [TX_BUF_LEN];
	extern uint16_t txbuf_len_start;
	extern uint16_t txbuf_len_end;



	extern volatile char _inputBuf_[];
	extern volatile uint8_t _inputBufCounterInput_;
	extern volatile uint8_t _inputBufCounterOutput_;
	extern volatile uint8_t _inputBufEmpty_;


	enum NumSys { DEC, BIN, OCT, HEX };

	enum Modes
	{
		CHAR_5B = 0,
		CHAR_6B = (1 << UCSZ00),
		CHAR_7B = (1 << UCSZ01),
		CHAR_8B = ((1 << UCSZ00) | (1 << UCSZ01)),
		CHAR_9B = ((1 << UCSZ00) | (1 << UCSZ01) | (1 << UCSZ02))
	};


	//set bit settings of USART, mode on input
	void setBitSettings(Modes bitness);
	//init function, baudrate on input
	void begin(uint64_t __baud);

	//send one char function
	void send(unsigned char __data);

	//send char array function
	void print(const char* __data);
	void print(int num);
	void print(long num);
	void print(unsigned long num);
	void println(int num, NumSys sys);

	void println();
	void println(const char* __data);
	void println(int num);
	void println(long num);
	void println(unsigned long num);
	void println(int data, NumSys sys);



	//get recieved data
	char read();
	//get is any data recieved
	bool available();
	//remove all recieved data
	void flush();

} // namespace usart

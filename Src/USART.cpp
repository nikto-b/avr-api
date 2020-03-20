#include "base.hpp"
#include "api.hpp"
#include "stringFuncs.hpp"
#include "USARTModes.hpp"
#include "customFuncAddr.hpp"
#include "USART.hpp"



namespace usart
{

	char txbuf [TX_BUF_LEN];
	uint16_t txbuf_len_start = 0;
	uint16_t txbuf_len_end = 0;

	/*
	* Function send
	* Desc     Send byte to USART0
	* Input    _data: byte to send
	* Output   none
	*/
	void send(unsigned char __data)			//send 1 byte to USART0
	{
		while(!(UCSR0A & (1 << UDRE0))){asm("NOP");}//TODO: send to buf and get with interrupt
		UDR0 = __data;
		/*
		* The transmit buffer can only be written
		* when the UDRE0 Flag in the UCSR0A Register is set
		* from atmega328p datasheet
		*/
	}

	/*
	* Function print
	* Desc     Send byte array to USART0
	* Input    __data: byte array to send
	* Output   none
	*/
	void print(const char* __data)	//send C-string to USART0
	{
		while(*__data != 0x00)
		{
			send(static_cast<uint8_t>(*(__data)));
			__data++;
		}
	}

	/*
	* Function print
	* Desc     Send byte array to USART0
	* Input    __data: byte array to send
	* Output   none
	*/
	void print(const unsigned char* __data)	//send C-string to USART0
	{
		while(*__data != 0x00)
		{
			send(static_cast<uint8_t>(*(__data)));
			__data++;
		}
	}

	/*
	* Function println
	* Desc     Send EndOfLine to USART0
	* Input    none
	* Output   none
	*/
	void println()
	{
		print(EOL);
	}

	/*
	* Function print
	* Desc     Convert to char array and send dec num to USART0
	* Input    __data: dec num
	* Output   none
	*/
	void print(int num)
	{
		char* __arr = int2str(num);
		print(__arr);
		free(__arr);
	}
	/*
	* Function print
	* Desc     Convert to char array and send dec num to USART0
	* Input    __data: dec num
	* Output   none
	*/
	void print(long __data)
	{
		char* __arr = long2str(__data);
		print(__arr);
		free(__arr);
	}
	/*
	* Function print
	* Desc     Convert to char array and send dec num to USART0
	* Input    __data: dec num
	* Output   none
	*/
	void print(unsigned long __data)
	{
		char* __arr = long2str(__data);
		print(__arr);
		free(__arr);
	}

	/*
	* Function print
	* Desc     Send num to USART0 with mode
	* Input    __data: num to send
	* 			__mode: mode used for sending num
	* Output   none
	*/
	void print(uint64_t __data, NumSys mode)
	{
		switch(mode)
		{
			case DEC:
			{
				print(static_cast<unsigned long>(__data));
				break;
			}
			case BIN:
			{
				char * ___arr;
				___arr = static_cast<char*>(dec2bin(__data));
				print(___arr);
				free(___arr);
				break;
			}
			default:
			{
				print(static_cast<unsigned long>(__data));
				break;
			}
		}
	}

	/*
	* Function println
	* Desc     Send to USART0 converted to char array num and EndOfLine
	* Input    __data: Num to send
	* Output   none
	*/
	void println(int __data)
	{
		print(__data);
		print(EOL);
	}
	/*
	* Function println
	* Desc     Send to USART0 converted to char array num and EndOfLine
	* Input    __data: Num to send
	* Output   none
	*/
	void println(long __data)
	{
		print(__data);
		print(EOL);
	}

	/*
	* Function println
	* Desc     Send num and EndOfLine to USART0 with mode
	* Input    __data: num to send
	* 			__mode: mode to send
	* Output   none
	*/
	void println(int __data, NumSys __mode)
	{
		print(static_cast<uint64_t>(__data), __mode);
		println();
	}
	/*
	* Function println
	* Desc     Send num and EndOfLine to USART0 with mode
	* Input    __data: num to send
	* 			__mode: mode to send
	* Output   none
	*/
	void println(long __data, NumSys __mode)
	{
		print(static_cast<uint64_t>(__data), __mode);
		println();
	}/*
	* Function println
	* Desc     Send num and EndOfLine to USART0 with mode
	* Input    __data: num to send
	* 			__mode: mode to send
	* Output   none
	*/
	void println(unsigned long __data, NumSys __mode)
	{
		print(static_cast<uint64_t>(__data), __mode);
		println();
	}

	/*
	* Function println
	* Desc     send char array and EndOfLine to USART0
	* Input    __data: char array to send
	* Output   none
	*/
	void println(const char* __data)
	{
		print(__data);
		print(EOL);
	}

	/*
	* Function println
	* Desc     send char array and EndOfLine to USART0
	* Input    __data: char array to send
	* Output   none
	*/
	void println(const unsigned char* __data)
	{
		print(__data);
		print(EOL);
	}

	/*
	* Function ISR(USART0_TX_vect)
	* Desc     Interrupt handler for vector USART0_TX
	* Input    interrupt vector
	* Output   none
	*/
	// #ifdef USART0_TX_vect
	// ISR(USART0_TX_vect)//interrupt handler called aftar transmitting data
	// #else
	// ISR(USART_TX_vect)//interrupt handler called aftar transmitting data
	// #endif
	inline void _ISR_TX()
	{
		// if(txbuf_len_start != txbuf_len_end)
		// {
		// 	UDR0 = txbuf[txbuf_len_start++];
		// }
		// else
		// {
		// 	txbuf_len_start = 0;
		// 	txbuf_len_end = 0;
		// }
		interrupt::call(interrupt::USART0_TX);
		/*#ifdef INTERRUPT_CUSTOMFUNCTX
			if(funcs[INTERRUPT_CUSTOMFUNCTX] != NULL)
				funcs[INTERRUPT_CUSTOMFUNCTX]();		//call custom function
		#endif
		*/
	}


	volatile char inputBuf[MAX_BUF_SIZE];//buffer for input from USART0
	volatile uint8_t inputBufCounterInput = 0;//index of last char placed by system
	volatile uint8_t inputBufCounterOutput = 0;//index of last char gotted by user
	volatile uint8_t inputBufEmpty = true;



	/*
	* Function ISR(USART0_RX_vect)
	* Desc     Interrupt handler for vector USART0_RX
	* Input    interrupt vector
	* Output   none
	*/
	// #ifdef USART0_RX_vect
	// ISR(USART0_RX_vect)		   //interrupt handler called after recieving data
	// #else
	// ISR(USART_RX_vect)		   //interrupt handler called after recieving data
	// #endif
	inline void _ISR_RX()
	{
		if(inputBufCounterInput >= MAX_BUF_SIZE	//check that counters are in borders of buf size
				|| inputBufEmpty)					//or buf empty
		{
			inputBufCounterInput = 0;				//start writing from zero
		}

		inputBuf[inputBufCounterInput] = static_cast<char>UDR0;	//save data

		if(inputBuf[inputBufCounterInput] != '\0')//check for garbage
		{
			inputBufEmpty = false;				//set empty flag down
			inputBufCounterInput++;				//go next index for writing
		}


		interrupt::call(interrupt::USART0_RX);
	}

	/*
	* Function read
	* Desc     Read byte recieved from USART0
	* Input    none
	* Output   Recieved byte
	*/
	char read()//get data from input USART0 buffer
	{
		if(inputBufCounterOutput >= MAX_BUF_SIZE)	//check that counters are in borders of buf size
		{
			inputBufCounterOutput = 0;				//start from zero
			inputBufEmpty = true;						//with empty buf
			return '\0';								//for bypassing -Wreturn-type
		}
		else if(inputBufCounterOutput >= inputBufCounterInput)//check that counter for output not overtaked input
		{
			char ___ret = inputBuf[inputBufCounterOutput];//save data to temp var
			inputBufCounterOutput = 0;						//set counters to zero
			inputBufCounterInput  = 0;
			inputBufEmpty = true;								//empty buf
			return ___ret;									//return data
		}
		else if(!inputBufEmpty)								//if have data
		{
			char ___ret = inputBuf[inputBufCounterOutput];//save data to temp var
			inputBufCounterOutput++;							//go to next index for reading
			if(inputBufCounterOutput >= MAX_BUF_SIZE)		//check that counter is in borders of buf size
			{
				inputBufCounterOutput = 0;					//start from zero
				inputBufEmpty = true;							//empty buf
			}
			return ___ret;									//return data
		}
		else
		{
			return '\0';					//ERROR
		}
	}

	/*
	* Function available
	* Desc     Return is recieved new byte
	* Input    none
	* Output   Have new state
	*/
	bool available()
	{
		if(inputBufCounterOutput >= inputBufCounterInput	//check that counter for output not overtaked input
		|| inputBufCounterOutput >= MAX_BUF_SIZE)
		{
			inputBufCounterOutput = 0;
			inputBufCounterInput  = 0;
			inputBufEmpty = true;								//empty buf
		}
		return !inputBufEmpty;
	}

	/*
	* Function flush
	* Desc     Clear USART0 registers
	* Input    none
	* Output   none
	*/
	void flush()
	{
		uint8_t __temp = 0;
		__temp = __temp;//for bypassing -Wunused-but-set-variable
		while(UCSR0A & (1 << RXC0))
		{
			__temp = UDR0;
			inputBufCounterInput = 0;
			inputBufCounterInput  = 0;
			inputBufEmpty = true;
		}
	}

	/*
	* Function setBitSettings
	* Desc     Set USART0 packet parameters
	* Input    __bitness: mode for transmitting
	* Output   none
	*/
	void setBitSettings(uint8_t __bitness)
	{
		UCSR0C = __bitness;
	}

	/*
	* Function begin
	* Desc     Initialize USART0
	* Input    __baud: baudrate for transmitting
	* Output   none
	*/
	void begin(uint64_t __baud)
	{
			for(int i = 0; i < MAX_BUF_SIZE; i++)//flush data array
			{
				inputBuf[i] = '\0';
			}

		UCSR0A = 1 <<  U2X0;									 //double speed mode
		uint16_t __baudPrescaller =  static_cast<uint16_t>((F_CPU / (8 * __baud)) - 1);//((Clock rate / (16 * baudrate))) - 1
															//for U2X0 mode:
															//((Clock rate / (8 * baudrate))) - 1
			if (((F_CPU == 16000000UL) && (__baud == 57600)) || (__baudPrescaller > 4095))	//disable double speed mode
			{																				//if prescaller is too high
				UCSR0A = 0;
				__baudPrescaller = static_cast<uint16_t>(F_CPU / (16 * __baud));
			}

		UBRR0L = static_cast<uint8_t>(__baudPrescaller);//set low bits of baud prescaller
		UBRR0H = static_cast<uint8_t>(__baudPrescaller >> 8);//set high bits of baud prescaller

		UCSR0B |= (1 << RXEN0) | (1 << RXCIE0);//enable recieve and interrupt on recieve

		UCSR0B |= (1 << TXEN0) | (1 << TXCIE0);//enable trancieve and interrupt on trancieve
												//TODO: changable bit size
		UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); //set USART0 Character Size to 8 bit
		/*
		* Character Size table:
		* 000 5-bit
		* 001 6-bit
		* 010 7-bit
		* 011 8-bit
		* 100 Reserved
		* 101 Reserved
		* 110 Reserved
		* 111 9-bit
		*/
	}


}

#ifdef USART0_TX_vect
ISR(USART0_TX_vect)//interrupt handler called aftar transmitting data
#else
ISR(USART_TX_vect)//interrupt handler called aftar transmitting data
#endif
{
	usart::_ISR_TX();
}


#ifdef USART0_RX_vect
ISR(USART0_RX_vect)		   //interrupt handler called after recieving data
#else
ISR(USART_RX_vect)		   //interrupt handler called after recieving data
#endif
{
	usart::_ISR_RX();
}
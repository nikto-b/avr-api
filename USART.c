#if USE_USART0 == 1

	#if USE_USART0_OUTPUT == 1

		void USART0Send(char __data__)			//send 1 byte to USART0
		{
			while(!(UCSR0A & (1 << UDRE0))){}
			UDR0 = __data__;
			/*
			 * The transmit buffer can only be written
			 * when the UDRE0 Flag in the UCSR0A Register is set
			 * from atmega328p datasheet
			 */
		}

		void USART0Print(char* __data__)	//send C-string to USART0
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(__data__ == 0) return;
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			uint8_t __temp__ = 0;
			while(__data__[__temp__] != 0x00)
			{
				USART0Send(__data__[__temp__]);
				__temp__++;
			}
		}

		void USART0Print(int __data__)
		{
			char* arr = int2str(__data__);
			USART0Print(arr);
			free(arr);
		}

		void USART0Print(int __data__, byte __mode__)
		{
			switch(__mode__)
			{
				case DEC:
				{
					USART0Print(__data__);
					break;
				}
				case BIN:
				{
					char* arr = dec2bin(__data__);
					USART0Print(arr);
					free(arr);
					break;
				}
				default:
				{
					USART0Print(__data__);
					break;
				}
			}
		}

		inline void USART0Println(int __data__)
		{
			USART0Print(__data__);
			USART0Send('\n');
		}

		inline void USART0Println(int __data__, byte __mode__)
		{
			USART0Print(__data__, __mode__);
			USART0Send('\n');
		}

		inline void USART0Println(char* __data__)
		{
			USART0Print(__data__);
			//USART0Send('\n');
			USART0Print(EOL);
		}

		inline void USART0Println()
		{
			USART0Send('\n');
		}

		ISR(USART0_TX_vect)//interrupt handler called aftar transmitting data
		{
			if(funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] != NULL)
				funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR]();		//call custom function
		}

	#endif //if USE_USART0_OUTPUT == 1


	#if USE_USART0_INPUT == 1

		#define _MAX_BUF_SIZE_ 256

		char _inputBuf_[_MAX_BUF_SIZE_];//buffer for input from USART0
		uint8_t _inputBufCounterInput_ = 0;//index of last char placed by system
		uint8_t _inputBufCounterOutput_ = 0;//index of last char gotted by user
		uint8_t _inputBufEmpty_ = true;



		ISR(USART0_RX_vect)		   //interrupt handler called after recieving data
		{
			if(_inputBufCounterInput_ >= _MAX_BUF_SIZE_	//check that counters are in borders of buf size
					|| _inputBufEmpty_)					//or buf empty
			{
				_inputBufCounterInput_ = 0;				//start writing from zero
			}

			_inputBuf_[_inputBufCounterInput_] = UDR0;	//save data

			if(_inputBuf_[_inputBufCounterInput_] != NULL)//check for garbage
			{
				_inputBufEmpty_ = false;				//set empty flag down
				_inputBufCounterInput_++;				//go next index for writing
			}

			if(funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] != NULL)
				funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR]();//call custom function
		}

		char USART0Read()//get data from input USART0 buffer
		{
			if(_inputBufCounterOutput_ >= _MAX_BUF_SIZE_)	//check that counters are in borders of buf size
			{
				_inputBufCounterOutput_ = 0;				//start from zero
				_inputBufEmpty_ = true;						//with empty buf
			}
			else if(_inputBufCounterOutput_ >= _inputBufCounterInput_)//check that counter for output not overtaked input
			{
				char ___ret___ = _inputBuf_[_inputBufCounterOutput_];//save data to temp var
				_inputBufCounterOutput_ = 0;						//set counters to zero
				_inputBufCounterInput_  = 0;
				_inputBufEmpty_ = true;								//empty buf
				return ___ret___;									//return data
			}
			else if(!_inputBufEmpty_)								//if have data
			{
				char ___ret___ = _inputBuf_[_inputBufCounterOutput_];//save data to temp var
				_inputBufCounterOutput_++;							//go to next index for reading
				if(_inputBufCounterOutput_ >= _MAX_BUF_SIZE_)		//check that counter is in borders of buf size
				{
					_inputBufCounterOutput_ = 0;					//start from zero
					_inputBufEmpty_ = true;							//empty buf
				}
				return ___ret___;									//return data
			}
			else
			{
				return NULL;					//ERROR
			}
		}

		bool USART0Available()
		{
			if(_inputBufCounterOutput_ >= _inputBufCounterInput_	//check that counter for output not overtaked input
			|| _inputBufCounterOutput_ >= _MAX_BUF_SIZE_)
			{
				_inputBufCounterOutput_ = 0;
				_inputBufCounterInput_  = 0;
				_inputBufEmpty_ = true;								//empty buf
			}
			return !_inputBufEmpty_;
		}
		
		void USART0Flush()
		{
			uint8_t __temp__;
			while(UCSR0A & (1 << RXC0))
			{
				__temp__ = UDR0;
				_inputBufCounterInput_ = 0;
				_inputBufCounterInput_  = 0;
				_inputBufEmpty_ = true;
			}
		}

	#endif //if USE_USART0_INPUT == 1

	void USART0SetBitSettings(uint8_t __bitness)
	{
		#if USE_FUNC_INPUT_PROTECTOR == 1
			if(__bitness == USART0_CHAR_5B
			|| __bitness == USART0_CHAR_6B
			|| __bitness == USART0_CHAR_7B
			|| __bitness == USART0_CHAR_8B
			|| __bitness == USART0_CHAR_9B)
				UCSR0C = __bitness;
		#else //if USE_FUNC_INPUT_PROTECTOR == 1
		UCSR0C = __bitness;
		#endif //if USE_FUNC_INPUT_PROTECTOR != 1
	}

	void USART0Begin(uint64_t __baud)
	{
		#if USE_USART0_INPUT == 1

			for(int i = 0; i < _MAX_BUF_SIZE_; i++)
			{
				_inputBuf_[i] = NULL;
			}
		#endif //if USE_USART0_INPUT == 1

		UCSR0A = 1 <<  U2X0;									 //double speed mode
		uint16_t __baudPrescaller =  ((F_CPU / (8 * __baud))) - 1;//((Clock rate / (16 * baudrate))) - 1
															   //for U2X0 mode:
															  //((Clock rate / (8 * baudrate))) - 1
		#if USE_SERIAL_FASTBAUD == 1
			if (((F_CPU == 16000000UL) && (__baud == 57600)) || (__baudPrescaller > 4095))	//disable double speed mode
			{																				//if prescaller is too high
				UCSR0A = 0;
				__baudPrescaller = (F_CPU / (16 * __baud));
			}
		#endif //if USE_SERIAL_FASTBAUD == 1

		UBRR0L = (uint8_t)(__baudPrescaller);//set low bits of baud prescaller
		UBRR0H = (uint8_t)(__baudPrescaller>>8);//set high bits of baud prescaller

		#if USE_USART0_INPUT == 1
			UCSR0B |= (1 << RXEN0) | (1 << RXCIE0);//enable recieve and interrupt on recieve
		#endif //if USE_USART0_INPUT == 1

		#if USE_USART0_OUTPUT == 1
			UCSR0B |= (1 << TXEN0) | (1 << TXCIE0);//enable trancieve and interrupt on trancieve
		#endif //if USE_USART0_OUTPUT == 1		  //
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


#endif //if USE_USART0 == 1

#if USE_USART0 == 1

	#if USE_USART0_OUTPUT == 1
	
		void USARTSend(char data)			//send 1 byte to USART
		{	
			while(!(UCSR0A & (1 << UDRE0))){}
			UDR0 = data;
			/*
			 * The transmit buffer can only be written 
			 * when the UDRE0 Flag in the UCSR0A Register is set 
			 * from atmega328p datasheet
			 */
		}
		
		
		void USARTPrint(char* _data)	//send C-string to USART
		{	
			while(*_data != 0x00)
			{
				USARTSend(*_data);
				_data++;
			}
		}
		
		
		ISR(USART0_TX_vect)//interrupt handler called aftar transmitting data
		{			
			if(funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] != NULL)
				funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR]();		//call custom function 		
		}
		
	#endif //if USE_USART0_OUTPUT == 1
	
	
	#if USE_USART0_INPUT == 1
		
		#ifndef _MAX_BUF_SIZE_
			#define _MAX_BUF_SIZE_ 256
		#endif //ifndef _MAX_BUF_SIZE_
		
		char _inputBuf_[_MAX_BUF_SIZE_];//buffer for input from USART
		uint8_t _inputBufCounterInput_ = 0;//index of last char placed by system
		uint8_t _inputBufCounterOutput_ = 0;//index of last char gotted by user
		uint8_t _inputBufEmpty_ = false;
		
		unsigned char USARTData = 0;//input USART buffer
		ISR(USART0_RX_vect)	       //TODO: define all interrupt vectors
		{						  //interrupt handler called after recieving data
			
			if(_inputBufCounterInput_ >= _MAX_BUF_SIZE_
					|| _inputBufEmpty_)
			{
				_inputBufCounterInput_ = 0;
			}
			
			_inputBuf_[_inputBufCounterInput_] = UDR0;
			_inputBufCounterInput_++;
			
			if(funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] != NULL)
				funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR]();//call custom function
		}
		
		char USARTRead()//get data from input USART buffer
		{
			char __ret = _inputBuf_[_inputBufCounterOutput_];	//save data from buf
			_inputBuf_[_inputBufCounterOutput_] = NULL;			//delete data in buf
			_inputBufCounterOutput_++;
			if(_inputBufCounterOutput_ >= _MAX_BUF_SIZE_
			|| _inputBufCounterOutput_ >= _inputBufCounterInput_)
			{
				_inputBufCounterOutput_ = 0;
				_inputBufCounterInput_ = 0;
				_inputBufEmpty_ = true;
			}
			else if(!_inputBufEmpty_)
			{
				return __ret;
			}
			return NULL;
		}
		
		bool USARTAvailable()
		{
			return _inputBufEmpty_;
		}

	#endif //if USE_USART0_INPUT == 1


	void USARTBegin(uint64_t _baud)
	{		
		UCSR0A = 1 <<  U2X0;									 //double speed mode
		uint16_t _baudPrescaller =  ((F_CPU / (8 * _baud))) - 1;//((Clock rate / (16 * baudrate))) - 1
															   //for U2X0 mode: 
															  //((Clock rate / (8 * baudrate))) - 1
		#if USE_SERIAL_FASTBAUD == 1
			if (((F_CPU == 16000000UL) && (_baud == 57600)) || (_baudPrescaller > 4095))	//disable double speed mode
			{																				//if prescaller is too high
				UCSR0A = 0;
				_baudPrescaller = (F_CPU / (16 * _baud));
			}
		#endif //if USE_SERIAL_FASTBAUD == 1
		
		UBRR0L = (uint8_t)(_baudPrescaller);//set low bits of baud prescaller
		UBRR0H = (uint8_t)(_baudPrescaller>>8);//set high bits of baud prescaller
		
		#if USE_USART0_INPUT == 1
			UCSR0B |= (1 << RXEN0) | (1 << RXCIE0);//enable recieve and interrupt on recieve
		#endif //if USE_USART0_INPUT == 1
		
		#if USE_USART0_OUTPUT == 1
			UCSR0B |= (1 << TXEN0) | (1 << TXCIE0);//enable trancieve and interrupt on trancieve
		#endif //if USE_USART0_OUTPUT == 1		  //
												 //TODO: changable bit size
		UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); //set USART Character Size to 8 bit
		/*
		 * ATMEGA328P Character Size table:
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

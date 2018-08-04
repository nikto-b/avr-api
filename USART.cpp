#if USE_USART0 == 1

	#if USE_USART0_OUTPUT == 1
	
		#define _MAX_BUF_SIZE_ 256
		
		char _outputBuff_[_MAX_BUF_SIZE_];	//buffer for output into USART
		uint16_t _outputBufCounterInput_;	//index of last char placed by user
		uint16_t _outputBufCounterOutput_;	//index of last char gotted by system
		uint8_t _outputEmpty_ = true;		//lock of TX flag
		
		void USARTSend(char data)			//send 1 byte to USART
		{	
			/*
			 * The transmit buffer can only be written 
			 * when the UDRE0 Flag in the UCSR0A Register is set 
			 * from atmega328p datasheet
			 */

			if(_outputEmpty_ == true		//if TX unlocked
			&& (UCSR0A & (1<<UDRE0)))		//and transmitter prepared
			{
				_outputEmpty_ = false;			//lock TX
				_outputBufCounterInput_  = 0;	//set counters
				_outputBufCounterOutput_ = 0;	//to zero
				UDR0 = data;					//write byte to TX
			}
			else
			{
				if(_outputBufCounterInput_ >= _MAX_BUF_SIZE_)//start from zero if 
				{											//counter out of range
					_outputBufCounterInput_ = 0;
				}
				_outputBuff_[_outputBufCounterInput_] = data;	//write data to buf				
				_outputBufCounterInput_++;						//go to next index
			}
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
			if(_outputEmpty_ == false							//if TX locked
			&& _outputBufCounterOutput_ < _MAX_BUF_SIZE_			//and counter in range
			&& _outputBuff_[_outputBufCounterOutput_] != NULL)	//and have char to transmit
			{
				UDR0 = _outputBuff_[_outputBufCounterOutput_];		//send data from buf to USART reg
				*(_outputBuff_ + _outputBufCounterOutput_) = NULL;	//remove data from buf
				_outputBufCounterOutput_++;							//go to next data index
				_outputEmpty_ = false;								//lock TX
			}
			else if(_outputBuff_[_outputBufCounterOutput_] == NULL)	//if  have no char for transmitting
			{
				_outputEmpty_ = true;			//unlock TX
				_outputBufCounterOutput_ = 0;	//set counters
				_outputBufCounterInput_  = 0;	//to zero
			}									//and prepare to start transmitting again
			
			if(funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] != NULL)
				funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR]();		//call custom function 		
		}
		
	#endif //if USE_USART0_OUTPUT == 1
	
	
	#if USE_USART0_INPUT == 1
		
		#ifndef _MAX_BUF_SIZE_
			#define _MAX_BUF_SIZE_ 256
		#endif //ifndef _MAX_BUF_SIZE_
		
		unsigned char* _inputBuf_;//buffer for input from USART
		uint8_t _inputBufCounterInput_ = 0;//index of last char placed by system
		uint8_t _inputBufCounterOutput_ = 0;//index of last char gotted by user
		
		unsigned char USARTData = 0;//input USART buffer
		ISR(USART0_RX_VECT)		//TODO: define all interrupt vectors
		{		//interrupt handler called after recieving data
			
			if(_inputBufCounterInput_ >= _MAX_BUF_SIZE_)
				_inputBufCounterInput_ = 0;
			
			_inputBuf_[_inputBufCounterInput_] = UDR0;
			_inputBufCounterInput_++;
			
			if(funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] != NULL)
				funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR]();//call custom function
		}
		
		char USARTRead()
		{	//get data from input USART buffer
			return USARTData;
		}

	#endif //if USE_USART0_INPUT == 1


	void USARTBegin(uint64_t _baud)
	{
		#if USE_USART0_OUTPUT
			if(_outputBuff_ == NULL)
			{
				PORTB = 1 << PB7;
			}
			for(int i = 0; i < _MAX_BUF_SIZE_; i++)
			{
				_outputBuff_[i] = 0;
			}
			_outputBufCounterInput_  = 0;
			_outputBufCounterOutput_ = 0;
		#endif //if USE_USART0_OUTPUT
		
		UCSR0A = 1 <<  U2X0;									//double speed mode
		uint16_t _baudPrescaller =  ((F_CPU / (8 * _baud))) - 1;//((Clock rate / (16 * baudrate))) - 1
																 //for U2X0 mode: 
																 //   ((Clock rate / (8 * baudrate))) - 1
		/*#if USE_SERIAL_FASTBAUD == 1
			#pragma message "using fast baud"				//TODO:check U2X0 mode and cleanup
			if (((F_CPU == 16000000UL) && (_baud == 57600)) || (_baudPrescaller >4095))
			{
				UCSR0A = 0;
				_baudPrescaller = (F_CPU / (16 * _baud));
			}
		#endif*/
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

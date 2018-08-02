#if USE_USART0 == 1

	
	void USARTBegin(uint64_t _baud)
	{
		//UCSR0A = 1 <<  U2X0;
		uint16_t _baudPrescaller =  ((F_CPU / (16 * _baud))) - 1;//((Clock rate / (16 * baudrate))) - 1
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
		#endif
		
		#if USE_USART0_OUTPUT == 1
			UCSR0B |= (1 << TXEN0) | (1 << TXCIE0);//enable trancieve and interrupt on trancieve
		#endif									  //
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
	
	#if USE_USART0_OUTPUT == 1
		void USARTSend(unsigned char data)
		{
			while(!(UCSR0A & (1<<UDRE0)));//just wait cycle
			/*
			 * The transmit buffer can only be written 
			 * when the UDRE0 Flag in the UCSR0A Register 
			 * is set (c)atmega328p datasheet
			 */
			UDR0 = data;//send data to USART data register
		}
		
		void USARTPrint(char* _data)
		{//send C-string to USART
			while(*_data != 0x00)
			{
				USARTSend(*_data);
				_data++;
			}
		}
		ISR(USART0_TX_VECT)//interrupt called aftar transmitting data
		{
			if(funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] != NULL)
				funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR]();//call custom function		
		}
	#endif //if USE_USART0_OUTPUT == 1
	
	
	#if USE_USART0_INPUT == 1
	
		unsigned char USARTData = 0;//input USART buffer
		ISR(USART0_RX_VECT)		//TODO: define all interrupt vectors
		{		//interrupt called after recieving data
			USARTData = UDR0;//save data to input buffer
			if(funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] != NULL)
				funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR]();//call custom function
		}
		
		char USARTRead()
		{//get data from input USART buffer
			return USARTData;
		}

	#endif //if USE_USART0_INPUT == 1


#endif //if USE_USART0 == 1

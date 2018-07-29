#if USE_USART0 == 1

	
	void USARTBegin(uint64_t _baud)
	{
		//UCSR0A = 1 <<  U2X0;
		uint16_t _baudPrescaller =  ((F_CPU / (16 * _baud))) - 1;
		/*#if USE_SERIAL_FASTBAUD == 1
			#pragma message "using fast baud"
			if (((F_CPU == 16000000UL) && (_baud == 57600)) || (_baudPrescaller >4095))
			{
				UCSR0A = 0;
				_baudPrescaller = (F_CPU / (16 * _baud));
			}
		#endif*/
		UBRR0L = (uint8_t)(_baudPrescaller);
		UBRR0H = (uint8_t)(_baudPrescaller>>8);
		
		#if USE_USART0_INPUT == 1
			UCSR0B |= (1 << RXEN0) | (1<<RXCIE0);
		#endif
		
		#if USE_USART0_OUTPUT == 1
			UCSR0B |= (1 << TXEN0);
		#endif
		
		UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	}
	
	#if USE_USART0_OUTPUT == 1
		void USARTSend(unsigned char data)
		{
			while(!(UCSR0A & (1<<UDRE0)));//just wait cycle
			UDR0 = data;
		}
		
		void USARTPrint(char* _data)
		{
			while(*_data != 0x00)
			{
				USARTSend(*_data);
				_data++;
			}
		}
		ISR(USART0_TX_VECT)
		{
			if(funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] != NULL)
				funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR]();			
		}
	#endif //if USE_USART0_OUTPUT == 1
	
	
	#if USE_USART0_INPUT == 1
	
		unsigned char USARTData = 0;
		ISR(USART0_RX_VECT)		//TODO: define all interrupt vectors
		{
			USARTData = UDR0;
			if(funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] != NULL)
				funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR]();
		}
		
		char USARTRead()
		{
			return USARTData;
		}

	#endif //if USE_USART0_INPUT == 1


#endif //if USE_USART0 == 1

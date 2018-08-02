

#if USE_TIMERS == 1
	#if defined(TCCR0A)//if mcu have TIMER0
		#pragma message "TIMER0 found"
		
		void TIMER0Init(uint8_t _mode, uint8_t _clockSource, uint8_t _count)
		{
			TCCR0B = 0;
			TIMSK0 = 0;//set param regs to zero
			
			TCCR0B |= _mode;//set mode
			
			#if TIMER0_USE_COMPA == 1
				TIMSK0 |= (1<<OCIE0A);//enable interrupt on compare with A num
			#endif //if TIMER0_USE_COMPA == 1
			
			#if TIMER0_USE_COMPB == 1
				TIMSK0 |= (1<<OCIE0B);//enable interrupt on compare with B num
			#endif //if TIMER0_USE_COMPB == 1
			
			#if TIMER0_USE_OVF == 1
				TIMSK0 |= (1 << TOIE0);//enable interrupt on overflow
			#endif //if TIMER0_USE_OVF == 1
			
			//TODO: add setters for A and B nums
			
			OCR0A = (uint8_t)_count;//set A num
			
			//OCR0AL = (uint8_t)(_count >> 8);//set low registers of num //(legacy code)
			TCCR0B |= _clockSource;//set clock source
		}
		
		#if TIMER0_USE_COMPA == 1//if using interrupt on compare with A num
		//TODO: send all interrupt vectors to a .h file
			ISR(TIMER0_COMPA_vect)//COMPA interrupt handler
			{
				if(funcs[TIMER0_COMPA_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER0_COMPA_CUSTOMFUNC_ADDR]();//call custom function
			}
		#endif //if TIMER0_USE_COMPA == 1
		
		#if TIMER0_USE_COMPB == 1//if using interrupt on compare with B num
			ISR(TIMER0_COMPB_vect)//COMPB interrupt handler
			{
				if(funcs[TIMER0_COMPB_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER0_COMPB_CUSTOMFUNC_ADDR]();//call custom function
			}
		#endif //if TIMER0_USE_COMPB == 1
		
		#if TIMER0_USE_OVF == 1//if using interrupt on overflow
			ISR(TIMER0_OVF_vect)//OVF interrupt handler
			{
				if(funcs[TIMER0_OVF_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER0_OVF_CUSTOMFUNC_ADDR]();//call custom function
			}
		#endif //if TIMER0_USE_OVF == 1
		
	#endif //if defined(TCCR0A)


	#if defined(TCCR1A)//if mcu have TIMER1
		#pragma message "TIMER1 found"
		
		void TIMER1Init(uint8_t _mode, uint8_t _clockSource, uint16_t _count)
		{
			TCCR1B = 0;
			TIMSK1 = 0;//set settings registers to zero
			
			TCCR1B |= _mode;//set mode of timer
			
			#if TIMER1_USE_COMPA == 1
				TIMSK1 |= (1<<OCIE0A);//enable interrupt on compare with A num
			#endif //if TIMER1_USE_COMPA == 1
			
			#if TIMER1_USE_COMPB == 1
				TIMSK1 |= (1<<OCIE0B);//enable interrupt on compare with B num
			#endif //if TIMER1_USE_COMPB == 1
			
			#if TIMER1_USE_OVF == 1
				TIMSK1 |= (1 << TOIE0);//enable interrupt on overflow
			#endif //if TIMER1_USE_OVF == 1
			
			OCR1A = (uint8_t)_count;//set num to counter reg of timer
			
			//OCR0AH = (uint8_t)_count;//legacy
			//OCR0AL = (uint8_t)(_count >> 8);
			//OCR0AL = (uint8_t)(_count >> 8);
			TCCR1B |= _clockSource;//set clock source
		}
		
		#if TIMER1_USE_COMPA == 1//if using interrupt on compare with A num
			ISR(TIMER1_COMPA_vect)//COMPA interrupt handler
			{
				if(funcs[TIMER1_COMPA_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER1_COMPA_CUSTOMFUNC_ADDR]();//call custom function
			}
		#endif //if TIMER1_USE_COMPA == 1
		
		#if TIMER0_USE_COMPB == 1//if using interrupt on compare with B num
			ISR(TIMER1_COMPB_vect)//COMPB interrupt handler
			{
				if(funcs[TIMER1_COMPB_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER1_COMPB_CUSTOMFUNC_ADDR]();//call custom function
			}
		#endif //if TIMER0_USE_COMPB == 1
		
		#if TIMER1_USE_OVF == 1//if using interrupt on overflow
			ISR(TIMER1_OVF_vect)//OVF interrupt handler
			{
				if(funcs[TIMER1_OVF_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER1_OVF_CUSTOMFUNC_ADDR]();//call custom function
			}
		#endif //if TIMER1_USE_OVF == 1
		
	#endif //if defined(TCCR1A)


	//TODO: refactor
	/*
	#if defined(TCCR2A)
		#pragma message "TIMER2 found"
		#define pwmTimer2(_val) if(_val > 0 && _val < 255){ sbi(TCCR2A, COM2A1); OCR2A = _val; }//else HIGH or LOW signal
		
		#if TIMER2_USE_COMPA == 1
			ISR(TIMER2_COMPA_vect)
			{
				if(funcs[TIMER2_COMPA_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER2_COMPA_CUSTOMFUNC_ADDR]();
			}
		#endif
		
		#if TIMER2_USE_COMPB == 1
			ISR(TIMER2_COMPB_vect)
			{
				if(funcs[TIMER2_COMPB_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER2_COMPB_CUSTOMFUNC_ADDR]();
			}
		#endif
		
		#if TIMER2_USE_OVF == 1
			ISR(TIMER2_OVF_vect)
			{
				if(funcs[TIMER2_OVF_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER2_OVF_CUSTOMFUNC_ADDR]();
			}
		#endif
	#endif //if defined(TCCR2A)
	*/
		
#endif //if USE_TIMERS == 1



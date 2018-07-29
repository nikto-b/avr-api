

#if USE_TIMERS == 1
	#if defined(TCCR0A)
		#pragma message "TIMER0 found"
		
		void TIMER0Init(uint8_t _mode, uint8_t _clockSource, uint8_t _count)
		{
			TCCR0B = 0;
			TIMSK0 = 0;
			TCCR0B |= _mode;
			#if TIMER0_USE_COMPA == 1
				TIMSK0 |= (1<<OCIE0A);
			#endif
			#if TIMER0_USE_COMPB == 1
				TIMSK0 |= (1<<OCIE0B);
			#endif
			#if TIMER0_USE_OVF == 1
				TIMSK0 |= (1 << TOIE0);
			#endif
			OCR0A = (uint8_t)_count;
			//OCR0AL = (uint8_t)(_count >> 8);
			TCCR0B |= _clockSource;
		}
		
		#if TIMER0_USE_COMPA == 1
			ISR(TIMER0_COMPA_vect)
			{
				if(funcs[TIMER0_COMPA_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER0_COMPA_CUSTOMFUNC_ADDR]();
			}
		#endif
		
		#if TIMER0_USE_COMPB == 1
			ISR(TIMER0_COMPB_vect)
			{
				if(funcs[TIMER0_COMPB_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER0_COMPB_CUSTOMFUNC_ADDR]();
			}
		#endif
		
		#if TIMER0_USE_OVF == 1
			ISR(TIMER0_OVF_vect)
			{
				if(funcs[TIMER0_OVF_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER0_OVF_CUSTOMFUNC_ADDR]();
			}
		#endif
		
	#endif


	#if defined(TCCR1A)
		#pragma message "TIMER1 found"
		
		void TIMER1Init(uint8_t _mode, uint8_t _clockSource, uint16_t _count)
		{
			TCCR0B = 0;
			TIMSK0 = 0;
			TCCR0B |= _mode;
			#if TIMER0_USE_COMPA == 1
				TIMSK0 |= (1<<OCIE0A);
			#endif
			#if TIMER0_USE_COMPB == 1
				TIMSK0 |= (1<<OCIE0B);
			#endif
			#if TIMER0_USE_OVF == 1
				TIMSK0 |= (1 << TOIE0);
			#endif
			OCR0A = (uint8_t)_count;
			//OCR0AH = (uint8_t)_count;
			//OCR0AL = (uint8_t)(_count >> 8);
			//OCR0AL = (uint8_t)(_count >> 8);
			TCCR0B |= _clockSource;
		}
		
		#if TIMER1_USE_COMPA == 1
			ISR(TIMER1_COMPA_vect)
			{
				if(funcs[TIMER1_COMPA_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER1_COMPA_CUSTOMFUNC_ADDR]();
			}
		#endif
		
		#if TIMER0_USE_COMPB == 1
			ISR(TIMER1_COMPB_vect)
			{
				if(funcs[TIMER1_COMPB_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER1_COMPB_CUSTOMFUNC_ADDR]();
			}
		#endif
		
		#if TIMER1_USE_OVF == 1
			ISR(TIMER1_OVF_vect)
			{
				if(funcs[TIMER1_OVF_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER1_OVF_CUSTOMFUNC_ADDR]();
			}
		#endif
		
		#endif
	#endif


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
#endif



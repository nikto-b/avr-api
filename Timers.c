#if USE_TIMERS == 1
	
	#ifdef TCCR0A //if defined T/C0
		/*
		 * Function TIMER0Init
		 * Desc     init T/C0
		 * Input    _com: what Compare Output Mode use to
		 *			_wfmode: what Waveform generation mode use to
		 *			_clk: what clock source use to
		 * Output   none
		 */
		void TIMER0Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk)
		{
			TCCR0A = _wfmode | _com;
			TCCR0B = _clk & TIMER0_CLK_SRC_MASK;
		}

		/*
		 * Function TIMER0SetCLK
		 * Desc     Change clock source in T/C0
		 * Input    _clk: what clk change to
		 * Output   none
		 */		
		void TIMER0SetCLK(uint8_t _clk)
		{
			TCCR0B &= ~TIMER0_CLK_SRC_MASK;
			TCCR0B |= _clk & TIMER0_CLK_SRC_MASK;
		}

		#if 1 == 1

			/*
			 * Function: ISR(TIMER0_COMPA_vect)
			 * Desc: Interrupt handler for T/C0 Compare with A
			 * Input: interrupt vector
			 * Output: none
			 */
			ISR(TIMER0_COMPA_vect)
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC0_COMPA);
			}

			#ifdef OCR0AL
					/*
					 * Function TIMER0SetA
					 * Desc     Set A num of T/C0
					 * Input    __A: what num set to
					 * Output   none
					*/
					void TIMER0SetA(uint16_t __A)
					{
						OCR0AH = (uint8_t)__A;		//set high registers of num
						OCR0AL = (uint8_t)(__A >> 8);	//set low registers of num
					}
				#else //ifdef OCR0AL
					/*
					 * Function TIMER0SetA
					 * Desc     set A num of T/C0
					 * Input    __A: what num set to
					 * Output   none
					*/
					void TIMER0SetA(uint8_t __A)
					{
						OCR0A = (uint8_t)__A;//set B num
					}
				#endif //ifndef OCR0AL
				/*
				 * Function TIMER0EnableCOMAInterrupt
				 * Desc     enable interrupt on compare with A num
				 * Input    none
				 * Output   none
				*/
				inline void TIMER0EnableCOMPAInterrupt(void)
				{
					TIMSK0 = (TIMSK0 & ~(1 << OCIE0A)) | (1 << OCIE0A);//enable interrupt on compare with A num
				}

				/*
				 * Function TIMER0DisableCOMPAInterrupt
				 * Desc     Disable interrupt on compare with A num
				 * Input    none
				 * Output   none
				*/
				inline void TIMER0DisableCOMPAInterrupt(void)
				{
					TIMSK0 &= ~(1 << OCIE0A);//disable interrupt on compare with A num
				}
			#endif //if TIMER0_USE_COMPA == 1
		
	#endif //ifdef TCCR0A

	#ifdef TCCR3A //if defined T/C3
		/*
		 * Function TIMER3Init
		 * Desc     init T/C3
		 * Input    __mode: what mode of T/C3
		 * Output   none
		 */
		void TIMER3Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk)
		{
			TCCR3A = _wfmode | _com;
			TCCR3B = _clk;
		}
		
	#endif //ifdef TCCR3A

#endif //if USE_TIMERS == 1
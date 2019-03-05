#if USE_TIMERS == 1

















#if USE_LEGACY_VER == 0 || !defined(USE_LEGACY_VER)



	#define GENINIT(n)												\
	/*															*/	\
	/* Function TIMERnInit										*/	\
	/* Desc     init T/Cn 										*/	\
	/* Input    _com: what Compare Output Mode use to 			*/	\
	/*			_wfmode: what Waveform generation mode use to 	*/	\
	/*			_clk: what clock source use to 					*/	\
	/* Output   none	 										*/	\
	/**/																\
	void TIMER ## n ## Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk)\
	{																\
		TCCR ## n ## A = _wfmode | _com;							\
		TCCR ## n ## B = _clk & TIMER ## n ## _CLK_SRC_MASK;		\
	}


	#define GENSETCLK(n)											\
	/*															*/	\
	/* Function TIMERnSetCLK									*/	\
	/* Desc     Change clock source in T/Cn 					*/	\
	/* Input    _clk: what clk change to 						*/	\
	/* Output   none 											*/	\
	/**/															\
	void TIMER ## n ## SetCLK(uint8_t _clk)							\
	{																\
		TCCR ## n ## B &= ~TIMER ## n ## _CLK_SRC_MASK;				\
		TCCR ## n ## B |= _clk & TIMER ## n ## _CLK_SRC_MASK;		\
	}

	#define GENISR_COMPk(n, k)										\
	/*														*/		\
	/* Function: ISR(TIMERn_COMPk_vect)						*/		\
	/* Desc: Interrupt handler for T/Cn Compare with A 		*/		\
	/* Input: interrupt vector 								*/		\
	/* Output: none											*/		\
	/**/															\
	ISR(TIMER ## n ## _COMP ## k ## _vect)							\
	{																\
		callCustomFunc(INTERRUPT_CUSTOMFUNC_TC ## n ## _COMP ## k);	\
	}

	#define GENSETk_16B(n, k)										\
	/*										*/						\
	/* Function TIMERnSetk					*/						\
	/* Desc     Set k num of T/Cn 			*/						\
	/* Input    __k: what num set to 		*/						\
	/* Output   none						*/						\
	/**/															\
	void TIMER ## n ## Set ## k(uint16_t __k)						\
	{																\
		OCR ## n ## k ## H = (uint8_t)__k;		/*set high registers of num*/\
		OCR ## n ## k ## L = (uint8_t)(__k >> 8);	/*set low registers of num*/\
	}

	#define GENSETk_8B(n, k)										\
	/*															*/	\
	/* Function TIMERnSetk 										*/	\
	/* Desc     set k num of T/Cn 								*/	\
	/* Input    __k: what num set to 							*/	\
	/* Output   none 											*/	\
	/**/ 															\
	void TIMER ## n ## Set ## k(uint8_t __k)						\
	{																\
		OCR ## n ## k = (uint8_t)__k;/*set k num*/ 					\
	}

	#define GENENABLECOMPkINTERRUPT(n, k)							\
	/*															*/	\
	/* Function TIMERnEnableCOMkInterrupt						*/	\
	/* Desc     enable interrupt on compare with k num 			*/	\
	/* Input    none											*/	\
	/* Output   none											*/	\
	/**/															\
	inline void TIMER ## n ## EnableCOMP ## k ## Interrupt(void)	\
	{																\
		TIMSK ## n = (TIMSK ## n & ~(1 << OCIE ## n ## k )) | (1 << OCIE ## n ## k );/*enable interrupt on compare with k num*/\
	}

	#define GENDISABLECOMPkINTERRUPT(n, k)							\
	/*														*/		\
	/* Function TIMERnDisableCOMPkInterrupt					*/		\
	/* Desc     Disable interrupt on compare with k num		*/		\
	/* Input    none										*/		\
	/* Output   none										*/		\
	/**/															\
	inline void TIMER ## n ## DisableCOMP ## k ## Interrupt(void)	\
	{																\
		TIMSK ## n &= ~(1 << OCIE ## n ## k );/*disable interrupt on compare with k num*/\
	}



	#ifdef TCCR0A
		GENINIT(0)
		GENSETCLK(0)
		#if (defined(OCIE0A) && TIMER0_USE_COMPA == 1)
			GENISR_COMPk(0, A)
			#ifdef OCR0_COMPAL
				GENSETk_16B(0, A)
			#else
				GENSETk_8B(0, A)
			#endif
			GENENABLECOMPkINTERRUPT(0, A)
			GENDISABLECOMPkINTERRUPT(0, A)
		#endif //if defined(OCIE0A) && TIMER0_USE_COMPA

		#if (defined(OCIE0B) && TIMER0_USE_COMPB == 1)
			GENISR_COMPk(0, B)
			#ifdef OCR0_COMPBL
				GENSETk_16B(0, B)
			#else
				GENSETk_8B(0, B)
			#endif
			GENENABLECOMPkINTERRUPT(0, B)
			GENDISABLECOMPkINTERRUPT(0, B)
		#endif //if defined(OCIE0B) && TIMER0_USE_COMPB

		#if (defined(OCIE0C) && TIMER0_USE_COMPC == 1)
			GENISR_COMPk(0, C)
			#ifdef OCR0_COMPCL
				GENSETk_16B(0, C)
			#else
				GENSETk_8B(0, C)
			#endif
			GENENABLECOMPkINTERRUPT(0, C)
			GENDISABLECOMPkINTERRUPT(0, C)
		#endif //if defined(OCIE0C) && TIMER0_USE_COMPC
	#endif	//ifdef TCCR0A


	#ifdef TCCR1A
		GENINIT(1)
		GENSETCLK(1)
		#if (defined(OCIE1A) && TIMER1_USE_COMPA == 1)
			GENISR_COMPk(1, A)
			#ifdef OCR1_COMPAL
				GENSETk_16B(1, A)
			#else
				GENSETk_8B(1, A)
			#endif
			GENENABLECOMPkINTERRUPT(1, A)
			GENDISABLECOMPkINTERRUPT(1, A)
		#endif //if defined(OCIE1A) && TIMER1_USE_COMPA

		#if (defined(OCIE1B) && TIMER1_USE_COMPB == 1)
			GENISR_COMPk(1, B)
			#ifdef OCR1_COMPBL
				GENSETk_16B(1, B)
			#else
				GENSETk_8B(1, B)
			#endif
			GENENABLECOMPkINTERRUPT(1, B)
			GENDISABLECOMPkINTERRUPT(1, B)
		#endif //if defined(OCIE1B) && TIMER1_USE_COMPB

		#if (defined(OCIE1C) && TIMER1_USE_COMPC == 1)
			GENISR_COMPk(1, C)
			#ifdef OCR1_COMPCL
				GENSETk_16B(1, C)
			#else
				GENSETk_8B(1, C)
			#endif
			GENENABLECOMPkINTERRUPT(1, C)
			GENDISABLECOMPkINTERRUPT(1, C)
		#endif //if defined(OCIE1C) && TIMER1_USE_COMPC
	#endif	//ifdef TCCR1A




	#ifdef TCCR2A
		GENINIT(2)
		GENSETCLK(2)
		#if (defined(OCIE2A) && TIMER2_USE_COMPA == 1)
			GENISR_COMPk(2, A)
			#ifdef OCR2_COMPAL
				GENSETk_16B(2, A)
			#else
				GENSETk_8B(2, A)
			#endif
			GENENABLECOMPkINTERRUPT(2, A)
			GENDISABLECOMPkINTERRUPT(2, A)
		#endif //if defined(OCIE2A) && TIMER2_USE_COMPA

		#if (defined(OCIE2B) && TIMER2_USE_COMPB == 1)
			GENISR_COMPk(2, B)
			#ifdef OCR2_COMPBL
				GENSETk_16B(2, B)
			#else
				GENSETk_8B(2, B)
			#endif
			GENENABLECOMPkINTERRUPT(2, B)
			GENDISABLECOMPkINTERRUPT(2, B)
		#endif //if defined(OCIE2B) && TIMER2_USE_COMPB

		#if (defined(OCIE2C) && TIMER2_USE_COMPC == 1)
			GENISR_COMPk(2, C)
			#ifdef OCR2_COMPCL
				GENSETk_16B(2, C)
			#else
				GENSETk_8B(2, C)
			#endif
			GENENABLECOMPkINTERRUPT(2, C)
			GENDISABLECOMPkINTERRUPT(2, C)
		#endif //if defined(OCIE2C) && TIMER2_USE_COMPC
	#endif	//ifdef TCCR2A


	#ifdef TCCR3A
		GENINIT(3)
		GENSETCLK(3)
		#if (defined(OCIE3A) && TIMER3_USE_COMPA == 1)
			GENISR_COMPk(3, A)
			#ifdef OCR3_COMPAL
				GENSETk_16B(3, A)
			#else
				GENSETk_8B(3, A)
			#endif
			GENENABLECOMPkINTERRUPT(3, A)
			GENDISABLECOMPkINTERRUPT(3, A)
		#endif //if defined(OCIE3A) && TIMER3_USE_COMPA

		#if (defined(OCIE3B) && TIMER3_USE_COMPB == 1)
			GENISR_COMPk(3, B)
			#ifdef OCR3_COMPBL
				GENSETk_16B(3, B)
			#else
				GENSETk_8B(3, B)
			#endif
			GENENABLECOMPkINTERRUPT(3, B)
			GENDISABLECOMPkINTERRUPT(3, B)
		#endif //if defined(OCIE3B) && TIMER3_USE_COMPB

		#if (defined(OCIE3C) && TIMER3_USE_COMPC == 1)
			GENISR_COMPk(3, C)
			#ifdef OCR3_COMPCL
				GENSETk_16B(3, C)
			#else
				GENSETk_8B(3, C)
			#endif
			GENENABLECOMPkINTERRUPT(3, C)
			GENDISABLECOMPkINTERRUPT(3, C)
		#endif //if defined(OCIE3C) && TIMER3_USE_COMPC
	#endif	//ifdef TCCR3A



	#ifdef TCCR4A
		GENINIT(4)
		GENSETCLK(4)
		#if (defined(OCIE4A) && TIMER4_USE_COMPA == 1)
			GENISR_COMPk(4, A)
			#ifdef OCR4_COMPAL
				GENSETk_16B(4, A)
			#else
				GENSETk_8B(4, A)
			#endif
			GENENABLECOMPkINTERRUPT(4, A)
			GENDISABLECOMPkINTERRUPT(4, A)
		#endif //if defined(OCIE4A) && TIMER4_USE_COMPA

		#if (defined(OCIE4B) && TIMER4_USE_COMPB == 1)
			GENISR_COMPk(4, B)
			#ifdef OCR4_COMPBL
				GENSETk_16B(4, B)
			#else
				GENSETk_8B(4, B)
			#endif
			GENENABLECOMPkINTERRUPT(4, B)
			GENDISABLECOMPkINTERRUPT(4, B)
		#endif //if defined(OCIE4B) && TIMER4_USE_COMPB

		#if (defined(OCIE4C) && TIMER4_USE_COMPC == 1)
			GENISR_COMPk(4, C)
			#ifdef OCR4_COMPCL
				GENSETk_16B(4, C)
			#else
				GENSETk_8B(4, C)
			#endif
			GENENABLECOMPkINTERRUPT(4, C)
			GENDISABLECOMPkINTERRUPT(4, C)
		#endif //if defined(OCIE4C) && TIMER4_USE_COMPC
	#endif	//ifdef TCCR4A


	#ifdef TCCR5A
		GENINIT(5)
		GENSETCLK(5)
		#if (defined(OCIE5A) && TIMER5_USE_COMPA == 1)
			GENISR_COMPk(5, A)
			#ifdef OCR5_COMPAL
				GENSETk_16B(5, A)
			#else
				GENSETk_8B(5, A)
			#endif
			GENENABLECOMPkINTERRUPT(5, A)
			GENDISABLECOMPkINTERRUPT(5, A)
		#endif //if defined(OCIE5A) && TIMER5_USE_COMPA

		#if (defined(OCIE5B) && TIMER5_USE_COMPB == 1)
			GENISR_COMPk(5, B)
			#ifdef OCR5_COMPBL
				GENSETk_16B(5, B)
			#else
				GENSETk_8B(5, B)
			#endif
			GENENABLECOMPkINTERRUPT(5, B)
			GENDISABLECOMPkINTERRUPT(5, B)
		#endif //if defined(OCIE5B) && TIMER5_USE_COMPB

		#if (defined(OCIE5C) && TIMER5_USE_COMPC == 1)
			GENISR_COMPk(5, C)
			#ifdef OCR5_COMPCL
				GENSETk_16B(5, C)
			#else
				GENSETk_8B(5, C)
			#endif
			GENENABLECOMPkINTERRUPT(5, C)
			GENDISABLECOMPkINTERRUPT(5, C)
		#endif //if defined(OCIE5C) && TIMER5_USE_COMPC
	#endif	//ifdef TCCR5A



	#ifdef TCCR6A
		GENINIT(6)
		GENSETCLK(6)
		#if (defined(OCIE6A) && TIMER6_USE_COMPA == 1)
			GENISR_COMPk(6, A)
			#ifdef OCR6_COMPAL
				GENSETk_16B(6, A)
			#else
				GENSETk_8B(6, A)
			#endif
			GENENABLECOMPkINTERRUPT(6, A)
			GENDISABLECOMPkINTERRUPT(6, A)
		#endif //if defined(OCIE6A) && TIMER6_USE_COMPA

		#if (defined(OCIE6B) && TIMER6_USE_COMPB == 1)
			GENISR_COMPk(6, B)
			#ifdef OCR6_COMPBL
				GENSETk_16B(6, B)
			#else
				GENSETk_8B(6, B)
			#endif
			GENENABLECOMPkINTERRUPT(6, B)
			GENDISABLECOMPkINTERRUPT(6, B)
		#endif //if defined(OCIE6B) && TIMER6_USE_COMPB

		#if (defined(OCIE6C) && TIMER6_USE_COMPC == 1)
			GENISR_COMPk(6, C)
			#ifdef OCR6_COMPCL
				GENSETk_16B(6, C)
			#else
				GENSETk_8B(6, C)
			#endif
			GENENABLECOMPkINTERRUPT(6, C)
			GENDISABLECOMPkINTERRUPT(6, C)
		#endif //if defined(OCIE6C) && TIMER6_USE_COMPC
	#endif	//ifdef TCCR6A



	#ifdef TCCR7A
		GENINIT(7)
		GENSETCLK(7)
		#if (defined(OCIE7A) && TIMER7_USE_COMPA == 1)
			GENISR_COMPk(7, A)
			#ifdef OCR7_COMPAL
				GENSETk_16B(7, A)
			#else
				GENSETk_8B(7, A)
			#endif
			GENENABLECOMPkINTERRUPT(7, A)
			GENDISABLECOMPkINTERRUPT(7, A)
		#endif //if defined(OCIE7A) && TIMER7_USE_COMPA

		#if (defined(OCIE7B) && TIMER7_USE_COMPB == 1)
			GENISR_COMPk(7, B)
			#ifdef OCR7_COMPBL
				GENSETk_16B(7, B)
			#else
				GENSETk_8B(7, B)
			#endif
			GENENABLECOMPkINTERRUPT(7, B)
			GENDISABLECOMPkINTERRUPT(7, B)
		#endif //if defined(OCIE7B) && TIMER7_USE_COMPB

		#if (defined(OCIE7C) && TIMER7_USE_COMPC == 1)
			GENISR_COMPk(7, C)
			#ifdef OCR7_COMPCL
				GENSETk_16B(7, C)
			#else
				GENSETk_8B(7, C)
			#endif
			GENENABLECOMPkINTERRUPT(7, C)
			GENDISABLECOMPkINTERRUPT(7, C)
		#endif //if defined(OCIE7C) && TIMER7_USE_COMPC
	#endif	//ifdef TCCR7A



	#ifdef TCCR8A
		GENINIT(8)
		GENSETCLK(8)
		#if (defined(OCIE8A) && TIMER8_USE_COMPA == 1)
			GENISR_COMPk(8, A)
			#ifdef OCR8_COMPAL
				GENSETk_16B(8, A)
			#else
				GENSETk_8B(8, A)
			#endif
			GENENABLECOMPkINTERRUPT(8, A)
			GENDISABLECOMPkINTERRUPT(8, A)
		#endif //if defined(OCIE8A) && TIMER8_USE_COMPA

		#if (defined(OCIE8B) && TIMER8_USE_COMPB == 1)
			GENISR_COMPk(8, B)
			#ifdef OCR8_COMPBL
				GENSETk_16B(8, B)
			#else
				GENSETk_8B(8, B)
			#endif
			GENENABLECOMPkINTERRUPT(8, B)
			GENDISABLECOMPkINTERRUPT(8, B)
		#endif //if defined(OCIE8B) && TIMER8_USE_COMPB

		#if (defined(OCIE8C) && TIMER8_USE_COMPC == 1)
			GENISR_COMPk(8, C)
			#ifdef OCR8_COMPCL
				GENSETk_16B(8, C)
			#else
				GENSETk_8B(8, C)
			#endif
			GENENABLECOMPkINTERRUPT(8, C)
			GENDISABLECOMPkINTERRUPT(8, C)
		#endif //if defined(OCIE8C) && TIMER8_USE_COMPC
	#endif	//ifdef TCCR8A







	#undef n
	#undef k
	#undef GENSETCLK
	#undef GENINIT
	#undef GENDISABLECOMPkINTERRUPT
	#undef GENENABLECOMPkINTERRUPT
	#undef GENISR_COMPk
	#undef GENSETk_8B
	#undef GENSETAk_16B




#endif



#if USE_LEGACY_VER == 1

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

		#if defined(OCIE0A) && TIMER0_USE_COMPA == 1

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
		#endif //if defined(OCIE0A) && TIMER0_USE_COMPA == 1



		#if defined(OCIE0B) && TIMER0_USE_COMPB
			/*
			 * Function: ISR(TIMER0_COMPB_vect)
			 * Desc: Interrupt handler for T/C0 Compare with B
			 * Input: interrupt vector
			 * Output: none
			 */
			ISR(TIMER0_COMPB_vect)
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC0_COMPB);
			}

			#ifdef OCR0BL
					/*
					 * Function TIMER0SetB
					 * Desc     Set B num of T/C0
					 * Input    __B: what num set to
					 * Output   none
					*/
					void TIMER0SetB(uint16_t __B)
					{
						OCR0BH = (uint8_t)__B;		//set high registers of num
						OCR0BL = (uint8_t)(__B >> 8);	//set low registers of num
					}
				#else //ifdef OCR0BL
					/*
					 * Function TIMER0SetB
					 * Desc     set B num of T/C0
					 * Input    __B: what num set to
					 * Output   none
					*/
					void TIMER0SetB(uint8_t __B)
					{
						OCR0B = (uint8_t)__B;//set B num
					}
			#endif //ifndef OCR0BL
				/*
				 * Function TIMER0EnableCOMBInterrupt
				 * Desc     enable interrupt on compare with B num
				 * Input    none
				 * Output   none
				*/
				inline void TIMER0EnableCOMPBInterrupt(void)
				{
					TIMSK0 = (TIMSK0 & ~(1 << OCIE0B)) | (1 << OCIE0B);//enable interrupt on compare with B num
				}

				/*
				 * Function TIMER0DisableCOMPBInterrupt
				 * Desc     Disable interrupt on compare with B num
				 * Input    none
				 * Output   none
				*/
				inline void TIMER0DisableCOMPBInterrupt(void)
				{
					TIMSK0 &= ~(1 << OCIE0B);//disable interrupt on compare with B num
				}
		#endif //if defined(OCIE0B) && TIMER0_USE_COMPB == 1
		
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
		
	#endif

#endif //if USE_TIMERS == 1
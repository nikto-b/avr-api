/*
 * TODO:	COMPC on T/C №1,3,4
*/
 


#if USE_TIMERS == 1
	#if defined(TCCR0A)//if mcu have TIMER0
		#pragma message "TIMER0 found"
		

		/*
		 * Function TIMER0Init
		 * Desc     init T/C0
		 * Input    __mode: what mode of T/C0
		 * Output   none
		*/
		void TIMER0Init(uint8_t __mode)
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				#pragma message "using func input protector"
				if(!validateTimer0Mode(__mode))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			TCCR0B = 0;
			TIMSK0 = 0;//set param regs to zero
			
			TCCR0B |= __mode;//set mode
		}
		
		/*
		 * Function TIMER0SetCLK
		 * Desc     set clock source of T/C0
		 * Input    __source: what source of T/C0
		 * Output   none
		*/
		void TIMER0SetCLK(uint8_t __source)
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(!validateTimer0CLK(__source))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			
			TCCR0B = (TCCR0B & ~__source) | __source;
		}
		
		/*
		 * Function TIMER0Init
		 * Desc     init T/C0
		 * Input    __mode: what mode init to
		 * 			__source: what source set to
		 * Output   none
		*/
		void TIMER0Init(uint8_t __mode, uint8_t __source)
		{
			TIMER0Init(__mode);
			TIMER0SetCLK(__source);
		}
		

		#if TIMER0_USE_COMPA == 1//if using interrupt on compare with A num
			/*
			 * Function ISR(TIMER0_COMPA_vect)
			 * Desc     Interrupt handler for vector TIMER0COMPA
			 * Input    Interrupt vector
			 * Output   none
			*/
			ISR(TIMER0_COMPA_vect)//COMPA interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC0_COMPA);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC0_COMPA
					if(funcs[INTERRUPT_CUSTOMFUNC_TC0_COMPA] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC0_COMPA]();//call custom function
				#endif
				*/
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




		#if TIMER0_USE_COMPB == 1//if using interrupt on compare with B num
			/*
			 * Function ISR(TIMER0_COMPB_vect)
			 * Desc     Interrupt handler for vector TIMER0_COMPB_vect
			 * Input    Interrupt vector
			 * Output   none
			*/
		 	ISR(TIMER0_COMPB_vect)//COMPB interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC0_COMPB);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC0_COMPA
					if(funcs[INTERRUPT_CUSTOMFUNC_TC0_COMPB] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC0_COMPB]();//call custom function
				#endif
				*/
			}

			#ifdef OCR0BL
				/*
				 * Function TIMER0SetB
				 * Desc     Set B num for T/C0
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER0SetB(uint16_t __B)
				{
					OCR0BH = (uint8_t)__B;		//set high registers of num
					OCR0BL = (uint8_t)(__B >> 8);//set low registers of num
				}
			#else //ifdef OCR0BL
				/*
				 * Function TIMER0SetB
				 * Desc     Set B num for T/C0
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER0SetB(uint8_t __B)
				{
					OCR0B = (uint8_t)__B;//set B num
				}
			#endif //ifndef OCR0BL


			/*
			 * Function TIMER0EnableCOMPBInterrupt
			 * Desc     Enable interrupt on compare with B num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER0EnableCOMPBInterrupt(void)
			{
				TIMSK0 = (TIMSK0 & ~(1 << OCIE0B)) | (1<<OCIE0B);//enable interrupt on compare with B num
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

		#endif //if TIMER0_USE_COMPB == 1




		#if TIMER0_USE_OVF == 1//if using interrupt on overflow
			/*
			 * Function ISR(TIMER0_OVF_vect)
			 * Desc     Interrupt handler for vector TIMER0_OVF_vect
			 * Input    Interrupt vector
			 * Output   none
			*/
			ISR(TIMER0_OVF_vect)//OVF interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC0_OVF);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC0_OVF
					if(funcs[INTERRUPT_CUSTOMFUNC_TC0_OVF] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC0_OVF]();//call custom function
				#endif
				*/
			}
			
			/*
			 * Function TIMER0EncbleOVFISR
			 * Desc     Enable interrupt at overflow
			 * Input    none
			 * Output   none 
			*/
			inline void TIMER0EnableOVFISR(void)
			{
				TIMSK0 = (TIMSK0 & ~(1 << TOIE0)) | (1 << TOIE0);//enable interrupt on overflow
			}
			
			/*
			 * Function TIMER0DisableOVFISR
			 * Desc     Disavle onterrupt on overflow
			 * Input    none
			 * Output   none
			*/
			inline void TIMER0DisableOVFISR(void)
			{
				TIMSK0 &= ~(1 << TOIE0);
			}
			
		#endif //if TIMER0_USE_OVF == 1
	#endif //if defined(TCCR0A)
	
	
	
	#if defined(TCCR1A)//if mcu have TIMER1
		#pragma message "TIMER1 found"
		

		/*
		 * Function TIMER1SetMode
		 * Desc     Set mode of T/C1
		 * Input    __mode: what mode needed to set
		 * Output   none
		*/
		void TIMER1SetMode(uint8_t __mode)
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(!validateTimer1Mode(__mode))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			
			TCCR1B |= __mode;//set mode
		}
		
		/*
		 * Function TIMER1SetCLK
		 * Desc     Set clock source of T/C1
		 * Input    __source: what source needed set to
		 * Output   none
		*/
		inline void TIMER1SetCLK(uint8_t __source)
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(!validateTimer1CLK(__source))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			
			TCCR1B = (TCCR1B & ~__source) | __source;
		}
				
		/*
		 * Function TIMER1Init
		 * Desc     initialize T/C1
		 * Input    __mode: what mode set to
		 * 			__source: what source set to
		 * Output   none
		*/
		void TIMER1Init(uint8_t __mode, uint8_t __source)
		{
			TIMER1SetMode(__mode);
			TIMER1SetCLK(__source);
		}
		

		#if TIMER1_USE_COMPA == 1//if using interrupt on compare with A num
			/*
			 * Function ISR(TIMER1_COMPA_vect)
			 * Desc     Interrupt handler for vector TIMER1_COMPA
			 * Input    Interrupt vector
			 * Output   none
			*/
			ISR(TIMER1_COMPA_vect)//COMPA interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC1_COMPA);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC1_COMPA
					if(funcs[INTERRUPT_CUSTOMFUNC_TC1_COMPA] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC1_COMPA]();//call custom function
				#endif
				*/
			}


			#ifdef OCR1AL
				/*
				 * Function TIMER1SetA
				 * Desc     Set A num of T/C1
				 * Input    __A: what num set to
				 * Output   none
				*/
				void TIMER1SetA(uint16_t __A)
				{
					OCR1AH = (uint8_t)__A;		//set high registers of num
					OCR1AL = (uint8_t)(__A >> 8);	//set low registers of num
				}
			#else //ifdef OCR2AL
				/*
				 * Function TIMER1SetA
				 * Desc     Set A num of T/C1
				 * Input    __A: what num set to
				 * Output   none
				*/
				void TIMER1SetA(uint8_t __A)
				{
					OCR1A = (uint8_t)__A;//set B num
				}
			#endif //ifndef OCR1AL


			/*
			 * Function TIMER1EnableCOMPAInterrupt
			 * Desc     Enable interrupt on compare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER1EnableCOMPAInterrupt(void)
			{
				TIMSK1 = (TIMSK1 & ~(1 << OCIE1A)) | (1 << OCIE1A);//enable interrupt on compare with A num
			}

			/*
			 * Function TIMER1DisableCOMPAInterrupt
			 * Desc     Disable interrupt on compare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER1DisableCOMPAInterrupt(void)
			{
				TIMSK1 &= ~(1 << OCIE1A);//disable interrupt on compare with A num
			}

		#endif //if TIMER1_USE_COMPA == 1




		#if TIMER1_USE_COMPB == 1//if using interrupt on compare with B num
			/*
			 * Function ISR(TIMER1_COMPB_vect)
			 * Desc     Interrupt handler for vector TIMER1_COMPB
			 * Input    Interrupt vector
			 * Output   none
			*/
		 	ISR(TIMER1_COMPB_vect)//COMPB interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC1_COMPB);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC1_COMPB
					if(funcs[INTERRUPT_CUSTOMFUNC_TC1_COMPB] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC1_COMPB]();//call custom function
				#endif
				*/
			}

			#ifdef OCR1BL
				/*
				 * Function TIMER1SetB
				 * Desc     Set B num of T/C1
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER1SetB(uint16_t __B)
				{
					OCR1BH = (uint8_t)__B;		//set high registers of num
					OCR1BL = (uint8_t)(__B >> 8);//set low registers of num
				}
			#else //ifdef OCR1BL
				/*
				 * Function TIMER1SetB
				 * Desc     Set B num of T/C1
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER1SetB(uint8_t __B)
				{
					OCR1B = (uint8_t)__B;//set B num
				}
			#endif //ifndef OCR1BL


			/*
			 * Function TIMER1EnableCOMPBInterrupt
			 * Desc     enable interrupt on compare with B num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER1EnableCOMPBInterrupt(void)
			{
				TIMSK1 = (TIMSK1 & ~(1 << OCIE1B)) | (1<<OCIE1B);//enable interrupt on compare with B num
			}

			/*
			 * Function TIMER1DisableCOMPBInterrupt
			 * Desc     Disable interrupt on compare with B num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER1DisableCOMPBInterrupt(void)
			{
				TIMSK1 &= ~(1 << OCIE1B);//disable interrupt on compare with B num
			}

		#endif //if TIMER1_USE_COMPB == 1




		#if TIMER1_USE_OVF == 1//if using interrupt on overflow
			/*
			 * Function ISR(TIMER1_OVF_vect)
			 * Desc     Interrupt handler for vector TIMER1_OVF
			 * Input    Interrupt vector
			 * Output   none
			*/
			ISR(TIMER1_OVF_vect)//OVF interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC1_OVF);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC1_OVF
					if(funcs[INTERRUPT_CUSTOMFUNC_TC1_OVF] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC1_OVF]();//call custom function
				#endif
				*/
			}
			
			/*
			 * Function TIMER1EnavleOVFISR
			 * Desc     Enable interrupt on overflow
			 * Input    none
			 * Output   none
			*/
			inline void TIMER1EnableOVFISR(void)
			{
				TIMSK1 = (TIMSK1 & ~(1 << TOIE1)) | (1 << TOIE1);//enable interrupt on overflow
			}
			
			/*
			 * Function TIMER1DisableOVFISR
			 * Desc     Disable interrupt on overflow
			 * Input    none
			 * Output   none
			*/
			inline void TIMER1DisableOVFISR(void)
			{
				TIMSK1 &= ~(1 << TOIE1);
			}
			
		#endif //if TIMER1_USE_OVF == 1
	#endif //if defined(TCCR1A)
	
	
	
	#if defined(TCCR2A)//if mcu have TIMER2
		#pragma message "TIMER2 found"
		

		/*
		 * Function TIMER2SetMode
		 * Desc     set mode of T/C2
		 * Input    __mode: what mode set to
		 * Output   none
		*/
		void TIMER2SetMode(uint8_t __mode)
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(!validateTimer2Mode(__mode))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			
			
			TCCR2B |= __mode;//set mode
		}
				
		/*
		 * Function TIMER2SetCLK
		 * Desc     Set clock source of T/C2
		 * Input    __source: what source set to
		 * Output   none
		*/
		inline void TIMER2SetCLK(uint8_t __source)
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(!validateTimer2CLK(__source))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			
			TCCR2B = (TCCR2B & ~__source) | __source;
		}
		
		/*
		 * Function TIMER2Init
		 * Desc     Initialize T/C2
		 * Input    __mode: what mode set to
		 * 			__source: what source set to
		 * Output   none
		*/
		void TIMER2Init(uint8_t __mode, uint8_t __source)
		{
			TIMER2SetMode(__mode);
			TIMER2SetCLK(__source);
		}
		

		#if TIMER2_USE_COMPA == 1//if using interrupt on compare with A num
			/*
			 * Function ISR(TIMER2_COMPA_vect)
			 * Desc     interrupt handler for TIMER2_COMPA
			 * Input    Interrupt vector
			 * Output   none
			*/
			ISR(TIMER2_COMPA_vect)//COMPA interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC2_COMPA);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC2_COMPA
					if(funcs[INTERRUPT_CUSTOMFUNC_TC2_COMPA] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC2_COMPA]();//call custom function
				#endif
				*/
			}

			#ifdef OCR2AL
				/*
				 * Function TIMER2SetA
				 * Desc     Set A num for T/C2
				 * Input    __A: what num set to
				 * Output   none
				*/
				void TIMER2SetA(uint16_t __A)
				{
					OCR2AH = (uint8_t)__A;		//set high registers of num
					OCR2AL = (uint8_t)(__A >> 8);	//set low registers of num
				}
			#else //ifdef OCR2AL
			/*
			 * Function TIMER2SetA
			 * Desc     Set A num for T/C2
			 * Input    __A: what num set to
			 * Output   none
			*/
				void TIMER2SetA(uint8_t __A)
				{
					OCR2A = (uint8_t)__A;//set B num
				}
			#endif //ifndef OCR2AL


			/*
			 * Function TIMER2EnableCOMPAInterrupt
			 * Desc     enable interrupt on compare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER2EnableCOMPAInterrupt(void)
			{
				TIMSK2 = (TIMSK2 & ~(1 << OCIE2A)) | (1<<OCIE2A);//enable interrupt on compare with A num
			}

			/*
			 * Function TIMER2DisableCOMPAInterrupt
			 * Desc     disable interrupt on conpare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER2DisableCOMPAInterrupt(void)
			{
				TIMSK2 &= ~(1 << OCIE2A);//disable interrupt on compare with A num
			}

		#endif //if TIMER2_USE_COMPA == 1




		#if TIMER2_USE_COMPB == 1//if using interrupt on compare with B num
			/*
			 * Function ISR(TIMER2_COMPB_vect)
			 * Desc     Interrupt handler for vector TIMER2_COMPB
			 * Input    Interrupt vector
			 * Output   none
			*/
		 	ISR(TIMER2_COMPB_vect)//COMPB interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC2_COMPB);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC2_COMPB
					if(funcs[INTERRUPT_CUSTOMFUNC_TC2_COMPB] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC2_COMPB]();//call custom function
				#endif
				*/
			}

			#ifdef OCR2BL
				/*
				 * Function TIMER2SetB
				 * Desc     Set B num for T/C2
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER2SetB(uint16_t __B)
				{
					OCR2BH = (uint8_t)__B;		//set high registers of num
					OCR2BL = (uint8_t)(__B >> 8);//set low registers of num
				}
			#else //ifdef OCR2BL
				/*
				 * Function TIMER2SetB
				 * Desc     Set B num for T/C2
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER2SetB(uint8_t __B)
				{
					OCR2B = (uint8_t)__B;//set B num
				}
			#endif //ifndef OCR2BL


			/*
			 * Function TIMER2EnableCOMPBInterrupt
			 * Desc     Enable interrupt on compare with B num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER2EnableCOMPBInterrupt(void)
			{
				TIMSK2 = (TIMSK2 & ~(1 << OCIE2B)) | (1 << OCIE2B);//enable interrupt on compare with B num
			}

			/*
			 * Function TIMER2DisableCOMPBInterrupt
			 * Desc     Disable interrupt on compare with B num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER2DisableCOMPBInterrupt(void)
			{
				TIMSK2 &= ~(1 << OCIE2B);//disable interrupt on compare with B num
			}

		#endif //if TIMER2_USE_COMPB == 1




		#if TIMER2_USE_OVF == 1//if using interrupt on overflow
			/*
			 * Function ISR(TIMER2_OVF_vect)
			 * Desc     Interrupt handler for vector TIMER2_OVF
			 * Input    Interrupt vector
			 * Output   none
			*/
			ISR(TIMER2_OVF_vect)//OVF interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC2_OVF);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC2_OVF
					if(funcs[INTERRUPT_CUSTOMFUNC_TC2_OVF] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC2_OVF]();//call custom function
				#endif
				*/
			}
						
			/*
			 * Function TIMER2EnableOVFISR
			 * Desc     Enable interrupt on overflow
			 * Input    none
			 * Output   none
			*/
			inline void TIMER2EnableOVFISR(void)
			{
				TIMSK2 = (TIMSK2 & ~(1 << TOIE2)) | (1 << TOIE2);//enable interrupt on overflow
			}
			
			/*
			 * Function TIMER2DisableOVFISR
			 * Desc     Disable interrupt on overflow
			 * Input    none
			 * Output   none
			*/
			inline void TIMER2DisableOVFISR(void)
			{
				TIMSK2 &= ~(1 << TOIE2);
			}
			
		#endif //if TIMER2_USE_OVF == 1
	#endif //if defined(TCCR2A)
	
	
	
	#if defined(TCCR3A)//if mcu have TIMER3
		#pragma message "TIMER3 found"
		

		/*
		 * Function TIMER3SetMode
		 * Desc     Set mode for T/C3
		 * Input    __mode: what mode set to
		 * Output   none
		*/
		void TIMER3SetMode(uint8_t __mode)
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(!validateTimer3Mode(__mode))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			
			TCCR3B = 0;
			TIMSK3 = 0;//set param regs to zero
			
			TCCR3B |= __mode;//set mode
		}
		
		/*
		 * Function TIMER3SetCLK
		 * Desc     Set clock source for T/C3
		 * Input    __source: what source set to
		 * Output   none
		*/
		inline void TIMER3SetCLK(uint8_t __source)
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(!validateTimer3CLK(__source))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			
			TCCR3B = (TCCR3B & ~__source) | __source;
		}
		
		/*
		 * Function TIMER3Init
		 * Desc     Initialize T/C3
		 * Input    __mode: what mode set to
		 * 			__source: what source set to
		 * Output   none
		*/
		void TIMER3Init(uint8_t __mode, uint8_t __source)
		{
			TIMER3SetMode(__mode);
			TIMER3SetCLK(__source);
		}
		

		#if TIMER3_USE_COMPA == 1//if using interrupt on compare with A num
			/*
			 * Function ISR(TIMER3_COMPA_vect)
			 * Desc     Interrupt handler for vector TIMER3_COMPA
			 * Input    Iterrupt vector
			 * Output   none
			*/
			ISR(TIMER3_COMPA_vect)//COMPA interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC3_COMPA);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC3_COMPA
					if(funcs[INTERRUPT_CUSTOMFUNC_TC3_COMPA] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC3_COMPA]();//call custom function
				#endif
				*/
			}

			#ifdef OCR3AL
			/*
			 * Function TIMER3SetA
			 * Desc     Set A num for T/C3
			 * Input    __A: what num set to
			 * Output   none
			*/
				void TIMER3SetA(uint16_t __A)
				{
					OCR3AH = (uint8_t)__A;		//set high registers of num
					OCR3AL = (uint8_t)(__A >> 8);	//set low registers of num
				}
			#else //ifdef OCR3AL
			/*
			 * Function TIMER3SetA
			 * Desc     Set A num for T/C3
			 * Input    __A: what num set to
			 * Output   none
			*/
				void TIMER3SetA(uint8_t __A)
				{
					OCR3A = (uint8_t)__A;//set B num
				}
			#endif //ifndef OCR3AL


			/*
			 * Function TIMER3EnableCOMPAInterrupt
			 * Desc     Enable interrupt at compare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER3EnableCOMPAInterrupt(void)
			{
				TIMSK3 = (TIMSK3 & ~(1 << OCIE3A)) | (1<<OCIE3A);//enable interrupt on compare with A num
			}

			/*
			 * Function TIMER3DisableCOMPAInterrupt
			 * Desc     Disable interrupt on compare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER3DisableCOMPAInterrupt(void)
			{
				TIMSK3 &= ~(1 << OCIE3A);//disable interrupt on compare with A num
			}

		#endif //if TIMER3_USE_COMPA == 1




		#if TIMER3_USE_COMPB == 1//if using interrupt on compare with B num
			/*
			 * Function ISR(TIMER3_COMPB_vect)
			 * Desc     Interrupt handler for vector TIMER3_COMPB
			 * Input    Interrupt vector
			 * Output   none
			*/
		 	ISR(TIMER3_COMPB_vect)//COMPB interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC3_COMPB);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC3_COMPB
					if(funcs[INTERRUPT_CUSTOMFUNC_TC3_COMPB] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC3_COMPB]();//call custom function
				#endif
				*/
			}

			#ifdef OCR3BL
				/*
				 * Function TIMER3SetB
				 * Desc     Set B num for T/C3
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER3SetB(uint16_t __B)
				{
					OCR3BH = (uint8_t)__B;		//set high registers of num
					OCR3BL = (uint8_t)(__B >> 8);//set low registers of num
				}
			#else //ifdef OCR3BL
				/*
				 * Function TIMER3SetB
				 * Desc     Set B num for T/C3
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER3SetB(uint8_t __B)
				{
					OCR3B = (uint8_t)__B;//set B num
				}
			#endif //ifndef OCR3BL


			/*
			 * Function TIMER3EnableCOMPBInterrupt
			 * Desc     Enable interrupt on compare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER3EnableCOMPBInterrupt(void)
			{
				TIMSK3 = (TIMSK3 & ~(1 << OCIE3B)) | (1 << OCIE3B);//enable interrupt on compare with B num
			}

			/*
			 * Function TIMER3DisableCOMPBInterrupt
			 * Desc     Disable interrupt on compare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER3DisableCOMPBInterrupt(void)
			{
				TIMSK3 &= ~(1 << OCIE3B);//disable interrupt on compare with B num
			}

		#endif //if TIMER3_USE_COMPB == 1




		#if TIMER3_USE_OVF == 1//if using interrupt on overflow
			/*
			 * Function ISR(TIMER3_OVF_vect)
			 * Desc     Interrupt handler for vector TIMER3_OVf
			 * Input    Interrupt vector
			 * Output   none
			*/
			ISR(TIMER3_OVF_vect)//OVF interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC3_OVF);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC3_OVF
					if(funcs[INTERRUPT_CUSTOMFUNC_TC3_OVF] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC3_OVF]();//call custom function
				#endif
				*/
			}
			
			/*
			 * Function TIMER3EnableOVFISR
			 * Desc     Enable interrupt on overflow
			 * Input    none
			 * Output   none
			*/
			inline void TIMER3EnableOVFISR(void)
			{
				TIMSK3 = (TIMSK3 & ~(1 << TOIE3)) | (1 << TOIE3);//enable interrupt on overflow
			}
			
			/*
			 * Function TIMER3DisableOVFISR
			 * Desc     Disable interrupt on overflow
			 * Input    none
			 * Output   none
			*/
			inline void TIMER3DisableOVFISR(void)
			{
				TIMSK3 &= ~(1 << TOIE3);
			}
			
		#endif //if TIMER3_USE_OVF == 1
	#endif //if defined(TCCR3A)
	
	
	
	#if defined(TCCR4A)//if mcu have TIMER4
		#pragma message "TIMER4 found"
		

		/*
		 * Function TIMER4SetMode
		 * Desc     Set mode of T/C4
		 * Input    __mode: what mode set to
		 * Output   none
		*/
		void TIMER4SetMode(uint8_t __mode)
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(!validateTimer4Mode(__mode))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			
			TCCR4B |= __mode;//set mode
		}
				
		/*
		 * Function TIMER4SetCLK
		 * Desc     Ste clock source for T/C4
		 * Input    __source: what source set to
		 * Output   none
		*/
		inline void TIMER4SetCLK(uint8_t __source)
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(!validateTimer4CLK(__source))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			TCCR4B = (TCCR4B & ~__source) | __source;
		}
				
		/*
		 * Function TIMER4Init
		 * Desc     Initialize T/C4
		 * Input    __mode: what mode set to
		 * 			__source: what source set to
		 * Output   none
		*/
		void TIMER4Init(uint8_t __mode, uint8_t __source)
		{
			TIMER4SetMode(__mode);
			TIMER4SetCLK(__source);
		}
		

		#if TIMER4_USE_COMPA == 1//if using interrupt on compare with A num
			/*
			 * Function ISR(TIMER4_COMPA_vect)
			 * Desc     Interrupt handler for vector TIMER4_COMPA
			 * Input    Interrupt vector
			 * Output   none
			*/
			ISR(TIMER4_COMPA_vect)//COMPA interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC4_COMPA);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC4_COMPA
					if(funcs[INTERRUPT_CUSTOMFUNC_TC4_COMPA] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC4_COMPA]();//call custom function
				#endif
				*/
			}

			#ifdef OCR4AL
				/*
				 * Function TIMER4SetA
				 * Desc     Set A num for T/C4
				 * Input    __A: what num set to
				 * Output   none
				*/
				void TIMER4SetA(uint16_t __A)
				{
					OCR4AH = (uint8_t)__A;		//set high registers of num
					OCR4AL = (uint8_t)(__A >> 8);	//set low registers of num
				}
			#else //ifdef OCR4AL
				/*
				 * Function TIMER4SetA
				 * Desc     Set A num for T/C4
				 * Input    __A: what num set to
				 * Output   none
				*/
				void TIMER4SetA(uint8_t __A)
				{
					OCR4A = (uint8_t)__A;//set B num
				}
			#endif //ifndef OCR4AL


			/*
			 * Function TIMER4EnableCOMPAInterrupt
			 * Desc     Enable interrupt on compare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER4EnableCOMPAInterrupt(void)
			{
				TIMSK4 = (TIMSK4 & ~(1 << OCIE4A)) | (1 << OCIE4A);//enable interrupt on compare with A num
			}

			/*
			 * Function TIMER4DisableCOMPAInterrupt
			 * Desc     Disable interrupt on compare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER4DisableCOMPAInterrupt(void)
			{
				TIMSK4 &= ~(1 << OCIE4A);//disable interrupt on compare with A num
			}

		#endif //if TIMER4_USE_COMPA == 1




		#if TIMER4_USE_COMPB == 1//if using interrupt on compare with B num
			/*
			 * Function ISR(TIMER4_COMPB_vect)
			 * Desc     Interrupt handler for vector TIMER4_COMPB
			 * Input    Interrupt vector
			 * Output   none
			*/
		 	ISR(TIMER4_COMPB_vect)//COMPB interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC4_COMPB);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC4_COMPB
					if(funcs[INTERRUPT_CUSTOMFUNC_TC4_COMPB] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC4_COMPB]();//call custom function
				#endif
				*/
			}

			#ifdef OCR4BL
				/*
				 * Function TIMER4SetB
				 * Desc     Set B num for T/C4
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER4SetB(uint16_t __B)
				{
					OCR4BH = (uint8_t)__B;		//set high registers of num
					OCR4BL = (uint8_t)(__B >> 8);//set low registers of num
				}
			#else //ifdef OCR4BL
				/*
				 * Function TIMER4SetB
				 * Desc     Set B num for T/C4
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER4SetB(uint8_t __B)
				{
					OCR4B = (uint8_t)__B;//set B num
				}
			#endif //ifndef OCR4BL


			/*
			 * Function TIMER4EnableOMPBInterrupt
			 * Desc     Enable interrupt on compare with B num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER4EnableCOMPBInterrupt(void)
			{
				TIMSK4 = (TIMSK4 & ~(1 << OCIE4B)) | (1 << OCIE4B);//enable interrupt on compare with B num
			}

			/*
			 * Function TIMER4DisableCOMPBInterrupt
			 * Desc     Disable interrupt on compare with B num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER4DisableCOMPBInterrupt(void)
			{
				TIMSK4 &= ~(1 << OCIE4B);//disable interrupt on compare with B num
			}

		#endif //if TIMER4_USE_COMPB == 1




		#if TIMER4_USE_OVF == 1//if using interrupt on overflow
			/*
			 * Function ISR(TIMER4_OVF_vect)
			 * Desc     Interrupt handler for vector TIMER4_OVF
			 * Input    Interrupt vector
			 * Output   none
			*/
			ISR(TIMER4_OVF_vect)//OVF interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC4_OVF);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC4_OVF
					if(funcs[INTERRUPT_CUSTOMFUNC_TC4_OVF] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC4_OVF]();//call custom function
				#endif
				*/
			}
			
			/*
			 * Function TIMER4EnableOVFISR
			 * Desc     Enable interrupt on overflow
			 * Input    none
			 * Output   none
			*/
			inline void TIMER4EnableOVFISR(void)
			{
				TIMSK4 = (TIMSK4 & ~(1 << TOIE4)) | (1 << TOIE4);//enable interrupt on overflow
			}
			
			/*
			 * Function TIMER4DisableOVFISR
			 * Desc     Disable interrupt on overflow
			 * Input    none
			 * Output   none
			*/
			inline void TIMER4DisableOVFISR(void)
			{
				TIMSK4 &= ~(1 << TOIE4);
			}
			
		#endif //if TIMER4_USE_OVF == 1
	#endif //if defined(TCCR4A)
	
	
	
	#if defined(TCCR5A)//if mcu have TIMER5
		#pragma message "TIMER5 found"
		

		/*
		 * Function TIMER5SetMode
		 * Desc     Set mode for T/C5
		 * Input    __mode: what mode set to
		 * Output   none
		*/
		void TIMER5SetMode(uint8_t __mode)
		{
			
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(!validateTimer5Mode(__mode))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			TCCR5B = 0;
			TIMSK5 = 0;//set param regs to zero
			
			TCCR5B |= __mode;//set mode
		}
		
		/*
		 * Function TIMER5SetCLK
		 * Desc     Set clock source for T/C5
		 * Input    __source: what source set to
		 * Output   none
		*/
		inline void TIMER5SetCLK(uint8_t __source)
		{
			#if USE_FUNC_INPUT_PROTECTOR == 1
				if(!validateTimer5CLK(__source))
				{
					return;
				}
			#endif //if USE_FUNC_INPUT_PROTECTOR == 1
			TCCR5B = (TCCR5B & ~__source) | __source;
		}
		
		/*
		 * Function TIMER5Init
		 * Desc     Initialize T/C5
		 * Input    __mode: what mode set to
		 * 			__source: what clock source set to
		 * Output   none
		*/
		void TIMER5Init(uint8_t __mode, uint8_t __source)
		{
			TIMER5SetMode(__mode);
			TIMER5SetCLK(__source);
		}
		

		#if TIMER5_USE_COMPA == 1//if using interrupt on compare with A num
			/*
			 * Function ISR(TIMER5_COMPA_vect)
			 * Desc     Interrupt handler for vector TIMER5_COMPA
			 * Input    Interrupt vector
			 * Output   none
			*/
			ISR(TIMER5_COMPA_vect)//COMPA interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC5_COMPA);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC5_COMPA
					if(funcs[INTERRUPT_CUSTOMFUNC_TC5_COMPA] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC5_COMPA]();//call custom function
				#endif
				*/
			}

			#ifdef OCR5AL
				/*
				 * Function TIMER5SetA
				 * Desc     Set A num for T/C5
				 * Input    __A: what num set to
				 * Output   none
				*/
				void TIMER5SetA(uint16_t __A)
				{
					OCR5AH = (uint8_t)__A;		//set high registers of num
					OCR5AL = (uint8_t)(__A >> 8);	//set low registers of num
				}
			#else //ifdef OCR5AL
				/*
				 * Function TIMER5SetA
				 * Desc     Set A num for T/C5
				 * Input    __A: what num set to
				 * Output   none
				*/
				void TIMER5SetA(uint8_t __A)
				{
					OCR5A = (uint8_t)__A;//set B num
				}
			#endif //ifndef OCR5AL


			/*
			 * Function TIMER5EnableCOMPAInterrupt
			 * Desc     Enable interrupt on compare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER5EnableCOMPAInterrupt(void)
			{
				TIMSK5 = (TIMSK5 & ~(1 << OCIE5A)) | (1 << OCIE5A);//enable interrupt on compare with A num
			}

			/*
			 * Function TIMER5DisableCOMPAInterrupt
			 * Desc     Disable interrupt on compare with A num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER5DisableCOMPAInterrupt(void)
			{
				TIMSK5 &= ~(1 << OCIE5A);//disable interrupt on compare with A num
			}

		#endif //if TIMER5_USE_COMPA == 1




		#if TIMER5_USE_COMPB == 1//if using interrupt on compare with B num
			/*
			 * Function ISR(TIMER5_COMPB_vect)
			 * Desc     Interrupt handler for vector TIMER5_COMPB
			 * Input    Interrupt vector
			 * Output   none
			*/
		 	ISR(TIMER5_COMPB_vect)//COMPB interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC5_COMPB);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC5_COMPB
					if(funcs[INTERRUPT_CUSTOMFUNC_TC5_COMPB] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC5_COMPB]();//call custom function
				#endif
				*/
			}

			#ifdef OCR5BL
				/*
				 * Function TIMER5SetB
				 * Desc     Set B num for T/C5
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER5SetB(uint16_t __B)
				{
					OCR5BH = (uint8_t)__B;		//set high registers of num
					OCR5BL = (uint8_t)(__B >> 8);//set low registers of num
				}
			#else //ifdef OCR5BL
				/*
				 * Function TIMER5SetB
				 * Desc     Set B num for T/C5
				 * Input    __B: what num set to
				 * Output   none
				*/
				void TIMER5SetB(uint8_t __B)
				{
					OCR5B = (uint8_t)__B;//set B num
				}
			#endif //ifndef OCR5BL


			/*
			 * Function TIMER5EnableCOMPBInterrupt
			 * Desc     Enable interrupt on compare with B num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER5EnableCOMPBInterrupt(void)
			{
				TIMSK5 = (TIMSK5 & ~(1 << OCIE5B)) | (1 << OCIE5B);//enable interrupt on compare with B num
			}

			/*
			 * Function TIMER5DisableCOMPBInterrupt
			 * Desc     Disable interrupt on compare with B num
			 * Input    none
			 * Output   none
			*/
			inline void TIMER5DisableCOMPBInterrupt(void)
			{
				TIMSK5 &= ~(1 << OCIE5B);//disable interrupt on compare with B num
			}

		#endif //if TIMER5_USE_COMPB == 1




		#if TIMER5_USE_OVF == 1//if using interrupt on overflow
			/*
			 * Function ISR(TIMER5_OVF_vect)
			 * Desc     Interrupt handler for vector TIMER5_OVF
			 * Input    Interrupt vect
			 * Output   none
			*/
			ISR(TIMER5_OVF_vect)//OVF interrupt handler
			{
				callCustomFunc(INTERRUPT_CUSTOMFUNC_TC5_OVF);
				/*#ifdef INTERRUPT_CUSTOMFUNC_TC5_OVF
					if(funcs[INTERRUPT_CUSTOMFUNC_TC5_OVF] != NULL)
						funcs[INTERRUPT_CUSTOMFUNC_TC5_OVF]();//call custom function
				#endif
				*/
			}
			
			/*
			 * Function TIMER5EnableOVFISR
			 * Desc     Enable interrupt on overflow
			 * Input    none
			 * Output   none
			*/
			inline void TIMER5EnableOVFISR(void)
			{
				TIMSK5 = (TIMSK5 & ~(1 << TOIE5)) | (1 << TOIE5);//enable interrupt on overflow
			}
			
			/*
			 * Function TIMER5DisableOVFISR
			 * Desc     Disable interrupt on overflow
			 * Input    none
			 * Output   none
			*/
			inline void TIMER5DisableOVFISR(void)
			{
				TIMSK5 &= ~(1 << TOIE5);
			}
			
		#endif //if TIMER5_USE_OVF == 1
	#endif //if defined(TCCR5A)
	
	
#endif //if USE_TIMERS == 1

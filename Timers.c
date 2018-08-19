#if USE_TIMERS == 1
	#if defined(TCCR0A)//if mcu have TIMER0
		#pragma message "TIMER0 found"
		

		void TIMER0Init(uint8_t __mode__)
		{
			TCCR0B = 0;
			TIMSK0 = 0;//set param regs to zero
			
			TCCR0B |= __mode__;//set mode
		}
		
		inline void TIMER0SetCLK(uint8_t __source__)
		{
			TCCR0B = (TCCR0B & ~__source__) | __source__;
		}
		
		void TIMER0Init(uint8_t __mode__, uint8_t __source__)
		{
			TIMER0Init(__mode__);
			TIMER0SetCLK(__source__);
		}
		

		#if TIMER0_USE_COMPA == 1//if using interrupt on compare with A num
			ISR(TIMER0_COMPA_vect)//COMPA interrupt handler
			{
				if(funcs[TIMER0_COMPA_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER0_COMPA_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR0AL
				void TIMER0SetA(uint16_t __A__)
				{
					OCR0AH = (uint8_t)__A__;		//set high registers of num
					OCR0AL = (uint8_t)(__A__ >> 8);	//set low registers of num
				}
			#else //ifdef OCR0AL
				void TIMER0SetA(uint8_t __A__)
				{
					OCR0A = (uint8_t)__A__;//set B num
				}
			#endif //ifndef OCR0AL


			inline void TIMER0EnableCOMPAInterrupt()
			{
				TIMSK0 = (TIMSK0 & ~(1 << OCIE0A)) | (1 << OCIE0A);//enable interrupt on compare with A num
			}

			inline void TIMER0DisableCOMPAInterrupt()
			{
				TIMSK0 &= ~(1 << OCIE0A);//disable interrupt on compare with A num
			}

		#endif //if TIMER0_USE_COMPA == 1




		#if TIMER0_USE_COMPB == 1//if using interrupt on compare with B num
		 	ISR(TIMER0_COMPB_vect)//COMPB interrupt handler
			{
				if(funcs[TIMER0_COMPB_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER0_COMPB_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR0BL
				void TIMER0SetB(uint16_t __B__)
				{
					OCR0BH = (uint8_t)__B__;		//set high registers of num
					OCR0BL = (uint8_t)(__B__ >> 8);//set low registers of num
				}
			#else //ifdef OCR0BL
				void TIMER0SetB(uint8_t __B__)
				{
					OCR0B = (uint8_t)__B__;//set B num
				}
			#endif //ifndef OCR0BL


			inline void TIMER0EnableCOMPBInterrupt()
			{
				TIMSK0 = (TIMSK0 & ~(1 << OCIE0B)) | (1<<OCIE0B);//enable interrupt on compare with B num
			}

			inline void TIMER0DisableCOMPBInterrupt()
			{
				TIMSK0 &= ~(1 << OCIE0B);//disable interrupt on compare with B num
			}

		#endif //if TIMER0_USE_COMPB == 1




		#if TIMER0_USE_OVF == 1//if using interrupt on overflow
			ISR(TIMER0_OVF_vect)//OVF interrupt handler
			{
				if(funcs[TIMER0_OVF_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER0_OVF_CUSTOMFUNC_ADDR]();//call custom function
			}
			
			inline void TIMER0EnableOVFISR()
			{
				TIMSK0 = (TIMSK0 & ~(1 << TOIE0)) | (1 << TOIE0);//enable interrupt on overflow
			}
			
			inline void TIMER0DisableOVFISR()
			{
				TIMSK0 &= ~(1 << TOIE0);
			}
			
		#endif //if TIMER0_USE_OVF == 1
	#endif //if defined(TCCR0A)
	
	
	
	#if defined(TCCR1A)//if mcu have TIMER1
		#pragma message "TIMER1 found"
		

		void TIMER1Init(uint8_t __mode__)
		{
			TCCR1B = 0;
			TIMSK1 = 0;//set param regs to zero
			
			TCCR1B |= __mode__;//set mode
		}
		
		inline void TIMER1SetCLK(uint8_t __source__)
		{
			TCCR1B = (TCCR1B & ~__source__) | __source__;
		}
		
		void TIMER1Init(uint8_t __mode__, uint8_t __source__)
		{
			TIMER1Init(__mode__);
			TIMER1SetCLK(__source__);
		}
		

		#if TIMER1_USE_COMPA == 1//if using interrupt on compare with A num
			ISR(TIMER1_COMPA_vect)//COMPA interrupt handler
			{
				if(funcs[TIMER1_COMPA_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER1_COMPA_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR1AL
				void TIMER1SetA(uint16_t __A__)
				{
					OCR1AH = (uint8_t)__A__;		//set high registers of num
					OCR1AL = (uint8_t)(__A__ >> 8);	//set low registers of num
				}
			#else //ifdef OCR2AL
				void TIMER1SetA(uint8_t __A__)
				{
					OCR1A = (uint8_t)__A__;//set B num
				}
			#endif //ifndef OCR1AL


			inline void TIMER1EnableCOMPAInterrupt()
			{
				TIMSK1 = (TIMSK1 & ~(1 << OCIE1A)) | (1 << OCIE1A);//enable interrupt on compare with A num
			}

			inline void TIMER1DisableCOMPAInterrupt()
			{
				TIMSK1 &= ~(1 << OCIE1A);//disable interrupt on compare with A num
			}

		#endif //if TIMER1_USE_COMPA == 1




		#if TIMER1_USE_COMPB == 1//if using interrupt on compare with B num
		 	ISR(TIMER1_COMPB_vect)//COMPB interrupt handler
			{
				if(funcs[TIMER1_COMPB_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER1_COMPB_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR1BL
				void TIMER1SetB(uint16_t __B__)
				{
					OCR1BH = (uint8_t)__B__;		//set high registers of num
					OCR1BL = (uint8_t)(__B__ >> 8);//set low registers of num
				}
			#else //ifdef OCR1BL
				void TIMER1SetB(uint8_t __B__)
				{
					OCR1B = (uint8_t)__B__;//set B num
				}
			#endif //ifndef OCR1BL


			inline void TIMER1EnableCOMPBInterrupt()
			{
				TIMSK1 = (TIMSK1 & ~(1 << OCIE1B)) | (1<<OCIE1B);//enable interrupt on compare with B num
			}

			inline void TIMER1DisableCOMPBInterrupt()
			{
				TIMSK1 &= ~(1 << OCIE1B);//disable interrupt on compare with B num
			}

		#endif //if TIMER1_USE_COMPB == 1




		#if TIMER1_USE_OVF == 1//if using interrupt on overflow
			ISR(TIMER1_OVF_vect)//OVF interrupt handler
			{
				if(funcs[TIMER1_OVF_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER1_OVF_CUSTOMFUNC_ADDR]();//call custom function
			}
			
			inline void TIMER1EnableOVFISR()
			{
				TIMSK1 = (TIMSK1 & ~(1 << TOIE1)) | (1 << TOIE1);//enable interrupt on overflow
			}
			
			inline void TIMER1DisableOVFISR()
			{
				TIMSK1 &= ~(1 << TOIE1);
			}
			
		#endif //if TIMER1_USE_OVF == 1
	#endif //if defined(TCCR1A)
	
	
	
	#if defined(TCCR2A)//if mcu have TIMER2
		#pragma message "TIMER2 found"
		

		void TIMER2Init(uint8_t __mode__)
		{
			TCCR2B = 0;
			TIMSK2 = 0;//set param regs to zero
			
			TCCR2B |= __mode__;//set mode
		}
		
		inline void TIMER2SetCLK(uint8_t __source__)
		{
			TCCR2B = (TCCR2B & ~__source__) | __source__;
		}
		
		void TIMER2Init(uint8_t __mode__, uint8_t __source__)
		{
			TIMER2Init(__mode__);
			TIMER2SetCLK(__source__);
		}
		

		#if TIMER2_USE_COMPA == 1//if using interrupt on compare with A num
			ISR(TIMER2_COMPA_vect)//COMPA interrupt handler
			{
				if(funcs[TIMER2_COMPA_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER2_COMPA_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR2AL
				void TIMER2SetA(uint16_t __A__)
				{
					OCR2AH = (uint8_t)__A__;		//set high registers of num
					OCR2AL = (uint8_t)(__A__ >> 8);	//set low registers of num
				}
			#else //ifdef OCR2AL
				void TIMER2SetA(uint8_t __A__)
				{
					OCR2A = (uint8_t)__A__;//set B num
				}
			#endif //ifndef OCR2AL


			inline void TIMER2EnableCOMPAInterrupt()
			{
				TIMSK2 = (TIMSK2 & ~(1 << OCIE2A)) | (1<<OCIE2A);//enable interrupt on compare with A num
			}

			inline void TIMER2DisableCOMPAInterrupt()
			{
				TIMSK2 &= ~(1 << OCIE2A);//disable interrupt on compare with A num
			}

		#endif //if TIMER2_USE_COMPA == 1




		#if TIMER2_USE_COMPB == 1//if using interrupt on compare with B num
		 	ISR(TIMER2_COMPB_vect)//COMPB interrupt handler
			{
				if(funcs[TIMER2_COMPB_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER2_COMPB_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR2BL
				void TIMER2SetB(uint16_t __B__)
				{
					OCR2BH = (uint8_t)__B__;		//set high registers of num
					OCR2BL = (uint8_t)(__B__ >> 8);//set low registers of num
				}
			#else //ifdef OCR2BL
				void TIMER2SetB(uint8_t __B__)
				{
					OCR2B = (uint8_t)__B__;//set B num
				}
			#endif //ifndef OCR2BL


			inline void TIMER2EnableCOMPBInterrupt()
			{
				TIMSK2 = (TIMSK2 & ~(1 << OCIE2B)) | (1 << OCIE2B);//enable interrupt on compare with B num
			}

			inline void TIMER2DisableCOMPBInterrupt()
			{
				TIMSK2 &= ~(1 << OCIE2B);//disable interrupt on compare with B num
			}

		#endif //if TIMER2_USE_COMPB == 1




		#if TIMER2_USE_OVF == 1//if using interrupt on overflow
			ISR(TIMER2_OVF_vect)//OVF interrupt handler
			{
				if(funcs[TIMER2_OVF_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER2_OVF_CUSTOMFUNC_ADDR]();//call custom function
			}
			
			inline void TIMER2EnableOVFISR()
			{
				TIMSK2 = (TIMSK2 & ~(1 << TOIE2)) | (1 << TOIE2);//enable interrupt on overflow
			}
			
			inline void TIMER2DisableOVFISR()
			{
				TIMSK2 &= ~(1 << TOIE2);
			}
			
		#endif //if TIMER2_USE_OVF == 1
	#endif //if defined(TCCR2A)
	
	
	
	#if defined(TCCR3A)//if mcu have TIMER3
		#pragma message "TIMER3 found"
		

		void TIMER3Init(uint8_t __mode__)
		{
			TCCR3B = 0;
			TIMSK3 = 0;//set param regs to zero
			
			TCCR3B |= __mode__;//set mode
		}
		
		inline void TIMER3SetCLK(uint8_t __source__)
		{
			TCCR3B = (TCCR3B & ~__source__) | __source__;
		}
		
		void TIMER3Init(uint8_t __mode__, uint8_t __source__)
		{
			TIMER3Init(__mode__);
			TIMER3SetCLK(__source__);
		}
		

		#if TIMER3_USE_COMPA == 1//if using interrupt on compare with A num
			ISR(TIMER3_COMPA_vect)//COMPA interrupt handler
			{
				if(funcs[TIMER3_COMPA_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER3_COMPA_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR3AL
				void TIMER3SetA(uint16_t __A__)
				{
					OCR3AH = (uint8_t)__A__;		//set high registers of num
					OCR3AL = (uint8_t)(__A__ >> 8);	//set low registers of num
				}
			#else //ifdef OCR3AL
				void TIMER3SetA(uint8_t __A__)
				{
					OCR3A = (uint8_t)__A__;//set B num
				}
			#endif //ifndef OCR3AL


			inline void TIMER3EnableCOMPAInterrupt()
			{
				TIMSK3 = (TIMSK3 & ~(1 << OCIE3A)) | (1<<OCIE3A);//enable interrupt on compare with A num
			}

			inline void TIMER3DisableCOMPAInterrupt()
			{
				TIMSK3 &= ~(1 << OCIE3A);//disable interrupt on compare with A num
			}

		#endif //if TIMER3_USE_COMPA == 1




		#if TIMER3_USE_COMPB == 1//if using interrupt on compare with B num
		 	ISR(TIMER3_COMPB_vect)//COMPB interrupt handler
			{
				if(funcs[TIMER3_COMPB_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER3_COMPB_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR3BL
				void TIMER3SetB(uint16_t __B__)
				{
					OCR3BH = (uint8_t)__B__;		//set high registers of num
					OCR3BL = (uint8_t)(__B__ >> 8);//set low registers of num
				}
			#else //ifdef OCR3BL
				void TIMER3SetB(uint8_t __B__)
				{
					OCR3B = (uint8_t)__B__;//set B num
				}
			#endif //ifndef OCR3BL


			inline void TIMER3EnableCOMPBInterrupt()
			{
				TIMSK3 = (TIMSK3 & ~(1 << OCIE3B)) | (1 << OCIE3B);//enable interrupt on compare with B num
			}

			inline void TIMER3DisableCOMPBInterrupt()
			{
				TIMSK3 &= ~(1 << OCIE3B);//disable interrupt on compare with B num
			}

		#endif //if TIMER3_USE_COMPB == 1




		#if TIMER3_USE_OVF == 1//if using interrupt on overflow
			ISR(TIMER3_OVF_vect)//OVF interrupt handler
			{
				if(funcs[TIMER3_OVF_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER3_OVF_CUSTOMFUNC_ADDR]();//call custom function
			}
			
			inline void TIMER3EnableOVFISR()
			{
				TIMSK3 = (TIMSK3 & ~(1 << TOIE3)) | (1 << TOIE3);//enable interrupt on overflow
			}
			
			inline void TIMER3DisableOVFISR()
			{
				TIMSK3 &= ~(1 << TOIE3);
			}
			
		#endif //if TIMER3_USE_OVF == 1
	#endif //if defined(TCCR3A)
	
	
	
	#if defined(TCCR4A)//if mcu have TIMER4
		#pragma message "TIMER4 found"
		

		void TIMER4Init(uint8_t __mode__)
		{
			TCCR4B = 0;
			TIMSK4 = 0;//set param regs to zero
			
			TCCR4B |= __mode__;//set mode
		}
		
		inline void TIMER4SetCLK(uint8_t __source__)
		{
			TCCR4B = (TCCR4B & ~__source__) | __source__;
		}
		
		void TIMER4Init(uint8_t __mode__, uint8_t __source__)
		{
			TIMER4Init(__mode__);
			TIMER4SetCLK(__source__);
		}
		

		#if TIMER4_USE_COMPA == 1//if using interrupt on compare with A num
			ISR(TIMER4_COMPA_vect)//COMPA interrupt handler
			{
				if(funcs[TIMER4_COMPA_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER4_COMPA_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR4AL
				void TIMER4SetA(uint16_t __A__)
				{
					OCR4AH = (uint8_t)__A__;		//set high registers of num
					OCR4AL = (uint8_t)(__A__ >> 8);	//set low registers of num
				}
			#else //ifdef OCR4AL
				void TIMER4SetA(uint8_t __A__)
				{
					OCR4A = (uint8_t)__A__;//set B num
				}
			#endif //ifndef OCR4AL


			inline void TIMER4EnableCOMPAInterrupt()
			{
				TIMSK4 = (TIMSK4 & ~(1 << OCIE4A)) | (1 << OCIE4A);//enable interrupt on compare with A num
			}

			inline void TIMER4DisableCOMPAInterrupt()
			{
				TIMSK4 &= ~(1 << OCIE4A);//disable interrupt on compare with A num
			}

		#endif //if TIMER4_USE_COMPA == 1




		#if TIMER4_USE_COMPB == 1//if using interrupt on compare with B num
		 	ISR(TIMER4_COMPB_vect)//COMPB interrupt handler
			{
				if(funcs[TIMER4_COMPB_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER4_COMPB_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR4BL
				void TIMER4SetB(uint16_t __B__)
				{
					OCR4BH = (uint8_t)__B__;		//set high registers of num
					OCR4BL = (uint8_t)(__B__ >> 8);//set low registers of num
				}
			#else //ifdef OCR4BL
				void TIMER4SetB(uint8_t __B__)
				{
					OCR4B = (uint8_t)__B__;//set B num
				}
			#endif //ifndef OCR4BL


			inline void TIMER4EnableCOMPBInterrupt()
			{
				TIMSK4 = (TIMSK4 & ~(1 << OCIE4B)) | (1 << OCIE4B);//enable interrupt on compare with B num
			}

			inline void TIMER4DisableCOMPBInterrupt()
			{
				TIMSK4 &= ~(1 << OCIE4B);//disable interrupt on compare with B num
			}

		#endif //if TIMER4_USE_COMPB == 1




		#if TIMER4_USE_OVF == 1//if using interrupt on overflow
			ISR(TIMER4_OVF_vect)//OVF interrupt handler
			{
				if(funcs[TIMER4_OVF_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER4_OVF_CUSTOMFUNC_ADDR]();//call custom function
			}
			
			inline void TIMER4EnableOVFISR()
			{
				TIMSK4 = (TIMSK4 & ~(1 << TOIE4)) | (1 << TOIE4);//enable interrupt on overflow
			}
			
			inline void TIMER4DisableOVFISR()
			{
				TIMSK4 &= ~(1 << TOIE4);
			}
			
		#endif //if TIMER4_USE_OVF == 1
	#endif //if defined(TCCR4A)
	
	
	
	#if defined(TCCR5A)//if mcu have TIMER5
		#pragma message "TIMER5 found"
		

		void TIMER5Init(uint8_t __mode__)
		{
			TCCR5B = 0;
			TIMSK5 = 0;//set param regs to zero
			
			TCCR5B |= __mode__;//set mode
		}
		
		inline void TIMER5SetCLK(uint8_t __source__)
		{
			TCCR5B = (TCCR5B & ~__source__) | __source__;
		}
		
		void TIMER5Init(uint8_t __mode__, uint8_t __source__)
		{
			TIMER5Init(__mode__);
			TIMER5SetCLK(__source__);
		}
		

		#if TIMER5_USE_COMPA == 1//if using interrupt on compare with A num
			ISR(TIMER5_COMPA_vect)//COMPA interrupt handler
			{
				if(funcs[TIMER5_COMPA_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER5_COMPA_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR5AL
				void TIMER5SetA(uint16_t __A__)
				{
					OCR5AH = (uint8_t)__A__;		//set high registers of num
					OCR5AL = (uint8_t)(__A__ >> 8);	//set low registers of num
				}
			#else //ifdef OCR5AL
				void TIMER5SetA(uint8_t __A__)
				{
					OCR5A = (uint8_t)__A__;//set B num
				}
			#endif //ifndef OCR5AL


			inline void TIMER5EnableCOMPAInterrupt()
			{
				TIMSK5 = (TIMSK5 & ~(1 << OCIE5A)) | (1 << OCIE5A);//enable interrupt on compare with A num
			}

			inline void TIMER5DisableCOMPAInterrupt()
			{
				TIMSK5 &= ~(1 << OCIE5A);//disable interrupt on compare with A num
			}

		#endif //if TIMER5_USE_COMPA == 1




		#if TIMER5_USE_COMPB == 1//if using interrupt on compare with B num
		 	ISR(TIMER5_COMPB_vect)//COMPB interrupt handler
			{
				if(funcs[TIMER5_COMPB_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER5_COMPB_CUSTOMFUNC_ADDR]();//call custom function
			}

			#ifdef OCR5BL
				void TIMER5SetB(uint16_t __B__)
				{
					OCR5BH = (uint8_t)__B__;		//set high registers of num
					OCR5BL = (uint8_t)(__B__ >> 8);//set low registers of num
				}
			#else //ifdef OCR5BL
				void TIMER5SetB(uint8_t __B__)
				{
					OCR5B = (uint8_t)__B__;//set B num
				}
			#endif //ifndef OCR5BL


			inline void TIMER5EnableCOMPBInterrupt()
			{
				TIMSK5 = (TIMSK5 & ~(1 << OCIE5B)) | (1 << OCIE5B);//enable interrupt on compare with B num
			}

			inline void TIMER5DisableCOMPBInterrupt()
			{
				TIMSK5 &= ~(1 << OCIE5B);//disable interrupt on compare with B num
			}

		#endif //if TIMER5_USE_COMPB == 1




		#if TIMER5_USE_OVF == 1//if using interrupt on overflow
			ISR(TIMER5_OVF_vect)//OVF interrupt handler
			{
				if(funcs[TIMER5_OVF_CUSTOMFUNC_ADDR] != NULL)
					funcs[TIMER5_OVF_CUSTOMFUNC_ADDR]();//call custom function
			}
			
			inline void TIMER5EnableOVFISR()
			{
				TIMSK5 = (TIMSK5 & ~(1 << TOIE5)) | (1 << TOIE5);//enable interrupt on overflow
			}
			
			inline void TIMER5DisableOVFISR()
			{
				TIMSK5 &= ~(1 << TOIE5);
			}
			
		#endif //if TIMER5_USE_OVF == 1
	#endif //if defined(TCCR5A)
	
	
#endif //if USE_TIMERS == 1

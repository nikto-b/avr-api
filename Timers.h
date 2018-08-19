#if USE_TIMERS == 1

	#include "timerCustomfuncAddrs.h"
	#include "Timers.c"
	//#include "TimerModes.h"
	
	#ifdef TCCR0A 	//TIMER0
		void TIMER0Init(uint8_t);
		void TIMER0SetCLK(uint8_t);
		void TIMER0Init(uint8_t, uint8_t);
		
		
		//just for fun
		#ifdef OCR0AL//check 16 bit
			#pragma message "TIMER0 16 bit"
		#else //ifdef OCR0AL
			#pragma message "TIMER0 8 bit"			
		#endif //ifndef OCR0AL
		
		
		#if TIMER0_USE_COMPA == 1//if using interrupt on compare with A num
			#ifdef OCR0AL
				void TIMER0SetA(uint16_t);
			#else //ifdef OCR0AL
				void TIMER0SetA(uint8_t);
			#endif //ifndef OCR0AL
		#endif //if TIMER0_USE_COMPA == 1
		
		#if TIMER0_USE_COMPB == 1
			#ifdef OCR0BL
				void TIMER0SetB(uint16_t);
			#else //ifdef OCR0BL
				void TIMER0SetB(uint8_t);
			#endif //ifndef OCR0BL
		#endif //if TIMER0_USE_COMPB == 1

		#if TIMER0_USE_OVF == 1
			
		#endif //if TIMER0_USE_OVF == 1
		
	#endif //ifdef TCCR0A
	
	
	
	#ifdef TCCR1A 	//TIMER1
		void TIMER1Init(uint8_t);
		void TIMER1SetCLK(uint8_t);
		void TIMER1Init(uint8_t, uint8_t);
		
		
		//just for fun
		#ifdef OCR1AL//check 16 bit
			#pragma message "TIMER1 16 bit"
		#else //ifdef OCR1AL
			#pragma message "TIMER1 8 bit"			
		#endif //ifndef OCR1AL
		
		
		#if TIMER1_USE_COMPA == 1//if using interrupt on compare with A num
			#ifdef OCR1AL
				void TIMER1SetA(uint16_t);
			#else //ifdef OCR1AL
				void TIMER1SetA(uint8_t);
			#endif //ifndef OCR1AL
		#endif //if TIMER1_USE_COMPA == 1
		
		#if TIMER1_USE_COMPB == 1
			#ifdef OCR1BL
				void TIMER1SetB(uint16_t);
			#else //ifdef OCR1BL
				void TIMER1SetB(uint8_t);
			#endif //ifndef OCR1BL
		#endif //if TIMER1_USE_COMPB == 1

		#if TIMER1_USE_OVF == 1
			
		#endif //if TIMER1_USE_OVF == 1
		
	#endif //ifdef TCCR1A
	
	
	
	#ifdef TCCR2A //TIMER2
		void TIMER2Init(uint8_t);
		void TIMER2SetCLK(uint8_t);
		void TIMER2Init(uint8_t, uint8_t);
		
		
		//just for fun
		#ifdef OCR2AL//check 16 bit
			#pragma message "TIMER2 16 bit"
		#else //ifdef OCR2AL
			#pragma message "TIMER2 8 bit"			
		#endif //ifndef OCR2AL
		
		
		#if TIMER2_USE_COMPA == 1//if using interrupt on compare with A num
			#ifdef OCR2AL
				void TIMER2SetA(uint16_t);
			#else //ifdef OCR2AL
				void TIMER2SetA(uint8_t);
			#endif //ifndef OCR2AL
		#endif //if TIMER2_USE_COMPA == 1
		
		#if TIMER2_USE_COMPB == 1
			#ifdef OCR2BL
				void TIMER2SetB(uint16_t);
			#else //ifdef OCR2BL
				void TIMER2SetB(uint8_t);
			#endif //ifndef OCR2BL
		#endif //if TIMER2_USE_COMPB == 1

		#if TIMER2_USE_OVF == 1
			
		#endif //if TIMER2_USE_OVF == 1
		
	#endif //ifdef TCCR2A
	
	
	
	#ifdef TCCR3A //TIMER3
		void TIMER3Init(uint8_t);
		void TIMER3SetCLK(uint8_t);
		void TIMER3Init(uint8_t, uint8_t);
		
		
		//just for fun
		#ifdef OCR3AL//check 16 bit
			#pragma message "TIMER3 16 bit"
		#else //ifdef OCR3AL
			#pragma message "TIMER3 8 bit"			
		#endif //ifndef OCR3AL
		
		
		#if TIMER3_USE_COMPA == 1//if using interrupt on compare with A num
			#ifdef OCR3AL
				void TIMER3SetA(uint16_t);
			#else //ifdef OCR3AL
				void TIMER3SetA(uint8_t);
			#endif //ifndef OCR3AL
		#endif //if TIMER3_USE_COMPA == 1
		
		#if TIMER3_USE_COMPB == 1
			#ifdef OCR3BL
				void TIMER3SetB(uint16_t);
			#else //ifdef OCR3BL
				void TIMER3SetB(uint8_t);
			#endif //ifndef OCR3BL
		#endif //if TIMER3_USE_COMPB == 1

		#if TIMER3_USE_OVF == 1
			
		#endif //if TIMER3_USE_OVF == 1
		
	#endif //ifdef TCCR3A
	
	
	
	#ifdef TCCR4A //TIMER4
		void TIMER4Init(uint8_t);
		void TIMER4SetCLK(uint8_t);
		void TIMER4Init(uint8_t, uint8_t);
		
		
		//just for fun
		#ifdef OCR4AL//check 16 bit
			#pragma message "TIMER4 16 bit"
		#else //ifdef OCR4AL
			#pragma message "TIMER4 8 bit"			
		#endif //ifndef OCR4AL
		
		
		#if TIMER4_USE_COMPA == 1//if using interrupt on compare with A num
			#ifdef OCR4AL
				void TIMER4SetA(uint16_t);
			#else //ifdef OCR4AL
				void TIMER4SetA(uint8_t);
			#endif //ifndef OCR4AL
		#endif //if TIMER4_USE_COMPA == 1
		
		#if TIMER4_USE_COMPB == 1
			#ifdef OCR4BL
				void TIMER4SetB(uint16_t);
			#else //ifdef OCR4BL
				void TIMER4SetB(uint8_t);
			#endif //ifndef OCR4BL
		#endif //if TIMER4_USE_COMPB == 1

		#if TIMER4_USE_OVF == 1
			
		#endif //if TIMER4_USE_OVF == 1
		
	#endif //ifdef TCCR4A
	
	
	
	#ifdef TCCR5A //TIMER5
		void TIMER5Init(uint8_t);
		void TIMER5SetCLK(uint8_t);
		void TIMER5Init(uint8_t, uint8_t);
		
		
		//just for fun
		#ifdef OCR5AL//check 16 bit
			#pragma message "TIMER5 16 bit"
		#else //ifdef OCR5AL
			#pragma message "TIMER5 8 bit"			
		#endif //ifndef OCR5AL
		
		
		#if TIMER5_USE_COMPA == 1//if using interrupt on compare with A num
			#ifdef OCR5AL
				void TIMER5SetA(uint16_t);
			#else //ifdef OCR5AL
				void TIMER5SetA(uint8_t);
			#endif //ifndef OCR5AL
		#endif //if TIMER5_USE_COMPA == 1
		
		#if TIMER5_USE_COMPB == 1
			#ifdef OCR5BL
				void TIMER5SetB(uint16_t);
			#else //ifdef OCR5BL
				void TIMER5SetB(uint8_t);
			#endif //ifndef OCR5BL
		#endif //if TIMER5_USE_COMPB == 1

		#if TIMER5_USE_OVF == 1
			
		#endif //if TIMER5_USE_OVF == 1
		
	#endif //ifdef TCCR5A
	
	
#endif

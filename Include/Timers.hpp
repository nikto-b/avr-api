#pragma once

#include "base.hpp"
#include "TimerModes.hpp"


void analogWrite(uint8_t _pin, uint16_t _num);
void analogWrite(uint8_t _timer, uint8_t _ch, uint16_t _num);


#ifdef TCCR0A 	//TIMER0
	void TIMER0Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
	void TIMER0SetCLK(uint8_t);
	void TIMER0Flush();

	//just for fun
	#ifdef OCR0AL//check 16 bit
		#pragma message "TIMER0 16 bit"
	#else //ifdef OCR0AL
		#pragma message "TIMER0 8 bit"
	#endif //ifndef OCR0AL

	#ifdef OCR0AL
		void TIMER0SetA(uint16_t);
	#else //ifdef OCR0AL
		void TIMER0SetA(uint8_t);
	#endif //ifndef OCR0AL

	  void TIMER0EnableCOMPAInterrupt();
	  void TIMER0DisableCOMPAInterrupt();

	#ifdef OCR0BL
		void TIMER0SetB(uint16_t);
	#else //ifdef OCR0BL
		void TIMER0SetB(uint8_t);
	#endif //ifndef OCR0BL

	  void TIMER0EnableCOMPBInterrupt();
	  void TIMER0DisableCOMPBInterrupt();

	#ifdef OCR0CL
		void TIMER0SetC(uint16_t);
	#else //ifdef OCR0CL
		void TIMER0SetC(uint8_t);
	#endif //ifndef OCR0CL

	  void TIMER0EnableCOMPCInterrupt();
	  void TIMER0DisableCOMPCInterrupt();
#endif //ifdef TCCR0A



#ifdef TCCR1A 	//TIMER1
	void TIMER1Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
	void TIMER1SetCLK(uint8_t);
	void TIMER1Flush();

	//just for fun
	#ifdef OCR1AL//check 16 bit
		#pragma message "TIMER1 16 bit"
	#else //ifdef OCR1AL
		#pragma message "TIMER1 8 bit"
	#endif //ifndef OCR1AL

	#ifdef OCR1AL
		void TIMER1SetA(uint16_t);
	#else //ifdef OCR1AL
		void TIMER1SetA(uint8_t);
	#endif //ifndef OCR1AL

	  void TIMER1EnableCOMPAInterrupt();
	  void TIMER1DisableCOMPAInterrupt();

	#ifdef OCR1BL
		void TIMER1SetB(uint16_t);
	#else //ifdef OCR1BL
		void TIMER1SetB(uint8_t);
	#endif //ifndef OCR1BL

	  void TIMER1EnableCOMPBInterrupt();
	  void TIMER1DisableCOMPBInterrupt();

	#if defined(OCR1CL)
		void TIMER1SetC(uint16_t);
	#else //ifdef OCR1CL
		void TIMER1SetC(uint8_t);
	#endif //ifndef OCR1CL

	  void TIMER1EnableCOMPCInterrupt();
	  void TIMER1DisableCOMPCInterrupt();
#endif //ifdef TCCR1A





#ifdef TCCR2A 	//TIMER2
	void TIMER2Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
	void TIMER2SetCLK(uint8_t);
	void TIMER2Flush();

	//just for fun
	#ifdef OCR2AL//check 16 bit
		#pragma message "TIMER2 16 bit"
	#else //ifdef OCR2AL
		#pragma message "TIMER2 8 bit"
	#endif //ifndef OCR2AL

	#ifdef OCR2AL
		void TIMER2SetA(uint16_t);
	#else //ifdef OCR2AL
		void TIMER2SetA(uint8_t);
	#endif //ifndef OCR2AL

	  void TIMER2EnableCOMPAInterrupt();
	  void TIMER2DisableCOMPAInterrupt();

	#ifdef OCR2BL
		void TIMER2SetB(uint16_t);
	#else //ifdef OCR2BL
		void TIMER2SetB(uint8_t);
	#endif //ifndef OCR2BL

	  void TIMER2EnableCOMPBInterrupt();
	  void TIMER2DisableCOMPBInterrupt();

	#ifdef OCR2CL
		void TIMER2SetC(uint16_t);
	#else //ifdef OCR2CL
		void TIMER2SetC(uint8_t);
	#endif //ifndef OCR2CL

	  void TIMER2EnableCOMPCInterrupt();
	  void TIMER2DisableCOMPCInterrupt();
#endif //ifdef TCCR2A





#ifdef TCCR3A 	//TIMER3
	void TIMER3Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
	void TIMER3SetCLK(uint8_t);
	void TIMER3Flush();

	//just for fun
	#ifdef OCR3AL//check 16 bit
		#pragma message "TIMER3 16 bit"
	#else //ifdef OCR3AL
		#pragma message "TIMER3 8 bit"
	#endif //ifndef OCR3AL

	#ifdef OCR3AL
		void TIMER3SetA(uint16_t);
	#else //ifdef OCR3AL
		void TIMER3SetA(uint8_t);
	#endif //ifndef OCR3AL

	  void TIMER3EnableCOMPAInterrupt();
	  void TIMER3DisableCOMPAInterrupt();

	#ifdef OCR3BL
		void TIMER3SetB(uint16_t);
	#else //ifdef OCR3BL
		void TIMER3SetB(uint8_t);
	#endif //ifndef OCR3BL

	  void TIMER3EnableCOMPBInterrupt();
	  void TIMER3DisableCOMPBInterrupt();

	#ifdef OCR3CL
		void TIMER3SetC(uint16_t);
	#else //ifdef OCR3CL
		void TIMER3SetC(uint8_t);
	#endif //ifndef OCR3CL

	  void TIMER3EnableCOMPCInterrupt();
	  void TIMER3DisableCOMPCInterrupt();
#endif //ifdef TCCR3A





#ifdef TCCR4A 	//TIMER4
	void TIMER4Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
	void TIMER4SetCLK(uint8_t);
	void TIMER4Flush();

	//just for fun
	#ifdef OCR4AL//check 16 bit
		#pragma message "TIMER4 16 bit"
	#else //ifdef OCR4AL
		#pragma message "TIMER4 8 bit"
	#endif //ifndef OCR4AL

	#ifdef OCR4AL
		void TIMER4SetA(uint16_t);
	#else //ifdef OCR4AL
		void TIMER4SetA(uint8_t);
	#endif //ifndef OCR4AL

	  void TIMER4EnableCOMPAInterrupt();
	  void TIMER4DisableCOMPAInterrupt();

	#ifdef OCR4BL
		void TIMER4SetB(uint16_t);
	#else //ifdef OCR4BL
		void TIMER4SetB(uint8_t);
	#endif //ifndef OCR4BL

	  void TIMER4EnableCOMPBInterrupt();
	  void TIMER4DisableCOMPBInterrupt();

	#ifdef OCR4CL
		void TIMER4SetC(uint16_t);
	#else //ifdef OCR4CL
		void TIMER4SetC(uint8_t);
	#endif //ifndef OCR4CL

	  void TIMER4EnableCOMPCInterrupt();
	  void TIMER4DisableCOMPCInterrupt();
#endif //ifdef TCCR4A





#ifdef TCCR5A 	//TIMER5
	void TIMER5Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
	void TIMER5SetCLK(uint8_t);
	void TIMER5Flush();

	//just for fun
	#ifdef OCR5AL//check 16 bit
		#pragma message "TIMER5 16 bit"
	#else //ifdef OCR5AL
		#pragma message "TIMER5 8 bit"
	#endif //ifndef OCR5AL

	#ifdef OCR5AL
		void TIMER5SetA(uint16_t);
	#else //ifdef OCR5AL
		void TIMER5SetA(uint8_t);
	#endif //ifndef OCR5AL

	  void TIMER5EnableCOMPAInterrupt();
	  void TIMER5DisableCOMPAInterrupt();

	#ifdef OCR5BL
		void TIMER5SetB(uint16_t);
	#else //ifdef OCR5BL
		void TIMER5SetB(uint8_t);
	#endif //ifndef OCR5BL

	  void TIMER5EnableCOMPBInterrupt();
	  void TIMER5DisableCOMPBInterrupt();

	#ifdef OCR5CL
		void TIMER5SetC(uint16_t);
	#else //ifdef OCR5CL
		void TIMER5SetC(uint8_t);
	#endif //ifndef OCR5CL

	  void TIMER5EnableCOMPCInterrupt();
	  void TIMER5DisableCOMPCInterrupt();
#endif //ifdef TCCR5A





#ifdef TCCR6A 	//TIMER6
	void TIMER6Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
	void TIMER6SetCLK(uint8_t);
	void TIMER6Flush();

	//just for fun
	#ifdef OCR6AL//check 16 bit
		#pragma message "TIMER6 16 bit"
	#else //ifdef OCR6AL
		#pragma message "TIMER6 8 bit"
	#endif //ifndef OCR6AL

	#ifdef OCR6AL
		void TIMER6SetA(uint16_t);
	#else //ifdef OCR6AL
		void TIMER6SetA(uint8_t);
	#endif //ifndef OCR6AL

	  void TIMER6EnableCOMPAInterrupt();
	  void TIMER6DisableCOMPAInterrupt();

	#ifdef OCR6BL
		void TIMER6SetB(uint16_t);
	#else //ifdef OCR6BL
		void TIMER6SetB(uint8_t);
	#endif //ifndef OCR6BL

	  void TIMER6EnableCOMPBInterrupt();
	  void TIMER6DisableCOMPBInterrupt();

	#ifdef OCR6CL
		void TIMER6SetC(uint16_t);
	#else //ifdef OCR6CL
		void TIMER6SetC(uint8_t);
	#endif //ifndef OCR6CL

	  void TIMER6EnableCOMPCInterrupt();
	  void TIMER6DisableCOMPCInterrupt();
#endif //ifdef TCCR6A





#ifdef TCCR7A 	//TIMER7
	void TIMER7Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
	void TIMER7SetCLK(uint8_t);
	void TIMER7Flush();

	//just for fun
	#ifdef OCR7AL//check 16 bit
		#pragma message "TIMER7 16 bit"
	#else //ifdef OCR7AL
		#pragma message "TIMER7 8 bit"
	#endif //ifndef OCR7AL

	#ifdef OCR7AL
		void TIMER7SetA(uint16_t);
	#else //ifdef OCR7AL
		void TIMER7SetA(uint8_t);
	#endif //ifndef OCR7AL

	  void TIMER7EnableCOMPAInterrupt();
	  void TIMER7DisableCOMPAInterrupt();

	#ifdef OCR7BL
		void TIMER7SetB(uint16_t);
	#else //ifdef OCR7BL
		void TIMER7SetB(uint8_t);
	#endif //ifndef OCR7BL

	  void TIMER7EnableCOMPBInterrupt();
	  void TIMER7DisableCOMPBInterrupt();

	#ifdef OCR7CL
		void TIMER7SetC(uint16_t);
	#else //ifdef OCR7CL
		void TIMER7SetC(uint8_t);
	#endif //ifndef OCR7CL

	  void TIMER7EnableCOMPCInterrupt();
	  void TIMER7DisableCOMPCInterrupt();
#endif //ifdef TCCR7A





#ifdef TCCR8A 	//TIMER8
	void TIMER8Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
	void TIMER8SetCLK(uint8_t);
	void TIMER8Flush();

	//just for fun
	#ifdef OCR8AL//check 16 bit
		#pragma message "TIMER8 16 bit"
	#else //ifdef OCR8AL
		#pragma message "TIMER8 8 bit"
	#endif //ifndef OCR8AL

	#ifdef OCR8AL
		void TIMER8SetA(uint16_t);
	#else //ifdef OCR8AL
		void TIMER8SetA(uint8_t);
	#endif //ifndef OCR8AL

	  void TIMER8EnableCOMPAInterrupt();
	  void TIMER8DisableCOMPAInterrupt();

	#ifdef OCR8BL
		void TIMER8SetB(uint16_t);
	#else //ifdef OCR8BL
		void TIMER8SetB(uint8_t);
	#endif //ifndef OCR8BL

	  void TIMER8EnableCOMPBInterrupt();
	  void TIMER8DisableCOMPBInterrupt();

	#ifdef OCR8CL
		void TIMER8SetC(uint16_t);
	#else //ifdef OCR8CL
		void TIMER8SetC(uint8_t);
	#endif //ifndef OCR8CL

	  void TIMER8EnableCOMPCInterrupt();
	  void TIMER8DisableCOMPCInterrupt();
#endif //ifdef TCCR8A

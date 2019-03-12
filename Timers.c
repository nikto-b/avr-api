#pragma once

#include "Timers.h"
#include "customFuncAddr.h"

#define GENINIT(n)												\
/*															*/	\
/* Function TIMERnInit										*/	\
/* Desc     init T/Cn 										*/	\
/* Input    _com: what Compare Output Mode use to 			*/	\
/*			_wfmode: what Waveform generation mode use to 	*/	\
/*			_clk: what clock source use to 					*/	\
/* Output   none	 										*/	\
/**/															\
void TIMER ## n ## Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk)\
{																\
	TCCR ## n ## A = (TCCR ## n ## A & ~(_wfmode | _com)) | (_wfmode | _com);\
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
void TIMER ## n ## Set ## k (uint16_t __k)						\
{																\
	OCR ## n ## k ## L = (uint8_t)__k;		/*set high registers of num*/\
	OCR ## n ## k ## H = (uint8_t)(__k >> 8);	/*set low registers of num*/\
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
void TIMER ## n ## EnableCOMP ## k ## Interrupt(void)	\
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
void TIMER ## n ## DisableCOMP ## k ## Interrupt(void)	\
{																\
	TIMSK ## n &= ~(1 << OCIE ## n ## k );/*disable interrupt on compare with k num*/\
}

#define GENFLUSH(n)												\
/*														*/		\
/* Function TIMERnDisableCOMPkInterrupt					*/		\
/* Desc     Disable interrupt on compare with k num		*/		\
/* Input    none										*/		\
/* Output   none										*/		\
/**/															\
void TIMER ## n ## Flush()										\
{																\
	TIMSK ## n = 0;												\
	TCCR ## n ## A = 0;											\
	TCCR ## n ## B = 0;											\
}


#ifdef TCCR0A
	GENINIT(0)
	GENSETCLK(0)
	GENFLUSH(0)
	#if (defined(OCIE0A))
		GENISR_COMPk(0, A)
		#ifdef OCR0AL
			GENSETk_16B(0, A)
		#else
			GENSETk_8B(0, A)
		#endif
		GENENABLECOMPkINTERRUPT(0, A)
		GENDISABLECOMPkINTERRUPT(0, A)
	#endif //if defined(OCIE0A) && TIMER0_USE_COMPA

	#if (defined(OCIE0B))
		GENISR_COMPk(0, B)
		#ifdef OCR0BL
			GENSETk_16B(0, B)
		#else
			GENSETk_8B(0, B)
		#endif
		GENENABLECOMPkINTERRUPT(0, B)
		GENDISABLECOMPkINTERRUPT(0, B)
	#endif //if defined(OCIE0B) && TIMER0_USE_COMPB

	#if (defined(OCIE0C))
		GENISR_COMPk(0, C)
		#ifdef OCR0CL
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
	GENFLUSH(1)
	#if (defined(OCIE1A))
		GENISR_COMPk(1, A)
		#ifdef OCR1AL
			GENSETk_16B(1, A)
		#else
			GENSETk_8B(1, A)
		#endif
		GENENABLECOMPkINTERRUPT(1, A)
		GENDISABLECOMPkINTERRUPT(1, A)
	#endif //if defined(OCIE1A) && TIMER1_USE_COMPA

	#if (defined(OCIE1B))
		GENISR_COMPk(1, B)
		#ifdef OCR1BL
			GENSETk_16B(1, B)
		#else
			GENSETk_8B(1, B)
		#endif
		GENENABLECOMPkINTERRUPT(1, B)
		GENDISABLECOMPkINTERRUPT(1, B)
	#endif //if defined(OCIE1B) && TIMER1_USE_COMPB

	#if (defined(OCIE1C))
		GENISR_COMPk(1, C)
		#ifdef OCR1CL
			GENSETk_16B(1, C)
		#else
			GENSETk_8B(1, C)
		#endif
		//void TIMER1SetC (uint16_t __k)						\
		//{																\
		//	OCR1CH = (uint8_t)__k;		/*set high registers of num*/\
		//	OCR1CL = (uint8_t)(__k >> 8);	/*set low registers of num*/\
		//}

		GENENABLECOMPkINTERRUPT(1, C)
		GENDISABLECOMPkINTERRUPT(1, C)
	#endif //if defined(OCIE1C) && TIMER1_USE_COMPC
#endif	//ifdef TCCR1A




#ifdef TCCR2A
	GENINIT(2)
	GENSETCLK(2)
	GENFLUSH(2)
	#if (defined(OCIE2A))
		GENISR_COMPk(2, A)
		#ifdef OCR2AL
			GENSETk_16B(2, A)
		#else
			GENSETk_8B(2, A)
		#endif
		GENENABLECOMPkINTERRUPT(2, A)
		GENDISABLECOMPkINTERRUPT(2, A)
	#endif //if defined(OCIE2A) && TIMER2_USE_COMPA

	#if (defined(OCIE2B))
		GENISR_COMPk(2, B)
		#ifdef OCR2BL
			GENSETk_16B(2, B)
		#else
			GENSETk_8B(2, B)
		#endif
		GENENABLECOMPkINTERRUPT(2, B)
		GENDISABLECOMPkINTERRUPT(2, B)
	#endif //if defined(OCIE2B) && TIMER2_USE_COMPB

	#if (defined(OCIE2C))
		GENISR_COMPk(2, C)
		#ifdef OCR2CL
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
	GENFLUSH(3)
	#ifdef OCIE3A
		GENISR_COMPk(3, A)
		#ifdef OCR3AL
			GENSETk_16B(3, A)
		#else
			GENSETk_8B(3, A)
		#endif
		GENENABLECOMPkINTERRUPT(3, A)
		GENDISABLECOMPkINTERRUPT(3, A)
	#endif //if defined(OCIE3A) && TIMER3_USE_COMPA

	#if (defined(OCIE3B))
		GENISR_COMPk(3, B)
		#ifdef OCR3BL
			GENSETk_16B(3, B)
		#else
			GENSETk_8B(3, B)
		#endif
		GENENABLECOMPkINTERRUPT(3, B)
		GENDISABLECOMPkINTERRUPT(3, B)
	#endif //if defined(OCIE3B) && TIMER3_USE_COMPB

	#if (defined(OCIE3C))
		GENISR_COMPk(3, C)
		#ifdef OCR3CL
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
	GENFLUSH(4)
	#if (defined(OCIE4A))
		GENISR_COMPk(4, A)
		#ifdef OCR4AL
			GENSETk_16B(4, A)
		#else
			GENSETk_8B(4, A)
		#endif
		GENENABLECOMPkINTERRUPT(4, A)
		GENDISABLECOMPkINTERRUPT(4, A)
	#endif //if defined(OCIE4A) && TIMER4_USE_COMPA

	#if (defined(OCIE4B))
		GENISR_COMPk(4, B)
		#ifdef OCR4BL
			GENSETk_16B(4, B)
		#else
			GENSETk_8B(4, B)
		#endif
		GENENABLECOMPkINTERRUPT(4, B)
		GENDISABLECOMPkINTERRUPT(4, B)
	#endif //if defined(OCIE4B) && TIMER4_USE_COMPB

	#if (defined(OCIE4C))
		GENISR_COMPk(4, C)
		#ifdef OCR4CL
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
	GENFLUSH(5)
	#if (defined(OCIE5A))
		GENISR_COMPk(5, A)
		#ifdef OCR5AL
			GENSETk_16B(5, A)
		#else
			GENSETk_8B(5, A)
		#endif
		GENENABLECOMPkINTERRUPT(5, A)
		GENDISABLECOMPkINTERRUPT(5, A)
	#endif //if defined(OCIE5A) && TIMER5_USE_COMPA

	#if (defined(OCIE5B))
		GENISR_COMPk(5, B)
		#ifdef OCR5BL
			GENSETk_16B(5, B)
		#else
			GENSETk_8B(5, B)
		#endif
		GENENABLECOMPkINTERRUPT(5, B)
		GENDISABLECOMPkINTERRUPT(5, B)
	#endif //if defined(OCIE5B) && TIMER5_USE_COMPB

	#if (defined(OCIE5C))
		GENISR_COMPk(5, C)
		#ifdef OCR5CL
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
	GENFLUSH(6)
	#if (defined(OCIE6A))
		GENISR_COMPk(6, A)
		#ifdef OCR6AL
			GENSETk_16B(6, A)
		#else
			GENSETk_8B(6, A)
		#endif
		GENENABLECOMPkINTERRUPT(6, A)
		GENDISABLECOMPkINTERRUPT(6, A)
	#endif //if defined(OCIE6A) && TIMER6_USE_COMPA

	#if (defined(OCIE6B))
		GENISR_COMPk(6, B)
		#ifdef OCR6BL
			GENSETk_16B(6, B)
		#else
			GENSETk_8B(6, B)
		#endif
		GENENABLECOMPkINTERRUPT(6, B)
		GENDISABLECOMPkINTERRUPT(6, B)
	#endif //if defined(OCIE6B) && TIMER6_USE_COMPB

	#if (defined(OCIE6C) && TIMER6_USE_COMPC == 1)
		GENISR_COMPk(6, C)
		#ifdef OCR6CL
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
	GENFLUSH(7)
	#if (defined(OCIE7A))
		GENISR_COMPk(7, A)
		#ifdef OCR7AL
			GENSETk_16B(7, A)
		#else
			GENSETk_8B(7, A)
		#endif
		GENENABLECOMPkINTERRUPT(7, A)
		GENDISABLECOMPkINTERRUPT(7, A)
	#endif //if defined(OCIE7A) && TIMER7_USE_COMPA

	#if (defined(OCIE7B) && TIMER7_USE_COMPB == 1)
		GENISR_COMPk(7, B)
		#ifdef OCR7BL
			GENSETk_16B(7, B)
		#else
			GENSETk_8B(7, B)
		#endif
		GENENABLECOMPkINTERRUPT(7, B)
		GENDISABLECOMPkINTERRUPT(7, B)
	#endif //if defined(OCIE7B) && TIMER7_USE_COMPB

	#if (defined(OCIE7C))
		GENISR_COMPk(7, C)
		#ifdef OCR7CL
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
	GENFLUSH(8)
	#if (defined(OCIE8A))
		GENISR_COMPk(8, A)
		#ifdef OCR8AL
			GENSETk_16B(8, A)
		#else
			GENSETk_8B(8, A)
		#endif
		GENENABLECOMPkINTERRUPT(8, A)
		GENDISABLECOMPkINTERRUPT(8, A)
	#endif //if defined(OCIE8A) && TIMER8_USE_COMPA

	#if (defined(OCIE8B))
		GENISR_COMPk(8, B)
		#ifdef OCR8BL
			GENSETk_16B(8, B)
		#else
			GENSETk_8B(8, B)
		#endif
		GENENABLECOMPkINTERRUPT(8, B)
		GENDISABLECOMPkINTERRUPT(8, B)
	#endif //if defined(OCIE8B) && TIMER8_USE_COMPB

	#if (defined(OCIE8C))
		GENISR_COMPk(8, C)
		#ifdef OCR8CL
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




void analogWrite(uint8_t _pin, uint16_t _num)
{
	uint8_t _timer = _pin / 3;
	uint8_t _ch = _pin % 3;
	analogWrite(_timer, _ch, _num);
}

void analogWrite(uint8_t _timer, uint8_t _ch, uint16_t _num)
{
	switch(_timer)
	{
		#ifdef TCCR0A
		case 0:
		{
			switch(_ch)
			{
				#ifdef OCIE0A
				case 0:
				{
					TIMER0Init(TIMER0_COMA_FPWM_CM_ST, TIMER0_WF_FPWM, TIMER0_CLK_SRC_1024);
					TIMER0SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE0B
				case 1:
				{
					TIMER0Init(TIMER0_COMB_FPWM_NORMAL, TIMER0_WF_FPWM, TIMER0_CLK_SRC_1024);
					TIMER0SetB(_num);
					break;
				}
				#endif
				#ifdef OCIE0C
				case 2:
				{
					TIMER0Init(TIMER0_COMC_FPWM_NORMAL, TIMER0_WF_FPWM, TIMER0_CLK_SRC_1024);
					TIMER0SetC(_num);
					break;
				}
				#endif
			}
			break;
		}
		#endif
		#ifdef TCCR1A
		case 1:
		{
			switch(_ch)
			{
				#ifdef OCIE1A
				case 0:
				{
					TIMER1Init(TIMER1_COMA_CM_ST, TIMER1_WF_FPWM_8B, TIMER1_CLK_SRC_1024);
					TIMER1SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE1B
				case 1:
				{
					TIMER1Init(TIMER1_COMB_CM_ST, TIMER1_WF_FPWM_8B, TIMER1_CLK_SRC_1024);
					TIMER1SetB(_num);
					break;
				}
				#endif
				#ifdef OCIE1C
				case 2:
				{
					TIMER1Init(TIMER1_COMC_CM_ST, TIMER1_WF_FPWM_8B, TIMER1_CLK_SRC_1024);
					TIMER1SetC(_num);
					break;
				}
				#endif
			}
			break;
		}
		#endif
		#ifdef TCCR2A
		case 2:
		{
			switch(_ch)
			{
				#ifdef OCIE2A
				case 0:
				{
					TIMER2Init(TIMER2_COMA_CM_ST, TIMER2_WF_FPWM, TIMER2_CLK_SRC_1024);
					TIMER2SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE2B
				case 1:
				{
					TIMER2Init(TIMER2_COMB_CM_ST, TIMER2_WF_FPWM, TIMER2_CLK_SRC_1024);
					TIMER2SetB(_num);
					break;
				}
				#endif
				#ifdef OCIE2C
				case 2:
				{
					TIMER2Init(TIMER2_COMC_CM_ST, TIMER2_WF_FPWM, TIMER2_CLK_SRC_1024);
					TIMER2SetC(_num);
					break;
				}
				#endif
			}
			break;
		}
		#endif
		#ifdef TCCR3A
		case 3:
		{
			switch(_ch)
			{
				#ifdef OCIE3A
				case 0:
				{
					TIMER3Init(TIMER3_COMA_CM_ST, TIMER3_WF_FPWM_8B, TIMER3_CLK_SRC_1024);
					TIMER3SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE3B
				case 1:
				{
					TIMER3Init(TIMER3_COMB_CM_ST, TIMER3_WF_FPWM_8B, TIMER3_CLK_SRC_1024);
					TIMER3SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE3C
				case 2:
				{
					TIMER3Init(TIMER3_COMC_CM_ST, TIMER3_WF_FPWM_8B, TIMER3_CLK_SRC_1024);
					TIMER3SetA(_num);
					break;
				}
				#endif
			}
			break;
		}
		#endif
		#ifdef TCCR4A
		case 4:
		{
			switch(_ch)
			{
				#ifdef OCIE4A
				case 0:
				{
					TIMER4Init(TIMER4_COMA_CM_ST, TIMER4_WF_FPWM_8B, TIMER4_CLK_SRC_1024);
					TIMER4SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE4B
				case 1:
				{
					TIMER4Init(TIMER4_COMB_CM_ST, TIMER4_WF_FPWM_8B, TIMER4_CLK_SRC_1024);
					TIMER4SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE4C
				case 2:
				{
					TIMER4Init(TIMER4_COMC_CM_ST, TIMER4_WF_FPWM_8B, TIMER4_CLK_SRC_1024);
					TIMER4SetA(_num);
					break;
				}
				#endif
			}
			break;
		}
		#endif
		#ifdef TCCR5A
		case 5:
		{
			switch(_ch)
			{
				#ifdef OCIE5A
				case 0:
				{
					TIMER5Init(TIMER5_COMA_CM_ST, TIMER5_WF_FPWM_8B, TIMER5_CLK_SRC_1024);
					TIMER5SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE5B
				case 1:
				{
					TIMER5Init(TIMER5_COMB_CM_ST, TIMER5_WF_FPWM_8B, TIMER5_CLK_SRC_1024);
					TIMER5SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE5C
				case 2:
				{
					TIMER5Init(TIMER5_COMC_CM_ST, TIMER5_WF_FPWM_8B, TIMER5_CLK_SRC_1024);
					TIMER5SetA(_num);
					break;
				}
				#endif
			}
			break;
		}
		#endif
		#ifdef TCCR6A
		case 6:
		{
			switch(_ch)
			{
				#ifdef OCIE6A
				case 0:
				{
					TIMER6Init(TIMER6_COMA_CM_ST, TIMER6_WF_FPWM, TIMER6_CLK_SRC_1024);
					TIMER6SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE6B
				case 1:
				{
					TIMER6Init(TIMER6_COMB_CM_ST, TIMER6_WF_FPWM, TIMER6_CLK_SRC_1024);
					TIMER6SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE6C
				case 2:
				{
					TIMER6Init(TIMER6_COMC_CM_ST, TIMER6_WF_FPWM, TIMER6_CLK_SRC_1024);
					TIMER6SetA(_num);
					break;
				}
				#endif
			}
			break;
		}
		#endif
		#ifdef TCCR7A
		case 7:
		{
			switch(_ch)
			{
				#ifdef OCIE7A
				case 0:
				{
					TIMER7Init(TIMER7_COMA_CM_ST, TIMER7_WF_FPWM, TIMER7_CLK_SRC_1024);
					TIMER7SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE7B
				case 1:
				{
					TIMER7Init(TIMER7_COMB_CM_ST, TIMER7_WF_FPWM, TIMER7_CLK_SRC_1024);
					TIMER7SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE7C
				case 2:
				{
					TIMER7Init(TIMER7_COMC_CM_ST, TIMER7_WF_FPWM, TIMER7_CLK_SRC_1024);
					TIMER7SetA(_num);
					break;
				}
				#endif
			}
			break;
		}
		#endif
		#ifdef TCCR8A
		case 8:
		{
			switch(_ch)
			{
				#ifdef OCIE8A
				case 0:
				{
					TIMER8Init(TIMER8_COMA_CM_ST, TIMER8_WF_FPWM, TIMER8_CLK_SRC_1024);
					TIMER8SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE8B
				case 1:
				{
					TIMER8Init(TIMER8_COMB_CM_ST, TIMER8_WF_FPWM, TIMER8_CLK_SRC_1024);
					TIMER8SetA(_num);
					break;
				}
				#endif
				#ifdef OCIE8C
				case 2:
				{
					TIMER8Init(TIMER8_COMC_CM_ST, TIMER8_WF_FPWM, TIMER8_CLK_SRC_1024);
					TIMER8SetA(_num);
					break;
				}
				#endif
			}
			break;
		}
		#endif
	}
}
#define INT_ALOWED ((SREG >> 7) & 1)

//block interrupts for running user's code, 
//will allow interrupts after running user's code
#define ATOMIC_FORCED(...)  								\
{															\
	(														\
	 [&] ()					/*define lambda*/ 				\
	 { 														\
	 	cli();				/*block interrupts*/			\
	 	__VA_ARGS__ 		/*do user code*/				\
	 	sei();				/*allow interrupts*/			\
	 } () 					/*run lambda*/					\
	 );														\
}
//end of macro ATOMIC_FORCED

//block interrupts for running user's code,
//will allow interrupts only if they was allowed
//using more static memory than dynamic
#define ATOMIC_SMART_1(...)	/*will save RAM for u*/			\
{															\
	if(INT_ALOWED)			/*if int's allowed*/			\
	{														\
		(													\
			[&] ()			/*define lambda*/				\
			{												\
				cli();		/*block interrupts*/ 			\
				__VA_ARGS__	/*do user code*/				\
				sei();		/*allow interrupts*/			\
			} ()			/*run lambda*/					\
			);												\
	} 														\
	else					/*if int's not allowed*/		\
	{						/*doesn't need to block int's*/	\
		__VA_ARGS__			/*do user code*/				\
	}														\
}
//end of macro ATOMIC_SMART_1

//block interrupts for running user's code,
//will allow interrupts only if they was allowed
//using more dynamic memory than staic
#define ATOMIC_SMART_2(...)  /*will save ROM for u*/		\
{															\
	uint8_t _ = INT_ALOWED;	/*save int state*/				\
	(														\
		[&] () 				/*define lambda*/				\
		{ 													\
			cli();			/*block interrupts*/			\
			__VA_ARGS__		/*do user code*/  				\
			if(_)			/*if int's was allowed*/		\
				sei();		/*allow interrupts*/			\
		} ()				/*run lambda*/					\
		);													\
}
//end of macro ATOMIC_SMART_2

/*
 *	use of ATOMIC macro sample:
 *	ATOMIC_FORCED
 *	(
 *		foo();	//any other funcs
 *	)
 */

//#ifndef USE_LEGACY_VER
//	#define USE_LEGACY_VER 0
//#endif


#ifdef __OPTIMIZE_SIZE__ 					//if optimizing for size
	#define ATOMIC_SMART ATOMIC_SMART_2		//prefer to use RAM instead of ROM
#else	//ifdef __OPTIMIZE_SIZE__
	#define ATOMIC_SMART ATOMIC_SMART_1		//prefer to use ROM instead of RAM
#endif	//ifndef __OPTIMIZE_SIZE__

#include "customFuncAddr.h"

#include "settings.h"



#if USE_FUNC_INPUT_PROTECTOR == 1
	#include "FuncsInputProtector.h"//because of dependences on TimerModes and ADCModes
#endif //if USE_FUNC_INPUT_PROTECTOR == 1


#include "digitalRegisters.h"


#define byte uint8_t		//define for 8 bit var
#define bool uint8_t		//define for bool var because C has not bool or boolean variable

#define cbi(_sfr, _bit) (_SFR_BYTE(_sfr) &= ~_BV(_bit))
#define sbi(_sfr, _bit) (_SFR_BYTE(_sfr) |= _BV(_bit))


#define delay(x) _delay_ms(x)


void delayMicroseconds(uint64_t _us);
#include "delayMicroseconds.c"


#if USE_TIMERS == 1
	#include "TimerModes_2560.h" //TODO: refactor
	#include "Timers.h"
#endif //if USE_TIMERS == 1


#if USE_USART == 1
	#pragma message "using USART"
	#include "USART.h"
#endif


#if USE_ADC == 1
	#include "ADCModes.h"
	#include "ADC.h"
#endif //if USE_ADC == 1

#if USE_WATCHDOG == 1
	#include "watchdogModes.h"
	#include "watchdog.h"
#endif //if USE_WATCHDOG == 1


#if USE_FUNC_INPUT_PROTECTOR == 1
	#include "FuncsInputProtector.c"
#endif //if USE_FUNC_INPUT_PROTECTOR == 1

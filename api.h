#pragma once

#define INT_ALOWED ((SREG >> 7) & 1)

#include "settings.h"

#include "customFuncAddr.h"

#include "digitalRegisters.h"
#include "Timers.h"
#include "USART.h"
#include "ADC.h"
#include "watchdog.h"
#include "TWI.h"

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

>>>>>>> master




#define byte uint8_t		//define for 8 bit var
#define bool uint8_t		//define for bool var because C has not bool or boolean variable

#define cbi(_sfr, _bit) (_SFR_BYTE(_sfr) &= ~_BV(_bit))
#define sbi(_sfr, _bit) (_SFR_BYTE(_sfr) |= _BV(_bit))


#define delay(x) _delay_ms(x)


//#include "FuncsInputProtector.c"

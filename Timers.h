#if USE_TIMERS == 1

	#include "Timers.cpp"
	#include "TimerModes.h"
	
	#if defined(TCCR0A)
		void TIMER0Init(uint8_t _mode, uint8_t _clockSource, uint8_t _count);
	#endif
	
	#if defined(TCCR1A)
		void TIMER1Init(uint8_t _mode, uint8_t _clockSource, uint16_t _count);
	#endif

#endif

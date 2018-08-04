#if USE_CUSTOM_INTERRUPTS == 1
	
	void (*funcs[21])();
	#if USE_TIMERS == 1
		#include "timerCustomfuncAddrs.h"
	#endif
	
	#if USE_USART0 == 1
		#if USE_USART0_OUTPUT == 1
			#define USART0_TX_VECT USART0_TX_vect
		#endif
		
	#endif
	
#endif //USE_CUSTOM_INTERRUPTS == 1

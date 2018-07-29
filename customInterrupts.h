#if USE_CUSTOM_INTERRUPTS == 1
	
	void (*funcs[21])();
	#if USE_TIMERS == 1
		#include "timerCustomfuncAddrs.h"
	#endif
	
#endif //USE_CUSTOM_INTERRUPTS == 1

#if USE_WATCHDOG == 1
	
	#ifndef _WD_MODES
		#error "No watchdog timer modes included!"
	#endif //ifndef _WD_MODES
	
	#include "watchdog.c"
	
	void WDSetMode(uint8_t _mode);
	void WDSetCycles(uint8_t _cycles);
	void WDFlush(void);
	
#endif //if USE_WATCHDOG == 1

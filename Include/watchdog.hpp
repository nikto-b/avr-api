#pragma once

#include "base.hpp"

#include "watchdogModes.hpp"
#include "customFuncAddr.hpp"
#ifndef _WD_MODES
	#error "No watchdog timer modes included!"
#endif //ifndef _WD_MODES


void WDSetMode(uint8_t _mode);
void WDSetCycles(uint8_t _cycles);
void WDFlush(void);
	

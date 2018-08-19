void (*funcs[21])();
#include "settings.h"

#include "digitalRegisters.h"

#define byte uint8_t		//define for 8 bit var
#define bool uint8_t		//define for bool var because C has not bool or boolean variable

#define cbi(_sfr, _bit) (_SFR_BYTE(_sfr) &= ~_BV(_bit))
#define sbi(_sfr, _bit) (_SFR_BYTE(_sfr) |= _BV(_bit))

#include "delayMicroseconds.c"

void delayMicroseconds(uint64_t _us);

#if USE_TIMERS == 1
	#include "TimerModes_2560.h" //TODO: refactor
	#include "Timers.h"
#endif //if USE_TIMERS == 1

#if USE_USART == 1
	#pragma message "using USART"
	#include "USART.h"
#endif

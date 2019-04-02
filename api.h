#pragma once

#include "settings.h"

#include "customFuncAddr.h"

#include "digitalRegisters.h"
#include "Timers.h"
#include "USART.h"
#include "ADC.h"
#include "watchdog.h"
#include "TWI.h"
#include "ATOMIC.h"
#include "numFuncs.h"



#define byte uint8_t		//define for 8 bit var
#define bool uint8_t		//define for bool var because C has not bool or boolean variable

#define cbi(_sfr, _bit) (_SFR_BYTE(_sfr) &= ~_BV(_bit))
#define sbi(_sfr, _bit) (_SFR_BYTE(_sfr) |= _BV(_bit))


#define delay(x) _delay_ms(x)



//#include "FuncsInputProtector.c"

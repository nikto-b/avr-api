#pragma once

#include "settings.hpp"

#include "customFuncAddr.hpp"

#include "digitalRegisters.hpp"
#include "Timers.hpp"
#include "USART.hpp"
#include "ADC.hpp"
#include "watchdog.hpp"
#include "TWI.hpp"
#include "ATOMIC.hpp"
#include "numFuncs.hpp"



#define byte uint8_t		//define for 8 bit var
#define bool uint8_t		//define for bool var because C has not bool or boolean variable

#define cbi(_sfr, _bit) (_SFR_BYTE(_sfr) &= ~_BV(_bit))
#define sbi(_sfr, _bit) (_SFR_BYTE(_sfr) |= _BV(_bit))


#define delay(x) _delay_ms(x)



//#include "FuncsInputProtector.c"

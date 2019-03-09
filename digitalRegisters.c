#pragma once

#include "base.h"
#include "digitalRegisters.h"





/*
 * Function digitalWrite
 * Desc     write state to pin
 * Input    __pin: what pin write to
 * 			__state: what state write
 * Output   none
*/
void digitalWrite(uint8_t __pin, bool __state)		//because
{
	uint8_t __port = __pin / 8;
	__pin %= 8;	//get local shift
	*(&START_PORT + __port * 3) = ((*(&START_PORT + __port * 3)) & (~(1 << __pin))) | (__state << __pin);	
}

/*
 * Function digitalRead
 * Desc     Return state of pin
 * Input    __pin: what pin state return to
 * Output   state
*/
int digitalRead(uint8_t __pin)
{
	uint8_t __port = __pin / 8;
	__pin %= 8;
	return (*(&START_PORT - 2 + __port * 3) >> __pin) & 1;
}

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2

/*
 * Function pinMode
 * Desc     set mode of pin(I/O)
 * 			WARNING! Recurcy(depth 1)!
 * Input    __pin: what pin state set to
 * 			__state: what state set to
 * Output   none
*/
void pinMode(uint8_t __pin, uint8_t __state)
{
	uint8_t __port = __pin / 8;
	if(__state == INPUT_PULLUP)
	{
		digitalWrite(__pin, HIGH);
		__state = HIGH;
	}
	*(&START_PORT - 1 + __port) = (*(&START_PORT - 1 + __port) & (~(__state << __pin))) | (__state << __pin);
}

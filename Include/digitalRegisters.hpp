#pragma once
#include "base.hpp"

namespace io
{
	enum Mode 	{ OUTPUT, INPUT, INPUT_PULLUP };
	enum State	{ HIGH = 1, LOW = 0 };


		
	/*
	 * Function setMode
	 * Desc     set mode of pin (OUTPUT/INPUT/INPUT_PULLUP)
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set mode (example: PD4)
	 * 			mode:	mode of pin		(example: INPUT)
	 * Output   none
	*/
	void setMode(uint8_t *port, uint8_t pin, Mode mode);
		
	/*
	 * Function setState
	 * Desc     set pin to some state (LOW/HIGH) if it's output
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set state(example: PD4)
	 * 			state:	state of pin	(example: LOW)
	 * Output	none
	*/
	void setState(uint8_t *port, uint8_t pin, State state);
		
	/*
	 * Function getState
	 * Desc     get state of pin (LOW/HIGH)
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set state(example: PD4)
	 * Output	state of pin
	*/
	State getState(uint8_t *port, uint8_t pin);

} // namespace io
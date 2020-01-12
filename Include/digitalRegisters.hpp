#pragma once
#include "base.hpp"

namespace gpio
{
	enum Mode 	{ OUTPUT, INPUT, INPUT_PULLUP };
	enum State	{ HIGH = 1, LOW = 0 };

	struct PinState
	{
		const uint8_t 	pin;
		const State 	state;

		PinState(const uint8_t pin, const State state);
	};


		
	/*
	 * Function setMode
	 * Desc     set mode of pin (OUTPUT/INPUT/INPUT_PULLUP)
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set mode (example: PD4)
	 * 			mode:	mode of pin		(example: INPUT)
	 * Output   none
	*/
    void setMode(volatile uint8_t *port, const uint8_t pin, const Mode mode);
		
	/*
	 * Function setState
	 * Desc     set pin to some state (LOW/HIGH) if it's output
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set state(example: PD4)
	 * 			state:	state of pin	(example: LOW)
	 * Output	none
	*/
	void setState(volatile uint8_t *port, const uint8_t pin, const State state);

	/*
	 * Function setState
	 * Desc     set pin to some state (LOW/HIGH) if it's output
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			status:	status of pin	(example: {PD2, HIGH})
	 * Output	none
	*/
	void setState(volatile uint8_t *port, const PinState status);
		
	/*
	 * Function setStates
	 * Desc     set pins to some state (LOW/HIGH) if it's output
	 * Input    port: 		port of pin 	(example: PORTD)
	 * 			statuses:	state of pin	(example: {{PD2, HIGH}, {PD3, LOW}})
	 * Output	none
	*/
	template <const size_t N>
	void setStates(volatile uint8_t *port, const PinState (&statuses) [N])	//realisation here because of troubles with compilation of templates
    {																		//all magic just to make compiler to optimize it
        uint8_t disableMask = 0, 
                enableMask = 0;
        for(uint8_t i = 0; i < N; i++)
        {
            disableMask |= 1 << statuses[i].pin;
            if(statuses[i].state == HIGH)
                enableMask  |= 1 << statuses[i].pin;
        }
        *port = (*port & ~disableMask) | enableMask;
    }

	/*
	 * Function getState
	 * Desc     get state of pin (LOW/HIGH)
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set state(example: PD4)
	 * Output	state of pin
	*/
	State getState(volatile uint8_t *port, const uint8_t pin);

} // namespace gpio
#include "base.hpp"

namespace gpio
{
	enum Mode 	{ OUTPUT, INPUT, INPUT_PULLUP };
	enum State	{ HIGH = 1, LOW = 0, TOGGLE = 2 };

	struct PinState
	{
		const uint8_t 	pin;
		const State 	state;

		PinState(const uint8_t pin, const State state);
	};


        //get dir register of port whitch PORTn register given
    inline const volatile uint8_t* 	_DirReg(const volatile uint8_t* port) 	{ return port - 1; }
    inline volatile uint8_t* 		_DirReg(volatile uint8_t* port) 		{ return port - 1; }

        //get pin register of port whitch PORTn register given
    inline const volatile uint8_t* 	_PinReg(const volatile uint8_t* port) 	{ return port - 2; }
    inline volatile uint8_t* 		_PinReg(volatile uint8_t* port) 		{ return port - 2; }
	

	/*
	 * Function setState
	 * Desc     set pin to some state (LOW/HIGH) if it's output
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set state(example: PD4)
	 * 			state:	state of pin	(example: LOW)
	 * Output	none
	*/
	template<State state>
	inline void setState(volatile uint8_t *port, const uint8_t pin)
	{	
		if constexpr (state == TOGGLE) 
			*port = static_cast<uint8_t>((*port) ^ (1 << pin));
		else
			*port = static_cast<uint8_t>(((*port) & ~(1 << pin)) | (state << pin));
	}

		
	/*
	 * Function setMode
	 * Desc     set mode of pin (OUTPUT/INPUT/INPUT_PULLUP)
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set mode (example: PD4)
	 * 			mode:	mode of pin		(example: INPUT)
	 * Output   none
	*/
    inline void setMode(volatile uint8_t *port, const uint8_t pin, const Mode mode)
	{
        volatile uint8_t *dir = _DirReg(port);

        switch (mode)
        {
            case OUTPUT:
            {
                *dir = static_cast<uint8_t>(((*dir) & ~(1 << pin)) | (1 << pin));    //set pin bit to 1 - set it to OUTPUT
                break;
            }
            case INPUT_PULLUP:
            {
                setState<HIGH>(port, pin);
                [[fallthrough]];
            }
            case INPUT:
            {
                *dir = static_cast<uint8_t>((*dir) & ~(1 << pin));    //set pin bit to 0 - set it to INPUT
                break;
            }
        }
    }

	/*
	 * Function setState
	 * Desc     set pin to some state (LOW/HIGH) if it's output
	 * 			Prefer to use templated variant because it can be faster inlined
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			status:	status of pin	(example: {PD2, HIGH})
	 * Output	none
	*/
	inline void setState(volatile uint8_t *port, const PinState status)
	{
		if(status.state != TOGGLE)
			*port = static_cast<uint8_t>((*(port) & ~(1 << status.pin)) | (status.state << status.pin));
		else
			*port = static_cast<uint8_t>(*(port) ^ (1 << status.pin));
	}

	template <const size_t N>
	constexpr uint8_t _genDisableMask(const PinState (&statuses) [N])
	{
		uint8_t mask = 0;
		for(uint8_t i = 0; i < N; i++)
        {
            mask = static_cast<uint8_t>(mask | (1 << statuses[i].pin));
        }
		return mask;
	}

	template <const size_t N>
	constexpr uint8_t _genEnableMask(const uint8_t portState, const PinState (&statuses) [N])
	{
		uint8_t mask = 0;
		for(uint8_t i = 0; i < N; i++)
        {
            if(statuses[i].state != TOGGLE)
				mask = static_cast<uint8_t>(mask | (statuses[i].state << statuses[i].pin));
			else
				mask = static_cast<uint8_t>(mask | (~portState & (1 << statuses[i].pin)));
        }
		return mask;
	}
		
	/*
	 * Function setStates
	 * Desc     set pins to some state (LOW/HIGH) if it's output
	 * Input    port: 		port of pin 	(example: PORTD)
	 * 			statuses:	state of pin	(example: {{PD2, HIGH}, {PD3, LOW}})
	 * Output	none
	*/
	template <const size_t N>
	inline void setStates(volatile uint8_t *port, const PinState (&statuses) [N])
    {
        *port = static_cast<uint8_t>((*port & ~_genDisableMask<N>(statuses)) | _genEnableMask<N>(*port, statuses));
    }

	/*
	 * Function getState
	 * Desc     get state of pin (LOW/HIGH)
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set state(example: PD4)
	 * Output	state of pin
	*/
	inline State getState(const volatile uint8_t *port, const uint8_t pin)
	{
        return static_cast<State>(((*(_PinReg(port))) >> pin) & 1);
	}

} // namespace gpio
#include "base.hpp"
#include "digitalRegisters.hpp"


namespace gpio
{
        //get dir register of port whitch PORTn register given
    inline volatile uint8_t* DirReg(volatile uint8_t* port)
    {
        return port - 1;
    }
        //get pin register of port whitch PORTn register given
    inline volatile uint8_t* PinReg(volatile uint8_t* port)
    {
        return port - 2;
    }

		
	/*
	 * Function setMode
	 * Desc     set mode of pin (OUTPUT/INPUT/INPUT_PULLUP)
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set mode (example: PD4)
	 * 			mode:	mode of pin		(example: INPUT)
	 * Output   none
	 */
    void setMode(volatile uint8_t *port, const uint8_t pin, const Mode mode) 
    {
        volatile uint8_t *dir = DirReg(port);

        switch (mode)
        {
            case OUTPUT:
            {
                *dir = (*dir) & ~(1 << pin);    //set pin bit to 0 - set it to OUTPUT
                break;
            }
            case INPUT_PULLUP:
            {
                setState(port, pin, HIGH);
                __attribute__((fallthrough));
            }
            case INPUT:
            {
                *dir = ((*dir) & ~(1 << pin)) | (1 << pin);    //set pin bit to 0 - set it to INPUT
                break;
            }
        }
    }
		
	/*
	 * Function setState
	 * Desc     set pin to some state (LOW/HIGH) if it's output
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set state(example: PD4)
	 * 			state:	state of pin	(example: LOW)
	 * Output	none
	 */
	void setState(volatile uint8_t *port, const uint8_t pin, const State state)
    {
        *port = (*(port) & ~(1 << pin)) | (state << pin);
    }


	/*
	 * Function setState
	 * Desc     set pin to some state (LOW/HIGH) if it's output
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			status:	status of pin	(example: {PD2, HIGH})
	 * Output	none
	*/
	void setState(volatile uint8_t *port, const PinState status)
    {
        *port = (*(port) & ~(1 << status.pin)) | (status.state << status.pin);
    }
		
	/*
	 * Function getState
	 * Desc     get state of pin (LOW/HIGH)
	 * Input    port: 	port of pin 	(example: PORTD)
	 * 			pin:	pin to set state(example: PD4)
	 * Output	state of pin
	 */
	State getState(volatile uint8_t *port, const uint8_t pin)
    {
        const volatile uint8_t *pinreg = PinReg(port);
        return static_cast<State>(((*(pinreg)) >> pin) & 1);
    }




	PinState::PinState(const uint8_t _pin, const State _state) : pin(_pin), state(_state) {}
    
} // namespace gpio

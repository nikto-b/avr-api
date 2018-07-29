#define PortReg(port) ((port))
#define DirReg(port) (((port) - 1))
#define PinReg(port) (((port) - 2))

#if defined(PORTA)
	#define START_PORT PORTA
#elif defined(PORTB)
	#define START_PORT PORTB
#else
	#error "can't find begining port"
#endif




#define HIGH 1
#define LOW 0

void digitalWrite(uint8_t _pin, bool _state)		//because
{
	uint8_t _port = _pin / 8;
	_pin %= 8;
	*(&START_PORT + _port * 3) = ((*(&START_PORT + _port * 3)) & (~(1 << _pin))) | (_state << _pin);	
}

int digitalRead(uint8_t _pin)
{
	uint8_t _port = _pin / 8;
	_pin %= 8;
	return (*(&START_PORT - 2 + _port * 3) >> _pin) & 1;
}

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2

void pinMode(uint8_t _pin, uint8_t _state)
{
	uint8_t _port = _pin / 8;
	if(_state < INPUT_PULLUP)
	{
		*(&START_PORT - 1 + _port) = (*(&START_PORT - 1 + _port) & (~(_state << _pin))) | (_state << _pin);
	}
	else 
	{
		digitalWrite(_pin, HIGH);
		pinMode(_pin, INPUT);
	}
}

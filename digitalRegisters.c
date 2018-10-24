#if defined(PORTA)
	#define START_PORT PORTA
#elif defined(PORTB)
	#define START_PORT PORTB
#else
	#error "can't find zero port"
#endif


//--------MODES--------
#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2

//--------STATES--------
#define HIGH 1
#define LOW 0

void digitalWrite(uint8_t _pin, bool _state)		//set pin at _pin to state at _state
{
	uint8_t _port = _pin / 8;	//get register index
	_pin %= 8;					//get pin index in register
				
	*(&START_PORT + _port * 3) 							//address offset from zero reg; 	
	= ((*(&START_PORT + _port * 3)) & (~(1 << _pin))) 	//save old data, disable _pin;
	| (_state << _pin);									//set _pin to _state
}

int digitalRead(uint8_t _pin)						//read state of pin _pin
{
	uint8_t _port = _pin / 8;	//get register index
	_pin %= 8;					//get pin index in reg
	return (*(&START_PORT - 2 + _port * 3) >> _pin) & 1;	//offset addr and get target bit
}


void pinMode(uint8_t _pin, uint8_t _state)//set pin _pin to mode _state
{
	uint8_t _port = _pin / 8;			//get reg index
	if(_state != INPUT_PULLUP)			//if needeed only changing mode
	{
		*(&START_PORT - 1 + _port * 3) 		//offset addr of reg
		= (*(&START_PORT - 1 + _port * 3) & (~(_state << _pin)))//flush old mode 
		| (_state << _pin);				//set mode of _pin to state _state
	}
	else 								//if need PULLUP
	{
		digitalWrite(_pin, HIGH);		//enable internal resistors
		pinMode(_pin, INPUT);			//set port to input
	}
}

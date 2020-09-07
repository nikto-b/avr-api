#include "base.hpp"
#include "api.hpp"

using gpio::HIGH;
using gpio::LOW;
using gpio::TOGGLE;


int main()
{
	gpio::setMode(&PORTB, PB7, gpio::OUTPUT);
	sei();
	
	gpio::setState(&PORTB, {PB7, HIGH});
	

	while(1)
	{
        gpio::setState<TOGGLE>(&PORTB, PB7);
        delay(100);
	}
	return 0;
}

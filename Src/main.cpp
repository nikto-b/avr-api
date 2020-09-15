#include "base.hpp"
#include "api.hpp"

using gpio::HIGH;
using gpio::LOW;
using gpio::TOGGLE;


int main()
{
	usart::begin<0>(115200);
	adc::init();
	adc::setRef(adc::ref::AREF);
	sei();

	while(1)
	{
		usart::println<0>(adc::analogRead(0));
        delay(100);
	}
	return 0;
}

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
	timer::init<1>(timer::com::_1_A_NORMAL, timer::wf::_1_WF_FPWM_8B, timer::clk::_0_SRC_1024);

	while(1)
	{
		usart::println<0>(adc::analogRead(0));
        delay(100);
	}
	return 0;
}

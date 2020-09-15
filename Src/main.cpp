#include "base.hpp"
#include "api.hpp"
#include "type_traits.hpp"

using gpio::HIGH;
using gpio::LOW;
using gpio::TOGGLE;


int main()
{
	std::integral_constant<uint64_t, 115200> baud_t;
	usart::begin<0>(baud_t.value);
	adc::init();
	adc::setRef(adc::ref::AREF);
	sei();
	timer::init<1>(timer::com::_1_A_NORMAL, timer::wf::_1_WF_FPWM_8B, timer::clk::_0_SRC_1024);
	timer::setVar<1, timer::Var::A>(static_cast<uint8_t>(255));

	while(1)
	{
		usart::println<0>(adc::analogRead(0));
        delay(100);
	}
	return 0;
}

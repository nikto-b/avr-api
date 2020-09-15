#pragma once
namespace adc
{
	//				ANALOG  REFERENCE
	namespace ref 
	{
		const uint8_t AREF                  = 0;
		const uint8_t AVCC                  = (1 << REFS0);					//external capacitor at AREF pin
		const uint8_t INT_1_1V              = (1 << REFS1);					//Internal 1.1V  with ext cap at AREF pin
		const uint8_t INT_2_56V             = ((1 << REFS0) | (1 << REFS1));//Internal 2.56V with ext cap at AREF pin
	} // namespace ref

	//				ADC CONTROL
	namespace control 
	{
		const uint8_t ENABLE            = (1 << ADEN);
		const uint8_t START_CONVERTION  = (1 << ADSC);
		#ifdef ADATE
		const uint8_t AUTOTRIGGER       = (1 << ADATE);
		#endif
		const uint8_t INTERRUPT_FLAG_EN = (1 << ADIF);
		const uint8_t INTERRUPT_EN      = (1 << ADIE);
	} // namespace control
	
	//				ADC PRESCALLERS
	namespace prescaller 
	{
		const uint8_t MASK           = ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
		const uint8_t DEF            = 0;
		const uint8_t _2             = (1 << ADPS0);
		const uint8_t _4             = (1 << ADPS1);
		const uint8_t _8             = ((1 << ADPS0) | (1 << ADPS1));
		const uint8_t _16            = (1 << ADPS2);
		const uint8_t _32            = ((1 << ADPS2) | (1 << ADPS0));
		const uint8_t _64            = ((1 << ADPS2) | (1 << ADPS1));
		const uint8_t _128           = ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));
	} // namespace prescaller

	//			ADC AUTOTRIGGER SOURCES
	namespace autotrigger 
	{
		#ifdef ADTS2
		const uint8_t MASK                 = ((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));
		const uint8_t ANALOG_COMPARATOR    = (1 << ADTS0);
		const uint8_t EXT_INTERRUPT_REQ_0  = (1 << ADTS1);
		const uint8_t TC0_COMPA            = ((1 << ADTS0) | (1 << ADTS1));
		const uint8_t TC0_OVF              = (1 << ADTS2);
		const uint8_t TC1_COMPB            = ((1 << ADTS2) | (1 << ADTS0));
		const uint8_t TC1_OVF              = ((1 << ADTS2) | (1 << ADTS1));
		const uint8_t TC1_CAPT_EV          = ((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));
		#endif
		const uint8_t FREERUN              = 0;
	} // namespace autotrigger

	//Modes isn't currently used, background is default now
	//					ADC MODES
	namespace mode 
	{
		const uint8_t BACKGROUND           = 0;
		const uint8_t DEADLINE             = 1;
		const uint8_t MANUAL               = 3;
	} // namespace mode
}
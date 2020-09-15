#pragma once
#include "ADCModes.hpp"

namespace adc
{
	const uint8_t  NUM_OF_ANALOG_PINS  = 15;
	const uint16_t ADC_DATA_MASK       = 1023;
	const uint16_t ADC_CHANGED_MASK    = 1024;
		

	void setAnalogChanged(uint8_t __pin, uint8_t __state);
	bool getAnalogChanged(uint8_t __pin);
	void sendControl(uint8_t __contr);
	void setRef(uint8_t __ref);
	void setPrescaller(uint8_t __prescaller);
	void setAutotriggerSRC(uint8_t __src);
	void disableDigitalInput0to7(uint8_t __mask);
	#ifdef DIDR2
	void ADCDisableDigitalInput8to15(uint8_t __mask);
	#endif
	void enable(void);
	void disable(void);
	void startConvert(void);
	void stopConvert(void);
	void flush(void);
	void init(void);
	int analogRead(uint8_t _pin);
} // namespace adc
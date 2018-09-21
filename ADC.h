#if USE_ADC == 1

	#ifndef ADC_H_
		#define ADC_H_
	#endif 
	
	#ifndef _ADC_MODES
		#pragma error "No ADC modes table found!"
	#endif //ifndef _ADC_MODES
	
	#include "ADC.c"
	void ADCSetAnalogChanged(uint8_t __pin, uint8_t __state);
	uint8_t ADCGetAnalogChanged(uint8_t __pin);

	void ADCInit(void);

	int analogRead(uint8_t _pin);
#endif

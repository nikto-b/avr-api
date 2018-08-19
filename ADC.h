#if USE_ADC == 1

	#ifndef ADC_H_
		#define ADC_H_
	#endif 

	#include "ADC.c"

	void ADC_init(void);

	int analogRead(uint8_t _pin);
#endif

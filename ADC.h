#if USE_ADC == 1

	#ifndef ADC_H_
		#define ADC_H_
	#endif 
	
	#ifndef _ADC_MODES
		#pragma error "No ADC modes table found!"
	#endif //ifndef _ADC_MODES
	
	void ADCSetAnalogChanged(uint8_t __pin, uint8_t __state);
	uint8_t ADCGetAnalogChanged(uint8_t __pin);
	void ADCSendControl(uint8_t __contr);
	void ADCSetRef(uint8_t __ref);
	void ADCSetPrescaller(uint8_t __prescaller);
	void ADCSetAutotriggerSRC(uint8_t __src);

		
	#if ADC_MODE == ADC_MODE_BACKGROUND || ADC_MODE == ADC_MODE_DEADLINE
		void ADCInit(void);
	#endif //if ADC_MODE == ADC_MODE_BACKGROUND || ADC_MODE == ADC_MODE_DEADLINE
	
	#if ADC_MODE != ADC_MODE_MANUAL
		int analogRead(uint8_t _pin);
	#endif //if ADC_MODE != ADC_MODE_MANUAL
	
	#include "ADC.c"
#endif

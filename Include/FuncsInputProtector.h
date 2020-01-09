
#if USE_TIMERS == 1
	//TIMER0
	uint8_t validateTimer0Mode(uint8_t __mode);
	uint8_t validateTimer0CLK(uint8_t __source);
	
	
	//TIMER1
	uint8_t validateTimer1Mode(uint8_t __mode);
	uint8_t validateTimer1CLK(uint8_t __source);
	
	
	//TIMER2
	uint8_t validateTimer2Mode(uint8_t __mode);
	uint8_t validateTimer2CLK(uint8_t __source);
	
	
	//TIMER3
	uint8_t validateTimer3Mode(uint8_t __mode);
	uint8_t validateTimer3CLK(uint8_t __source);
	
	
	//TIMER4
	uint8_t validateTimer4Mode(uint8_t __mode);
	uint8_t validateTimer4CLK(uint8_t __source);
	
	
	//TIMER5
	uint8_t validateTimer5Mode(uint8_t __mode);
	uint8_t validateTimer5CLK(uint8_t __source);
	
	
#endif //if USE_TIMERS == 1

#if USE_ADC == 1
	
	#ifndef _ADC_MODES
		#pragma error "No ADC modes table found!"
	#endif //ifndef _ADC_MODES
	
	uint8_t validateADCREF(uint8_t __aref);
	
	uint8_t validateADCControl(uint8_t __contr);
	
	uint8_t validateADCPrescaller(uint8_t __prescaller);
	
	uint8_t validateADCAutotriggerSRC(uint8_t __src);
	
#endif //if USE_ADC == 1

#if defined(ADCL) && USE_ADC == 1
	#pragma message "ADC found"
	uint8_t analog_ref;
	volatile int* analogPins = (int*)malloc(NUM_OF_ANALOG_PINS);
	volatile int curr_pin = 0;
	
	void ADC_init()
	{
	  ADCSRA = 0;
	  ADCSRB = 0;
	  ADMUX |= (1 << REFS0); 	//set reference voltage
	  //ADMUX |= (1 << ADLAR); //configure ADC for 8-bit work (PT1)
	  analog_ref = ADMUX;			//save ref
	  ADMUX |= (curr_pin & NUM_OF_ANALOG_PINS);		//set pin for converting
	  //  ADCSRA |= (1 << ADPS2) ;//  set divider - 16
	  //  ADCSRA &= ~ (1 << ADPS1) | (1 << ADPS0);
	  ADCSRA |= (1 << ADPS2) | (1 << ADPS0);//set divider 32
	  ADCSRA &= ~ (1 << ADPS1);
	  ADCSRA |= (1 << ADATE); 	//set autoconvert at trigger
	  ADCSRA |= (1 << ADIE); 	//ADC interrupt enable
	  ADCSRA |= (1 << ADEN);	//enable ADC
	  ADCSRA |= (1 << ADSC);	//start conversion
	}

	ISR(ADC_vect)
	{
		analogPins[curr_pin] = ADCL | (ADCH << 8);//get 10 bit result
		//analogPins[curr_pin] = ADCH; 					//configure ADC for 8--bit work(PT2)
		curr_pin++;
		if(curr_pin >= NUM_OF_ANALOG_PINS)
		{
			curr_pin = 0;
		}
		ADMUX = analog_ref | (curr_pin & NUM_OF_ANALOG_PINS);
	}
	
	
	int analogRead(uint8_t _pin)
	{
		if(_pin < NUM_OF_ANALOG_PINS)
		{
			return analogPins[_pin];
		}
		return 0;
	}
#endif //if defined(ADCL) && USE_ADC == 1

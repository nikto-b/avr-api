#if defined(ADCL) && USE_ADC == 1
	#pragma message "ADC found"
	#define ADC_DATA_MASK 1023
	#define ADC_CHANGED_MASK 1024
	uint8_t _analogRef;
	volatile uint16_t _analogPins[NUM_OF_ANALOG_PINS];
	volatile uint8_t _currPin = 0;
	
	void ADCSetAnalogChanged(uint8_t __pin, uint8_t __state)
	{
		_analogPins[__pin] = (_analogPins[__pin] & ~ADC_CHANGED_MASK) | (__state * ADC_CHANGED_MASK);
	}
	
	uint8_t ADCGetAnalogChanged(uint8_t __pin)
	{
		return (_analogPins[__pin] & ADC_CHANGED_MASK) != 0;
	}
	
	
	
	void ADCSendControl(uint8_t __contr)
	{
		#if USE_FUNC_INPUT_PROTECTOR == 1
			if(!validateADCControl(__contr))
			{
				return;
			}
		#endif //if USE_FUNC_INPUT_PROTECTOR == 1
		
		ADCSRA |= __contr;
	}
	
	void ADCSetRef(uint8_t __ref)
	{
		#if USE_FUNC_INPUT_PROTECTOR == 1
			if(!validateADCREF(__ref))
			{
				return;
			}
		#endif //if USE_FUNC_INPUT_PROTECTOR == 1
		
		ADMUX |= __ref;
		_analogRef = __ref;
	}
	
	void ADCSetPrescaller(uint8_t __prescaller)
	{
		#if USE_FUNC_INPUT_PROTECTOR == 1
			if(!validateADCPrescaller(__prescaller))
			{
				return;
			}
		#endif //if USE_FUNC_INPUT_PROTECTOR == 1
		ADCSRA = (ADCSRA & ~ADC_PRESCALLER_MASK) | __prescaller;
	}
	
	void ADCSetAutotriggerSRC(uint8_t __src)
	{
		#if USE_FUNC_INPUT_PROTECTOR == 1
			if(!validateADCAutotriggerSRC(__src))
			{
				return;
			}
		#endif //if USE_FUNC_INPUT_PROTECTOR == 1
		ADCSRB = (ADCSRB & ~ADC_ADTS_MASK) | __src;
	}

	inline void ADCDisableDigitalInput0to7(uint8_t __mask)
	{
		DIDR0 = __mask;
	}
	
	inline void ADCDisableDigitalInput8to15(uint8_t __mask)
	{
		DIDR2 = __mask;
	}
	
	inline void ADCEnable()
	{
		ADCSendControl(ADC_CONTROL_ENABLE);
	}
	
	inline void ADCDisable()
	{
		ADCSRA = (ADCSRA & ~ADC_CONTROL_ENABLE);
	}
	
	inline void ADCStartConvert()
	{
		ADCSendControl(ADC_CONTROL_START_CONVERTION);
	}
	
	inline void ADCStopConvert()
	{
		ADCSRA = (ADCSRA & ~ADC_CONTROL_START_CONVERTION);
	}
	
	inline void ADCFlush()
	{
		ADCSRA = 0;
		ADCSRB = 0;
		DIDR2  = 0;
		DIDR0  = 0;
	}
	
	
	void ADCInit()
	{
		for(int i = 0; i < NUM_OF_ANALOG_PINS; i++)
		{
			_analogPins[i] = 0;
		}
		ADCFlush();
		ADCSetRef(ADC_REF_AVCC);
		ADMUX |= (_currPin & NUM_OF_ANALOG_PINS);
		ADCSetPrescaller(ADC_PRESCALLER_32);
		ADCSendControl(ADC_CONTROL_AUTOTRIGGER);
		ADCSendControl(ADC_CONTROL_INTERRUPT_EN);//WTF?
		ADCEnable();
		ADCStartConvert();
		//*/
		
		//ADCSRA = 0;
		//ADCSRB = 0;
		//ADMUX |= (1 << REFS0); 	//set reference voltage
		//ADMUX |= (1 << ADLAR); //configure ADC for 8-bit work (PT1)
		//_analogRef = ADMUX;			//save ref
		//ADMUX |= (_currPin & NUM_OF_ANALOG_PINS);		//set pin for converting
		//  ADCSRA |= (1 << ADPS2) ;//  set divider - 16
		//  ADCSRA &= ~ (1 << ADPS1) | (1 << ADPS0);
		//ADCSRA |= (1 << ADPS2) | (1 << ADPS0);//set divider 32
		//ADCSRA &= ~ (1 << ADPS1);
		//ADCSRA |= (1 << ADATE); 	//set autoconvert at trigger
		//ADCSRA |= (1 << ADIE); 	//ADC interrupt enable
		//ADCSRA |= (1 << ADEN);	//enable ADC
		//ADCSRA |= (1 << ADSC);	//start conversion*/
		//ADCStartConvert();
	}

	ISR(ADC_vect)
	{
		_analogPins[_currPin] = ADCL | (ADCH << 8);
		ADCSetAnalogChanged(_currPin, 1);
		_currPin++;
		if(_currPin >= NUM_OF_ANALOG_PINS)
		{
			_currPin = 0;
		}		
		ADMUX = _analogRef | (_currPin & NUM_OF_ANALOG_PINS);
	}
	
	
	int analogRead(uint8_t __pin)
	{
		ADCSetAnalogChanged(__pin, 0);
		return _analogPins[__pin] & ADC_DATA_MASK;
	}
#endif //if defined(ADCL) && USE_ADC == 1

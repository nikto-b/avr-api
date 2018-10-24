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
		#if USE_ADC_8BIT == 1
			ADMUX |= (1 << ADLAR);
		#endif //if USE_ADC_8BIT == 1
		_analogRef = ADMUX;
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
	
	#if ADC_MODE == ADC_MODE_BACKGROUND
	
		void ADCInit()
		{
			for(int i = 0; i < NUM_OF_ANALOG_PINS; i++)
			{
				_analogPins[i] = 0;
			}
			ADCFlush();
			
			ADCSetRef(ADC_REF_AVCC);
			ADCSetPrescaller(ADC_DEF_PRESCALLER);
			ADCSendControl(ADC_CONTROL_AUTOTRIGGER);
			ADCSendControl(ADC_CONTROL_INTERRUPT_EN);
			ADCEnable();
			ADCStartConvert();
		}

		ISR(ADC_vect)
		{
			#if USE_ADC_8BIT == 1
				_analogPins[_currPin] = ADCH;// = ADCL | (ADCH << 8);
			#else
				_analogPins[_currPin] = ADCL | (ADCH << 8);
			#endif
			
			ADCSetAnalogChanged(_currPin, 1);
			_currPin++;
			if(_currPin >= NUM_OF_ANALOG_PINS)
			{
				_currPin = 0;
			}		
			ADMUX = _analogRef | (_currPin & NUM_OF_ANALOG_PINS);
			if(funcs[ADC_ONCOMPARE_CUSTOMFUNC_ADDR] != NULL)
				funcs[ADC_ONCOMPARE_CUSTOMFUNC_ADDR]();
		}
		
		
		int analogRead(uint8_t __pin)
		{
			ADCSetAnalogChanged(__pin, 0);
			return _analogPins[__pin] & ADC_DATA_MASK;
		}
	//#endif //if ADC_MODE == ADC_MODE_BACKGROUND
	#elif ADC_MODE == ADC_MODE_LOCK
		int analogRead(uint8_t __pin)
		{
			ADCSetRef(ADC_REF_AVCC);
			ADCSetPrescaller(ADC_DEF_PRESCALLER);
			ADMUX = _analogRef | __pin;
			ADCEnable();
			ADCStartConvert();
			while(!ADCSRA >> ADIF)
			{
				asm("NOP");//todo: sleep instad busyloop
			}			
			#if USE_ADC_8BIT == 1
				return ADCH;// = ADCL | (ADCH << 8);
			#else
				return ADCL | (ADCH << 8);
			#endif
		}
		
		ISR(ADC_vect)
		{
			if(funcs[ADC_ONCOMPARE_CUSTOMFUNC_ADDR] != NULL)
				funcs[ADC_ONCOMPARE_CUSTOMFUNC_ADDR]();
		}
	//#endif //elif ADC_MODE == ADC_MODE_LOCK
	#elif ADC_MODE == ADC_MODE_DEADLINE
	
		void ADCInit()
		{
			for(int i = 0; i < NUM_OF_ANALOG_PINS; i++)
			{
				_analogPins[i] = 0;
			}
			ADCFlush();
			
			ADCSetRef(ADC_REF_AVCC);
			ADCSetPrescaller(ADC_DEF_PRESCALLER);
			ADCSendControl(ADC_CONTROL_AUTOTRIGGER);
			ADCSendControl(ADC_CONTROL_INTERRUPT_EN);
			ADCEnable();
			ADCStartConvert();
		}

		ISR(ADC_vect)
		{
			#if USE_ADC_8BIT == 1
				_analogPins[_currPin] = ADCH;// = ADCL | (ADCH << 8);
			#else
				_analogPins[_currPin] = ADCL | (ADCH << 8);
			#endif
			
			ADCSetAnalogChanged(_currPin, 1);
			_currPin++;
			if(_currPin >= NUM_OF_ANALOG_PINS)
			{
				_currPin = 0;
			}		
			ADMUX = _analogRef | (_currPin & NUM_OF_ANALOG_PINS);
			if(funcs[ADC_ONCOMPARE_CUSTOMFUNC_ADDR] != NULL)
				funcs[ADC_ONCOMPARE_CUSTOMFUNC_ADDR]();
		}
		
		
		int analogRead(uint8_t __pin)
		{
			while(!ADCGetAnalogChanged(__pin))
			{
				asm("NOP");//todo: sleep instad busyloop
			}
			ADCSetAnalogChanged(__pin, 0);
			return _analogPins[__pin] & ADC_DATA_MASK;
		}
	#endif //elif ADC_MODE == ADC_MODE_LOCK
#endif //if defined(ADCL) && USE_ADC == 1

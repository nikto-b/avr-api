#include "base.hpp"
#include "ADC.hpp"
#define NUM_OF_ANALOG_PINS 15
#include "customFuncAddr.hpp"

#if defined(ADCL)
	#pragma message "ADC found"
	#define ADC_DATA_MASK 1023
	#define ADC_CHANGED_MASK 1024
	uint8_t _analogRef;
	volatile uint16_t _analogPins[NUM_OF_ANALOG_PINS];
	volatile uint8_t _currPin = 0;

	/*
	 * Function _ADCSetAnalogChanged
	 * Desc     Set state of "isNewMeasure"
	 * Input    __pin: state of what pin?
	 * 			__state: state to set
	 * Output   none
	*/
	void _ADCSetAnalogChanged(uint8_t __pin, uint8_t __state)
	{
		_analogPins[__pin] = (_analogPins[__pin] & ~ADC_CHANGED_MASK) | (__state * ADC_CHANGED_MASK);
	}

	/*
	 * Function ADCGetAnalogChanged
	 * Desc     Return state of "isNewMeasure"
	 * Input    __pin: what pin get state
	 * Output   state
	*/
	bool ADCGetAnalogChanged(uint8_t __pin)
	{
		return (_analogPins[__pin] & ADC_CHANGED_MASK) != 0;
	}



	/*
	 * Function ADCSendControl
	 * Desc     Set control signal to ADC
	 * Input    _contr: control signal
	 * Output   none
	*/
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

	/*
	 * Function ADCSetRef
	 * Desc     Set analog reference source
	 * Input    __ref: analog reference source
	 * Output   none
	*/
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

	/*
	 * Function ADCSetPrescaller
	 * Desc     Set ADC prescaller
	 * Input    __prescaller: prescaller to set
	 * Output   none
	*/
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

	/*
	 * Function ADCSetAnalogAutotriggerSCR
	 * Desc     Set source for autotrigger
	 * Input    __src: source
	 * Output   none
	*/
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

#ifdef DIDR0
	/*
	 * Function ADCDisableDigitalInput0to7
	 * Desc     Disable digital input for pins 0 to 7
	 * Input    __mask: mask for disabling
	 * Output   none
	*/
	  void ADCDisableDigitalInput0to7(uint8_t __mask)
	{
		DIDR0 = __mask;
	}
#endif //ifdef DIDR0

#ifdef DIDR2
	/*
	 * Function ADCDisableDigitalInput8to15
	 * Desc     Disable digital input for pins 8 to 15
	 * Input    __mask: mask for disabling
	 * Output   none
	*/
	  void ADCDisableDigitalInput8to15(uint8_t __mask)
	{
		//DIDR2 = __mask;
	}
#endif //ifdef DIDR2

	/*
	 * Function ADCEnable
	 * Desc     Start ADC
	 * Input    none
	 * Output   none
	*/
	  void ADCEnable(void)
	{
		ADCSendControl(ADC_CONTROL_ENABLE);
	}

	/*
	 * Function ADCDisable
	 * Desc     Stop ADC
	 * Input    none
	 * Output   none
	*/
	  void ADCDisable(void)
	{
		ADCSRA = (ADCSRA & ~ADC_CONTROL_ENABLE);
	}

	/*
	 * Function ADCStartConvert
	 * Desc     Start converting
	 * Input    none
	 * Output   none
	*/
	  void ADCStartConvert(void)
	{
		ADCSendControl(ADC_CONTROL_START_CONVERTION);
	}

	/*
	 * Function ADCStopConvert
	 * Desc     Stop converting
	 * Input    none
	 * Output   none
	*/
	  void ADCStopConvert(void)
	{
		ADCSRA = (ADCSRA & ~ADC_CONTROL_START_CONVERTION);
	}

	/*
	 * Function ADCFlush
	 * Desc     Clear registers
	 * Input    none
	 * Output   none
	*/
  void ADCFlush(void)
	{
		ADCSRA = 0;
		ADCSRB = 0;
		#ifdef DIDR2
		//DIDR2  = 0;
		#endif //ifdef DIDR2
		#ifdef DIDR0
		DIDR0  = 0;
		#endif
	}


	/*
	 * Function ADCInit
	 * Desc     Initialize ADC
	 * Input    none
	 * Output   none
	*/
	void ADCInit(void)
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
		ADCSendControl(ADC_CONTROL_INTERRUPT_EN);
		ADCEnable();
		ADCStartConvert();
		//*/
						//legacy
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

	/*
	 * Function ISR(ADC_vect)
	 * Desc     Interrupt handler for vector ADC_vect
	 * Input    Interrupt vector
	 * Output   none
	*/
	ISR(ADC_vect)
	{
		_analogPins[_currPin] = ADCL | (ADCH << 8);
		_ADCSetAnalogChanged(_currPin, 1);
		_currPin++;
		if(_currPin >= NUM_OF_ANALOG_PINS)
		{
			_currPin = 0;
		}
		ADMUX = _analogRef | (_currPin & NUM_OF_ANALOG_PINS);
		callCustomFunc(INTERRUPT_CUSTOMFUNC_ADC);
	}


	/*
	 * Function analogRead
	 * Desc     Return measurment of pin
	 * Input    __pin: pin for returning measurment
	 * Output   measurment
	*/
	int analogRead(uint8_t __pin)
	{
		_ADCSetAnalogChanged(__pin, 0);
		return _analogPins[__pin] & ADC_DATA_MASK;
	}
#endif //if defined(ADCL) && USE_ADC == 1

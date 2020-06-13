#include "base.hpp"
#include "ADC.hpp"
#include "customFuncAddr.hpp"

namespace adc
{
	uint8_t _analogRef;
	volatile uint16_t _analogPins[NUM_OF_ANALOG_PINS];
	volatile uint8_t _currPin = 0;

	/*
	* Function ADCSetAnalogChanged
	* Desc     Set state of "isNewMeasure"
	* Input    __pin: state of what pin?
	* 			__state: state to set
	* Output   none
	*/
	void ADCSetAnalogChanged(uint8_t __pin, uint8_t __state)
	{
		_analogPins[__pin] = (_analogPins[__pin] & static_cast<uint8_t>(~ADC_CHANGED_MASK)) | static_cast<uint8_t>(__state * ADC_CHANGED_MASK);
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
		ADCSRA = static_cast<uint8_t>((ADCSRA & ~ADC_PRESCALLER_MASK) | __prescaller);
	}

	/*
	* Function ADCSetAnalogAutotriggerSCR
	* Desc     Set source for autotrigger
	* Input    __src: source
	* Output   none
	*/
	#ifdef ADCSRB
	void ADCSetAutotriggerSRC(uint8_t __src)
	{
		ADCSRB = static_cast<uint8_t>((ADCSRB & ~ADC_ADTS_MASK) | __src);
	}
	#endif

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
			DIDR2 = __mask;
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
		ADCSRA = static_cast<uint8_t>(ADCSRA & ~ADC_CONTROL_ENABLE);
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
		ADCSRA = static_cast<uint8_t>(ADCSRA & ~ADC_CONTROL_START_CONVERTION);
	}

	/*
	* Function ADCFlush
	* Desc     Clear registers
	* Input    none
	* Output   none
	*/
	void ADCFlush(void)
	{
		#ifdef ADCSRB
		ADCSRA = 0;
		ADCSRB = 0;
		#else
		ADCSR = 0;
		#endif
		#ifdef DIDR2
		DIDR2  = 0;
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
			_analogPins[i] = 0;
		ADCFlush();
		ADCSetRef(ADC_REF_AVCC);
		ADMUX = ADMUX | _currPin;	//because -Wconversion breaks this thing
		ADCSetPrescaller(ADC_PRESCALLER_32);
		#ifdef ADC_CONTROL_AUTOTRIGGER
		ADCSendControl(ADC_CONTROL_AUTOTRIGGER);
		#endif
		ADCSendControl(ADC_CONTROL_INTERRUPT_EN);
		ADCEnable();
		ADCStartConvert();
	}


	/*
	* Function analogRead
	* Desc     Return measurment of pin
	* Input    __pin: pin for returning measurment
	* Output   measurment
	*/
	int analogRead(uint8_t __pin)
	{
		ADCSetAnalogChanged(__pin, 0);
		return _analogPins[__pin] & ADC_DATA_MASK;
	}

} // namespace adc

/*
* Function ISR(ADC_vect)
* Desc     Interrupt handler for vector ADC_vect
* Input    Interrupt vector
* Output   none
*/
ISR(ADC_vect)
{
	adc::_analogPins[adc::_currPin] = static_cast<uint16_t>(ADCL | (ADCH << 8));
	adc::ADCSetAnalogChanged(adc::_currPin, 1);
	adc::_currPin++;
	if(adc::_currPin >= adc::NUM_OF_ANALOG_PINS)
	{
		adc::_currPin = 0;
	}														//NOTE: why?
	ADMUX = static_cast<uint8_t>(adc::_analogRef | (adc::_currPin & adc::NUM_OF_ANALOG_PINS));
	interrupt::call(interrupt::ADC);
}
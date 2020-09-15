#include "base.hpp"
#include "ADC.hpp"
#include "customFuncAddr.hpp"

namespace adc
{
	uint8_t _analogRef;
	volatile uint16_t _analogPins[NUM_OF_ANALOG_PINS];
	volatile uint8_t _currPin = 0;

	/*
	* Function setAnalogChanged
	* Desc     Set state of "isNewMeasure"
	* Input    __pin: state of what pin?
	* 			__state: state to set
	* Output   none
	*/
	void setAnalogChanged(uint8_t __pin, uint8_t __state)
	{
		_analogPins[__pin] = (_analogPins[__pin] & static_cast<uint8_t>(~ADC_CHANGED_MASK)) | static_cast<uint8_t>(__state * ADC_CHANGED_MASK);
	}

	/*
	* Function getAnalogChanged
	* Desc     Return state of "isNewMeasure"
	* Input    __pin: what pin get state
	* Output   state
	*/
	bool getAnalogChanged(uint8_t __pin)
	{
		return (_analogPins[__pin] & ADC_CHANGED_MASK) != 0;
	}



	/*
	* Function sendControl
	* Desc     Send control signal to ADC
	* Input    _contr: control signal
	* Output   none
	*/
	void sendControl(uint8_t __contr)
	{
		ADCSRA |= __contr;
	}

	/*
	* Function setRef
	* Desc     Set analog reference source
	* Input    __ref: analog reference source
	* Output   none
	*/
	void setRef(uint8_t __ref)
	{
		ADMUX |= __ref;
		_analogRef = __ref;
	}

	/*
	* Function setPrescaller
	* Desc     Set ADC prescaller
	* Input    __prescaller: prescaller to set
	* Output   none
	*/
	void setPrescaller(uint8_t __prescaller)
	{
		ADCSRA = static_cast<uint8_t>((ADCSRA & ~adc::prescaller::MASK) | __prescaller);
	}

	/*
	* Function setAutotriggerSRC
	* Desc     Set source for autotrigger
	* Input    __src: source
	* Output   none
	*/
	#ifdef ADCSRB
	void setAutotriggerSRC(uint8_t __src)
	{
		ADCSRB = static_cast<uint8_t>((ADCSRB & ~adc::autotrigger::MASK) | __src);
	}
	#endif

	#ifdef DIDR0
		/*
		* Function disableDigitalInput0to7
		* Desc     Disable digital input for pins 0 to 7
		* Input    __mask: mask for disabling
		* Output   none
		*/
		void disableDigitalInput0to7(uint8_t __mask)
		{
			DIDR0 = __mask;
		}
	#endif //ifdef DIDR0

	#ifdef DIDR2
		/*
		* Function disableDigitalInput8to15
		* Desc     Disable digital input for pins 8 to 15
		* Input    __mask: mask for disabling
		* Output   none
		*/
		void disableDigitalInput8to15(uint8_t __mask)
		{
			DIDR2 = __mask;
		}
	#endif //ifdef DIDR2

	/*
	* Function enable
	* Desc     Start ADC
	* Input    none
	* Output   none
	*/
	void enable(void)
	{
		sendControl(adc::control::ENABLE);
	}

	/*
	* Function disable
	* Desc     Stop ADC
	* Input    none
	* Output   none
	*/
	void disable(void)
	{
		ADCSRA = static_cast<uint8_t>(ADCSRA & ~adc::control::ENABLE);
	}

	/*
	* Function startConvert
	* Desc     Start converting
	* Input    none
	* Output   none
	*/
	void startConvert(void)
	{
		sendControl(adc::control::START_CONVERTION);
	}

	/*
	* Function stopConvert
	* Desc     Stop converting
	* Input    none
	* Output   none
	*/
	void stopConvert(void)
	{
		ADCSRA = static_cast<uint8_t>(ADCSRA & ~adc::control::START_CONVERTION);
	}

	/*
	* Function flush
	* Desc     Clear registers
	* Input    none
	* Output   none
	*/
	void flush(void)
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
	* Function init
	* Desc     Initialize ADC
	* Input    none
	* Output   none
	*/
	void init(void)
	{
		for(int i = 0; i < NUM_OF_ANALOG_PINS; i++)
			_analogPins[i] = 0;
		flush();
		setRef(adc::ref::AVCC);
		ADMUX |= _currPin;
		setPrescaller(adc::prescaller::_32);
		#ifdef ADC_CONTROL_AUTOTRIGGER
		sendControl(ADC_CONTROL_AUTOTRIGGER);
		#endif
		sendControl(adc::control::INTERRUPT_EN);
		enable();
		startConvert();
	}


	/*
	* Function analogRead
	* Desc     Return measurment of pin
	* Input    __pin: pin for returning measurment
	* Output   measurment
	*/
	int analogRead(uint8_t __pin)
	{
		setAnalogChanged(__pin, 0);
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
	adc::setAnalogChanged(adc::_currPin, 1);
	adc::_currPin++;
	if(adc::_currPin >= adc::NUM_OF_ANALOG_PINS)
	{
		adc::_currPin = 0;
	}														//NOTE: why?
	ADMUX = static_cast<uint8_t>(adc::_analogRef | (adc::_currPin & adc::NUM_OF_ANALOG_PINS));
	interrupt::call(interrupt::ADC);
}
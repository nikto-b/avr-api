#include "ADCModes.hpp"

namespace adc
{
  const int NUM_OF_ANALOG_PINS  = 15;
  const int ADC_DATA_MASK       = 1023;
	const int ADC_CHANGED_MASK    = 1024;
	

  void ADCSetAnalogChanged(uint8_t __pin, uint8_t __state);
  bool ADCGetAnalogChanged(uint8_t __pin);
  void ADCSendControl(uint8_t __contr);
  void ADCSetRef(uint8_t __ref);
  void ADCSetPrescaller(uint8_t __prescaller);
  void ADCSetAutotriggerSRC(uint8_t __src);
  void ADCDisableDigitalInput0to7(uint8_t __mask);
  #ifdef DIDR2
  void ADCDisableDigitalInput8to15(uint8_t __mask);
  #endif
  void ADCEnable(void);
  void ADCDisable(void);
  void ADCStartConvert(void);
  void ADCStopConvert(void);
  void ADCFlush(void);
  void ADCInit(void);
  int analogRead(uint8_t _pin);
} // namespace adc
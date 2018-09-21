#define _ADC_MODES
//				ANALOG  REFERENCE
#define ADC_REF_AREF 		0	
#define ADC_REF_AVCC 		(1 << REFS0)					//external capacitor at AREF pin
#define ADC_REF_INT_1_1V	(1 << REFS1)					//Internal 1.1V  with ext cap at AREF pin
#define ADC_REF_INT_2_56V	((1 << REFS0) | (1 << REFS1))	//Internal 2.56V with ext cap at AREF pin

//				ADC CONTROL
#define ADC_CONTROL_ENABLE	(1 << ADEN)
#define ADC_CONTROL_START_CONVERTION (1 << ADSC)
#define ADC_CONTROL_AUTOTRIGGER (1 << ADATE)
#define ADC_CONTROL_INTERRUPT_FLAG_EN (1 << ADIF)
#define ADC_CONTROL_INTERRUPT_EN (1 << ADEN)

//				ADC PRESCALLERS
#define ADC_PRESCALLER_MASK ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))
#define ADC_PRESCALLER_DEF	0
#define ADC_PRESCALLER_2	(1 << ADPS0)
#define ADC_PRESCALLER_4	(1 << ADPS1)
#define ADC_PRESCALLER_8	((1 << ADPS0) | (1 << ADPS1))
#define ADC_PRESCALLER_16	(1 << ADPS2)
#define ADC_PRESCALLER_32	((1 << ADPS2) | (1 << ADPS0))
#define ADC_PRESCALLER_64	((1 << ADPS2) | (1 << ADPS1))
#define ADC_PRESCALLER_128	((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))

//				ADC AUTOTRIGGER SOURCES
#define ADC_ADTS_MASK					((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0))
#define ADC_ADTS_FREERUN				0
#define ADC_ADTS_ANALOG_COMPARATOR		(1 << ADTS0)
#define ADC_ADTS_EXT_INTERRUPT_REQ_0	(1 << ADTS1)
#define ADC_ADTS_TC0_COMPA				((1 << ADTS0) | (1 << ADTS1))
#define ADC_ADTS_TC0_OVF				(1 << ADTS2)
#define ADC_ADTS_TC1_COMPB				((1 << ADTS2) | (1 << ADTS0))
#define ADC_ADTS_TC1_OVF				((1 << ADTS2) | (1 << ADTS1))
#define ADC_ADTS_TC1_CAPT_EV			((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0))

//				ADC MODES
#define ADC_MODE_BACKGROUND	0
#define ADC_MODE_DEADLINE	1
#define ADC_MODE_MANUAL		3

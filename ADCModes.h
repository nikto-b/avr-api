#define _ADC_MODES
//				ANALOG  REFERENCE
#define ADC_REF_AREF 		0								//external at AREF
#define ADC_REF_AVCC 		(1 << REFS0)					//external capacitor at AREF pin
#define ADC_REF_INT_1_1V	(1 << REFS1)					//Internal 1.1V  with ext cap at AREF pin
#define ADC_REF_INT_2_56V	((1 << REFS0) | (1 << REFS1))	//Internal 2.56V with ext cap at AREF pin

//				ADC CONTROL
#define ADC_CONTROL_ENABLE	(1 << ADEN)						//enable ADC
#define ADC_CONTROL_START_CONVERTION (1 << ADSC)			//start convertion
#define ADC_CONTROL_AUTOTRIGGER (1 << ADATE)				//enable autotrigger
#define ADC_CONTROL_INTERRUPT_FLAG_EN (1 << ADIF)			//enable interrupt flag
#define ADC_CONTROL_INTERRUPT_EN (1 << ADIE)				//enable interrupt

//				ADC PRESCALLERS
#define ADC_PRESCALLER_MASK ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))//mask for funcInputProterctor
#define ADC_PRESCALLER_DEF	0								//default prescaller(*1)
#define ADC_PRESCALLER_2	(1 << ADPS0)					//*2
#define ADC_PRESCALLER_4	(1 << ADPS1)					//*4
#define ADC_PRESCALLER_8	((1 << ADPS0) | (1 << ADPS1))	//*8
#define ADC_PRESCALLER_16	(1 << ADPS2)					//*16
#define ADC_PRESCALLER_32	((1 << ADPS2) | (1 << ADPS0))	//*32
#define ADC_PRESCALLER_64	((1 << ADPS2) | (1 << ADPS1))	//*64
#define ADC_PRESCALLER_128	((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))//*128

//				ADC AUTOTRIGGER SOURCES
#define ADC_ADTS_MASK					((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0))	//mask for funcInputProtector
#define ADC_ADTS_FREERUN				0												//
#define ADC_ADTS_ANALOG_COMPARATOR		(1 << ADTS0)									//ADC TRIGGER
#define ADC_ADTS_EXT_INTERRUPT_REQ_0	(1 << ADTS1)									//EXTERNAL INTERRUPT
#define ADC_ADTS_TC0_COMPA				((1 << ADTS0) | (1 << ADTS1))					//TC0 COMPARE WITH A
#define ADC_ADTS_TC0_OVF				(1 << ADTS2)									//TC0 OVERFLOW
#define ADC_ADTS_TC1_COMPB				((1 << ADTS2) | (1 << ADTS0))					//TC1 COMPARE WITH B
#define ADC_ADTS_TC1_OVF				((1 << ADTS2) | (1 << ADTS1))					//TC1 OVERFLOW
#define ADC_ADTS_TC1_CAPT_EV			((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0))	//TC1 CAPTURE EVENT

//				ADC MODES
#define ADC_MODE_BACKGROUND	0				//background work with interrupts
#define ADC_MODE_DEADLINE	1				//background + wait for update
#define ADC_MODE_LOCK		2				//reinit at analogRead()
#define ADC_MODE_MANUAL		3				//manual controlling of ADC



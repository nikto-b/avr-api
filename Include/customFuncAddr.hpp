#include "base.hpp"

#define INTERRUPT_CUSTOMFUNC_RESET			0		//reset from ext pin, Power-On-Reset, Brown-out Reset, Watchdog reset, JTAG AVR Reset
#define INTERRUPT_CUSTOMFUNC_INT0			1		//ext interrupt req 0
#define INTERRUPT_CUSTOMFUNC_INT1			2		//ext interrupt req 1
#define INTERRUPT_CUSTOMFUNC_INT2			3		//ext interrupt req 2
#define INTERRUPT_CUSTOMFUNC_INT3			4		//ext interrupt req 3
#define INTERRUPT_CUSTOMFUNC_INT4			5		//ext interrupt req 4
#define INTERRUPT_CUSTOMFUNC_INT5			6		//ext interrupt req 5
#define INTERRUPT_CUSTOMFUNC_INT6			7		//ext interrupt req 6
#define INTERRUPT_CUSTOMFUNC_INT7			8		//ext interrupt req 7
#define INTERRUPT_CUSTOMFUNC_PCINT0			9		//pin change interrupt request 0
#define INTERRUPT_CUSTOMFUNC_PCINT1			10		//pin change interrupt request 1
#define INTERRUPT_CUSTOMFUNC_PINT2			11		//pin change interrupt request 2
#define INTERRUPT_CUSTOMFUNC_WDT			12		//watchdog time-out interrupt
#define INTERRUPT_CUSTOMFUNC_TC2_COMPA		13		//Timer/Counter2 Compare Match A
#define INTERRUPT_CUSTOMFUNC_TC2_COMPB		14		//Timer/Counter2 Compare Match B
#define INTERRUPT_CUSTOMFUNC_TC2_OVF		15		//Timer/Counter2 Overflow
#define INTERRUPT_CUSTOMFUNC_TC1_CAPT		16		//Timer/Counter1 Capture Event
#define INTERRUPT_CUSTOMFUNC_TC1_COMPA		17		//Timer/Counter1 Compare Match A
#define INTERRUPT_CUSTOMFUNC_TC1_COMPB		18		//Timer/Counter1 Compare Match B
#define INTERRUPT_CUSTOMFUNC_TC1_COMPC		19		//Timer/Counter1 Compare Match C
#define INTERRUPT_CUSTOMFUNC_TC1_OVF		20		//Timer/Counter1 Overflow
#define INTERRUPT_CUSTOMFUNC_TC0_COMPA		21		//Timer/Counter0 Compare Match A
#define INTERRUPT_CUSTOMFUNC_TC0_COMPB		22		//Timer/Counter0 Compare Match B
#define INTERRUPT_CUSTOMFUNC_TC0_OVF		23		//Timer/Counter0 Overflow
#define INTERRUPT_CUSTOMFUNC_SPI_STC		24		//SPI Serial Transfer Complete
#define INTERRUPT_CUSTOMFUNC_USART0_RX		25		//USART0 RX Complete
#define INTERRUPT_CUSTOMFUNC_USART0_UDRE	26		//USART0 Data Register Empty
#define INTERRUPT_CUSTOMFUNC_USART0_TX		27		//USART0 TX Complete
#define INTERRUPT_CUSTOMFUNC_ANALOG_COMP	28		//Analog Comparator
#define INTERRUPT_CUSTOMFUNC_ADC			29		//ADC Conversion Complete
#define INTERRUPT_CUSTOMFUNC_EE_READY		30		//EEPROM Ready
#define INTERRUPT_CUSTOMFUNC_TC3_CAPT		31		//Timer/Counter3 Capture Event
#define INTERRUPT_CUSTOMFUNC_TC3_COMPA		32		//Timer/Counter3 Cpmpare Match A
#define INTERRUPT_CUSTOMFUNC_TC3_COMPB		33		//Timer/Counter3 Compare Match B
#define INTERRUPT_CUSTOMFUNC_TC3_COMPC		34		//Timer/Counter3 Compare Match C
#define INTERRUPT_CUSTOMFUNC_TC3_OVF		35		//Timer/Counter3 Overflow
#define INTERRUPT_CUSTOMFUNC_USART1_RX		36		//USART1 RX Complete
#define INTERRUPT_CUSTOMFUNC_USART1_UDRE	37		//USART1 Data Register Empty
#define INTERRUPT_CUSTOMFUNC_USART1_TX		38		//USART1 TX Complete
#define INTERRUPT_CUSTOMFUNC_TWI			39		//2-wire Serial Interface
#define INTERRUPT_CUSTOMFUNC_SPM_READY		40		//Store Program Memory Ready
#define INTERRUPT_CUSTOMFUNC_TC4_CAPT		41		//Timer/Counter4 Capture Event
#define INTERRUPT_CUSTOMFUNC_TC4_COMPA		42		//Timer/Counter4 Compare Match A
#define INTERRUPT_CUSTOMFUNC_TC4_COMPB		43		//Timer/Counter4 Compare Match B
#define INTERRUPT_CUSTOMFUNC_TC4_COMPC		44		//Timer/Counter4 Compare Match C
#define INTERRUPT_CUSTOMFUNC_TC4_OVF		45		//Timer/Counter4 Overflow
#define INTERRUPT_CUSTOMFUNC_TC5_CAPT		46		//Timer/Counter4 Capture Event
#define INTERRUPT_CUSTOMFUNC_TC5_COMPA		47		//Timer/Counter4 Compare Match A
#define INTERRUPT_CUSTOMFUNC_TC5_COMPB		48		//Timer/Counter4 Compare Match B
#define INTERRUPT_CUSTOMFUNC_TC5_COMPC		49		//Timer/Counter4 Compare Match C
#define INTERRUPT_CUSTOMFUNC_TC5_OVF		50		//Timer/Counter4 Overflow
#define INTERRUPT_CUSTOMFUNC_USART2_RX		51		//USART2 RX Complete
#define INTERRUPT_CUSTOMFUNC_USART2_UDRE	52		//USART2 Data Register Empty
#define INTERRUPT_CUSTOMFUNC_USART2_TX		53		//USART2 TX Complete
#define INTERRUPT_CUSTOMFUNC_USART3_RX		54		//USART3 RX Complete
#define INTERRUPT_CUSTOMFUNC_USART3_UDRE	55		//USART3 Data Register Empty
#define INTERRUPT_CUSTOMFUNC_USART3_TX		56		//USART3 TX Complete

#define INTERRUPT_CUSTOMFUNC_NUM_OF_UNITS	57		//num of origin custom functions

 void callCustomFunc(unsigned char __addr);
 void setCustomFunc(uint8_t __addr, void(* __func)());
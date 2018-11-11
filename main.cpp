#include <avr/io.h>			//include for base avr funcs
#define F_CPU 16000000		//define with freq
#include <util/delay.h> 	//include for delay func
#include <avr/interrupt.h>	//include interrupt funcs
#include <stdlib.h>

#define NUM_OF_ANALOG_PINS 7
#define ARDUINO_SUPPORT 0
#define USE_FUNC_INPUT_PROTECTOR 0

//-----------ADC-----------
#define USE_ADC 1
#define USE_ADC_8BIT 1
#define ADC_MODE ADC_MODE_DEADLINE
#define ADC_DEF_PRESCALLER ADC_PRESCALLER_128

//---------TIMERS----------
#define USE_TIMERS 1
#define TIMER0_USE_COMPA 1
#define TIMER5_USE_COMPA 1

//---------USART----------
#define EOL (char*)"\n\r"
#define USE_USART 1
#define USE_USART0 1
#define USE_USART0_OUTPUT 1
#define USE_USART0_INPUT 1
#define USE_SERIAL_FASTBAUD 0

//---------CUSTOM_INTERRUPTS----------
#define USE_CUSTOM_INTERRUPTS 1


#define USE_WATCHDOG 1

#include "api.h"//custom lib for AVR
#define DEBUG					1


void wdt_handler(void)
{
	USART0Println("WDT!");
	WDStop();
}

int main()
{
	DDRB = ((1 << PB0) | (1 << PB1) | (1 << PB7) | (1 << PB1));								//8, 9, 13 output
	DDRC = ((1 << PC5) | (1 << PC4) | (1 << PC3));											//A0,1,2 output
	DDRB |= ((1 << PB4) | (1 << PB5) | (1 << PB6));
	USART0Begin(115200);
	setCustomFunc(INTERRUPT_CUSTOMFUNC_WDT, wdt_handler);
	//asm("wdr");
	//WDTCSR |= (1 << WDCE) | (1 << WDE);
	//WDTCSR = (1 << WDE) | ((1 << WDP3) | (1 << WDP0));
	WDTStart(WD_TIME_4s);
	sei();
	USART0Print("s");
	while(1);
	return 0;
}

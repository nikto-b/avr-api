#include <avr/io.h>			//include for base avr funcs
#define F_CPU 16000000		//define with freq
#include <util/delay.h> 		//include for delay func
#include <avr/interrupt.h>	//include interrupt funcs
#include <stdlib.h>

#define NUM_OF_ANALOG_PINS 7
#define ARDUINO_SUPPORT 0
#define USE_ADC 1

//---------TIMERS----------
#define USE_TIMERS 1

//---------USART----------
#define USE_USART 1
#define USE_USART0 1
#define USE_USART0_OUTPUT 1
#define USE_USART0_INPUT 1
#define USE_SERIAL_FASTBAUD 0

//---------CUSTOM_INTERRUPTS----------
#define USE_CUSTOM_INTERRUPTS 1

#include "api.h"//custom api for AVR

void USART_RX()
{
}



int main()
{
	DDRB = ((1 << PB0) | (1 << PB1) | (1 << PB7));//8, 9, 13 output
	DDRC = ((1 << PC5) | (1 << PC4) | (1 << PC3));//A0,1,2 output
	DDRD = ((1 << PD2) | (1 << PD3) | (0 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));//2,3,4,5,6,7 output
	PORTB &= ~(1 << PB7);
	USART0Begin(115200);
	funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] = USART_RX;
	sei();
	while(1)
	{
		//USARTPrint("OK!\n");
		if(USART0Available())
		{	  
			//PORTB = 1 << PB7;
			USART0Println("found!");
			USART0Send(USART0Read());
			//USARTSend('\n');
			USART0Println((char)(str2int(int2str(2))));
			USART0Println();
		}
		_delay_ms(1);
	}
	return 0;
}

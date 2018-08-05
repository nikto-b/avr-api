#include <avr/io.h>			//include for base avr funcs
#define F_CPU 16000000		//define with freq
#include <util/delay.h> 		//include for delay func
#include <avr/interrupt.h>	//include interrupt funcs
#include <stdio.h>
#include <stdlib.h>

#define DEVICE atmega2560		//define with AVR name
//#define BOOTLOADER_ADDRESS 0x7000	//define with addr of bootloader in mem
#define NUM_OF_ANALOG_PINS 7
#define ARDUINO_SUPPORT 0
#define USE_ADC 0

//---------TIMERS----------
#define USE_TIMERS 0

//---------USART----------
#define USE_USART 1
#define USE_USART0 1
#define USE_USART0_OUTPUT 1
#define USE_USART0_INPUT 1
#define USE_SERIAL_FASTBAUD 0

//---------CUSTOM_INTERRUPTS----------
#define USE_CUSTOM_INTERRUPTS 1

#include "api.h"//custom api for AVR


using namespace std;


void usartGotCharFunc()
{
	USARTPrint("GOT MESSAGE!");
	//USARTPrint(USARTRead());
	USARTSend(USARTRead());
	USARTPrint("\n");
}

#if USE_TIMERS == 1


	#define overflows 1
	#define counter 80
	void TIMER0_CTC()
	{
		USARTSend('A');
	}
#endif

bool fuck = false;

void USART_RX()
{
	fuck = true;
}

char* decToBin(int _in, uint16_t _count)
{
	char *_res = (char*)malloc(_count);
	while(_in && _count >= 0)
	{
		_res[_count] = (_in & 1) + 48;
		_in >>= 1;
		_count--;
	}
	return _res;
}


int main()
{
	DDRB = ((1 << PB0) | (1 << PB1) | (1 << PB7));//8, 9, 13 output
	DDRC = ((1 << PC5) | (1 << PC4) | (1 << PC3));//A0,1,2 output
	DDRD = ((1 << PD2) | (1 << PD3) | (0 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));//2,3,4,5,6,7 output
	//DDRD = 1 << PD4;
	
	
	
	
	//funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] = USART_RX;
	//PORTB = 1;
	PORTB |= ~(1 << PB7);
	USARTBegin(115200);
	//TIMER0Init(TIMER0_MODE_CTC, TIMER0_CLOCK_EXTERNAL_RISING, 10);
	//funcs[TIMER0_COMPB_CUSTOMFUNC_ADDR] = TIMER0_CTC;
	funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] = USART_RX;
	sei();
	while(1)
	{
		USARTPrint("OK!\n");
	}
	return 0;
}

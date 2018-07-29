#include <avr/io.h>			//include for base avr funcs
#define F_CPU 16000000		//define with freq
#include <util/delay.h> 		//include for delay func
#include <avr/interrupt.h>	//include interrupt funcs
#include <stdio.h>
#include <stdlib.h>

#define DEVICE atmega328p		//define with AVR name
//#define BOOTLOADER_ADDRESS 0x7000	//define with addr of bootloader in mem
#define NUM_OF_ANALOG_PINS 7
#define ARDUINO_SUPPORT 1
#define USE_ADC 1

//---------TIMERS----------
#define USE_TIMERS 1

//---------USART----------
#define USE_USART 1
#define USE_USART0 1

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

bool wannaStopArmC = false;
bool wannaStopArmCC = false;

void USART_RX()
{
	USARTPrint("GOT\n");
	switch(USARTRead())
	{
		case '0':
		{
			PORTC ^= (1 << PC4);
			_delay_ms(1000);
			PORTC ^= (1 << PC4);
			break;
		}
		case '1':
		{
			PORTC ^= (1 << PC3);
			_delay_ms(1000);
			PORTC ^= (1 << PC3);
			break;
		}
		case '2':
		{
			PORTC ^= (1 << PC5);
			wannaStopArmC = !wannaStopArmC;		
			break;
		}
		case '3':
		{
			PORTD ^= (1 << PD6);
			wannaStopArmCC = !wannaStopArmCC;
			break;
		}
		case '4':
		{
			PORTD ^= (1 << PD4);
			_delay_ms(1000);
			PORTD ^= (1 << PD4);	
			break;
		}
		case '5':
		{
			PORTD ^= (1 << PD5);
			_delay_ms(1000);
			PORTD ^= (1 << PD5);			
			break;
		}
		case '6':
		{
			PORTD ^= (1 << PD3);
			_delay_ms(1000);
			PORTD ^= (1 << PD3);	
			break;
		}
		case '7':
		{
			PORTD ^= (1 << PD2);
			_delay_ms(1000);
			PORTD ^= (1 << PD2);
			break;
		}
		case '8':
		{
			
			break;
		}
		case '9':
		{
			
			break;
		}
	}
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

inline void setMotorDirectionC(uint8_t port, uint8_t pin, uint8_t direction)
{
  *(&port) = (*(&port) & ~(1 << pin)) | (direction << pin);
}
inline void doOneStepC(uint8_t pin, uint64_t delayMicros)
{
  //*(&port) = (*(&port) & ~(1 << pin)) | (1 << pin);//enable pins
  digitalWrite(pin, 1);
  delayMicroseconds(delayMicros);  
  digitalWrite(pin, 0);
  //*(&port) = (*(&port) & ~(1 << pin)) | (0 << pin);//disable pins
  delayMicroseconds(delayMicros);  
}


int main()
{
	DDRB = ((1 << PB0) | (1 << PB1));//8, 9 output
	DDRC = ((1 << PC5) | (1 << PC4) | (1 << PC3));//A0,1,2 output
	DDRD = ((1 << PD2) | (1 << PD3) | (0 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));//2,3,4,5,6,7 output
	//DDRD = 1 << PD4;
	
	
	
	
	funcs[USART0_RECIEVE_INTERRUPT_CUSTOMFUNC_ADDR] = USART_RX;
	/*PORTB = (1 << 9) - 1;
	PORTC = (1 << 9) - 1;
	PORTD |= ((1 << 9) - 1) << 2;*/
	//PORTD = 1 << PD4;
	PORTB = 1;
	USARTBegin(9600);
	TIMER0Init(TIMER0_MODE_CTC, TIMER0_CLOCK_EXTERNAL_RISING, 10);
	//funcs[TIMER0_COMPA_CUSTOMFUNC_ADDR] = TIMER0_CTC;
	funcs[TIMER0_COMPB_CUSTOMFUNC_ADDR] = TIMER0_CTC;
	sei();
	while(1)
	{
		//doOneStepC((8 * 1) + 3, 100);
		/*if((!((PIND >> 7) & 1)) && wannaStopArmCC)
		{
			PORTC &= ~(1 << PC5);
			PORTD &= ~(1 << PD6);
			wannaStopArmCC = 0;
			USARTPrint("AA\n");
		}
		if((!(PINB & 1)) && wannaStopArmC)
		{
			PORTC &= ~(1 << PC5);
			PORTD &= ~(1 << PD6);
			wannaStopArmC = 0;
			USARTPrint("AA\n");
		}*/
	}
	return 0;
}
#pragma message "don't forgot to allow interrupts and good luck with debugging!    :)"

#include <avr/io.h>			//include for base avr funcs
#define F_CPU 16000000		//define with freq
#include <util/delay.h> 	//include for delay func
#include <avr/interrupt.h>	//include interrupt funcs
#include <stdlib.h>

#define NUM_OF_ANALOG_PINS 7
#define ARDUINO_SUPPORT 0
#define USE_ADC 1
#define USE_FUNC_INPUT_PROTECTOR 0

//---------TIMERS----------
#define USE_TIMERS 1
#define TIMER0_USE_COMPA 1
#define TIMER5_USE_COMPA 1

//---------USART----------
#define EOL "\r\n"
#define USE_USART 1
#define USE_USART0 1
#define USE_USART0_OUTPUT 1
#define USE_USART0_INPUT 1
#define USE_SERIAL_FASTBAUD 0

//---------CUSTOM_INTERRUPTS----------
#define USE_CUSTOM_INTERRUPTS 1

#include "api.h"//custom lib for AVR


void disableWheelAC(void)
{
	PORTE &= ~(1 << PE5);	
}

void enableWheelAC(void)
{
	disableWheelAC();
	PORTE |= 1 << PE5;
}

void disableWheelACC(void)
{
	PORTE &= ~(1 << PE4);
}

void enableWheelACC(void)
{
	disableWheelACC();
	PORTE |= 1 << PE4;
}

void disableWheelBC(void)
{
	PORTH &= ~(1 << PH5);	
}

void enableWheelBC(void)
{
	disableWheelBC();
	PORTH |= 1 << PH5;
}

void disableWheelBCC(void)
{
	PORTH &= ~(1 << PH6);
}

void enableWheelBCC(void)
{
	disableWheelACC();
	PORTH |= 1 << PH6;
}

void disableWheelCC(void)
{
	PORTH &= ~(1 << PH4);	
}

void enableWheelCC(void)
{
	disableWheelCC();
	PORTH |= 1 << PH4;
}

void disableWheelCCC(void)
{
	PORTH &= ~(1 << PH3);
}

void enableWheelCCC(void)
{
	disableWheelCCC();
	PORTH |= 1 << PH3;
}

void disableWheelDC(void)
{
	PORTG &= ~(1 << PG5);	
}

void enableWheelDC(void)
{
	disableWheelDC();
	PORTG |= 1 << PG5;
}

void disableWheelDCC(void)
{
	PORTE &= ~(1 << PE3);
}

void enableWheelDCC(void)
{
	disableWheelACC();
	PORTE |= 1 << PE3;
}



void startForward(void)
{
	enableWheelDCC();
	enableWheelBC();
}
void stopForward(void)
{
	disableWheelDCC();
	disableWheelBC();
}

void startRight(void)
{
	enableWheelACC();
	enableWheelCC();
}
void stopRight(void)
{
	disableWheelACC();
	disableWheelCC();
}

void startLeft(void)
{
	enableWheelCCC();
	enableWheelAC();
}
void stopLeft(void)
{
	disableWheelCCC();
	disableWheelAC();
}

void startBackward(void)
{
	enableWheelDC();
	enableWheelBCC();
}
void stopBackward(void)
{
	disableWheelDC();
	disableWheelBCC();
}



void startFR(void)
{
	enableWheelACC();
	enableWheelBC();
}
void stopFR(void)
{
	disableWheelACC();
	disableWheelBC();
}

void startBR(void)
{
	enableWheelCC();
	enableWheelBCC();
}
void stopBR(void)
{
	disableWheelCC();
	disableWheelBCC();
}

void startBL(void)
{
	enableWheelCC();
	enableWheelDC();
}
void stopBL(void)
{
	disableWheelCC();
	disableWheelDC();
}

void startFL(void)
{
	enableWheelAC();
	enableWheelDCC();
}
void stopFL(void)
{
	disableWheelAC();
	disableWheelDCC();
}



void stopTurnC(void)
{
	disableWheelACC();
	disableWheelBCC();
	disableWheelCCC();
	disableWheelDCC();
}
void startTurnC(void)
{
	stopTurnC();
	enableWheelBCC();
	enableWheelCCC();
	enableWheelDCC();
	enableWheelACC();
}

void stopTurnCC(void)
{
	disableWheelAC();
	disableWheelBC();
	disableWheelCC();
	disableWheelDC();
}
void startTurnCC(void)
{
	stopTurnCC();
	enableWheelAC();
	enableWheelBC();
	enableWheelCC();
	enableWheelDC();
}




int main()
{
	DDRB = ((1 << PB0) | (1 << PB1) | (1 << PB7) | (1 << PB1));								//8, 9, 13 output
	DDRC = ((1 << PC5) | (1 << PC4) | (1 << PC3));											//A0,1,2 output
	DDRD = ((1 << PD2) | (1 << PD3) | (0 << PD4) | (1 << PD5) | (1 << PD6) | (0 << PD7));	//2,3,4,5,6,7 output
	//
	DDRE = ((1 << PE4) | (1 << PE5) | (1 << PE3));
	DDRG = (1 << PG5);
	DDRH = ((1 << PH3) | (1 << PH4) | (1 << PH5) | (1 << PH6));
	//DDRF = 1;
	//DDRF = 1;
	DDRL = 0;
	//PORTF = 1;
	DDRB |= ((1 << PB4) | (1 << PB5) | (1 << PB6));
	//PORTL = 1 << PL2;
	//PORTB &= ~(1 << PB7);
	//PORTD |= 1 << PD7;
	USART0Begin(115200);
	//PORTE = 0;
	//PORTG = 0;
	//PORTH = 0;
	//PORTL = 0;
	
	//ADCInit();
	/*ADCFlush();
	ADCSetRef(ADC_REF_AVCC);
	ADMUX |= (_currPin & NUM_OF_ANALOG_PINS);
	ADCSetPrescaller(ADC_PRESCALLER_32);
	ADCSendControl(ADC_CONTROL_AUTOTRIGGER);
	ADCSendControl(ADC_CONTROL_INTERRUPT_EN);
	ADCEnable();
	ADCStartConvert();*/
	/*ADCSRA = 0;
	ADCSRB = 0;
	ADMUX |= (1 << REFS0); 	//set reference voltage
	//ADMUX |= (1 << ADLAR); //configure ADC for 8-bit work (PT1)
	//_analog_ref = ADMUX;			//save ref
	ADMUX |= (0 & NUM_OF_ANALOG_PINS);		//set pin for converting
	//  ADCSRA |= (1 << ADPS2) ;//  set divider - 16
	//  ADCSRA &= ~ (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADPS2) | (1 << ADPS0);//set divider 32
	ADCSRA &= ~ (1 << ADPS1);
	ADCSRA |= (1 << ADATE); 	//set autoconvert at trigger
	ADCSRA |= (1 << ADIE); 	//ADC interrupt enable
	ADCSRA |= (1 << ADEN);	//enable ADC*/
	ADCInit();
	sei();
	ADCSRA |= (1 << ADSC);	//start conversion
	
	//enableWheelACC();
	//while(1){}
	
	//PORTE = 1 << PE4;//wheel A CC
	//PORTE = 1 << PE5;//wheel A C
	//PORTE = 1 << PE3;//wheel D CC
	//PORTG = 1 << PG5;//wheel D C
	//PORTH = 1 << PH3;//wheel C CC
	//PORTH = 1 << PH4;//wheel C C
	//PORTH = 1 << PH5;//wheel B C
	//PORTH = 1 << PH6;//wheel B CC
	int del = 800;
	
	USART0Println(ADCSRA, BIN);
	//while(1){}
	
	loop:
	USART0Println(analogRead(0));
	/*USART0Println("4");
	PORTB = 1 << PB4;
	USART0Println(analogRead(0));
	USART0Println();
	_delay_ms(del);
	USART0Println("5");
	PORTB = 1 << PB5;
	USART0Println(analogRead(0));
	USART0Println();
	_delay_ms(del);
	USART0Println("6");
	PORTB = 1 << PB6;
	USART0Println(analogRead(0));
	USART0Println();
	_delay_ms(del);
	USART0Println("0");
	PORTB = 0;
	USART0Println(analogRead(0));
	USART0Println();
	USART0Println();
	_delay_ms(del);
	*/
	/*enableWheelAC();
	USART0Println("AC");
	_delay_ms(del);
	disableWheelAC();
	USART0Println("STOP");
	_delay_ms(del);
	enableWheelACC();
	USART0Println("ACC");
	_delay_ms(del);
	disableWheelACC();
	USART0Println("STOP");
	_delay_ms(del);
	
	enableWheelBC();
	USART0Println("BC");
	_delay_ms(del);
	disableWheelBC();
	USART0Println("STOP");
	_delay_ms(del);
	enableWheelBCC();
	USART0Println("BCC");
	_delay_ms(del);
	disableWheelBCC();
	USART0Println("STOP");
	_delay_ms(del);
	
	enableWheelCC();
	USART0Println("CC");
	_delay_ms(del);
	disableWheelCC();
	USART0Println("STOP");
	_delay_ms(del);
	enableWheelCCC();
	USART0Println("CCC");
	_delay_ms(del);
	disableWheelCCC();
	USART0Println("STOP");
	_delay_ms(del);
	
	enableWheelDC();
	USART0Println("DC");
	_delay_ms(del);
	disableWheelDC();
	USART0Println("STOP");
	_delay_ms(del);
	enableWheelDCC();
	USART0Println("DCC");
	_delay_ms(del);
	disableWheelDCC();
	USART0Println("STOP");
	_delay_ms(del);
//*/

	/*USART0Println("F");
	startForward();
	_delay_ms(del);
	USART0Println("STOP");
	stopForward();
	_delay_ms(del);

	USART0Println("R");
	startRight();
	_delay_ms(del);
	USART0Println("STOP");
	stopRight();
	_delay_ms(del);

	USART0Println("L");
	startLeft();
	_delay_ms(del);
	USART0Println("STOP");
	stopLeft();
	_delay_ms(del);

	USART0Println("B");
	startBackward();
	_delay_ms(del);
	USART0Println("STOP");
	stopBackward();
	_delay_ms(del);//*/
	
	/*USART0Println("FR");
	startFR();
	_delay_ms(del);
	USART0Println("STOP");
	stopFR();
	_delay_ms(del);
	
	USART0Println("FL");
	startFL();
	_delay_ms(del);
	USART0Println("STOP");
	stopFL();
	_delay_ms(del);
	
	USART0Println("BR");
	startBR();
	_delay_ms(del);
	USART0Println("STOP");
	stopBR();
	_delay_ms(del);
	
	USART0Println("BL");
	startBL();
	_delay_ms(del);
	USART0Println("STOP");
	stopBL();
	_delay_ms(del);//*/
	
	
	/*startTurnC();
	USART0Println("C");
	_delay_ms(del);
	stopTurnC();
	USART0Println("STOP");
	_delay_ms(del);
	
	startTurnCC();
	USART0Println("CC");
	_delay_ms(del);
	stopTurnCC();
	USART0Println("STOP");
	_delay_ms(del);//*/
	
	_delay_ms(1);
	
	goto loop;//endless loop
	
	return 0;
}

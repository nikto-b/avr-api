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


uint8_t fuck = 0;




ISR(TWI_vect)
{
	//USART0Print("C");
	//USART0Println((int)TWSR);
	switch(TWSR)
	{
		case 0x00:
		{
			USART0Println("BUS FAIL");
			break;
		}
		case 0x08:
		{
			TWDR = (0x29 << 1) | 1;
			TWCR = (1 << TWIE) | (1 << TWEN) | (1 << TWINT);
			//USART0Println("0x08");
			break;
		}
		case 0x10:
		{
			USART0Println("0x10");
			break;
		}
		case 0x18:
		{
			TWDR = 1;
			USART0Println("0x18");
			TWCR = (1 << TWIE) | (1 << TWEN) | (1 << TWINT);
			break;
		}
		case 0x20:
		{
			USART0Println("0x20");
			break;
		}
		case 0x28:
		{
			break;
		}
		case 0x30:
		{
			
			break;
		}
		case 0x38:
		{
			
			break;
		}
		case 0x40:
		{
			if(fuck == 1)
			{
				//TWDR = 0xC0;
				fuck = 2;
				//TWCR = (1 << TWIE) | (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
				//USART0Println("0x40 STOP");
			}
			else if(fuck == 0)
			{
				fuck = 1;
				TWDR = 0xC1;
				TWCR = (1 << TWIE) | (1 << TWEN) | (1 << TWINT);	
				//USART0Println("0x40");			
			}
			break;
		}
		case 0x48:
		{
			TWCR = (1 << TWIE) | (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
			USART0Println("GO NACK!");
			break;
		}
		case 0x50:
		{
			break;
		}
		case 0x58:
		{
				fuck = 2;
				TWCR = (1 << TWIE) | (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
				fuck = 2;
				//USART0Println("0x58 STOP");
			
			
			break;
		}
		
	}
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
	//ADCInit();
	sei();
	int del = 20;
	int R, G, B;
	loop:
	//USART0Println("started");
	//TWSR = 3;
	fuck = 0;
	TWAR = 0x29;
	TWBR = 72;
	TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
	while(fuck != 2)
	{
		asm("nop");
	//USART0Println("FUCK");
	}

	USART0Println((int)TWDR);
	fuck = 0;
	goto loop;
	PORTB = 1 << PB5;//11
	_delay_ms(del);
	//USART0Print("G ");
	//USART0Println(analogRead(0));
	//_delay_ms(50);
	while(!ADCGetAnalogChanged(0)){asm("nop");}
	R = analogRead(0);
	/*PORTB = 1 << PB6;//12
	_delay_ms(del);
	//USART0Print("B ");
	//USART0Println(analogRead(0));
	//_delay_ms(50);
	while(!ADCGetAnalogChanged(0)){asm("nop");}
	B = analogRead(0);*/
	PORTB = 1 << PB7;//13
	_delay_ms(del);
	
	while(!ADCGetAnalogChanged(0)){asm("nop");}
	G = analogRead(0);//*/
	//_delay_ms(del);
	uint8_t __mess = 0;
	//R = 1023;
	/*__mess = 0;
	__mess <<= 5;
	__mess |= ((1 << 5) - 1) & R;
	USART0Send(__mess);
	
	_delay_ms(1);
	
	__mess = 1;
	__mess <<= 5;
	__mess |= (R >> 5) & ((1 << 5) - 1);
	USART0Send(__mess);
	
	
	//G = 1023;
	__mess = 2;
	__mess <<= 5;
	__mess |= ((1 << 5) - 1) & G;
	USART0Send(__mess);
	
	_delay_ms(1);
	
	__mess = 3;
	__mess <<= 5;
	__mess |= (G >> 5) & ((1 << 5) - 1);
	USART0Send(__mess);
	
	
	//B = 1023;
	__mess = 4;
	__mess <<= 5;
	__mess |= ((1 << 5) - 1) & B;
	USART0Send(__mess);
	
	_delay_ms(1);
	
	__mess = 5;
	__mess <<= 5;
	__mess |= (B >> 5) & ((1 << 5) - 1);
	USART0Send(__mess);
	
	
	
	
	
	
	*/
	USART0Print("R:");
	USART0Print(R);
	USART0Print(" G:");
	USART0Println(G);
	/*USART0Print(" B:");
	USART0Println(B);/*
	USART0Print(" A:");
	USART0Print(A);
	USART0Print(" W:");
	USART0Println(W);//*/
	//while(!ADCGetAnalogChanged(0)){asm("nop");}
	PORTB = 0;
	
	
	if(R >= 155 && R <= 160 && G >= 213 && G <= 215)
	{
		//USART0Send(1);
		USART0Println("GREEN");
	}
	else if(R >= 154 && R <= 156 && G >= 225 && G <= 228)
	{
		//USART0Send(2);
		USART0Println("RED");
	}
	else if(R >= 181 && R <= 182 && G >= 227 && G <= 229)
	{
		//USART0Send(3);
		USART0Println("YELLOW");
	}
	else if(R >= 135 && R <= 165 && G >= 205 && G <= 210)
	{
		//USART0Send(4);
		USART0Println("BLACK");
	}
	else if(R >= 180 && R <= 194 && G >= 220 && G <= 230)
	{
		//USART0Send(5);
		USART0Println("WHITE");
	}
	else if(R >= 135 && R <= 150 && G >= 215 && G <= 220)
	{
		//USART0Send(6);
		USART0Println("VIOLLETT");
	}
	_delay_ms(del);
	
	/*USART0Print("A: ");
	USART0Print(A);
	USART0Print(" W: ");
	USART0Println(W);*/
	
	//USART0Println("");
	
	/*if(R > 0 && R < 70)
		USART0Println("YELLOW\n");
	else if(R > 70 && R < 250)
		USART0Println("RED\n");
	else if(R > 300 && R < 800)
		USART0Println("GREEN\n");
	else if(R > 850 && R < 950)
		USART0Println("BLACK\n");*/
		
	//USART0Println();
	
	//_delay_ms(100);
	
	
	
	
	_delay_ms(1);
	
	goto loop;//endless loop
	
	return 0;
}

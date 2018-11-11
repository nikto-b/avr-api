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

/*
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
*/
void wdt_handler(void)
{
	USART0Println("WDT!");
	WDStop();
	//WDTStart(WD_TIME_4s);
}

int main()
{
	DDRB = ((1 << PB0) | (1 << PB1) | (1 << PB7) | (1 << PB1));								//8, 9, 13 output
	DDRC = ((1 << PC5) | (1 << PC4) | (1 << PC3));											//A0,1,2 output
	DDRB |= ((1 << PB4) | (1 << PB5) | (1 << PB6));
	USART0Begin(115200);
	funcs[WD_TIMEOUT_CUSTOMFUNC_ADDR] = wdt_handler;

	asm("wdr");
	WDTCSR |= (1 << WDCE) | (1 << WDE);
	WDTCSR = (1 << WDE) | ((1 << WDP3) | (1 << WDP0));
	//WDTStart(WD_TIME_4s);
	sei();
	USART0Print("s");
	
	loop:
	asm("nop");
	goto loop;
	
	return 0;
}

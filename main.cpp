#include "base.h"
#include "api.h"

int main()
{
	DDRE = 255;
	DDRG = 255;
	DDRH = 255;
	DDRF = 255;
	DDRK = 255;
	DDRB = 0xFF;
	uint8_t i = 0;
	const uint8_t del = 2;
	const uint8_t ppin = 5;
	const uint8_t max = 255;
	const uint8_t min = 0;
	USART0Begin(115200);
	sei();
	while(1)
	{
		for(i = min; i < max; i++)
		{
			analogWrite(ppin, i);
			USART0Println("A");
			delay(del);
		}
		for(i = max; i > min; i--)
		{
			analogWrite(ppin, i);
			USART0Println("B");
			delay(del);
		}		
	}
	loop:
	asm("NOP");
	goto loop;
	return 0;
}
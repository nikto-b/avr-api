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
	const uint8_t del = 1;
	const uint8_t ppin = 5;
	const uint8_t max = 255;
	const uint8_t min = 0;
	while(1)
	{
		for(i = min; i < max; i++)
		{
			analogWrite(ppin, i);
			delay(del);
		}
		for(i = max; i > min; i--)
		{
			analogWrite(ppin, i);
			delay(del);
		}		
	}
	loop:
	asm("NOP");
	goto loop;
	return 0;
}
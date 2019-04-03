#include "base.h"
#include "api.h"


#define COMPASS_CONFA		00
#define COMPASS_CONFB		01
#define COMPASS_MODE		02
#define COMPASS_DO_MSB_X	03
#define COMPASS_DO_LSB_X	04
#define COMPASS_DO_MSB_Z	05
#define COMPASS_DO_LSB_Z	06
#define COMPASS_DO_MSB_Y	07
#define COMPASS_DO_LSB_Y	08
#define COMPASS_STATUS		09
#define COMPASS_ID_A		10
#define COMPASS_ID_B		11
#define COMPASS_ID_C		12

int main()
{
	// DDRE = 255;
	// DDRG = 255;
	// DDRH = 255;
	// DDRF = 255;
	// DDRK = 255;
	// DDRB = 0xFF;
	// uint8_t i = 0;
	// const uint8_t del = 10;
	// const uint8_t ppin = 5;
	// const uint8_t max = 255;
	// const uint8_t min = 0;
	// USART0Begin(115200);
	// I2C_SetFreq(0x40);
	// uint8_t* p = (uint8_t*)malloc(2 * sizeof(uint8_t));
	// p[0] = 9;
	// p[1] = 1;
	// twiAddPack(0x0D, p, 2, I2C_WRITE);
	// twiStart();
	// uint64_t w = constrain(100, 10, 50);
	// p[0] = 0;
	// twiAddPack(0x0D, p, 1, I2C_WRITE);
	// p[0] = 6;
	// twiAddPack(0x0D, p, 1, I2C_READ);
	//p[0] = COMPASS_MODE;
	//p[1] = 1;
	//twiAddPack(0x0D, p, 2, I2C_WRITE);
	//twiStart();
	//sei();
	//delay(200);
	//p[0] = COMPASS_MODE;
	//twiAddPack(0x0D, p, 1, I2C_WRITE);
	//p[0] = 1;
	//twiAddPack(0x0D, p, 1, I2C_READ);
	// twiStart();
	// while(!twiHadRead()){asm("NOP");}
	// delay(50);
	// //USART0Println(twiGetByte());
	// while(twiHadRead())
	// {
	// 	USART0Println((int)twiGetByte());
	// }


	// while(1)
	// {
	// 	for(i = min; i < max; i++)
	// 	{
	// 		ATOMIC_SMART
	// 		(
	// 			analogWrite(ppin, i);
	// 		)
	// 		//analogWrite(11, i);
	// 		USART0Println("A");
	// 		delay(del);
	// 	}
	// 	for(i = max; i > min; i--)
	// 	{
	// 		analogWrite(ppin, i);
	// 		USART0Println("B");
	// 		delay(del);
	// 	}
	// }
	loop:
	asm("NOP");
	goto loop;
	return 0;
}

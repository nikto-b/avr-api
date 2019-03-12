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
	TIMER1Init(TIMER1_COMC_CM_ST | TIMER1_COMB_CM_ST | TIMER1_COMA_CM_ST, TIMER1_WF_FPWM_10B, TIMER1_CLK_SRC_1024);
	TIMER1SetC(511);
	//TIMER3Init(TIMER3_COMC_FPWM_CM_ST, TIMER3_WF_FPWM_10B, TIMER3_CLK_SRC_1024);
	//TIMER3SetC(1023);
	//TCCR3A=(1<<COM3C1)|(1<<WGM30);
	//TCCR3B=(1<<CS30);	
	//OCR3C = 255;
	//pinMode(15, OUTPUT);
	//TIMER1Init(TIMER1_COMC_FPWM_WGM_SET, TIMER1_WF_FPWM_8B, TIMER1_CLK_SRC_1024);
	//TIMER1SetC(100);
	loop:
	//analogWrite(1, 100);
		
	//for(int i = 0; i < 255; i++)
	//{
	asm("NOP");
		delay(1);
	//}
	goto loop;
	return 0;
}
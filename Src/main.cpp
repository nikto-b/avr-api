#include "base.h"
#include "api.h"

#define SCH_MAX_LEN			2047


void (*scheduleQueue[SCH_MAX_LEN])();

volatile uint16_t scheduleCounter = 0;
volatile uint16_t scheduleQueueLen = 0;



/*
 *	Function:	scheduleGetFuncIndex
 *	Desc:		Get index of function in sch queue
 *	Input:		void* func: ptr to func
 *	Output:		index of func
 */
uint16_t scheduleGetFuncIndex(void(*func))
{
	for(uint16_t i = 0; i < scheduleQueueLen; i++)
	{
		if(scheduleQueue[i] == func)
		{
			return i;
		}
	}
	return 0x00;
}


/*
 *	Function:	scheduleAddFunc
 *	Desc:		Add func to repeat by schedule (adding instead of idle)
 *	Input:		void* func: ptr to func
 *	Output:		index of added func
 */
void scheduleAddFunc(void(* func)())
{
	for(uint16_t i = 0; i < scheduleQueueLen; i++)
	{
		if(scheduleQueue[i] == 0)
		{
			ATOMIC_FORCED
			(
				scheduleQueue[i] = func;
				// return i;
			)
			return;
		}
	}
	// ATOMIC_FORCED
	// (
		USART0Println("ADD");
		scheduleQueue[scheduleQueueLen++] = func;
		// return scheduleQueueLen - 1;
	// )
}


/*
 *	Function:	scheduleAddFunc
 *	Desc:		Add func to repeat by schedule (adding instead of idle)
 *	Input:		void* func: ptr to func
 *				uint8_t del: min index of added task
 *	Output:		index of added func
 */
void scheduleAddFunc(void(* func)(), uint16_t del)
{
	for(uint16_t i = del; i < scheduleQueueLen; i++)
	{
		if(scheduleQueue[i] == 0)
		{
			ATOMIC_FORCED
			(
				scheduleQueue[i] = func;
				// return i;
			)
			return;
		}
	}
	ATOMIC_FORCED
	(
		while(scheduleQueueLen < del)
		{
			scheduleQueueLen++;
		}
		scheduleQueue[scheduleQueueLen++] = func;
		// return scheduleQueueLen - 1;
	)
}


/*
 *	Function:	scheduleAddFunc
 *	Desc:		Add func to repeat by schedule (adding instead of idle)
 *	Input:		void* func: ptr to func
 *				uint8_t stfunc: index of func from starting counting del
 *				uint8_t del: min index of added task
 *	Output:		index of added func
 */
void scheduleAddFunc(void(* func)(), uint16_t stfunc, uint16_t del)
{
	del += stfunc;
	 scheduleAddFunc(func, del);
}


/*
 *	Function:	scheduleAddFunc
 *	Desc:		Add func to repeat by schedule (adding instead of idle)
 *	Input:		void* func: ptr to func
 *				void* stfunc: func from starting counting del
 *				uint8_t del: min index of added task
 *	Output:		index of added func
 */
void scheduleAddFunc(void(* func)(), void(* stfunc)(), uint16_t del)
{
	del = scheduleGetFuncIndex(stfunc);
	 scheduleAddFunc(func, del);
}


/*
 *	Function:	scheduleRemoveFunc
 *	Desc:		Remove func fom schedule task queue
 *	Input:		uint8_t func: index of ptr to func
 *	Output:		none
 */
void scheduleRemoveFunc(uint16_t func)
{
	ATOMIC_FORCED
	(
		scheduleQueue[func] = 0;
	)
}

/*
 *	Function:	scheduleRemoveFunc
 *	Desc:		Remove func fom schedule task queue
 *	Input:		void* func: ptr to func
 *	Output:		none
 */
void scheduleRemoveFunc(void(* func)())
{
	ATOMIC_SMART
	(
		for(uint8_t i = 0; i < scheduleQueueLen; i++)
		{
			if(scheduleQueue[i] == func)
			{
				scheduleRemoveFunc(i);
				//break;
			}
		}
	)
}


char usartInBuf[512];
volatile uint16_t usartInBufCounter = 0;


// void parseInputCmds(void)
// {
// 	if (contains(usartInBuf, usartInBufCounter, '(') && contains(usartInBuf, usartInBufCounter, ')'))
// 	{
// 		char* _arr = strSplit(usartInBuf, usartInBufCounter + 1, '(', ')');
// 		usartInBufCounter = 0;
// 		//sei();
//
// 		if(_arr != 0)
// 		{
// 			USART0Println(_arr);
// 			// runControlCmd(_arr);
// 			free(_arr);
// 		}
// 	}
// 	else if (contains(usartInBuf, usartInBufCounter, '{'))
// 	{
// 		//setVar(_arr);
// 	}
// 	else if (contains(usartInBuf, usartInBufCounter, '['))
// 	{
// 		//setArr(_arr);
// 	}
// }


/*
 *	Function:	schedule
 *	Desc:		If have new bytes to read return 1(t), else 0(f)
 *	Input:		none
 *	Output:		none
 */
void schedule(void)
{
	// sei();
	PORTB |= 1 << 5;//enable in-fg
	// if(scheduleQueue[scheduleCounter] != 0)
	// {
		// USART0Println((long)scheduleQueue[scheduleCounter]);
		// USART0Println((long)&scheduleQueue[scheduleCounter]);
		// scheduleQueue[scheduleCounter]();
	// }
	scheduleCounter++;

	if(scheduleCounter >= scheduleQueueLen)
		scheduleCounter = 0;
	PORTB &= ~(1 << 5);//disable in-fg
}

void recvUsart()
{
	//digitalWrite(15, 0);
	//char c = USART0Read();
	usartInBuf[usartInBufCounter++] = USART0Read();
	//usartInBuf[usartInBufCounter++] = c;
	//USART0Println("A");
}


int main()
{
	DDRB = 255;
	USART0Begin(115200);
	for(uint16_t i = 0; i < SCH_MAX_LEN; i++)
	{
		scheduleQueue[i] = 0;
	}
	// sei();
	USART0Println("FUCK");
	setCustomFunc(INTERRUPT_CUSTOMFUNC_USART0_RX, recvUsart);

	// scheduleAddFunc(parseInputCmds);
	cli();
	setCustomFunc(INTERRUPT_CUSTOMFUNC_TC0_COMPA, schedule);
	TIMER0Init(TIMER0_COMA_NPWM_NORMAL, TIMER0_WF_CTC, TIMER0_CLK_SRC_1024);

	TIMER0EnableCOMPAInterrupt();
	TIMER0SetA(255);
	sei();
	USART0Println((long)scheduleQueue[0]);


	loop:
	asm("NOP");
	goto loop;
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
	return 0;
}

#pragma once

#include "customFuncAddr.h"
#include "USART.h"

void (*customFuncs[INTERRUPT_CUSTOMFUNC_NUM_OF_UNITS])();

/*
 * Function callCustomFunc
 * Desc     Call user's func by addr
 * Input    __addr: addr for calling func
 * Output   none
*/
void callCustomFunc(unsigned char __addr)
{
	if(customFuncs[__addr] != NULL)
	{
		//USART0Println("CALL");
		customFuncs[__addr]();
	}
}

/*
 * Function setCustomFunc
 * Desc     set user's func for calling by system
 * Input    __addr: addr to set
 * 			__func: ptr to user's func for setting
 * Output   none
*/
void setCustomFunc(uint8_t __addr, void(* __func)())
{
	if(__addr < INTERRUPT_CUSTOMFUNC_NUM_OF_UNITS)
	{
		//USART0Print("ADD");
		//USART0Println(__addr);
		customFuncs[__addr] = __func;
	}
}
#include "customFuncAddr.hpp"

namespace interrupt
{
	void (*customFuncs[NUM_OF_UNITS])();

	/*
	* Function call
	* Desc     Call user's func by addr
	* Input    addr: addr for calling func
	* Output   none
	*/
	void call(const Addr addr)
	{
		if(customFuncs[addr] != NULL)
		{
			customFuncs[addr]();
		}
	}

	/*
	* Function 	set
	* Desc     	set user's func for calling by system
	* Input    	addr: addr to set
	* 			func: ptr to user's func for setting
	* Output   	none
	*/
	void set(const Addr addr, void(* __func)())
	{
		customFuncs[addr] = __func;
	}
	
} // namespace interrupt
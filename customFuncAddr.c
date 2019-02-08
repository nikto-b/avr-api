/*
 * Function callCustomFunc
 * Desc     Call user's func by addr
 * Input    __addr: addr for calling func
 * Output   none
*/
inline void callCustomFunc(uint8_t __addr)
{
	if(customFuncs[__addr] != NULL)
		customFuncs[__addr]();
}

/*
 * Function setCustomFunc
 * Desc     set user's func for calling by system
 * Input    __addr: addr to set
 * 			__func: ptr to user's func for setting
 * Output   none
*/
inline void setCustomFunc(uint8_t __addr, void(* __func)())
{
	if(__addr < INTERRUPT_CUSTOMFUNC_NUM_OF_UNITS)
		customFuncs[__addr] = __func;
}

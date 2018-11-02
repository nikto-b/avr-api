inline void callCustomFunc(uint8_t _addr)
{
	if(customFuncs[_addr] != NULL)
		customFuncs[_addr]();
}

inline void setCustomFunc(uint8_t _addr, void* _func)
{
	if(_addr < INTERRUPT_CUSTOMFUNC_NUM_OF_UNITS)
		customFuncs[_addr] = _func;
}


void WDSetMode(uint8_t _mode)
{
	WDTCSR &= ~WD_MODE_MASK;
	#if USE_FUNC_INPUT_PROTECTOR == 0
		WDTCSR |= _mode;
	#else
		WDTCSR |= (_mode & WD_MODE_MASK);
	#endif
}

void WDSetCycles(uint8_t _cycles)
{
	WDTCSR &= ~WD_CYCLES_MASK;
	#if USE_FUNC_INPUT_PROTECTOR == 0
		WDTCSR |= _cycles;
	#else
		WDTCSR |= (_cycles & WD_CYCLES_MASK);
	#endif
}

void WDFlush(void)
{
	asm("WDR");
}

ISR(WDT_vect)
{
	if(funcs[WD_TIMEOUT_CUSTOMFUNC_ADDR] != NULL)
		funcs[WD_TIMEOUT_CUSTOMFUNC_ADDR]();
}

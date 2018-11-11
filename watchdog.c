#define WDSetTime(x) WDSetCycles(x)

/*
 * Function WDSetMode
 * Desc     Set mode of Watchdog timer
 * Input    __mode: what mode set to
 * Output   none
*/
void WDSetMode(uint8_t __mode)
{
	//WDTCSR &= ~WD_MODE_MASK;
	#if USE_FUNC_INPUT_PROTECTOR == 0
		WDTCSR = (1 << WDCE) | __mode;
	#else
		WDTCSR = (1 << WDCE) | (__mode & WD_MODE_MASK);
	#endif
}

/*
 * Function WDSetCycles
 * Desc     Set num of cycles watchdog go to
 * Input    __cycles: num of cycles, defined
 * Output   none
*/
void WDSetCycles(uint8_t __cycles)
{
	WDTCSR &= ~WD_CYCLES_MASK;
	#if USE_FUNC_INPUT_PROTECTOR == 0
		WDTCSR = (1 << WDIE) | __cycles;
	#else //if USE_FUNC_INPUT_PROTECTOR == 0
		WDTCSR = (1 << WDIE) | (__cycles & WD_CYCLES_MASK);
	#endif //if USE_FUNC_INPUT_PROTECTOR != 0
}

/*
 * Function WDStop
 * Desc     Say watchdog to stop counting, asm macros
 * Input    none
 * Output   none
*/
void WDStop(void)
{
	asm volatile ("wdr"); //clear watchdog timer
	MCUSR &= ~(1 << WDRF);
	WDTCSR = 0x00;
}

/*
 * Function WDTStart
 * Desc     Start watchdog timer
 * Input    __time: what time watchdog will be counting to
 * Output   none
*/
void WDTStart(uint8_t __time)
{
	WDStop();
	WDSetMode(WD_MODE_INT);
	WDSetTime(__time);
}

/*
 * Function ISR(WDT_vect)
 * Desc     Interrupt handler for vector WDT
 * Input    Interrupt vector
 * Output   none
*/
ISR(WDT_vect)
{
	callCustomFunc(INTERRUPT_CUSTOMFUNC_WDT);
}


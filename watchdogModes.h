#define _WD_MODES

//-----------------MODES-----------------
#define WD_MODE_STOP			0											//none
#define WD_MODE_INT				(1 << WDIE)									//interrupt
#define WD_MODE_SYSRESET		(1 << WDE)									//system reset
#define WD_MODE_INT_SYSRESET	((1 << WDIE) | (1 << WDE))					//interrupt and system reset
//#define WD_MODE_SYSRESET2		(1 << WDTON)								//????????		((1 << WDTON) | (X << WDE) | (X << WDIE))
#define WD_MODE_MASK			((1 << WDIE) | (1 << WDE))

/*
 * 
 * Bit 4 - WDCE: Watchdog Change Enable
 * This bit is used in timed sequences for changing WDE and prescaler bits. To clear the
 * WDE bit, and/or change the prescaler bits, WDCE must be set.
 * Once written to one, ha
 * rdware will clear WDCE after four clock cycles.
 * 
 */

#define WD_ENABLE				((1 << WDCE) | (1 << WDE))					//not treally shure it works like that


//-----------------PRESCALLERS-----------------								//typical time-out at VCC=5.0V
#define WD_CYCLES_2K			0											//16ms
#define WD_CYCLES_4K			(1 << WDP0)									//32ms
#define WD_CYCLES_8K			(1 << WDP1)									//64ms
#define WD_CYCLES_16K			((1 << WDP0) | (1 << WDP1))					//0.125s
#define WD_CYCLES_32K			(1 << WDP2)									//0.25s
#define WD_CYCLES_64K			((1 << WDP2) | (1 << WDP0))					//0.5s
#define WD_CYCLES_128K			((1 << WDP2) | (1 << WDP1))					//1.0s
#define WD_CYCLES_256K			((1 << WDP2) | (1 << WDP1) | (1 << WDP0))	//2.0s
#define WD_CYCLES_512K			(1 << WDP3)									//4.0s
#define WD_CYCLES_1024K			((1 << WDP3) | (1 << WDP0))					//8.0s
#define WD_CYCLES_MASK			((1 << WDP3) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0))


#define WD_TIMEOUT_CUSTOMFUNC_ADDR 12										//addr of useer function called by interrupt

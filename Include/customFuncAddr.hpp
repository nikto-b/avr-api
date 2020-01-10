#pragma once
#include "base.hpp"


namespace interrupt
{

    #undef PC0
    #undef PC1
    #undef PC2
    #undef ADC
    enum Addr 
    {
        RESET       = 0,		//reset from ext pin, Power-On-Reset, Brown-out Reset, Watchdog reset, JTAG AVR Reset
        EXT0        = 1,		//ext interrupt req 0
        EXT1        = 2,		//ext interrupt req 1
        EXT2        = 3,		//ext interrupt req 2
        EXT3        = 4,		//ext interrupt req 3
        EXT4	    = 5,		//ext interrupt req 4
        EXT5	    = 6,		//ext interrupt req 5
        EXT6	    = 7,		//ext interrupt req 6
        EXT7	    = 8,		//ext interrupt req 7
        PC0	        = 9,		//pin change interrupt request 0
        PC1	        = 10,		//pin change interrupt request 1
        PC2 	    = 11,		//pin change interrupt request 2
        WDT		    = 12,		//watchdog time-out interrupt
        TC2_COMPA	= 13,		//Timer/Counter2 Compare Match A
        TC2_COMPB	= 14,		//Timer/Counter2 Compare Match B
        TC2_OVF		= 15,		//Timer/Counter2 Overflow
        TC1_CAPT	= 16,		//Timer/Counter1 Capture Event
        TC1_COMPA	= 17,		//Timer/Counter1 Compare Match A
        TC1_COMPB	= 18,		//Timer/Counter1 Compare Match B
        TC1_COMPC	= 19,		//Timer/Counter1 Compare Match C
        TC1_OVF		= 20,		//Timer/Counter1 Overflow
        TC0_COMPA	= 21,		//Timer/Counter0 Compare Match A
        TC0_COMPB	= 22,		//Timer/Counter0 Compare Match B
        TC0_OVF		= 23,		//Timer/Counter0 Overflow
        SPI_STC		= 24,		//SPI Serial Transfer Complete
        USART0_RX	= 25,		//USART0 RX Complete
        USART0_UDRE	= 26,		//USART0 Data Register Empty
        USART0_TX	= 27,		//USART0 TX Complete
        ANALOG_COMP	= 28,		//Analog Comparator
        ADC			= 29,		//ADC Conversion Complete
        EE_READY	= 30,		//EEPROM Ready
        TC3_CAPT	= 31,		//Timer/Counter3 Capture Event
        TC3_COMPA	= 32,		//Timer/Counter3 Cpmpare Match A
        TC3_COMPB	= 33,		//Timer/Counter3 Compare Match B
        TC3_COMPC	= 34,		//Timer/Counter3 Compare Match C
        TC3_OVF		= 35,		//Timer/Counter3 Overflow
        USART1_RX	= 36,		//USART1 RX Complete
        USART1_UDRE	= 37,		//USART1 Data Register Empty
        USART1_TX	= 38,		//USART1 TX Complete
        TWI			= 39,		//2-wire Serial Interface
        SPM_READY	= 40,		//Store Program Memory Ready
        TC4_CAPT	= 41,		//Timer/Counter4 Capture Event
        TC4_COMPA	= 42,		//Timer/Counter4 Compare Match A
        TC4_COMPB	= 43,		//Timer/Counter4 Compare Match B
        TC4_COMPC	= 44,		//Timer/Counter4 Compare Match C
        TC4_OVF		= 45,		//Timer/Counter4 Overflow
        TC5_CAPT	= 46,		//Timer/Counter4 Capture Event
        TC5_COMPA	= 47,		//Timer/Counter4 Compare Match A
        TC5_COMPB	= 48,		//Timer/Counter4 Compare Match B
        TC5_COMPC	= 49,		//Timer/Counter4 Compare Match C
        TC5_OVF		= 50,		//Timer/Counter4 Overflow
        USART2_RX	= 51,		//USART2 RX Complete
        USART2_UDRE	= 52,		//USART2 Data Register Empty
        USART2_TX	= 53,		//USART2 TX Complete
        USART3_RX	= 54,		//USART3 RX Complete
        USART3_UDRE	= 55,		//USART3 Data Register Empty
        USART3_TX	= 56		//USART3 TX Complete
    };

    const uint8_t NUM_OF_UNITS = 57;		//num of origin custom functions

    void call(const Addr addr);
    void set(const Addr addr, void(* __func)());

}
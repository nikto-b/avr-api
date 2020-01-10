#pragma once
#ifndef _USART_MODES
	#define _USART_MODES

	#if USE_USART0 == 1
		#define USART0_CHAR_5B 0
		#define USART0_CHAR_6B (1 << UCSZ00)
		#define USART0_CHAR_7B (1 << UCSZ01)
		#define USART0_CHAR_8B ((1 << UCSZ00) | (1 << UCSZ01))
		#define USART0_CHAR_9B ((1 << UCSZ00) | (1 << UCSZ01) | (1 << UCSZ02))
	#endif //if USE_USART0 == 1
	
#endif //ifndef _USART_MODES

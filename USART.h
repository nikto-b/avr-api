#if USE_USART0 == 1

	#include "USART.cpp"
	
	void USARTBegin(uint64_t _baud);
	
	#if USE_USART0_OUTPUT == 1
		#pragma message "using USART output"
		
		void USARTSend(unsigned char);
		
		void USARTPrint(char*);
	#endif
	
	#if USE_USART0_INPUT == 1
		#pragma message "using USART input"
		
		char USARTRead(void);
	#endif

	
#endif //if USE_USART0 == 1



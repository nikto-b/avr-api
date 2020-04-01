#include "USART.hpp"



namespace usart
{
	struct buffers buffers0;

	#ifdef USART1_RX_vect
	struct buffers buffers1;
	#endif //ifdef USART1_RX_vect

	#ifdef USART2_RX_vect
	struct buffers buffers2;
	#endif //ifdef USART2_RX_vect

	#ifdef USART3_RX_vect
	struct buffers buffers3;
	#endif //ifdef USART3_RX_vect
	

	#ifdef NO_USART_RXBUF
		volatile char input0Value;
		#ifdef UCSR1A
			volatile char input1Value;
		#endif
		#ifdef UCSR2A
			volatile char input2Value;
		#endif
		#ifdef UCSR3A
			volatile char input3Value;
		#endif
	#endif

	/*
	* Function ISR(USART0_TX_vect)
	* Desc     Interrupt handler for vector USART0_TX
	* Input    interrupt vector
	* Output   none
	*/
	inline void _ISR_TX0()
	{
		interrupt::call(interrupt::USART0_TX);
	}

	
	/*
	* Function ISR(USART1_TX_vect)
	* Desc     Interrupt handler for vector USART1_TX
	* Input    interrupt vector
	* Output   none
	*/
	inline void _ISR_TX1()
	{
		interrupt::call(interrupt::USART1_TX);
	}
	/*
	* Function ISR(USART2_TX_vect)
	* Desc     Interrupt handler for vector USART2_TX
	* Input    interrupt vector
	* Output   none
	*/
	inline void _ISR_TX2()
	{
		interrupt::call(interrupt::USART2_TX);
	}
	/*
	* Function ISR(USART3_TX_vect)
	* Desc     Interrupt handler for vector USART3_TX
	* Input    interrupt vector
	* Output   none
	*/
	inline void _ISR_TX3()
	{
		interrupt::call(interrupt::USART3_TX);
	}

	template<const size_t n>
	constexpr interrupt::Addr _getUSARTn_RXInterrupt()
	{
		static_assert(isUsartNumberValid<n>(), "Bad USART num");

		interrupt::Addr ret = interrupt::USART0_RX;
		switch (n)
		{
		case 0:
			ret = interrupt::USART0_RX;
			break;
		case 1:
			ret = interrupt::USART1_RX;
			break;
		case 2:
			ret = interrupt::USART2_RX;
			break;
		case 3:
			ret = interrupt::USART3_RX;
			break;
		default:
			break;
		}
		return ret;
	}

	/*
	* Function ISR(USARTN_RX_vect)
	* Desc     Interrupt handler for vector USARTN_RX
	* Input    interrupt vector
	* Output   none
	*/
	template <const size_t N>
	inline void _ISR_RX()
	{
		#ifndef NO_USART_RXBUF
		if(_getBuffers<N>()->inputBufCounterInput >= MAX_BUF_SIZE	//check that counters are in borders of buf size
				|| _getBuffers<N>()->inputBufEmpty)					//or buf empty
		{
			_getBuffers<N>()->inputBufCounterInput = 0;				//start writing from zero
		}

		_getBuffers<N>()->inputBuf[_getBuffers<N>()->inputBufCounterInput] = static_cast<char>(*_getUDRn<N>());	//save data

		if(_getBuffers<N>()->inputBuf[_getBuffers<N>()->inputBufCounterInput] != '\0')//check for garbage
		{
			_getBuffers<N>()->inputBufEmpty = false;				//set empty flag down
			_getBuffers<N>()->inputBufCounterInput++;				//go next index for writing
		}
		#else //ifndef NO_USART_RXBUF
			*_getInputValue<N>() = static_cast<char>(*_getUDRn<N>());
			// input0Value = static_cast<char>(*_getUDRn<N>());
		#endif


		interrupt::call(_getUSARTn_RXInterrupt<N>());
	}


}

#ifdef USART0_TX_vect
ISR(USART0_TX_vect)//interrupt handler called aftar transmitting data
#else //ifdef USART0_TX_vect
ISR(USART_TX_vect)//interrupt handler called aftar transmitting data
#endif //ifndef USART0_TX_vect
{
	usart::_ISR_TX0();
}


#ifdef USART0_RX_vect
ISR(USART0_RX_vect)		   //interrupt handler called after recieving data
#else //ifdef USART0_RX_vect
ISR(USART_RX_vect)		   //interrupt handler called after recieving data
#endif //ifndef USART0_RX_vect
{
	usart::_ISR_RX<0>();
}

#ifdef USART1_RX_vect
ISR(USART1_RX_vect)
{
	usart::_ISR_RX<1>();
}
#endif //ifdef USART1_RX_vect

#ifdef USART1_TX_vect
ISR(USART1_TX_vect)
{
	usart::_ISR_TX1();
}
#endif //ifdef USART1_TX_vect

#ifdef USART2_RX_vect
ISR(USART2_RX_vect)
{
	usart::_ISR_RX<2>();
}
#endif //ifdef USART2_RX_vect

#ifdef USART2_TX_vect
ISR(USART2_TX_vect)
{
	usart::_ISR_TX2();
}
#endif //ifdef USART2_TX_vect

#ifdef USART3_RX_vect
ISR(USART3_RX_vect)
{
	usart::_ISR_RX<3>();
}
#endif //ifdef USART3_RX_vect

#ifdef USART3_TX_vect
ISR(USART3_TX_vect)
{
	usart::_ISR_TX3();
}
#endif //ifdef USART3_TX_vect
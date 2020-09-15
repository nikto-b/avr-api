#pragma once

#include "base.hpp"
#include "TimerModes.hpp"
#include "type_traits.hpp"

namespace timer
{
	enum Var {
		A, B, C
	};

	template <const int N>
	constexpr bool isTimerNumberValid()
	{
		#ifdef TCCR8A
			return N <= 8;
		#elif defined(TCCR7A)
			return N <= 7;
		#elif defined(TCCR6A)
			return N <= 6;
		#elif defined(TCCR5A)
			return N <= 5;
		#elif defined(TCCR4A)
			return N <= 4;
		#elif defined(TCCR3A)
			return N <= 3;
		#elif defined(TCCR2A)
			return N <= 2;
		#elif defined(TCCR1A)
			return N <= 1;
		#elif defined(TCCR0A)
			return N <= 0;
		#else
			return false;
		#endif
	}

	template <const int N>
	constexpr void assert_timer_number()
	{
		static_assert(isTimerNumberValid<N>(), "Invalid timer number");
	}

	template <const int N>
	constexpr volatile uint8_t* getTCCRA()
	{
		assert_timer_number<N>();
		volatile uint8_t* ret = NULL;
		switch (N)
		{
			#ifdef TCCR0A
			case 0:
				ret = &TCCR0A;
				break;
			#endif
			#ifdef TCCR1A
			case 1:
				ret =  &TCCR1A;
				break;
			#endif
			#ifdef TCCR2A
			case 2:
				ret =  &TCCR2A;
				break;
			#endif
			#ifdef TCCR3A
			case 3:
				ret =  &TCCR3A;
				break;
			#endif
			#ifdef TCCR4A
			case 4:
				ret =  &TCCR4A;
				break;
			#endif
			#ifdef TCCR5A
			case 5:
				ret =  &TCCR5A;
				break;
			#endif
			#ifdef TCCR6A
			case 6:
				ret =  &TCCR6A;
				break;
			#endif
			#ifdef TCCR7A
			case 7:
				ret =  &TCCR7A;
				break;
			#endif
			#ifdef TCCR8A
			case 8:
				ret =  &TCCR8A;
				break;
			#endif
		}
		return ret;
	}

	template <const int N>
	constexpr volatile uint8_t* getTCCRB()
	{
		assert_timer_number<N>();
		volatile uint8_t* ret = NULL;
		switch (N)
		{
			#ifdef TCCR0B
			case 0:
				ret = &TCCR0B;
				break;
			#endif
			#ifdef TCCR1B
			case 1:
				ret = &TCCR1B;
				break;
			#endif
			#ifdef TCCR2B
			case 2:
				ret = &TCCR2B;
				break;
			#endif
			#ifdef TCCR3B
			case 3:
				ret = &TCCR3B;
				break;
			#endif
			#ifdef TCCR4B
			case 4:
				ret = &TCCR4B;
				break;
			#endif
			#ifdef TCCR5B
			case 5:
				ret = &TCCR5B;
				break;
			#endif
			#ifdef TCCR6B
			case 6:
				ret = &TCCR6B;
				break;
			#endif
			#ifdef TCCR7B
			case 7:
				ret = &TCCR7B;
				break;
			#endif
			#ifdef TCCR8B
			case 8:
				ret = &TCCR8B;
				break;
			#endif
		}
		return ret;
	}

	template <const int N>
	constexpr volatile uint8_t* getOCRA8b()
	{
		assert_timer_number<N>();
		switch (N)
		{
			#if defined(OCR0A) && !defined(OCR0AL)
			case 0:
				return &OCR0A;
			#endif
			#if defined(OCR1A) && !defined(OCR1AL)
			case 1:
				return &OCR1A;
			#endif
			#if defined(OCR2A) && !defined(OCR2AL)
			case 2:
				return &OCR2A;
			#endif
			#if defined(OCR3A) && !defined(OCR3AL)
			case 3:
				return &OCR3A;
			#endif
			#if defined(OCR4A) && !defined(OCR4AL)
			case 4:
				return &OCR4A;
			#endif
			#if defined(OCR5A) && !defined(OCR5AL)
			case 5:
				return &OCR5A;
			#endif
			#if defined(OCR6A) && !defined(OCR6AL)
			case 6:
				return &OCR6A;
			#endif
			#if defined(OCR7A) && !defined(OCR7AL)
			case 7:
				return &OCR7A;
			#endif
			#if defined(OCR8A) && !defined(OCR8AL)
			case 8:
				return &OCR8A;
			#endif
			default:
				return NULL;
		}
	}

	template <const int N>
	constexpr volatile uint8_t* getOCRB8b()
	{
		assert_timer_number<N>();
		switch (N)
		{
			#if defined(OCR0B) && !defined(OCR0BL)
			case 0:
				return &OCR0B;
			#endif
			#if defined(OCR1B) && !defined(OCR1BL)
			case 1:
				return &OCR1B;
			#endif
			#if defined(OCR2B) && !defined(OCR2BL)
			case 2:
				return &OCR2B;
			#endif
			#if defined(OCR3B) && !defined(OCR3BL)
			case 3:
				return &OCR3B;
			#endif
			#if defined(OCR4B) && !defined(OCR4BL)
			case 4:
				return &OCR4B;
			#endif
			#if defined(OCR5B) && !defined(OCR5BL)
			case 5:
				return &OCR5B;
			#endif
			#if defined(OCR6B) && !defined(OCR6BL)
			case 6:
				return &OCR6B;
			#endif
			#if defined(OCR7B) && !defined(OCR7BL)
			case 7:
				return &OCR7B;
			#endif
			#if defined(OCR8B) && !defined(OCR8BL)
			case 8:
				return &OCR8B;
			#endif
			default:
				return NULL;
		}
	}

	template <const int N>
	constexpr volatile uint8_t* getOCRC8b()
	{
		assert_timer_number<N>();
		switch (N)
		{
			#if defined(OCR0C) && !defined(OCR0CL)
			case 0:
				return &OCR0C;
			#endif
			#if defined(OCR1C) && !defined(OCR1CL)
			case 1:
				return &OCR1C;
			#endif
			#if defined(OCR2C) && !defined(OCR2CL)
			case 2:
				return &OCR2C;
			#endif
			#if defined(OCR3C) && !defined(OCR3CL)
			case 3:
				return &OCR3C;
			#endif
			#if defined(OCR4C) && !defined(OCR4CL)
			case 4:
				return &OCR4C;
			#endif
			#if defined(OCR5C) && !defined(OCR5CL)
			case 5:
				return &OCR5C;
			#endif
			#if defined(OCR6C) && !defined(OCR6CL)
			case 6:
				return &OCR6C;
			#endif
			#if defined(OCR7C) && !defined(OCR7CL)
			case 7:
				return &OCR7C;
			#endif
			#if defined(OCR8C) && !defined(OCR8CL)
			case 8:
				return &OCR8C;
			#endif
			default:
				return NULL;
		}
	}

	template <const int N>
	constexpr volatile uint16_t* getOCRA16b()
	{
		assert_timer_number<N>();
		switch (N)
		{
			#if defined(OCR0A) && defined(OCR0AH)
			case 0:
				return &OCR0A;
			#endif
			#if defined(OCR1A) && defined(OCR1AH)
			case 1:
				return &OCR1A;
			#endif
			#if defined(OCR2A) && defined(OCR2AH)
			case 2:
				return &OCR2A;
			#endif
			#if defined(OCR3A) && defined(OCR3AH)
			case 3:
				return &OCR3A;
			#endif
			#if defined(OCR4A) && defined(OCR4AH)
			case 4:
				return &OCR4A;
			#endif
			#if defined(OCR5A) && defined(OCR5AH)
			case 5:
				return &OCR5A;
			#endif
			#if defined(OCR6A) && defined(OCR6AH)
			case 6:
				return &OCR6A;
			#endif
			#if defined(OCR7A) && defined(OCR7AH)
			case 7:
				return &OCR7A;
			#endif
			#if defined(OCR8A) && defined(OCR8AH)
			case 8:
				return &OCR8A;
			#endif
			default:
				return NULL;
		}
	}

	template <const int N>
	constexpr volatile uint16_t* getOCRB16b()
	{
		assert_timer_number<N>();
		switch (N)
		{
			#if defined(OCR0B) && defined(OCR0BH)
			case 0:
				return &OCR0B;
			#endif
			#if defined(OCR1B) && defined(OCR1BH)
			case 1:
				return &OCR1B;
			#endif
			#if defined(OCR2B) && defined(OCR2BH)
			case 2:
				return &OCR2B;
			#endif
			#if defined(OCR3B) && defined(OCR3BH)
			case 3:
				return &OCR3B;
			#endif
			#if defined(OCR4B) && defined(OCR4BH)
			case 4:
				return &OCR4B;
			#endif
			#if defined(OCR5B) && defined(OCR5BH)
			case 5:
				return &OCR5B;
			#endif
			#if defined(OCR6B) && defined(OCR6BH)
			case 6:
				return &OCR6B;
			#endif
			#if defined(OCR7B) && defined(OCR7BH)
			case 7:
				return &OCR7B;
			#endif
			#if defined(OCR8B) && defined(OCR8BH)
			case 8:
				return &OCR8B;
			#endif
			default:
				return NULL;
		}
	}

	template <const int N>
	constexpr volatile uint16_t* getOCRC16b()
	{
		assert_timer_number<N>();
		switch (N)
		{
			#if defined(OCR0C) && defined(OCR8CH)
			case 0:
				return &OCR0C;
			#endif
			#if defined(OCR1C) && defined(OCR8CH)
			case 1:
				return &OCR1C;
			#endif
			#if defined(OCR2C) && defined(OCR8CH)
			case 2:
				return &OCR2C;
			#endif
			#if defined(OCR3C) && defined(OCR8CH)
			case 3:
				return &OCR3C;
			#endif
			#if defined(OCR4C) && defined(OCR8CH)
			case 4:
				return &OCR4C;
			#endif
			#if defined(OCR5C) && defined(OCR8CH)
			case 5:
				return &OCR5C;
			#endif
			#if defined(OCR6C) && defined(OCR8CH)
			case 6:
				return &OCR6C;
			#endif
			#if defined(OCR7C) && defined(OCR8CH)
			case 7:
				return &OCR7C;
			#endif
			#if defined(OCR8C) && defined(OCR8CH)
			case 8:
				return &OCR8C;
			#endif
			default:
				return NULL;
		}
	}

	// template <const int N>
	// constexpr volatile uint8_t* getOCRAL()
	// {
	// 	assert_timer_number<N>();
	// 	switch (N)
	// 	{
	// 		#ifdef OCR0AL
	// 		case 0:
	// 			return &OCR0AL;
	// 		#endif
	// 		#ifdef OCR1AL
	// 		case 1:
	// 			return &OCR1AL;
	// 		#endif
	// 		#ifdef OCR2AL
	// 		case 2:
	// 			return &OCR2AL;
	// 		#endif
	// 		#ifdef OCR3AL
	// 		case 3:
	// 			return &OCR3AL;
	// 		#endif
	// 		#ifdef OCR4AL
	// 		case 4:
	// 			return &OCR4AL;
	// 		#endif
	// 		#ifdef OCR5AL
	// 		case 5:
	// 			return &OCR5AL;
	// 		#endif
	// 		#ifdef OCR6AL
	// 		case 6:
	// 			return &OCR6AL;
	// 		#endif
	// 		#ifdef OCR7AL
	// 		case 7:
	// 			return &OCR7AL;
	// 		#endif
	// 		#ifdef OCR8AL
	// 		case 8:
	// 			return &OCR8AL;
	// 		#endif
	// 		default:
	// 			return NULL;
	// 	}
	// }

	// template <const int N>
	// constexpr volatile uint8_t* getOCRBL()
	// {
	// 	assert_timer_number<N>();
	// 	switch (N)
	// 	{
	// 		#ifdef OCR0BL
	// 		case 0:
	// 			return &OCR0BL;
	// 		#endif
	// 		#ifdef OCR1BL
	// 		case 1:
	// 			return &OCR1BL;
	// 		#endif
	// 		#ifdef OCR2BL
	// 		case 2:
	// 			return &OCR2BL;
	// 		#endif
	// 		#ifdef OCR3BL
	// 		case 3:
	// 			return &OCR3BL;
	// 		#endif
	// 		#ifdef OCR4BL
	// 		case 4:
	// 			return &OCR4BL;
	// 		#endif
	// 		#ifdef OCR5BL
	// 		case 5:
	// 			return &OCR5BL;
	// 		#endif
	// 		#ifdef OCR6BL
	// 		case 6:
	// 			return &OCR6BL;
	// 		#endif
	// 		#ifdef OCR7BL
	// 		case 7:
	// 			return &OCR7BL;
	// 		#endif
	// 		#ifdef OCR8BL
	// 		case 8:
	// 			return &OCR8BL;
	// 		#endif
	// 		default:
	// 			return NULL;
	// 	}
	// }

	// template <const int N>
	// constexpr volatile uint8_t* getOCRCL()
	// {
	// 	assert_timer_number<N>();
	// 	switch (N)
	// 	{
	// 		#ifdef OCR0CL
	// 		case 0:
	// 			return &OCR0CL;
	// 		#endif
	// 		#ifdef OCR1CL
	// 		case 1:
	// 			return &OCR1CL;
	// 		#endif
	// 		#ifdef OCR2CL
	// 		case 2:
	// 			return &OCR2CL;
	// 		#endif
	// 		#ifdef OCR3CL
	// 		case 3:
	// 			return &OCR3CL;
	// 		#endif
	// 		#ifdef OCR4CL
	// 		case 4:
	// 			return &OCR4CL;
	// 		#endif
	// 		#ifdef OCR5CL
	// 		case 5:
	// 			return &OCR5CL;
	// 		#endif
	// 		#ifdef OCR6CL
	// 		case 6:
	// 			return &OCR6CL;
	// 		#endif
	// 		#ifdef OCR7CL
	// 		case 7:
	// 			return &OCR7CL;
	// 		#endif
	// 		#ifdef OCR8CL
	// 		case 8:
	// 			return &OCR8CL;
	// 		#endif
	// 		default:
	// 			return NULL;
	// 	}
	// }

	// template <const int N>
	// constexpr volatile uint8_t* getOCRAH()
	// {
	// 	assert_timer_number<N>();
	// 	switch (N)
	// 	{
	// 		#ifdef OCR0AH
	// 		case 0:
	// 			return &OCR0AH;
	// 		#endif
	// 		#ifdef OCR1AH
	// 		case 1:
	// 			return &OCR1AH;
	// 		#endif
	// 		#ifdef OCR2AH
	// 		case 2:
	// 			return &OCR2AH;
	// 		#endif
	// 		#ifdef OCR3AH
	// 		case 3:
	// 			return &OCR3AH;
	// 		#endif
	// 		#ifdef OCR4AH
	// 		case 4:
	// 			return &OCR4AH;
	// 		#endif
	// 		#ifdef OCR5AH
	// 		case 5:
	// 			return &OCR5AH;
	// 		#endif
	// 		#ifdef OCR6AH
	// 		case 6:
	// 			return &OCR6AH;
	// 		#endif
	// 		#ifdef OCR7AH
	// 		case 7:
	// 			return &OCR7AH;
	// 		#endif
	// 		#ifdef OCR8AH
	// 		case 8:
	// 			return &OCR8AH;
	// 		#endif
	// 		default:
	// 			return NULL;
	// 	}
	// }

	// template <const int N>
	// constexpr volatile uint8_t* getOCRBH()
	// {
	// 	assert_timer_number<N>();
	// 	switch (N)
	// 	{
	// 		#ifdef OCR0BH
	// 		case 0:
	// 			return &OCR0BH;
	// 		#endif
	// 		#ifdef OCR1BH
	// 		case 1:
	// 			return &OCR1BH;
	// 		#endif
	// 		#ifdef OCR2BH
	// 		case 2:
	// 			return &OCR2BH;
	// 		#endif
	// 		#ifdef OCR3BH
	// 		case 3:
	// 			return &OCR3BH;
	// 		#endif
	// 		#ifdef OCR4BH
	// 		case 4:
	// 			return &OCR4BH;
	// 		#endif
	// 		#ifdef OCR5BH
	// 		case 5:
	// 			return &OCR5BH;
	// 		#endif
	// 		#ifdef OCR6BH
	// 		case 6:
	// 			return &OCR6BH;
	// 		#endif
	// 		#ifdef OCR7BH
	// 		case 7:
	// 			return &OCR7BH;
	// 		#endif
	// 		#ifdef OCR8BH
	// 		case 8:
	// 			return &OCR8BH;
	// 		#endif
	// 		default:
	// 			return NULL;
	// 	}
	// }

	// template <const int N>
	// constexpr volatile uint8_t* getOCRCH()
	// {
	// 	assert_timer_number<N>();
	// 	switch (N)
	// 	{
	// 		#ifdef OCR0CH
	// 		case 0:
	// 			return &OCR0CH;
	// 		#endif
	// 		#ifdef OCR1CH
	// 		case 1:
	// 			return &OCR1CH;
	// 		#endif
	// 		#ifdef OCR2CH
	// 		case 2:
	// 			return &OCR2CH;
	// 		#endif
	// 		#ifdef OCR3CH
	// 		case 3:
	// 			return &OCR3CH;
	// 		#endif
	// 		#ifdef OCR4CH
	// 		case 4:
	// 			return &OCR4CH;
	// 		#endif
	// 		#ifdef OCR5CH
	// 		case 5:
	// 			return &OCR5CH;
	// 		#endif
	// 		#ifdef OCR6CH
	// 		case 6:
	// 			return &OCR6CH;
	// 		#endif
	// 		#ifdef OCR7CH
	// 		case 7:
	// 			return &OCR7CH;
	// 		#endif
	// 		#ifdef OCR8CH
	// 		case 8:
	// 			return &OCR8CH;
	// 		#endif
	// 		default:
	// 			return NULL;
	// 	}
	// }

	template <const int N, const Var V, class T>
	constexpr T* getOCR()
	{
		if constexpr (std::is_same<T, volatile uint16_t>::value)
		{
			switch (V)
			{
			case A:
				return getOCRA16b<N>();
			case B:
				return getOCRB16b<N>();
			case C:
				return getOCRC16b<N>();
			}
		}
		else if constexpr (std::is_same<T, volatile uint8_t>::value){
			switch (V)
			{
			case A:
				return getOCRA8b<N>();
			case B:
				return getOCRB8b<N>();
			case C:
				return getOCRC8b<N>();
			}
		}
		else {
			static_assert(std::is_same<T, uint8_t>::value || std::is_same<T, uint16_t>::value, "Invalid type");
			return NULL;
		}
	}

	// template <const int N, const Var V>
	// constexpr volatile uint8_t* getOCRL()
	// {
	// 	switch (V)
	// 	{
	// 	case A:
	// 		return getOCRAL<N>();
	// 	case B:
	// 		return getOCRBL<N>();
	// 	case C:
	// 		return getOCRCL<N>();
	// 	}
	// }

	// template <const int N, const Var V>
	// constexpr volatile uint8_t* getOCRH()
	// {
	// 	switch (V)
	// 	{
	// 	case A:
	// 		return getOCRAH<N>();
	// 	case B:
	// 		return getOCRBH<N>();
	// 	case C:
	// 		return getOCRCH<N>();
	// 	}
	// }

	template <const int N, const int K>
	constexpr uint8_t getWGM()
	{
		assert_timer_number<N>();
		switch (N)
		{
			#ifdef WGM00
			case 0:
				return K == 0? WGM00 : WGM01;
			#endif
			#ifdef WGM10
			case 1:
				return K == 0? WGM10 : WGM11;
			#endif
			#ifdef WGM20
			case 2:
				return K == 0? WGM20 : WGM21;
			#endif
			#ifdef WGM30
			case 3:
				return K == 0? WGM30 : WGM11;
			#endif
			#ifdef WGM40
			case 4:
				return K == 0? WGM40 : WGM11;
			#endif
			#ifdef WGM50
			case 5:
				return K == 0? WGM50 : WGM11;
			#endif
			#ifdef WGM60
			case 6:
				return K == 0? WGM60 : WGM11;
			#endif
			#ifdef WGM70
			case 7:
				return K == 0? WGM70 : WGM11;
			#endif
			#ifdef WGM80
			case 8:
				return K == 0? WGM80 : WGM11;
			#endif
			default:
				return 0;
		}
	}

	/*
	 * Function 	TIMERnInit
	 * Desc     	init Timer/Counter <n>
	 * Input    	com: what Compare Output Mode use to
	 *				wfmode: what Waveform generation mode use to
	 *				clk: what clock source use to
	 * Output   	none
	 */
	template<const int N>
	void init(const uint8_t com, const  uint8_t wfmode, const  uint8_t clk)
	{
		*getTCCRA<N>() = static_cast<uint8_t>((*getTCCRA<N>() & ~((wfmode & ((1 << getWGM<N, 0>()) | (1 << getWGM<N, 1>()))) | com)) 
											| ((wfmode & ((1 << getWGM<N, 0>()) | (1 << getWGM<N, 1>()))) | com));
		*getTCCRB<N>() = static_cast<uint8_t>((clk & timer::clk::getMask<N>()) | (wfmode & ~((1 << getWGM<N, 0>()) | (1 << getWGM<N, 1>()))));
	}

	/* 
	 * Function TIMERnSetCLK
	 * Desc     Change clock source in T/Cn
	 * Input    _clk: what clk change to
	 * Output   none
	 */
	template<const int N>
	void setClk(const uint8_t clk)
	{
		*getTCCRB<N>() &= static_cast<uint8_t>(~timer::clk::getMask<N>());
		*getTCCRB<N>() |= static_cast<uint8_t>(clk & timer::clk::getMask<N>());
	}

	template<const int N, const Var V, class T>
	void setVar(const T var)
	{
		*getOCR<N, V, T>() = var;
	}

	
	// template<const int N, const Var V>
	// void setVar(const uint16_t var)
	// {
	// 	*getOCR<N, V, uint16_t>() = var;
	// }

	

} // namespace timer


// void analogWrite(uint8_t _pin, uint16_t _num);
// void analogWrite(uint8_t _timer, uint8_t _ch, uint16_t _num);


// #ifdef TCCR0A 	//TIMER0
// 	void TIMER0Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
// 	void TIMER0SetCLK(uint8_t);
// 	void TIMER0Flush();

// 	//just for fun
// 	#ifdef OCR0AL//check 16 bit
// 		#pragma message "TIMER0 16 bit"
// 	#else //ifdef OCR0AL
// 		#pragma message "TIMER0 8 bit"
// 	#endif //ifndef OCR0AL

// 	#ifdef OCR0AL
// 		void TIMER0SetA(uint16_t);
// 	#else //ifdef OCR0AL
// 		void TIMER0SetA(uint8_t);
// 	#endif //ifndef OCR0AL

// 	  void TIMER0EnableCOMPAInterrupt();
// 	  void TIMER0DisableCOMPAInterrupt();

// 	#ifdef OCR0BL
// 		void TIMER0SetB(uint16_t);
// 	#else //ifdef OCR0BL
// 		void TIMER0SetB(uint8_t);
// 	#endif //ifndef OCR0BL

// 	  void TIMER0EnableCOMPBInterrupt();
// 	  void TIMER0DisableCOMPBInterrupt();

// 	#ifdef OCR0CL
// 		void TIMER0SetC(uint16_t);
// 	#else //ifdef OCR0CL
// 		void TIMER0SetC(uint8_t);
// 	#endif //ifndef OCR0CL

// 	  void TIMER0EnableCOMPCInterrupt();
// 	  void TIMER0DisableCOMPCInterrupt();
// #endif //ifdef TCCR0A



// #ifdef TCCR1A 	//TIMER1
// 	void TIMER1Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
// 	void TIMER1SetCLK(uint8_t);
// 	void TIMER1Flush();

// 	//just for fun
// 	#ifdef OCR1AL//check 16 bit
// 		#pragma message "TIMER1 16 bit"
// 	#else //ifdef OCR1AL
// 		#pragma message "TIMER1 8 bit"
// 	#endif //ifndef OCR1AL

// 	#ifdef OCR1AL
// 		void TIMER1SetA(uint16_t);
// 	#else //ifdef OCR1AL
// 		void TIMER1SetA(uint8_t);
// 	#endif //ifndef OCR1AL

// 	  void TIMER1EnableCOMPAInterrupt();
// 	  void TIMER1DisableCOMPAInterrupt();

// 	#ifdef OCR1BL
// 		void TIMER1SetB(uint16_t);
// 	#else //ifdef OCR1BL
// 		void TIMER1SetB(uint8_t);
// 	#endif //ifndef OCR1BL

// 	  void TIMER1EnableCOMPBInterrupt();
// 	  void TIMER1DisableCOMPBInterrupt();

// 	#if defined(OCR1CL)
// 		void TIMER1SetC(uint16_t);
// 	#else //ifdef OCR1CL
// 		void TIMER1SetC(uint8_t);
// 	#endif //ifndef OCR1CL

// 	  void TIMER1EnableCOMPCInterrupt();
// 	  void TIMER1DisableCOMPCInterrupt();
// #endif //ifdef TCCR1A





// #ifdef TCCR2A 	//TIMER2
// 	void TIMER2Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
// 	void TIMER2SetCLK(uint8_t);
// 	void TIMER2Flush();

// 	//just for fun
// 	#ifdef OCR2AL//check 16 bit
// 		#pragma message "TIMER2 16 bit"
// 	#else //ifdef OCR2AL
// 		#pragma message "TIMER2 8 bit"
// 	#endif //ifndef OCR2AL

// 	#ifdef OCR2AL
// 		void TIMER2SetA(uint16_t);
// 	#else //ifdef OCR2AL
// 		void TIMER2SetA(uint8_t);
// 	#endif //ifndef OCR2AL

// 	  void TIMER2EnableCOMPAInterrupt();
// 	  void TIMER2DisableCOMPAInterrupt();

// 	#ifdef OCR2BL
// 		void TIMER2SetB(uint16_t);
// 	#else //ifdef OCR2BL
// 		void TIMER2SetB(uint8_t);
// 	#endif //ifndef OCR2BL

// 	  void TIMER2EnableCOMPBInterrupt();
// 	  void TIMER2DisableCOMPBInterrupt();

// 	#ifdef OCR2CL
// 		void TIMER2SetC(uint16_t);
// 	#else //ifdef OCR2CL
// 		void TIMER2SetC(uint8_t);
// 	#endif //ifndef OCR2CL

// 	  void TIMER2EnableCOMPCInterrupt();
// 	  void TIMER2DisableCOMPCInterrupt();
// #endif //ifdef TCCR2A





// #ifdef TCCR3A 	//TIMER3
// 	void TIMER3Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
// 	void TIMER3SetCLK(uint8_t);
// 	void TIMER3Flush();

// 	//just for fun
// 	#ifdef OCR3AL//check 16 bit
// 		#pragma message "TIMER3 16 bit"
// 	#else //ifdef OCR3AL
// 		#pragma message "TIMER3 8 bit"
// 	#endif //ifndef OCR3AL

// 	#ifdef OCR3AL
// 		void TIMER3SetA(uint16_t);
// 	#else //ifdef OCR3AL
// 		void TIMER3SetA(uint8_t);
// 	#endif //ifndef OCR3AL

// 	  void TIMER3EnableCOMPAInterrupt();
// 	  void TIMER3DisableCOMPAInterrupt();

// 	#ifdef OCR3BL
// 		void TIMER3SetB(uint16_t);
// 	#else //ifdef OCR3BL
// 		void TIMER3SetB(uint8_t);
// 	#endif //ifndef OCR3BL

// 	  void TIMER3EnableCOMPBInterrupt();
// 	  void TIMER3DisableCOMPBInterrupt();

// 	#ifdef OCR3CL
// 		void TIMER3SetC(uint16_t);
// 	#else //ifdef OCR3CL
// 		void TIMER3SetC(uint8_t);
// 	#endif //ifndef OCR3CL

// 	  void TIMER3EnableCOMPCInterrupt();
// 	  void TIMER3DisableCOMPCInterrupt();
// #endif //ifdef TCCR3A





// #ifdef TCCR4A 	//TIMER4
// 	void TIMER4Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
// 	void TIMER4SetCLK(uint8_t);
// 	void TIMER4Flush();

// 	//just for fun
// 	#ifdef OCR4AL//check 16 bit
// 		#pragma message "TIMER4 16 bit"
// 	#else //ifdef OCR4AL
// 		#pragma message "TIMER4 8 bit"
// 	#endif //ifndef OCR4AL

// 	#ifdef OCR4AL
// 		void TIMER4SetA(uint16_t);
// 	#else //ifdef OCR4AL
// 		void TIMER4SetA(uint8_t);
// 	#endif //ifndef OCR4AL

// 	  void TIMER4EnableCOMPAInterrupt();
// 	  void TIMER4DisableCOMPAInterrupt();

// 	#ifdef OCR4BL
// 		void TIMER4SetB(uint16_t);
// 	#else //ifdef OCR4BL
// 		void TIMER4SetB(uint8_t);
// 	#endif //ifndef OCR4BL

// 	  void TIMER4EnableCOMPBInterrupt();
// 	  void TIMER4DisableCOMPBInterrupt();

// 	#ifdef OCR4CL
// 		void TIMER4SetC(uint16_t);
// 	#else //ifdef OCR4CL
// 		void TIMER4SetC(uint8_t);
// 	#endif //ifndef OCR4CL

// 	  void TIMER4EnableCOMPCInterrupt();
// 	  void TIMER4DisableCOMPCInterrupt();
// #endif //ifdef TCCR4A





// #ifdef TCCR5A 	//TIMER5
// 	void TIMER5Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
// 	void TIMER5SetCLK(uint8_t);
// 	void TIMER5Flush();

// 	//just for fun
// 	#ifdef OCR5AL//check 16 bit
// 		#pragma message "TIMER5 16 bit"
// 	#else //ifdef OCR5AL
// 		#pragma message "TIMER5 8 bit"
// 	#endif //ifndef OCR5AL

// 	#ifdef OCR5AL
// 		void TIMER5SetA(uint16_t);
// 	#else //ifdef OCR5AL
// 		void TIMER5SetA(uint8_t);
// 	#endif //ifndef OCR5AL

// 	  void TIMER5EnableCOMPAInterrupt();
// 	  void TIMER5DisableCOMPAInterrupt();

// 	#ifdef OCR5BL
// 		void TIMER5SetB(uint16_t);
// 	#else //ifdef OCR5BL
// 		void TIMER5SetB(uint8_t);
// 	#endif //ifndef OCR5BL

// 	  void TIMER5EnableCOMPBInterrupt();
// 	  void TIMER5DisableCOMPBInterrupt();

// 	#ifdef OCR5CL
// 		void TIMER5SetC(uint16_t);
// 	#else //ifdef OCR5CL
// 		void TIMER5SetC(uint8_t);
// 	#endif //ifndef OCR5CL

// 	  void TIMER5EnableCOMPCInterrupt();
// 	  void TIMER5DisableCOMPCInterrupt();
// #endif //ifdef TCCR5A





// #ifdef TCCR6A 	//TIMER6
// 	void TIMER6Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
// 	void TIMER6SetCLK(uint8_t);
// 	void TIMER6Flush();

// 	//just for fun
// 	#ifdef OCR6AL//check 16 bit
// 		#pragma message "TIMER6 16 bit"
// 	#else //ifdef OCR6AL
// 		#pragma message "TIMER6 8 bit"
// 	#endif //ifndef OCR6AL

// 	#ifdef OCR6AL
// 		void TIMER6SetA(uint16_t);
// 	#else //ifdef OCR6AL
// 		void TIMER6SetA(uint8_t);
// 	#endif //ifndef OCR6AL

// 	  void TIMER6EnableCOMPAInterrupt();
// 	  void TIMER6DisableCOMPAInterrupt();

// 	#ifdef OCR6BL
// 		void TIMER6SetB(uint16_t);
// 	#else //ifdef OCR6BL
// 		void TIMER6SetB(uint8_t);
// 	#endif //ifndef OCR6BL

// 	  void TIMER6EnableCOMPBInterrupt();
// 	  void TIMER6DisableCOMPBInterrupt();

// 	#ifdef OCR6CL
// 		void TIMER6SetC(uint16_t);
// 	#else //ifdef OCR6CL
// 		void TIMER6SetC(uint8_t);
// 	#endif //ifndef OCR6CL

// 	  void TIMER6EnableCOMPCInterrupt();
// 	  void TIMER6DisableCOMPCInterrupt();
// #endif //ifdef TCCR6A





// #ifdef TCCR7A 	//TIMER7
// 	void TIMER7Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
// 	void TIMER7SetCLK(uint8_t);
// 	void TIMER7Flush();

// 	//just for fun
// 	#ifdef OCR7AL//check 16 bit
// 		#pragma message "TIMER7 16 bit"
// 	#else //ifdef OCR7AL
// 		#pragma message "TIMER7 8 bit"
// 	#endif //ifndef OCR7AL

// 	#ifdef OCR7AL
// 		void TIMER7SetA(uint16_t);
// 	#else //ifdef OCR7AL
// 		void TIMER7SetA(uint8_t);
// 	#endif //ifndef OCR7AL

// 	  void TIMER7EnableCOMPAInterrupt();
// 	  void TIMER7DisableCOMPAInterrupt();

// 	#ifdef OCR7BL
// 		void TIMER7SetB(uint16_t);
// 	#else //ifdef OCR7BL
// 		void TIMER7SetB(uint8_t);
// 	#endif //ifndef OCR7BL

// 	  void TIMER7EnableCOMPBInterrupt();
// 	  void TIMER7DisableCOMPBInterrupt();

// 	#ifdef OCR7CL
// 		void TIMER7SetC(uint16_t);
// 	#else //ifdef OCR7CL
// 		void TIMER7SetC(uint8_t);
// 	#endif //ifndef OCR7CL

// 	  void TIMER7EnableCOMPCInterrupt();
// 	  void TIMER7DisableCOMPCInterrupt();
// #endif //ifdef TCCR7A





// #ifdef TCCR8A 	//TIMER8
// 	void TIMER8Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk);
// 	void TIMER8SetCLK(uint8_t);
// 	void TIMER8Flush();

// 	//just for fun
// 	#ifdef OCR8AL//check 16 bit
// 		#pragma message "TIMER8 16 bit"
// 	#else //ifdef OCR8AL
// 		#pragma message "TIMER8 8 bit"
// 	#endif //ifndef OCR8AL

// 	#ifdef OCR8AL
// 		void TIMER8SetA(uint16_t);
// 	#else //ifdef OCR8AL
// 		void TIMER8SetA(uint8_t);
// 	#endif //ifndef OCR8AL

// 	  void TIMER8EnableCOMPAInterrupt();
// 	  void TIMER8DisableCOMPAInterrupt();

// 	#ifdef OCR8BL
// 		void TIMER8SetB(uint16_t);
// 	#else //ifdef OCR8BL
// 		void TIMER8SetB(uint8_t);
// 	#endif //ifndef OCR8BL

// 	  void TIMER8EnableCOMPBInterrupt();
// 	  void TIMER8DisableCOMPBInterrupt();

// 	#ifdef OCR8CL
// 		void TIMER8SetC(uint16_t);
// 	#else //ifdef OCR8CL
// 		void TIMER8SetC(uint8_t);
// 	#endif //ifndef OCR8CL

// 	  void TIMER8EnableCOMPCInterrupt();
// 	  void TIMER8DisableCOMPCInterrupt();
// #endif //ifdef TCCR8A

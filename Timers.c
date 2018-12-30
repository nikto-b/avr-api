#if USE_TIMERS == 1
	
	#ifdef TCCR0A //if defined T/C0
		/*
		 * Function TIMER0Init
		 * Desc     init T/C0
		 * Input    __mode: what mode of T/C0
		 * Output   none
		 */
		void TIMER0Init(uint8_t _com ,uint8_t _wfmode, uint8_t _clk)
		{
			TCCR0A = _wfmode | _com;
			TCCR0B = _clk;
		}
		
	#endif //ifdef TCCR0A

#endif //if USE_TIMERS == 1
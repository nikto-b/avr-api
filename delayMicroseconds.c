void delayMicroseconds(uint64_t _us)												//thx arduino lib for this func
{
	#if F_CPU >= 24000000L
			if (!_us) return;
			_us *= 6;
			_us -= 5;
	#elif F_CPU >= 20000000L
			__asm__ __volatile__ (
					"nop" "\n\t"
					"nop" "\n\t"
					"nop" "\n\t"
					"nop");
			if (_us <= 1) return;
			_us = (_us << 2) + _us;
			_us -= 7;
	#elif F_CPU >= 16000000L
			if (_us <= 1) return;
			_us <<= 2;
	#elif F_CPU >= 12000000L
			if (us <= 1) return;
			_us = (_us << 1) + _us;
	#elif F_CPU >= 8000000L
			if (_us <= 2) return;
			_us <<= 1;
			_us -= 4;
	#else
			if (_us <= 16) return;
			if (_us <= 25) return;
			_us -= 22;
			_us >>= 2;
	#endif
        // busy wait
        __asm__ __volatile__ (
                "1: sbiw %0,1" "\n\t"
                "brne 1b" : "=w" (_us) : "0" (_us)
        );
}

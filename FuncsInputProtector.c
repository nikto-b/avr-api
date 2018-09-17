#pragma message "Using FuncInputProtector"

#if USE_TIMERS == 1
	//TIMER0
	
	uint8_t validateTimer0Mode(uint8_t __mode)
	{
		if(__mode != TIMER0_MODE_CTC
		&& __mode != TIMER0_MODE_FASTPWM
		&& __mode != TIMER0_MODE_FASTPWM_TOPOCRA
		&& __mode != TIMER0_MODE_NORMAL
		&& __mode != TIMER0_MODE_PWM_PHC
		&& __mode != TIMER0_MODE_PWM_PHC_TOPOCRA)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	uint8_t validateTimer0CLK(uint8_t __source)
	{		
		if(__source != TIMER0_CLOCK_1
		&& __source != TIMER0_CLOCK_1024
		&& __source != TIMER0_CLOCK_256
		&& __source != TIMER0_CLOCK_64
		&& __source != TIMER0_CLOCK_8
		&& __source != TIMER0_CLOCK_EXTERNAL_FALLING
		&& __source != TIMER0_CLOCK_EXTERNAL_RISING
		&& __source != TIMER0_CLOCK_NONE)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	
	//TIMER1
	
	uint8_t validateTimer1Mode(uint8_t __mode)
	{
		if(__mode != TIMER1_MODE_CTC_TOPICR1
		&& __mode != TIMER1_MODE_CTC_TOPOCR1A
		&& __mode != TIMER1_MODE_FASTPWM_10B
		&& __mode != TIMER1_MODE_FASTPWM_8B
		&& __mode != TIMER1_MODE_FASTPWM_9B
		&& __mode != TIMER1_MODE_FASTPWM_TOPICR1
		&& __mode != TIMER1_MODE_FASTPWM_TOPOCR1A
		&& __mode != TIMER1_MODE_NORMAL
		&& __mode != TIMER1_MODE_PWM_PHC_10B
		&& __mode != TIMER1_MODE_PWM_PHC_8B
		&& __mode != TIMER1_MODE_PWM_PHC_9B
		&& __mode != TIMER1_MODE_PWM_PHC_TOPICR1
		&& __mode != TIMER1_MODE_PWM_PHC_TOPOCR1A
		&& __mode != TIMER1_MODE_PWM_PHFRC_TOPICR1
		&& __mode != TIMER1_MODE_PWM_PHFRC_TOPOCR1A)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	uint8_t validateTimer1CLK(uint8_t __source)
	{
		if(__source != TIMER1_CLOCK_1
		&& __source != TIMER1_CLOCK_8
		&& __source != TIMER1_CLOCK_64
		&& __source != TIMER1_CLOCK_256
		&& __source != TIMER1_CLOCK_1024
		&& __source != TIMER1_CLOCK_EXTERNAL_FALLING
		&& __source != TIMER1_CLOCK_EXTERNAL_RISING
		&& __source != TIMER1_CLOCK_NONE)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	
	//TIMER2
	
	uint8_t validateTimer2Mode(uint8_t __mode)
	{
		if(__mode != TIMER2_MODE_CTC
		&& __mode != TIMER2_MODE_FASTPWM
		&& __mode != TIMER2_MODE_FASTPWM_TOPOCRA
		&& __mode != TIMER2_MODE_NORMAL
		&& __mode != TIMER2_MODE_PWM_PHC
		&& __mode != TIMER2_MODE_PWM_PHC_TOPOCRA)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	uint8_t validateTimer2CLK(uint8_t __source)
	{
		if(__source != TIMER2_CLOCK_NONE
		&& __source != TIMER2_CLOCK_1
		&& __source != TIMER2_CLOCK_8
		&& __source != TIMER2_CLOCK_32
		&& __source != TIMER2_CLOCK_64
		&& __source != TIMER2_CLOCK_128
		&& __source != TIMER2_CLOCK_256
		&& __source != TIMER2_CLOCK_1024)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	
	//TIMER3
	
	uint8_t validateTimer3Mode(uint8_t __mode)
	{
		if(__mode != TIMER3_MODE_CTC_TOPICR3
		&& __mode != TIMER3_MODE_CTC_TOPOCR3A
		&& __mode != TIMER3_MODE_FASTPWM_10B
		&& __mode != TIMER3_MODE_FASTPWM_8B
		&& __mode != TIMER3_MODE_FASTPWM_9B
		&& __mode != TIMER3_MODE_FASTPWM_TOPICR3
		&& __mode != TIMER3_MODE_NORMAL
		&& __mode != TIMER3_MODE_PWM_PHC_10B
		&& __mode != TIMER3_MODE_PWM_PHC_8B
		&& __mode != TIMER3_MODE_PWM_PHC_9B
		&& __mode != TIMER3_MODE_PWM_PHC_TOPICR3
		&& __mode != TIMER3_MODE_PWM_PHC_TOPOCR3A
		&& __mode != TIMER3_MODE_PWM_PHFRC_TOPICR3
		&& __mode != TIMER3_MODE_PWM_PHFRC_TOPOCR3A
		&& __mode != TIMER3_MODE_FASTPWM_TOPOCR3A)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	uint8_t validateTimer3CLK(uint8_t __source)
	{
		if(__source != TIMER3_CLOCK_NONE
		&& __source != TIMER3_CLOCK_1
		&& __source != TIMER3_CLOCK_8
		&& __source != TIMER3_CLOCK_64
		&& __source != TIMER3_CLOCK_256
		&& __source != TIMER3_CLOCK_1024
		&& __source != TIMER3_CLOCK_EXTERNAL_FALLING
		&& __source != TIMER3_CLOCK_EXTERNAL_RISING)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	
	//TIMER4
	
	uint8_t validateTimer4Mode(uint8_t __mode)
	{
		if(__mode != TIMER4_MODE_CTC_TOPICR4
		&& __mode != TIMER4_MODE_CTC_TOPOCR4A
		&& __mode != TIMER4_MODE_FASTPWM_10B
		&& __mode != TIMER4_MODE_FASTPWM_8B
		&& __mode != TIMER4_MODE_FASTPWM_9B
		&& __mode != TIMER4_MODE_FASTPWM_TOPICR4
		&& __mode != TIMER4_MODE_FASTPWM_TOPOCR4A
		&& __mode != TIMER4_MODE_NORMAL
		&& __mode != TIMER4_MODE_PWM_PHC_10B
		&& __mode != TIMER4_MODE_PWM_PHC_8B
		&& __mode != TIMER4_MODE_PWM_PHC_9B
		&& __mode != TIMER4_MODE_PWM_PHC_TOPICR4
		&& __mode != TIMER4_MODE_PWM_PHC_TOPOCR4A
		&& __mode != TIMER4_MODE_PWM_PHFRC_TOPICR4
		&& __mode != TIMER4_MODE_PWM_PHFRC_TOPOCR4A)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	uint8_t validateTimer4CLK(uint8_t __source)
	{
		if(__source != TIMER4_CLOCK_1
		&& __source != TIMER4_CLOCK_1024
		&& __source != TIMER4_CLOCK_256
		&& __source != TIMER4_CLOCK_64
		&& __source != TIMER4_CLOCK_8
		&& __source != TIMER4_CLOCK_EXTERNAL_FALLING
		&& __source != TIMER4_CLOCK_EXTERNAL_RISING
		&& __source != TIMER4_CLOCK_NONE)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	
	//TIMER5
	
	uint8_t validateTimer5Mode(uint8_t __mode)
	{
		if(__mode != TIMER5_MODE_CTC_TOPICR5
		&& __mode != TIMER5_MODE_CTC_TOPOCR5A
		&& __mode != TIMER5_MODE_FASTPWM_10B
		&& __mode != TIMER5_MODE_FASTPWM_8B
		&& __mode != TIMER5_MODE_FASTPWM_9B
		&& __mode != TIMER5_MODE_FASTPWM_TOPICR5
		&& __mode != TIMER5_MODE_FASTPWM_TOPOCR5A
		&& __mode != TIMER5_MODE_NORMAL
		&& __mode != TIMER5_MODE_PWM_PHC_10B
		&& __mode != TIMER5_MODE_PWM_PHC_8B
		&& __mode != TIMER5_MODE_PWM_PHC_9B
		&& __mode != TIMER5_MODE_PWM_PHC_TOPICR5
		&& __mode != TIMER5_MODE_PWM_PHC_TOPOCR5A
		&& __mode != TIMER5_MODE_PWM_PHFRC_TOPICR5
		&& __mode != TIMER5_MODE_PWM_PHFRC_TOPOCR5A)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	uint8_t validateTimer5CLK(uint8_t __source)
	{
		if(__source != TIMER5_CLOCK_1
		&& __source != TIMER5_CLOCK_1024
		&& __source != TIMER5_CLOCK_256
		&& __source != TIMER5_CLOCK_64
		&& __source != TIMER5_CLOCK_8
		&& __source != TIMER5_CLOCK_EXTERNAL_FALLING
		&& __source != TIMER5_CLOCK_EXTERNAL_RISING
		&& __source != TIMER5_CLOCK_NONE)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
#endif //if USE_TIMERS == 1

#if USE_ADC == 1

#endif //if USE_ADC == 1

#if USE_USART == 1

#endif //if USE_USART == 1

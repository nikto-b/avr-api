
//-------------------------------------------------------------------------TIMER-MODES---------------------------------------------------------------------------------------
#pragma message "using timer mode table for atmega2560"

//																			TIMER0
#define TIMER0_MODE_NORMAL 0
#define TIMER0_MODE_PWM_PHC (1 << WGM00)														//PWM PHASE CORRECT
#define TIMER0_MODE_CTC (1 << WGM01)															//CLEAR-ON-COMPARE; TOP - OCR1A
#define TIMER0_MODE_FASTPWM ((1 << WGM00) | (1 << WGM01))										//FAST-PWM
#define TIMER0_MODE_PWM_PHC_TOPOCRA ((1 << WGM02) | (1 << WGM00))								//PWM PHASE CORRECT TOP - OCRA
			//((1 << WGM2) | (1 << WGM1)) reserved
#define TIMER0_MODE_FASTPWM_TOPOCRA ((1 << WGM02) | (1 << WGM01) | (1 << WGM00))				//FASTPWM TOP - OCRA

//																			TIMER1
#define TIMER1_MODE_NORMAL 0
#define TIMER1_MODE_PWM_PHC_8B (1 << WGM10)														//PWM PHASE CORRECT, 8  BIT
#define TIMER1_MODE_PWM_PHC_9B (1 << WGM11)														//PWM PHASE CORRECT, 9  BIT
#define TIMER1_MODE_PWM_PHC_10B ((1 << WGM10) | (1 << WGM11))									//PWM PHASE CORRECT, 10 BIT
#define TIMER1_MODE_CTC_TOPOCR1A (1 << WGM12)													//CLEAR-ON-COMPARE; TOP - OCR1A
#define TIMER1_MODE_FASTPWM_8B ((1 << WGM10) | (1 << WGM12))									//FASTPWM, 8  BIT
#define TIMER1_MODE_FASTPWM_9B ((1 << WGM11) | (1 << WGM12))									//FASTPWM, 9  BIT
#define TIMER1_MODE_FASTPWM_10B ((1 << WGM10) | (1 << WGM11) | (1 << WGM12))					//FASTPWM, 10 BIT 
#define TIMER1_MODE_PWM_PHFRC_TOPICR1 (1 << WGM13)												//PWM PHASE AND FREQUENCY CORRECT, TOP - ICR1
#define TIMER1_MODE_PWM_PHFRC_TOPOCR1A ((1 << WGM13) | (1 << WGM10))							//PWM PHASE AND FREQUENCY CORRECT, TOP - OCR1A
#define TIMER1_MODE_PWM_PHC_TOPICR1 ((1 << WGM11) | (1 << WGM13))								//PWM PHASE CORRECT, TOP - ICR1
#define TIMER1_MODE_PWM_PHC_TOPOCR1A ((1 << WGM10) | (1 << WGM11) | (1 << WGM13))				//PWM PHASE CORRECT, TOP - OCR1A
#define TIMER1_MODE_CTC_TOPICR1 ((1 << WGM12) | (1 << WGM13))									//CLEAR-ON-COMPARE; TOP - ICR1
#define TIMER1_MODE_FASTPWM_TOPICR1 ((1 << WGM13) | (1 << WGM12) | (1 << WGM11))				//FASTPWM, TOP - ICR1
#define TIMER1_MODE_FASTPWM_TOPOCR1A ((1 << WGM13) | (1 << WGM12) | (1 << WGM11) | (1 << WGM10))//FASTPWM, TOP - OCR1A

//																			TIMER2
#define TIMER2_MODE_NORMAL 0
#define TIMER2_MODE_PWM_PHC (1 << WGM20)														//PWM PHASE CORRECT
#define TIMER2_MODE_CTC (1 << WGM21)															//CLEAR-ON-COMPARE
#define TIMER2_MODE_FASTPWM ((1 << WGM20) | (1 << WGM21))										//FASTPWM
					//(1 << WGM22) 						RESERVED
#define TIMER2_MODE_PWM_PHC_TOPOCRA ((1 << WGM22) | (1 << WGM20))								//PWM PHASE CORRECT, TOP - OCRA
					//((1 << WGM22) | (1 << WGM21))		RESERVED
#define TIMER2_MODE_FASTPWM_TOPOCRA ((1 << WGM22) | (1 << WGM21) | (1 << WGM20))				//FASTPWM, TOP - OCRA

//																			TIMER3
#define TIMER3_MODE_NORMAL 0
#define TIMER3_MODE_PWM_PHC_8B (1 << WGM30)														//PWM PHASE CORRECT, 8  BIT
#define TIMER3_MODE_PWM_PHC_9B (1 << WGM31)														//PWM PHASE CORRECT, 9  BIT
#define TIMER3_MODE_PWM_PHC_10B ((1 << WGM30) | (1 << WGM31))									//PWM PHASE CORRECT, 10 BIT
#define TIMER3_MODE_CTC_TOPOCR3A (1 << WGM32)													//CLEAR-ON-COMPARE; TOP - OCR3A
#define TIMER3_MODE_FASTPWM_8B ((1 << WGM30) | (1 << WGM32))									//FASTPWM, 8  BIT
#define TIMER3_MODE_FASTPWM_9B ((1 << WGM31) | (1 << WGM32))									//FASTPWM, 9  BIT
#define TIMER3_MODE_FASTPWM_10B ((1 << WGM30) | (1 << WGM31) | (1 << WGM32))					//FASTPWM, 10 BIT 
#define TIMER3_MODE_PWM_PHFRC_TOPICR3 (1 << WGM33)												//PWM PHASE AND FREQUENCY CORRECT, TOP - ICR3
#define TIMER3_MODE_PWM_PHFRC_TOPOCR3A ((1 << WGM33) | (1 << WGM30))							//PWM PHASE AND FREQUENCY CORRECT, TOP - OCR3A
#define TIMER3_MODE_PWM_PHC_TOPICR3 ((1 << WGM31) | (1 << WGM33))								//PWM PHASE CORRECT, TOP - ICR3
#define TIMER3_MODE_PWM_PHC_TOPOCR3A ((1 << WGM30) | (1 << WGM31) | (1 << WGM33))				//PWM PHASE CORRECT, TOP - OCR3A
#define TIMER3_MODE_CTC_TOPICR3 ((1 << WGM32) | (1 << WGM33))									//CLEAR-ON-COMPARE; TOP - ICR3
#define TIMER3_MODE_FASTPWM_TOPICR3 ((1 << WGM33) | (1 << WGM32) | (1 << WGM31))				//FASTPWM, TOP - ICR3
#define TIMER3_MODE_FASTPWM_TOPOCR3A ((1 << WGM33) | (1 << WGM32) | (1 << WGM31) | (1 << WGM30))//FASTPWM, TOP - OCR3A

//																			TIMER4
#define TIMER4_MODE_NORMAL 0
#define TIMER4_MODE_PWM_PHC_8B (1 << WGM40)														//PWM PHASE CORRECT, 8  BIT
#define TIMER4_MODE_PWM_PHC_9B (1 << WGM41)														//PWM PHASE CORRECT, 9  BIT
#define TIMER4_MODE_PWM_PHC_10B ((1 << WGM40) | (1 << WGM41))									//PWM PHASE CORRECT, 10 BIT
#define TIMER4_MODE_CTC_TOPOCR3A (1 << WGM42)													//CLEAR-ON-COMPARE; TOP - OCR4A
#define TIMER4_MODE_FASTPWM_8B ((1 << WGM40) | (1 << WGM42))									//FASTPWM, 8  BIT
#define TIMER4_MODE_FASTPWM_9B ((1 << WGM41) | (1 << WGM42))									//FASTPWM, 9  BIT
#define TIMER4_MODE_FASTPWM_10B ((1 << WGM40) | (1 << WGM41) | (1 << WGM42))					//FASTPWM, 10 BIT 
#define TIMER4_MODE_PWM_PHFRC_TOPICR4 (1 << WGM43)												//PWM PHASE AND FREQUENCY CORRECT, TOP - ICR4
#define TIMER4_MODE_PWM_PHFRC_TOPOCR4A ((1 << WGM43) | (1 << WGM40))							//PWM PHASE AND FREQUENCY CORRECT, TOP - OCR4A
#define TIMER4_MODE_PWM_PHC_TOPICR4 ((1 << WGM41) | (1 << WGM43))								//PWM PHASE CORRECT, TOP - ICR4
#define TIMER4_MODE_PWM_PHC_TOPOCR4A ((1 << WGM40) | (1 << WGM41) | (1 << WGM43))				//PWM PHASE CORRECT, TOP - OCR4A
#define TIMER4_MODE_CTC_TOPICR4 ((1 << WGM42) | (1 << WGM43))									//CLEAR-ON-COMPARE; TOP - ICR4
#define TIMER4_MODE_FASTPWM_TOPICR4 ((1 << WGM43) | (1 << WGM42) | (1 << WGM41))				//FASTPWM, TOP - ICR4
#define TIMER4_MODE_FASTPWM_TOPOCR4A ((1 << WGM43) | (1 << WGM42) | (1 << WGM41) | (1 << WGM40))//FASTPWM, TOP - OCR4A

//																			TIMER5
#define TIMER5_MODE_NORMAL 0
#define TIMER5_MODE_PWM_PHC_8B (1 << WGM50)														//PWM PHASE CORRECT, 8  BIT
#define TIMER5_MODE_PWM_PHC_9B (1 << WGM51)														//PWM PHASE CORRECT, 9  BIT
#define TIMER5_MODE_PWM_PHC_10B ((1 << WGM50) | (1 << WGM51))									//PWM PHASE CORRECT, 10 BIT
#define TIMER5_MODE_CTC_TOPOCR3A (1 << WGM52)													//CLEAR-ON-COMPARE; TOP - OCR5A
#define TIMER5_MODE_FASTPWM_8B ((1 << WGM50) | (1 << WGM52))									//FASTPWM, 8  BIT
#define TIMER5_MODE_FASTPWM_9B ((1 << WGM51) | (1 << WGM52))									//FASTPWM, 9  BIT
#define TIMER5_MODE_FASTPWM_10B ((1 << WGM50) | (1 << WGM51) | (1 << WGM52))					//FASTPWM, 10 BIT 
#define TIMER5_MODE_PWM_PHFRC_TOPICR5 (1 << WGM53)												//PWM PHASE AND FREQUENCY CORRECT, TOP - ICR5
#define TIMER5_MODE_PWM_PHFRC_TOPOCR5A ((1 << WGM53) | (1 << WGM50))							//PWM PHASE AND FREQUENCY CORRECT, TOP - OCR5A
#define TIMER5_MODE_PWM_PHC_TOPICR5 ((1 << WGM51) | (1 << WGM53))								//PWM PHASE CORRECT, TOP - ICR5
#define TIMER5_MODE_PWM_PHC_TOPOCR5A ((1 << WGM50) | (1 << WGM51) | (1 << WGM53))				//PWM PHASE CORRECT, TOP - OCR5A
#define TIMER5_MODE_CTC_TOPICR5 ((1 << WGM52) | (1 << WGM53))									//CLEAR-ON-COMPARE; TOP - ICR5
#define TIMER5_MODE_FASTPWM_TOPICR5 ((1 << WGM53) | (1 << WGM52) | (1 << WGM51))				//FASTPWM, TOP - ICR5
#define TIMER5_MODE_FASTPWM_TOPOCR5A ((1 << WGM43) | (1 << WGM52) | (1 << WGM51) | (1 << WGM50))//FASTPWM, TOP - OCR5A


//-------------------------------------------------------------------------TIMER DIVIDERS---------------------------------------------------------------------------------------

//																			TIMER0	
#define TIMER0_CLOCK_NONE 0														//T/C STOPPED
#define TIMER0_CLOCK_1 (1 << CS00)												//NO PRESCALING
#define TIMER0_CLOCK_8 (1 << CS01)												//FROM PRESCALER, CLK/8
#define TIMER0_CLOCK_64 ((1 << CS00) | (1 << CS01))								//FROM PRESCALER, CLK/64
#define TIMER0_CLOCK_256 (1 << CS02)											//FROM PRESCALER, CLK/256
#define TIMER0_CLOCK_1024 ((1 << CS02) | (1 << CS00)							//FROM PRESCALER, CLK/1024
#define TIMER0_CLOCK_EXTERNAL_FALLING ((1 << CS02) | (1 << CS01))				//EXTERNAL SOURCE ON T0
#define TIMER0_CLOCK_EXTERNAL_RISING ((1 << CS02) | (1 << CS01) | (CS00))		//EXTERNAL SOURCE ON T0

//																			TIMER1
#define TIMER1_CLOCK_NONE 0														//T/C STOPPED
#define TIMER1_CLOCK_1	(1 << CS10)												//NO PRESCALING
#define TIMER1_CLOCK_8 (1 << CS11)												//FROM PRESCALER, CLK/8
#define TIMER1_CLOCK_64 ((1 << CS10) | (1 << CS11))								//FROM PRESCALER, CLK/64
#define TIMER1_CLOCK_256 (1 << CS12)											//FROM PRESCALER, CLK/256
#define TIMER1_CLOCK_1024 ((1 << CS12) | (1 << CS10))							//FROM PRESCALER, CLK/1024
#define TIMER1_CLOCK_EXTERNAL_FALLING ((1 << CS11) | (1 << CD12)				//EXTERNAL SOURCE ON T1
#define TIMER1_CLOCK_EXTERNAL_RISING ((1 << CS10) | (1 << CS11) | (1 << CD12))	//EXTERNAL SOURCE ON T1

//																			TIMER2
#define TIMER2_CLOCK_NONE 0														//T/C STOPPED
#define TIMER2_CLOCK_1	(1 << CS20)												//NO PRESCALING
#define TIMER2_CLOCK_8 (1 << CA21)												//FROM PRESCALER, CLK/8
#define TIMER2_CLOCK_32 ((1 << CS20) | (1 << CA21))								//FROM PRESCALER, CLK/32
#define TIMER2_CLOCK_64 (1 << CA22)												//FROM PRESCALER, CLK/64
#define TIMER2_CLOCK_128 ((1 << CS20) | (1 << CA22))							//FROM PRESCALER, CLK/128
#define TIMER2_CLOCK_256 ((1 << CA21) | 1 << CA22))								//FROM PRESCALER, CLK/256
#define TIMER2_CLOCK_1024 ((1 << CA22) | (1 << CA21) | (1 << CS20))				//FROM PRESCALER, CLK/1024

//																			TIMER3
#define TIMER3_CLOCK_NONE 0														//T/C STOPPED
#define TIMER3_CLOCK_1	(1 << CS30)												//NO PRESCALING
#define TIMER3_CLOCK_8 (1 << CS31)												//FROM PRESCALER, CLK/8
#define TIMER3_CLOCK_64 ((1 << CS30) | (1 << CS31))								//FROM PRESCALER, CLK/64
#define TIMER3_CLOCK_256 (1 << CS32)											//FROM PRESCALER, CLK/256
#define TIMER3_CLOCK_1024 ((1 << CS32) | (1 << CS30))							//FROM PRESCALER, CLK/1024
#define TIMER3_CLOCK_EXTERNAL_FALLING ((1 << CS31) | (1 << CD32)				//EXTERNAL SOURCE ON T3
#define TIMER3_CLOCK_EXTERNAL_RISING ((1 << CS30) | (1 << CS31) | (1 << CD32))	//EXTERNAL SOURCE ON T3

//																			TIMER4
#define TIMER4_CLOCK_NONE 0														//T/C STOPPED
#define TIMER4_CLOCK_1	(1 << CS40)												//NO PRESCALING
#define TIMER4_CLOCK_8 (1 << CS41)												//FROM PRESCALER, CLK/8
#define TIMER4_CLOCK_64 ((1 << CS40) | (1 << CS41))								//FROM PRESCALER, CLK/64
#define TIMER4_CLOCK_256 (1 << CS42)											//FROM PRESCALER, CLK/256
#define TIMER4_CLOCK_1024 ((1 << CS42) | (1 << CS40))							//FROM PRESCALER, CLK/1024
#define TIMER4_CLOCK_EXTERNAL_FALLING ((1 << CS41) | (1 << CD42)				//EXTERNAL SOURCE ON T4
#define TIMER4_CLOCK_EXTERNAL_RISING ((1 << CS40) | (1 << CS41) | (1 << CD42))	//EXTERNAL SOURCE ON T4

//																			TIMER5
#define TIMER5_CLOCK_NONE 0														//T/C STOPPED
#define TIMER5_CLOCK_1	(1 << CS50)												//NO PRESCALING
#define TIMER5_CLOCK_8 (1 << CS51)												//FROM PRESCALER, CLK/8
#define TIMER5_CLOCK_64 ((1 << CS50) | (1 << CS51))								//FROM PRESCALER, CLK/64
#define TIMER5_CLOCK_256 (1 << CS52)											//FROM PRESCALER, CLK/256
#define TIMER5_CLOCK_1024 ((1 << CS52) | (1 << CS50))							//FROM PRESCALER, CLK/1024
#define TIMER5_CLOCK_EXTERNAL_FALLING ((1 << CS51) | (1 << CD52)				//EXTERNAL SOURCE ON T5
#define TIMER5_CLOCK_EXTERNAL_RISING ((1 << CS50) | (1 << CS51) | (1 << CD52))	//EXTERNAL SOURCE ON T5
//If external pin modes are used for the Timer/Counter0, transitions on the T0 pin 
//will clock the counter even if the pin is configured as an output. This feature allows software control of the counting

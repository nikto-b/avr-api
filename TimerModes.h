
//--------TIMER-MODES----
#pragma message "timer mode table for atmega328p, fill it with datasheet for your mcu"
//								TIMER0
#define TIMER0_MODE_NORMAL 0
#define TIMER0_MODE_PWM_PHC (1 << WGM00)
#define TIMER0_MODE_CTC (1 << WGM01)
#define TIMER0_MODE_FASTPWM ((1 << WGM00) | (1 << WGM01))
#define TIMER0_MODE_PWM_PHC_TOPOCRA ((1 << WGM02) | (1 << WGM00))
#define TIMER0_MODE_FASTPWM_TOPOCRA ((1 << WGM02) | (1 << WGM01) | (1 << WGM00))
//								TIMER1
#define TIMER1_MODE_NORMAL 0		
#define TIMER1_MODE_PWM_PHC_8B (1 << WGM10)														//PWM PHASE CORRECT
#define TIMER1_MODE_PWM_PHC_9B (1 << WGM11)
#define TIMER1_MODE_PWM_PHC_10B ((1 << WGM10) | (1 << WGM11))
#define TIMER1_MODE_CTC_TOPOCR1A (1 << WGM12)													//CLEAR-ON-COMPARE; TOP - OCR1A
#define TIMER1_MODE_FASTPWM_8B ((1 << WGM10) | (1 << WGM12))									//FAST-PWM
#define TIMER1_MODE_FASTPWM_9B ((1 << WGM11) | (1 << WGM12))
#define TIMER1_MODE_FASTPWM_10B ((1 << WGM10) | (1 << WGM11) | (1 << WGM12))
#define TIMER1_MODE_PWM_PHFRC_TOPICR1 (1 << WGM13)												//PWM PHASE AND FREQUENCY CORRECT; TOP - ICR1
#define TIMER1_MODE_PWM_PHFRC_TOPOCR1A ((1 << WGM13) | (1 << WGM10))							//TOP - OCR1A
#define TIMER1_MODE_PWM_PHC_TOPICR1 ((1 << WGM11) | (1 << WGM13))								//PWM PHASE CORRECT; TOP - ICR1
#define TIMER1_MODE_PWM_PHC_TOPOCR1A ((1 << WGM10) | (1 << WGM11) | (1 << WGM13))				//TOP - OCR1A
#define TIMER1_MODE_CTC_TOPICR1 ((1 << WGM12) | (1 << WGM13))									//CLEAR-ON-COMPARE; TOP - ICR1
#define TIMER1_MODE_FASTPWM_TOPICR1 ((1 << WGM13) | (1 << WGM12) | (1 << WGM11))				//FASTPWM; TOP - ICR1
#define TIMER1_MODE_FASTPWM_TOPOCR1A ((1 << WGM13) | (1 << WGM12) | (1 << WGM11) | (1 << WGM10))//FASTPWM; TOP - OCR1A
//								TIMER2
#define TIMER2_MODE_NORMAL 0
#define TIMER2_MODE_PWM_PHC (1 << WGM20)
#define TIMER2_MODE_CTC (1 << WGM21)
#define TIMER2_MODE_FASTPWM ((1 << WGM20) | (1 << WGM21))
#define TIMER2_MODE_PWM_PHC_TOPOCRA ((1 << WGM22) | (1 << WGM20))
#define TIMER2_MODE_FASTPWM_TOPOCRA ((1 << WGM22) | (1 << WGM21) | (1 << WGM20))

//----------------TIMER DIVIDERS--------------------
//								TIMER0	
#define TIMER0_CLOCK_NONE 0														//T/C STOPPED
#define TIMER0_CLOCK_1 (1 << CS00)												//NO PRESCALING
#define TIMER0_CLOCK_8 (1 << CS01)												//FROM PRESCALER
#define TIMER0_CLOCK_64 ((1 << CS00) | (1 << CS01))								//FROM PRESCALER
#define TIMER0_CLOCK_256 (1 << CS02)											//FROM PRESCALER
#define TIMER0_CLOCK_1024 ((1 << CS02) | (1 << CS00)							//FROM PRESCALER
#define TIMER0_CLOCK_EXTERNAL_FALLING ((1 << CS02) | (1 << CS01))				//EXTERNAL SOURCE ON T0
#define TIMER0_CLOCK_EXTERNAL_RISING ((1 << CS02) | (1 << CS01) | (CS00))		//EXTERNAL SOURCE ON T0
//								TIMER1
#define TIMER1_CLOCK_NONE 0														//T/C STOPPED
#define TIMER1_CLOCK_1	(1 << CS10)												//NO PRESCALING
#define TIMER1_CLOCK_8 (1 << CS11)												//FROM PRESCALER
#define TIMER1_CLOCK_64 ((1 << CS10) | (1 << CS11))								//FROM PRESCALER
#define TIMER1_CLOCK_256 (1 << CS12)											//FROM PRESCALER
#define TIMER1_CLOCK_1024 ((1 << CS12) | (1 << CS10))							//FROM PRESCALER
#define TIMER1_CLOCK_EXTERNAL_FALLING ((1 << CS11) | (1 << CD12)				//EXTERNAL SOURCE ON T1
#define TIMER1_CLOCK_EXTERNAL_RISING ((1 << CS10) | (1 << CS11) | (1 << CD12))	//EXTERNAL SOURCE ON T1
//								TIMER2
#define TIMER2_CLOCK_NONE 0														//T/C STOPPED
#define TIMER2_CLOCK_1	(1 << CS20)												//NO PRESCALING
#define TIMER2_CLOCK_8 (1 << CA21)												//FROM PRESCALER
#define TIMER2_CLOCK_32 ((1 << CS20) | (1 << CA21))								//FROM PRESCALER
#define TIMER2_CLOCK_64 (1 << CA22)												//FROM PRESCALER
#define TIMER2_CLOCK_128 ((1 << CS20) | (1 << CA22))							//FROM PRESCALER
#define TIMER2_CLOCK_256 ((1 << CA21) | 1 << CA22))								//FROM PRESCALER
#define TIMER2_CLOCK_1024 ((1 << CA22) | (1 << CA21) | (1 << CS20))				//FROM PRESCALER
//If external pin modes are used for the Timer/Counter0, transitions on the T0 pin 
//will clock the counter even if the pin is configured as an output. This feature allows software control of the counting

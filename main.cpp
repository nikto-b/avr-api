#include <avr/io.h>			//include for base avr funcs
#define F_CPU 16000000		//define with freq
#include <util/delay.h> 	//include for delay func
#include <avr/interrupt.h>	//include interrupt funcs
#include <stdlib.h>

#define NUM_OF_ANALOG_PINS 7
#define ARDUINO_SUPPORT 0
#define USE_FUNC_INPUT_PROTECTOR 0

//-----------ADC-----------
#define USE_ADC 1
#define USE_ADC_8BIT 1
#define ADC_MODE ADC_MODE_DEADLINE
#define ADC_DEF_PRESCALLER ADC_PRESCALLER_128

//---------TIMERS----------
#define USE_TIMERS 1
#define TIMER0_USE_COMPA 0
#define TIMER5_USE_COMPA 0
#define TIMER3_USE_COMPA 0

//---------USART----------
#define EOL "\n\r"
#define USE_USART 1
#define USE_USART0 1
#define USE_USART0_OUTPUT 1
#define USE_USART0_INPUT 1
#define USE_SERIAL_FASTBAUD 0

//---------CUSTOM_INTERRUPTS----------
#define USE_CUSTOM_INTERRUPTS 1


#define USE_WATCHDOG 1

#include "./api.h"//custom lib for AVR
#define DEBUG					0

#define _TWI_ACK				1
#define _TWI_NACK				0
#define _TWI_MASTER_BUF_LEN		255
#define _TWI_IN_BUF_LEN			255
#define _TWI_OUT_BUF_LEN		255
#define I2C_WRITE				0
#define I2C_READ				1
#define I2C_STANDBY				2
#define I2C_FAIL				3

/*************************** REGISTER MAP ***************************/
#define ADXL345_DEVID			0x00		// Device ID
#define ADXL345_RESERVED1		0x01		// Reserved. Do Not Access. 
#define ADXL345_THRESH_TAP		0x1D		// Tap Threshold. 
#define ADXL345_OFSX			0x1E		// X-Axis Offset. 
#define ADXL345_OFSY			0x1F		// Y-Axis Offset.
#define ADXL345_OFSZ			0x20		// Z- Axis Offset.
#define ADXL345_DUR				0x21		// Tap Duration.
#define ADXL345_LATENT			0x22		// Tap Latency.
#define ADXL345_WINDOW			0x23		// Tap Window.
#define ADXL345_THRESH_ACT		0x24		// Activity Threshold
#define ADXL345_THRESH_INACT	0x25		// Inactivity Threshold
#define ADXL345_TIME_INACT		0x26		// Inactivity Time
#define ADXL345_ACT_INACT_CTL	0x27		// Axis Enable Control for Activity and Inactivity Detection
#define ADXL345_THRESH_FF		0x28		// Free-Fall Threshold.
#define ADXL345_TIME_FF			0x29		// Free-Fall Time.
#define ADXL345_TAP_AXES		0x2A		// Axis Control for Tap/Double Tap.
#define ADXL345_ACT_TAP_STATUS	0x2B		// Source of Tap/Double Tap
#define ADXL345_BW_RATE			0x2C		// Data Rate and Power mode Control
#define ADXL345_POWER_CTL		0x2D		// Power-Saving Features Control
#define ADXL345_INT_ENABLE		0x2E		// Interrupt Enable Control
#define ADXL345_INT_MAP			0x2F		// Interrupt Mapping Control
#define ADXL345_INT_SOURCE		0x30		// Source of Interrupts
#define ADXL345_DATA_FORMAT		0x31		// Data Format Control
#define ADXL345_DATAX0			0x32		// X-Axis Data 0
#define ADXL345_DATAX1			0x33		// X-Axis Data 1
#define ADXL345_DATAY0			0x34		// Y-Axis Data 0
#define ADXL345_DATAY1			0x35		// Y-Axis Data 1
#define ADXL345_DATAZ0			0x36		// Z-Axis Data 0
#define ADXL345_DATAZ1			0x37		// Z-Axis Data 1
#define ADXL345_FIFO_CTL		0x38		// FIFO Control
#define ADXL345_FIFO_STATUS		0x39		// FIFO Status

#define ADXL345_BW_1600			0xF			// 1111		IDD = 40uA
#define ADXL345_BW_800			0xE			// 1110		IDD = 90uA
#define ADXL345_BW_400			0xD			// 1101		IDD = 140uA
#define ADXL345_BW_200			0xC			// 1100		IDD = 140uA
#define ADXL345_BW_100			0xB			// 1011		IDD = 140uA 
#define ADXL345_BW_50			0xA			// 1010		IDD = 140uA
#define ADXL345_BW_25			0x9			// 1001		IDD = 90uA
#define ADXL345_BW_12_5		    0x8			// 1000		IDD = 60uA 
#define ADXL345_BW_6_25			0x7			// 0111		IDD = 50uA
#define ADXL345_BW_3_13			0x6			// 0110		IDD = 45uA
#define ADXL345_BW_1_56			0x5			// 0101		IDD = 40uA
#define ADXL345_BW_0_78			0x4			// 0100		IDD = 34uA
#define ADXL345_BW_0_39			0x3			// 0011		IDD = 23uA
#define ADXL345_BW_0_20			0x2			// 0010		IDD = 23uA
#define ADXL345_BW_0_10			0x1			// 0001		IDD = 23uA
#define ADXL345_BW_0_05			0x0			// 0000		IDD = 23uA


 /************************** INTERRUPT PINS **************************/
#define ADXL345_INT1_PIN		0x00		//INT1: 0
#define ADXL345_INT2_PIN		0x01		//INT2: 1


 /********************** INTERRUPT BIT POSITION **********************/
#define ADXL345_INT_DATA_READY_BIT		0x07
#define ADXL345_INT_SINGLE_TAP_BIT		0x06
#define ADXL345_INT_DOUBLE_TAP_BIT		0x05
#define ADXL345_INT_ACTIVITY_BIT		0x04
#define ADXL345_INT_INACTIVITY_BIT		0x03
#define ADXL345_INT_FREE_FALL_BIT		0x02
#define ADXL345_INT_WATERMARK_BIT		0x01
#define ADXL345_INT_OVERRUNY_BIT		0x00

#define ADXL345_DATA_READY				0x07
#define ADXL345_SINGLE_TAP				0x06
#define ADXL345_DOUBLE_TAP				0x05
#define ADXL345_ACTIVITY				0x04
#define ADXL345_INACTIVITY				0x03
#define ADXL345_FREE_FALL				0x02
#define ADXL345_WATERMARK				0x01
#define ADXL345_OVERRUNY	0x00


//system vars
volatile uint8_t _twi_master_buf [_TWI_MASTER_BUF_LEN];
volatile uint8_t _twi_master_len		= 0;
volatile uint8_t _twi_initial_packet	= 0;
volatile uint8_t _twi_tx_len			= 0;
volatile uint8_t _twi_rx_len			= 0;

//input  vars
volatile uint8_t _twi_in_buf	 [_TWI_IN_BUF_LEN];
volatile uint8_t _twi_in_lens_buf[_TWI_IN_BUF_LEN];
volatile uint8_t _twi_in_len 			= 0;
volatile uint8_t _twi_in_lens_len 		= 0;

//output vars
volatile uint8_t _twi_out_buf	 [_TWI_OUT_BUF_LEN];
volatile uint8_t _twi_out_lens_buf[_TWI_OUT_BUF_LEN];
volatile uint8_t _twi_out_len			= 0;
volatile uint8_t _twi_out_lens_len	 	= 0;

volatile uint8_t _twi_err				= 0;

volatile int16_t _r16					= 0;
volatile uint8_t _twi_status			= I2C_STANDBY;

/*
 * Function I2C_SetFreq
 * Desc     Set working frequency of I2C bus
 * Input    _freq: what frequency set to
 * Output   none
*/
void I2C_SetFreq(uint8_t _freq)
{
	TWBR = _freq;
}

uint8_t I2C_GetError(void)
{
	return _twi_err;
}

void I2C_SetRxLen(uint8_t _len)
{
	_twi_rx_len = _len;
}

/*
 * Function _twi_start
 * Desc     Send start to TWI and do some buffer-cpy work
 * Input    none
 * Output   none
*/
void _twi_start(void)
{
	#if DEBUG == 1
		USART0Println("start");
		USART0Print("len:");
		USART0Println(_twi_in_lens_buf[_twi_in_lens_len - 1]);
		USART0Print("init:");
		USART0Println(_twi_in_buf[0]);
	#endif
	if(_twi_status == I2C_STANDBY
	|| _twi_status == I2C_FAIL)
	{
		_twi_initial_packet = _twi_in_buf[0];
		#if DEBUG == 1
			USART0Print("init");
			USART0Println(_twi_initial_packet);
		#endif
		_twi_status = (_twi_initial_packet & 1)? I2C_READ : I2C_WRITE;//I2C_READ if true, I2C_WRITE if false
												//because _twi_initial_packet = (slave_addr << 1) | (1 if READ, 0 if WRITE)
		#if DEBUG == 1
			USART0Print("s ");
			USART0Print((_twi_status == 1)? "READ" : "WRITE");
			USART0Println();
		#endif //if DEBUG == 1
		//if(_twi_status == I2C_WRITE)
		//{
			_twi_tx_len = _twi_in_lens_buf[_twi_in_lens_len - 1] - 1;
			#if DEBUG == 1
				USART0Println(_twi_tx_len);
			#endif //if DEBUG == 1
		//}
		if(_twi_status == I2C_WRITE)
		{
			for(int i = 0; i < _twi_tx_len; i++)
			{
				_twi_master_buf[i] = _twi_in_buf[i + 1];
				#if DEBUG == 1
					USART0Print("set ");
					USART0Print(_twi_master_buf[i]);
					USART0Print(" to ");
					USART0Println(i);
				#endif
				_twi_in_buf[i] = _twi_in_buf[i + _twi_tx_len + 1];		//MORE OPTIMIZATIONS!!!
			}
		}
		else if(_twi_status == I2C_READ)
		{
			_twi_rx_len = _twi_in_buf[1];
			_twi_tx_len = 0;
			_twi_in_len -= 1;
			for(int i = 0; i < _twi_in_len - 1; i++)
			{
				_twi_in_buf[i] = _twi_in_buf[i + 2];
			}
		}
		for(int i = _twi_tx_len; i < _twi_in_len; i++)
		{
			_twi_in_buf[i] = _twi_in_buf[i + _twi_in_lens_buf[_twi_in_lens_len - 1]];
		}
		_twi_in_len -= _twi_tx_len + 1;
		_twi_master_len = 0;
		_twi_in_lens_len--;
		for(int i = 0; i <= _twi_in_lens_len; i++)
		{
			_twi_in_lens_buf[i] = _twi_in_lens_buf[i + 1];
		}
		TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE);//sent start, enable interrupt, enable TWI
	}
	else
	{
		USART0Print("start fail\n\rstatus:");
		USART0Println(_twi_status);
	}
}

/*
 * Function _twi_stop
 * Desc     Sendstop to TWI and copy recieved bytes if have
 * Input    none
 * Output   none
*/
void _twi_stop(void)
{
	TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWSTO);
	#if DEBUG == 1
		USART0Println("stop");
		USART0Print("M:");
		USART0Println((char*)(((_twi_initial_packet & 1) == 1)? "R" : "W"));
	#endif
	if(_twi_status == I2C_READ)
	{
		#if DEBUG == 1
			USART0Println(_twi_master_buf[0]);
			USART0Print("twol ");
			USART0Print(_twi_out_len);
			USART0Print("twml ");
			USART0Println(_twi_master_len);
		#endif //if DEBUG == 1
		for(int i = _twi_out_len; i <= _twi_out_len + (_twi_rx_len); i++)
		{
			//_twi_master_len--;
			#if DEBUG == 1
				USART0Print("i:");
				USART0Println(i);
				USART0Print("outlen:");
				USART0Println(_twi_out_len);
			#endif //if DEBUG == 1
			_twi_out_buf[i] = _twi_master_buf[i - _twi_out_len];
		}
		_twi_out_len += _twi_rx_len;
		#if DEBUG == 1
			USART0Println(_twi_out_buf[0]);
			USART0Println(_twi_out_len);
		#endif //if DEBUG == 1
	}
	if(_twi_status != I2C_FAIL)
	{
		_twi_status = I2C_STANDBY;
	}
	if(_twi_in_len != 0)
	{
		if(_twi_status != I2C_FAIL)
		{
			#if DEBUG == 1
				USART0Println("pst");	
			#endif //if DEBUG == 1
			_twi_start();
		}
		else
		{
			USART0Println("pst fail\ncleanup...");
			_twi_in_len = 0;
			_twi_in_lens_len--;
		}
	}
}

/*
 * Function _twi_reply
 * Desc     Send reply on I2C(ACK or NACK)
 * Input    _ack: send ACK or NACK
 * Output   none
*/
void _twi_reply(uint8_t _ack)
{
	if(_ack)
	{
		TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWEA);
	}
	else
	{
		TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT);
	}
}

/*
 * Function I2C_Write
 * Desc     Send byte to TWI buf for transfering to I2C bus
 * Input    _in: byte to transfer
 * Output   none
*/
void I2C_Write(uint8_t _in)
{
	#if DEBUG == 1
		USART0Print("send ");
		USART0Print(_in);
		USART0Print(" to ");
		USART0Println(_twi_in_len);
	#endif //if DEBUG == 1
	_twi_in_buf[_twi_in_len] = _in;
	_twi_in_len++;
	_twi_in_lens_buf[_twi_in_lens_len - 1]++;
}

/*
 * Function I2C_Read
 * Desc		Read recieved byte from iic, 
 * 			wait if have no recieved but 
 * 			TWI working. ret 0 if no data 
 * 			in buf or TWI fail
 * Input	none
 * Output	none
*/
uint8_t I2C_Read(void)
{
	#if DEBUG == 1
		USART0Println("I2C_READ");
		USART0Print("outlen:");
		USART0Println(_twi_out_len);
		USART0Print("stat:");
		USART0Println(_twi_status);
	#endif //if DEBUG == 1
	cli();
	if((_twi_out_len > 0) || (_twi_out_len == 0 && _twi_status != I2C_STANDBY))
	{
		//#if DEBUG == 1
			//USART0Println("WAIT");
			//USART0Println(_twi_status);
			//USART0Println(_twi_out_len);
			//USART0Println(_twi_out_buf[0]);
			//USART0Println(_twi_out_buf[1]);
			//USART0Println(_twi_out_buf[2]);
			//USART0Println(_twi_out_buf[_twi_out_len]);
		//#endif //if DEBUG == 1
		while(_twi_out_len == 0 && _twi_status != I2C_STANDBY)
		{
			sei();
			if(_twi_status == I2C_FAIL)
			{
				//#if DEBUG == 1
					USART0Println("F1");
				//#endif //if DEBUG == 1
				return 0;
			}
		}//wait for byte
		if(_twi_out_len != 0 && _twi_status == I2C_STANDBY)
		{
			#if DEBUG == 1
				for(int i = 0; i < 8; i++)
				{
					USART0Print(i);
					USART0Print(" ");
					USART0Println(_twi_out_buf[i]);
				}
			#endif //if DEBUG == 1
			uint8_t _res = _twi_out_buf[0];
			_twi_out_len--;
			for(int i = 0; i <= _twi_out_len; i++)
			{
				_twi_out_buf[i] = _twi_out_buf[i + 1];
			}
			return _res;//_twi_out_buf[_twi_out_len];
		}
		else
		{
			USART0Println("F2");
			sei();
			return 0;
		}
	}
	else
	{
		//#if DEBUG == 1
			USART0Println("F3");
		//#endif //if DEBUG == 1
		sei();
		return 0;
	}
}

/*
 * Function I2C_BuildPacket
 * Desc     Build initial packet and  prepare buffers for data
 * Input    _addr: slave device addres
 * 			_mode: what mode will it use(Read or Write)
 * Output   none
*/
void I2C_BuildPacket(uint8_t _addr, uint8_t _mode)
{
	_twi_in_lens_len++;
	I2C_Write((_addr << 1) | (_mode & 1));
}


void I2C_BuildRead(uint8_t _addr, uint8_t _len)
{
	I2C_BuildPacket(_addr, I2C_READ);
	I2C_Write(_len);
}



enum regAddr
	{
	  SYSRANGE_START                              = 0x00,
	  SYSTEM_THRESH_HIGH                          = 0x0C,
	  SYSTEM_THRESH_LOW                           = 0x0E,
	  SYSTEM_SEQUENCE_CONFIG                      = 0x01,
	  SYSTEM_RANGE_CONFIG                         = 0x09,
	  SYSTEM_INTERMEASUREMENT_PERIOD              = 0x04,
	  SYSTEM_INTERRUPT_CONFIG_GPIO                = 0x0A,
	  GPIO_HV_MUX_ACTIVE_HIGH                     = 0x84,
	  SYSTEM_INTERRUPT_CLEAR                      = 0x0B,
	  RESULT_INTERRUPT_STATUS                     = 0x13,
	  RESULT_RANGE_STATUS                         = 0x14,
	  RESULT_CORE_AMBIENT_WINDOW_EVENTS_RTN       = 0xBC,
	  RESULT_CORE_RANGING_TOTAL_EVENTS_RTN        = 0xC0,
	  RESULT_CORE_AMBIENT_WINDOW_EVENTS_REF       = 0xD0,
	  RESULT_CORE_RANGING_TOTAL_EVENTS_REF        = 0xD4,
	  RESULT_PEAK_SIGNAL_RATE_REF                 = 0xB6,
	  ALGO_PART_TO_PART_RANGE_OFFSET_MM           = 0x28,
	  I2C_SLAVE_DEVICE_ADDRESS                    = 0x8A,
	  MSRC_CONFIG_CONTROL                         = 0x60,
	  PRE_RANGE_CONFIG_MIN_SNR                    = 0x27,
	  PRE_RANGE_CONFIG_VALID_PHASE_LOW            = 0x56,
	  PRE_RANGE_CONFIG_VALID_PHASE_HIGH           = 0x57,
	  PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT          = 0x64,
	  FINAL_RANGE_CONFIG_MIN_SNR                  = 0x67,
	  FINAL_RANGE_CONFIG_VALID_PHASE_LOW          = 0x47,
	  FINAL_RANGE_CONFIG_VALID_PHASE_HIGH         = 0x48,
	  FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT = 0x44,
	  PRE_RANGE_CONFIG_SIGMA_THRESH_HI            = 0x61,
	  PRE_RANGE_CONFIG_SIGMA_THRESH_LO            = 0x62,
	  PRE_RANGE_CONFIG_VCSEL_PERIOD               = 0x50,
	  PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI          = 0x51,
	  PRE_RANGE_CONFIG_TIMEOUT_MACROP_LO          = 0x52,
	  SYSTEM_HISTOGRAM_BIN                        = 0x81,
	  HISTOGRAM_CONFIG_INITIAL_PHASE_SELECT       = 0x33,
	  HISTOGRAM_CONFIG_READOUT_CTRL               = 0x55,
	  FINAL_RANGE_CONFIG_VCSEL_PERIOD             = 0x70,
	  FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI        = 0x71,
	  FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO        = 0x72,
	  CROSSTALK_COMPENSATION_PEAK_RATE_MCPS       = 0x20,
	  MSRC_CONFIG_TIMEOUT_MACROP                  = 0x46,
	  SOFT_RESET_GO2_SOFT_RESET_N                 = 0xBF,
	  IDENTIFICATION_MODEL_ID                     = 0xC0,
	  IDENTIFICATION_REVISION_ID                  = 0xC2,
	  OSC_CALIBRATE_VAL                           = 0xF8,
	  GLOBAL_CONFIG_VCSEL_WIDTH                   = 0x32,
	  GLOBAL_CONFIG_SPAD_ENABLES_REF_0            = 0xB0,
	  GLOBAL_CONFIG_SPAD_ENABLES_REF_1            = 0xB1,
	  GLOBAL_CONFIG_SPAD_ENABLES_REF_2            = 0xB2,
	  GLOBAL_CONFIG_SPAD_ENABLES_REF_3            = 0xB3,
	  GLOBAL_CONFIG_SPAD_ENABLES_REF_4            = 0xB4,
	  GLOBAL_CONFIG_SPAD_ENABLES_REF_5            = 0xB5,
	  GLOBAL_CONFIG_REF_EN_START_SELECT           = 0xB6,
	  DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD         = 0x4E,
	  DYNAMIC_SPAD_REF_EN_START_OFFSET            = 0x4F,
	  POWER_MANAGEMENT_GO1_POWER_FORCE            = 0x80,
	  VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV           = 0x89,
	  ALGO_PHASECAL_LIM                           = 0x30,
	  ALGO_PHASECAL_CONFIG_TIMEOUT                = 0x30,
};

ISR(TWI_vect)
{
	switch(TWSR)
	{
		case 0x00://bus fail
		{
				USART0Println("0x00");
			#if DEBUG == 1
			#endif //if DEBUG == 1
			_twi_err = 0x01;
			_twi_status = I2C_FAIL;
			_twi_stop();
			break;
		}
		case 0x08://start
		{
			#if DEBUG == 1
				USART0Println("0x08");
				USART0Print("M:");
				USART0Println((char*)((_twi_status == I2C_READ)? "R" : "W"));
				USART0Println(_twi_initial_packet);
			#endif //if DEBUG == 1
			TWDR = _twi_initial_packet; //send initial packet
			_twi_reply(_TWI_ACK);		//and reply ACK
			break;
		}
		case 0x10://reStart
		{
				USART0Println("0x10");
			#if DEBUG == 1
			#endif //if DEBUG == 1
			break;
		}
		case 0x28://byte+ACK
		{
			#if DEBUG == 1
				USART0Println("0x28");
			#endif //if DEBUG == 1
		}
		case 0x18://SLA+W+ACK
		{
			#if DEBUG == 1
				USART0Println("0x18");
				USART0Print("masl");
				USART0Println(_twi_master_len);
				USART0Print("txl");
				USART0Println(_twi_tx_len);
				
			#endif //if DEBUG == 1
			if(_twi_master_len < _twi_tx_len)
			{
				#if DEBUG == 1
					USART0Print("SEND ");
					USART0Println(_twi_master_buf[_twi_master_len]);
					USART0Print("i:");
					USART0Println(_twi_master_len);
				#endif //if DEBUG == 1
				TWDR = _twi_master_buf[_twi_master_len];
				_twi_master_len++;
				_twi_reply(_TWI_ACK);
			}
			else
			{
				#if DEBUG == 1
					USART0Println("STOP");
				#endif //if DEBUG == 1
				_twi_stop();
			}
			break;
		}
		case 0x20://SLA+W+NACK
		{
				USART0Println("0x20");
			#if DEBUG == 1
			#endif //if DEBUG == 1
			_twi_err = 0x20;
			_twi_status = I2C_FAIL;
			_twi_stop();
			break;
		}
		case 0x30://byte+NACK
		{
				USART0Println("0x30");
			#if DEBUG == 1
			#endif //if DEBUG == 1
			_twi_err = 0x30;
			_twi_status = I2C_FAIL;
			_twi_stop();
			break;
		}
		case 0x38://collision
		{
				USART0Println("0x38");
			#if DEBUG == 1
			#endif //if DEBUG == 1
			_twi_err = 0x38;
			_twi_status = I2C_FAIL;
			_twi_stop();
			break;
		}
		case 0x40://SLA+R+ACK
		{
				//USART0Println("0x40");
			#if DEBUG == 1
			#endif //if DEBUG == 1
			if(_twi_rx_len - _twi_master_len > 1)
			{
				_twi_reply(_TWI_ACK);
			}
			else
			{
				_twi_reply(_TWI_NACK);
			}
			break;
		}
		case 0x48://SLA+R+NACK
		{
				USART0Println("0x48");
			#if DEBUG == 1
			#endif //if DEBUG == 1
			_twi_err = 0x48;
			_twi_status = I2C_FAIL;
			_twi_stop();
			break;
		}
		case 0x50://recive byte
		{
				//USART0Println("0x50");
			#if DEBUG == 1
				USART0Print("R:");
				USART0Println(TWDR);
			#endif //if DEBUG == 1
			_twi_master_buf[_twi_master_len] = TWDR;
			_twi_master_len++;
			//_twi_rx_len--;
			
			if(_twi_rx_len - _twi_master_len > 1)
			{
				_twi_reply(_TWI_ACK);
			}
			else
			{
				_twi_reply(_TWI_NACK);
			}
			break;
		}
		case 0x58://recive byte+NACK
		{
				//USART0Println("0x58");
			#if DEBUG == 1
				USART0Print("R:");
				USART0Println(TWDR);
				USART0Print("ml");
				USART0Println(_twi_master_len);
			#endif //if DEBUG == 1
			_twi_master_buf[_twi_master_len] = TWDR;
			_twi_master_len++;
			_twi_stop();
			break;
		}
		default:
		{
			USART0Print("DEFAULT");
			USART0Println(TWSR);
			_twi_status = I2C_FAIL;
			_twi_stop();
		}
	}
}


uint8_t readReg(uint8_t _addr, uint8_t _reg)
{
	cli();
	uint8_t _res;
	I2C_BuildPacket(_addr, I2C_WRITE);
	I2C_Write(_reg);
	_twi_start();
	I2C_BuildRead(_addr, 1);
	_twi_start();
	_res = I2C_Read();
	sei();
	return _res;
}

uint16_t readReg16B(uint8_t _addr, uint8_t _reg)
{
	cli();
	uint16_t _res;
	I2C_BuildPacket(_addr, I2C_WRITE);
	I2C_Write(_reg);
	_twi_start();
	I2C_BuildRead(_addr, 2);
	_twi_start();
	USART0Println(_twi_out_buf[0]);
	USART0Println(_twi_out_buf[1]);
	_res = I2C_Read() << 8;
	_res |= I2C_Read();
	sei();
	return _res;
}

void writeReg(uint8_t _addr, uint8_t _reg, uint8_t _val)
{
	cli();
	I2C_BuildPacket(_addr, I2C_WRITE);
	I2C_Write(_reg);
	I2C_Write(_val);
	_twi_start();
	sei();
}

void writeReg16B(uint8_t _addr, uint8_t _reg, uint16_t _val)
{
	cli();
	I2C_BuildPacket(_addr, I2C_WRITE);
	I2C_Write(_reg);
	I2C_Write((_val >> 8) & 0xFF);
	I2C_Write(_val & 0xFF);
	_twi_start();
	sei();
}

uint64_t millis = 0;
uint8_t _millis = 0;


void timerfunc(void)
{
	_millis++;
	if(_millis >= 2)
	{
		millis++;
		_millis = 0;
	}
	//USART0Println("M");
}


/*
void setSignalRateLimit(uint8_t _addr, float _lim_mcps)
{
	
  if (_lim_mcps < 0 || _lim_mcps > 511.99) { return; }

	writeReg16Bit(_addr, FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, limit_Mcps * (1 << 7));

}

#define calcMacroPeriod(vcsel_period_pclks) ((((uint32_t)2304 * (vcsel_period_pclks) * 1655) + 500) / 1000)

uint32_t timeoutMicrosecondsToMclks(uint32_t timeout_period_us, uint8_t vcsel_period_pclks)
{
	uint32_t macro_period_ns = calcMacroPeriod(vcsel_period_pclks);
	return (((timeout_period_us * 1000) + (macro_period_ns / 2)) / macro_period_ns);
}

uint16_t encodeTimeout(uint16_t timeout_mclks)
{
	// format: "(LSByte * 2^MSByte) + 1"

	uint32_t ls_byte = 0;
	uint16_t ms_byte = 0;

	if (timeout_mclks > 0)
	{
		ls_byte = timeout_mclks - 1;

		while ((ls_byte & 0xFFFFFF00) > 0)
		{
			ls_byte >>= 1;
			ms_byte++;
		}

		return (ms_byte << 8) | (ls_byte & 0xFF);
	}
	else { return 0; }
}

void setMeasurementTimingBudget_us(uint8_t _addr, uint32_t _budget_us)
{
	uint16_t const StartOverhead      = 1320;
	uint16_t const EndOverhead        = 960;
	uint16_t const MsrcOverhead       = 660;
	uint16_t const TccOverhead        = 590;
	uint16_t const DssOverhead        = 690;
	uint16_t const PreRangeOverhead   = 660;
	uint16_t const FinalRangeOverhead = 550;

	uint32_t const MinTimingBudget = 20000;

	if (budget_us < MinTimingBudget) { return; }
	uint32_t used_budget_us = StartOverhead + EndOverhead;
}


enum vcselPeriodType { VcselPeriodPreRange, VcselPeriodFinalRange };


void setVcselPulsePeriod (vcselPeriodType type, uint8_t period_pclks)
{
	
}*/

#define encodeVcselPeriod(period_pclks) (((period_pclks) >> 1) - 1)
#define ADXL345_DEVICE (0x53)

void setRegBit(uint8_t _addr, uint8_t _reg, uint8_t _pos, uint8_t _state)
{
	uint8_t _b = 0;
	_b = readReg(_addr, _reg);
	if(_state)
	{
		_b |= (1 << _pos);
	}
	else
	{
		_b &= ~(1 << _pos);
	}
	writeReg(_addr, _reg, _b);
}

uint16_t readLen(uint8_t _addr)
{
	uint16_t var;
	writeReg(_addr, SYSRANGE_START, 0x01);
	delay(300);
	var = (readReg16B(_addr, RESULT_RANGE_STATUS + 10));
	writeReg(_addr, SYSTEM_INTERRUPT_CLEAR, 0x01);
	return var;
}

int main()
{
	DDRE = 255;
	DDRG = 255;
	DDRH = 255;
	DDRF = 255;
	PORTF = 255;
	PORTE = 0;


	for(int i = 0; i < 8; i++)
	{
		PORTF = (1 << i) | ((1 << i - 1) - 1);
		writeReg(0x29, 0x8A, 0x29 + i + 1);
	}
	PORTF = 255;
	//PORTF = ~((1 << PF0) | (1 << PF1) | (1 << PF2) | (1 << PF3) | (1 << PF4) | (1 << PF5) | (1 << PF6) | (1 << PF7));
	/*PORTE = 0;
	delay(100);
	PORTE = 1 << PE4;*/
	//srestart();
	//PORTD = (1 << PD0) | (1 << PD1);
	delay(100);
	sei();
	USART0Begin(115200);

	/*TCCR3A  = TIMER3_COMA_FPWM_CM_ST;
	TCCR3A |= TIMER3_WF_FPWM_TOPOCR3A;
	TCCR3B  = TIMER3_CLK_SRC_1;*/
	TIMER0Init(TIMER0_COMB_FPWM_CM_ST, TIMER0_WF_FPWM_TOPOCR0A, TIMER0_CLK_SRC_1);
	//TIMER3Init(TIMER3_COMA_FPWM_CM_ST)
	//OCR0B = 255; 

	//I2C_SetFreq(0x40);
	
				//LB
	/*TCCR3A=(1<<COM3A1)|(1<<WGM30);
	TCCR3B=(1<<CS30);	
	OCR3A = 1023;*/
	/*			//RF
	TCCR0A = (1 << COM0B1) | (1 << WGM30);
	TCCR0B = (1 << CS00);
	OCR0B = 1023;*/
	/*			//LF
	TCCR3A=(1<<COM3C1)|(1<<WGM30);
	TCCR3B=(1<<CS30);	
	OCR3C = 1023;*/
				//RB
	/*TCCR4A=(1<<COM4A1)|(1<<WGM40);
	TCCR4B=(1<<CS40);
	OCR4A = 1023;*/
	int var;
	
	loop:
	//goto loop;
	for(int i = 0; i < 256; i++)
	{
		OCR0B = i;
		delay(10);
	}
	for(int i = 255; i>= 0; i--)
	{
		OCR0B = i;
		delay(10);
	}
	/*
	writeReg(0x29, SYSRANGE_START, 0x01);
	delay(300);
	var = (readReg16B(0x29, RESULT_RANGE_STATUS + 10));
	writeReg(0x29, SYSTEM_INTERRUPT_CLEAR, 0x01);
	*/
	//delay(100);
	/*
	for(int i = 0; i < 8; i++)
	{
		USART0Println(readLen(0x29));
	}
	if(I2C_GetError())
	{
		USART0Println("STOP!!!");
		USART0Println("IN");
		for(int i = 0; i < _twi_in_len; i++)
		{
			USART0Print(i);
			USART0Send(':');
			USART0Println(_twi_in_buf[i]);
		}
		USART0Println("OUT");
		for(int i = 0; i < _twi_out_len; i++)
		{
			USART0Print(i);
			USART0Send(':');
			USART0Println(_twi_out_buf[i]);
		}
		USART0Println("MAS");
		for(int i = 0; i < _twi_master_len; i++)
		{
			USART0Print(i);
			USART0Send(':');
			USART0Println(_twi_master_buf[i]);
		}
		USART0Println("IN_LENS");
		for(int i = 0; i < _twi_in_lens_len; i++)
		{
			USART0Print(i);
			USART0Send(':');
			USART0Println(_twi_in_lens_buf[i]);
		}
		
		USART0Println();
		USART0Println(I2C_GetError());
		//srestart();
		while(1);
	}
	
	USART0Println();
	USART0Println();
	*/
	goto loop;

	//USART0Println(I2C_GetError());
	//USART0Println(I2C_Read());
	return 0;
}

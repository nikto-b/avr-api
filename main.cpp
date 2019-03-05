#include <avr/io.h>			//include for base avr funcs
#undef F_CPU
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
#define TIMER0_USE_COMPA 1
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


#define USE_WATCHDOG 0

#include "./api.h"				//custom lib for AVR
#define DEBUG					0

#define DISTANCE_METER_ARR_INDEX	1
/*
uint16_t lens[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t currI2CAddr = 0x00;
uint8_t addrs[8] = {0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53};
*/

#define NUM_OF_TOFS 8
volatile uint8_t addrs[NUM_OF_TOFS];
volatile uint16_t measures[NUM_OF_TOFS];
volatile uint16_t oscCalVal[NUM_OF_TOFS];
volatile uint8_t stopVars[NUM_OF_TOFS];
volatile uint8_t tofsRangeouted = 0;

inline void setTofRangeouted(uint8_t _tof, uint8_t _isR)
{
	tofsRangeouted &= ~(1 << _tof);
	tofsRangeouted |= (_isR & 1) << _tof;
}

inline uint8_t isTofRangeouted(uint8_t _tof)
{
	return (tofsRangeouted >> _tof) & 1;
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


#define _TWI_ACK				1
#define _TWI_NACK				0
#define _TWI_OUT_BUF_LEN		0xFF
#define _TWI_IN_BUF_LEN			0xFF
#define _TWI_USR_IN_BUF_LEN		0xFF
#define I2C_WRITE				0x00
#define I2C_READ				0x01
#define I2C_STANDBY				0x02
#define I2C_FAIL				0x03
#define I2C_RESTART_FAIL		0x04
#define I2C_DISABLED			0xFF

uint16_t	_twi_out_len = 0;
uint8_t		_twi_out_curr = 0;
uint16_t	_twi_in_len = 0;
uint16_t	_twi_usr_len = 0;
uint8_t		_twi_usr_packs = 0;
uint8_t		_twi_usr_lens = 0;
uint8_t 	_twi_out_queue[_TWI_OUT_BUF_LEN];
uint8_t 	_twi_in_queue[_TWI_IN_BUF_LEN];
uint8_t 	_twi_usr_in_queue[_TWI_USR_IN_BUF_LEN];
uint8_t		_twi_usr_in_lens[_TWI_USR_IN_BUF_LEN];

uint8_t		_twi_status = 0xFF;






/*
 * Function: I2C_SetFreq
 * Desc:     Set working frequency of I2C bus
 * Input:    _freq: what frequency set to
 * Output:   none
*/
inline void I2C_SetFreq(uint8_t _freq)
{
	TWBR = _freq;
}







/*
 *	Function:	shiftLeft
 *	Desc:		Shift some array to left on N elements
 *	Input:		void* arr: 		ptr to array shift to
 				uint8_t size:	size of element
 				uint32_t len: 	length of array
 				uint32_t el:	num of elements
 *	Output:		none
 */
void shiftLeft(uint8_t* arr, uint32_t len, uint32_t el)
{
	//cli();									//block interrupts, atomic block
	for(uint32_t i = 0; i < len - el; i++)
	{
		arr[i] = arr[i + el];
	}

	//sei();									//allow interrupts
}





/*
 *	Function:	shiftRight
 *	Desc:		Shift some array to right on N elements
 *	Input:		void* arr: ptr to array shift to
 				uint32_t len: length of array
 *	Output:		none
 */
void shiftRight(uint8_t* arr, uint32_t len, uint32_t el)
{
	//cli();									//block interrupts, atomic block

	//for(uint32_t i = len - el; i < len - el; i++)
	while(len >= el)
	{
		arr[len] = arr[len - el];
		len--;
	}

	//sei();									//allow interrupts
}






/*
 *	Function:	twiAddPack
 *	Desc:		Add package to user queue
 *	Input:		uint8_t  addr:			what addr of slave set to
 				const uint8_t* data:	pointer to data array
 				uint8_t len:			num of bytes in data array
 				uint8_t mode:			read or write mode use to
 *	Output:		none
 */
void twiAddPack(uint8_t addr, const uint8_t* data, uint8_t len, uint8_t mode)
{
	cli();										//block interrupts, must be atomic
	addr <<= 1;
	addr |= mode & 1;

	#if DEBUG == 1
		//USART0Print("addr:");
		//USART0Println(addr);
	#endif //if DEBUG == 1	
	_twi_usr_packs++;
	_twi_usr_in_queue[_twi_usr_len++] = addr;	//add addr of slave device to queue
	for(int i = 0; i < len; i++)				//iterate in data array and add all bytes in usr queue
	{
		#if DEBUG == 1
			//USART0Print("CP:");
			//USART0Println(data[i]);
		#endif //if DEBUG == 1
		_twi_usr_in_queue[_twi_usr_len++] = data[i];
	}
	_twi_usr_in_lens[_twi_usr_lens++] = len + 1;	//set num of bytes in pack
	sei();										//allow interrupts, atomic block ended
}






/*
 *	Function:	twiAddPack
 *	Desc:		Add package to user queue
 *	Input:		uint8_t  addr:		what addr of slave set to
 				uint8_t data:		byte send to
 				uint8_t mode:		read or write mode use to
 *	Output:		none
 */
void twiAddPack(uint8_t addr, uint8_t data, uint8_t mode)
{
	addr <<= 1;
	addr |= mode & 1;
	cli();										//block interrupts, must be atomic
	_twi_usr_packs++;
	_twi_usr_in_queue[_twi_usr_len++] = addr;	//add addr of slave device
	_twi_usr_in_queue[_twi_usr_len++] = data;	//				,byte to send
	_twi_usr_in_lens[_twi_usr_lens++] = 2;		//				and num of bytes in pack
	sei();										//allow interrupts, atomic block ended
}






/*
 *	Function:	twiGetByte
 *	Desc:		Get byte from input array(if have)
 *	Input:		none
 *	Output:		uint8_t: readed byte (0xFF if nothing to read)
 */
uint8_t twiGetByte(void)
{
	//USART0Println("reading byte from buf...");
	if(_twi_in_len > 0)
	{
		uint8_t _buf = _twi_in_queue[0];
		shiftLeft(_twi_in_queue, _twi_in_len--, 1);
		return _buf;
	}
	else
	{
		#if DEBUG == 1
			USART0Println("nothing to read");
		#endif //if DEBUG == 1
		return 0xFF;//nothing to read
	}
}






/*
 *	Function:	 _twi_reply
 *	Desc:		Send reply to TWI (ACK or NACK)
 *	Input:		uint8_t _ack: send ACK or NACK
 *	Output:		none
 */
void _twi_reply(uint8_t _ack)
{
	if(_ack == _TWI_ACK)
	{
		TWCR 	= (1 << TWEN) 	//enable TWI
				| (1 << TWIE) 	//set interrupt flag
				| (1 << TWINT) 	//allow interrupts
				| (1 << TWEA);	//allow ACK
	}
	else
	{
		TWCR 	= (1 << TWEN) 	//enable TWI
				| (1 << TWIE) 	//set interrupt flag
				| (1 << TWINT);	//allow interrupts
	}
}






/*
 *	Function:	
 *	Desc:		
 *	Input:		
 *	Output:		
 */
/*
 *	Function:	_twi_start
 *	Desc:		Start TWI for state machine
 *	Input:		none
 *	Output:		none
 */
inline void _twi_start(void)
{
	TWCR 	= (1 << TWSTA)	//forming start
			| (1 << TWINT)	//set interrupt flag
			| (1 << TWEN) 	//enable TWI
			| (1 << TWIE);	//allow interrupts
}






/*
 *	Function:	_twi_stop
 *	Desc:		Stop TWI for state machine
 *	Input:		none
 *	Output:		none
 */
inline void _twi_stop(void)
{
	TWCR 	= (1 << TWEN)	//enable TWI
			| (1 << TWIE)	//allow interrupts
			| (1 << TWINT)	//set interrupt flag
			| (1 << TWSTO);	//forming stop
}






/*
 *	Function:	twiStart
 *	Desc:		Start TWI state machine
 *	Input:		none
 *	Output:		none
 */
void twiStart(void)
{
	//cli();												//block interrupts, must be atomic

	if(_twi_status != I2C_READ
		&& _twi_status != I2C_WRITE)
	{
		uint8_t bytes = _twi_usr_in_lens[0];				//get num of bytes to send
		shiftLeft(_twi_usr_in_lens, _twi_usr_lens--, 1);	//shift array with lens of packs to left for 1 element
		//cli();		//TODO: fix
		for(uint8_t i = 0; i < bytes; i++)
		{													//iterate "bytes" times and copy package
			#if DEBUG == 1
				USART0Print("CP:");
				USART0Println(_twi_usr_in_queue[i]);
			#endif //if DEBUG == 1
			_twi_out_queue[i] = _twi_usr_in_queue[i];
		}
		shiftLeft(_twi_usr_in_queue, _twi_usr_len, bytes);//remove from user queue
		//cli();		//TODO: fix

		_twi_usr_len -= bytes;
		_twi_out_len = bytes;
		_twi_status = (_twi_out_queue[0] & 1)? I2C_READ : I2C_WRITE;//save status
		_twi_usr_packs--;
		_twi_start();										//kick the TWI machine
	}
	else
	{
		#if DEBUG == 1
			USART0Println("\t\t\t\t\t\t\t\ttrying to restart");
			USART0Print("status:");
			USART0Println(_twi_status);
		#endif //if DEBUG == 1
	}
	//sei();												//allow interrupts, atomic block ended
}





/*
 *	Function:	twiStop
 *	Desc:		Stop TWI state machine
 *	Input:		none
 *	Output:		none
 */
void twiStop(void)
{
	//cli();							//block interrupts, must be atomic

	#if DEBUG == 1
		USART0Println("to stb");
	#endif //if DEBUG == 1
	_twi_stop();					//go to standby
	_twi_status = I2C_STANDBY;
	_twi_out_len = 0;
	if(_twi_usr_packs > 0)
	{
		#if DEBUG == 1
			USART0Println("RESTART");
		#endif //if DEBUG == 1
		twiStart();					//kick state machine for new start
	}

	//sei();							//allow interrupts, atomic block ended
}






/*
 *	Function:	twiHadRead
 *	Desc:		If have new bytes to read return 1(t), else 0(f)
 *	Input:		none
 *	Output:		bool
 */
inline bool twiHadRead(void)
{
	return (_twi_in_len > 0);
}




ISR(TWI_vect)
{
	switch(TWSR)
	{
		case 0x00:												//bus fail
		{
			#if DEBUG == 1
				USART0Println("0x00");
			#endif //if DEBUG == 1
			_twi_status = I2C_FAIL;
			twiStop();
			break;
		}
		case 0x08:												//start
		{
			#if DEBUG == 1
				USART0Println("0x08");
				USART0Println(_twi_out_queue[0]);
				USART0Print("len:");
				USART0Println(_twi_out_len);
			#endif //if DEBUG == 1
			_twi_out_curr = 0;
			TWDR = _twi_out_queue[_twi_out_curr++];
			_twi_reply(_TWI_ACK);
			break;
		}
		case 0x10:												//reStart
		{
			#if DEBUG == 1
				USART0Println("0x10");
				USART0Println(_twi_out_queue[0]);
				USART0Print("len:");
				USART0Println(_twi_out_len);
			#endif //if DEBUG == 1
			_twi_out_curr = 0;
			TWDR = _twi_out_queue[_twi_out_curr++];
			_twi_reply(_TWI_ACK);
			break;
		}
		case 0x28:												//byte+ACK
		{
			#if DEBUG == 1
				USART0Println("0x28");
			#endif //if DEBUG == 1
		}
		case 0x18:												//SLA+W+ACK
		{
			#if DEBUG == 1
				USART0Println("0x18");
			#endif //if DEBUG == 1
			if(_twi_out_curr < _twi_out_len)
			{
				#if DEBUG == 1
					USART0Print("S:");
					USART0Println(_twi_out_queue[_twi_out_curr]);
				#endif //if DEBUG == 1
				TWDR = _twi_out_queue[_twi_out_curr++];
				_twi_reply(_TWI_ACK);
			}
			else
			{
				if(_twi_usr_packs == 0 || ((_twi_usr_in_queue[0])&1) == 0)
				{
					#if DEBUG == 1
						USART0Println("STOP");
					#endif //if DEBUG == 1
					twiStop();
				}
				else
				{
					#if DEBUG == 1
						USART0Println("Switching to read mode...");
					#endif //if DEBUG == 1
					//_twi_start();
					_twi_status = I2C_STANDBY;
					twiStart();
				}
				//_twi_reply(_TWI_NACK);
			}
			break;
		}
		case 0x20:												//SLA+W+NACK
		{
			#if DEBUG == 1
				USART0Println("0x20");
				USART0Println("\t\t\tFAIL");
				for(uint8_t i = 0; i < NUM_OF_TOFS; i++)
				{
					USART0Print(i);
					USART0Print("\t");
					USART0Println(addrs[i]);
				}
			#endif //if DEBUG == 1
				//handling of error
			if(_twi_status == I2C_READ) //TODO: TEST IT!
			{
				//for(uint8_t i = 0; i < _twi_out_queue[1]; i++)
					//_twi_in_queue[_twi_in_len++] = -1;
			}
			else if((_twi_usr_in_queue[0] & 1) == 0)
			{
				//USART0Println("bypassing errors on try-to-read");
				//for(uint8_t i = 0; i < _twi_usr_in_queue[1]; i++)
				//	_twi_in_queue[_twi_in_len++] = -1;
			}
			_twi_status = I2C_FAIL;
			twiStop();
			break;
		}
		case 0x30:												//byte+NACK
		{
			#if DEBUG == 1
				USART0Println("0x30");
			#endif //if DEBUG == 1
			_twi_status = I2C_FAIL;
			twiStop();
			break;
		}
		case 0x38:												//collision
		{
			#if DEBUG == 1
				USART0Println("0x38");
			#endif //if DEBUG == 1
			_twi_status = I2C_FAIL;
			twiStop();
			break;
		}
		case 0x40:												//SLA+R+ACK
		{
			#if DEBUG == 1
				USART0Println("0x40");
			#endif //if DEBUG == 1
			if(_twi_out_queue[1] <= 1)
				_twi_reply(_TWI_NACK);
			else
				_twi_reply(_TWI_ACK);
			break;
		}
		case 0x48:												//SLA+R+NACK
		{
			#if DEBUG == 1
				USART0Println("0x48");
			#endif //if DEBUG == 1
			_twi_status = I2C_FAIL;
			twiStop();
			break;
		}
		case 0x50:												//recive byte
		{
				//USART0Println("0x50");
			#if DEBUG == 1
				USART0Println("0x50");
				USART0Print("R");
				USART0Println((int)TWDR);
			#endif //if DEBUG == 1
			//USART0Print("\t\t\t");
			//USART0Println(_twi_in_len);
			_twi_in_queue[_twi_in_len++] = TWDR;
			//USART0Print("\t\tq");
			//USART0Println(_twi_out_queue[1]);
			_twi_out_queue[1]--;
			if(_twi_out_queue[1] <= 1)
				_twi_reply(_TWI_NACK);
			else
				_twi_reply(_TWI_ACK);
			break;
		}
		case 0x58:												//recive byte+NACK
		{
				//USART0Println("0x58");
			#if DEBUG == 1
				USART0Println("0x58");
				USART0Print("R:");
				USART0Println((int)TWDR);
			#endif //if DEBUG == 1
			//USART0Println(_twi_in_len);
			//USART0Print("\t\t\t");
			//USART0Println((int)TWDR);
			_twi_in_queue[_twi_in_len++] = TWDR;
			_twi_status = I2C_STANDBY;
			twiStop();
			break;
		}
		default:
		{
			USART0Print("DEFAULT");
			_twi_status = I2C_FAIL;
			twiStop();
		}
	}
}

void (*scheduleQueue[255])();
volatile uint8_t scheduleCounter = 0;
volatile uint8_t scheduleQueueLen = 0;






char* prepareVarMessage(uint8_t _reg, uint8_t _var)
{
	uint8_t _len = 4;

	uint8_t _t1 = getCountsOfDigits(_reg);
	uint8_t _t2 = getCountsOfDigits(_var);

	_len += _t1;
	_len += _t2;

	char* _ret = (char*)malloc(_len * sizeof(char));
	_ret[_len - 1] = '\0';								//null-terminator

	_ret[0] = '{';									//add beginning

	char* _t = byte2str(_reg);
	for(uint8_t i = 0; i < _t1; i++)					//copy reg part to ret
	{
		_ret[i + 1] = _t[i];
	}

	_ret[_t1 +  1] = ':';							//add spacing

	free(_t);
	
	_t = byte2str(_var);
	for(uint8_t i = 0; i < _t2; i++)					//copy var part to ret
	{
		_ret[i + 2 + _t1] = _t[i];
	}
	_ret[_len - 2] = '}';							//add ending
	free(_t);
	return _ret;
}

char* _prepareArrayMessage(uint8_t _reg, uint16_t* arr, uint32_t _arrLen)
{
	//USART0Println(_arrLen);
	uint32_t _len = 3;
	uint32_t _t1 = getCountsOfDigits(_reg);
	uint32_t _t2 = 0;
	for(uint32_t i = 0; i < _arrLen; i++)
	{
		_t2 += getCountsOfDigits(arr[i]);
	}
	_len += _t1 + _t2 + _arrLen;

	char* _ret = (char*)malloc(_len * sizeof(char));
	_ret[0] = '[';
	_ret[_len - 1] = '\0';

	char* _t = byte2str(_reg);	
	for(uint8_t i = 0; i < _t1; i++)					//copy reg part to ret
	{
		_ret[i + 1] = _t[i];
	}
	free(_t);
	_ret[_t1 +  1] = ':';							//add spacing
	uint32_t lastI = _t1 + 1;
	for(uint32_t i = 0; i < _arrLen; i++)
	{
		_t = int2str(arr[i]);
		for(uint32_t q = 0; q < getCountsOfDigits(arr[i]); q++)
		{
			_ret[++lastI] = _t[q];
		}
		_ret[++lastI] = ',';
		free(_t);
	}
	_ret[_len - 2] = ']';
	return _ret;
}

char* _prepareCmdMessage(char* _cmd, uint8_t _len)
{
	char* _ret = (char*)malloc(_len + 3);
	for(uint8_t i = 0; i < _len; i++)
	{
		_ret[i + 1] = _cmd[i]; 
	}
	_ret[_len + 2] = '\0';
	_ret[0] = '(';
	_ret[_len + 1] = ')';
	return _ret;
}

#define getByteCount(x)	(sizeof(*x))

#define prepareCmdMessage(x) _prepareCmdMessage(x, (sizeof(x) / getByteCount(x)) - 1)
#define prepareArrayMessage(x, y) _prepareArrayMessage(x, y, sizeof(y) / getByteCount(y))

#define sendSomeData(x) 							\
{													\
	char* _t = x;	/*run string-creator func*/		\
	USART0Println(_t);	/*send created string*/		\
	free(_t);		/*delete string*/				\
}

#define sendCmd(x) 		sendSomeData(	[&]()->char*	{return prepareCmdMessage(x);}()			)

#define sendArr(x, y) 	sendSomeData(	[&]()->char*	{return prepareArrayMessage(x, y);}()		)

#define sendArrDynamic(x, y, z) sendSomeData(	[&]()->char*	{return _prepareArrayMessage(x, y, z);}()	)

/*void sendArr(uint8_t x, uint16_t* y)
{
	_sendArr(x, y);
}*/

/*void sendArr(uint8_t x, uint16_t* y, uint32_t len)
{
	_sendArrDynamic(x, y, len);
}*/




/*
 *	Function:	scheduleAddFunc
 *	Desc:		Add func to repeat by schedule
 *	Input:		void* func: ptr to func
 *	Output:		none
 */
void scheduleAddFunc(void(* func)())
{
	ATOMIC_FORCED
	(
		scheduleQueue[scheduleQueueLen++] = func;
	)
}

/*
 *	Function:	scheduleRemoveFunc
 *	Desc:		Remove func fom schedule task queue
 *	Input:		uint8_t func: index of ptr to func
 *	Output:		none
 */
void scheduleRemoveFunc(uint8_t func)
{
	cli();
	for(uint8_t q = func; q < scheduleQueueLen - 1; q++)
	{
		scheduleQueue[q] = scheduleQueue[q + 1];
	}
	scheduleQueueLen--;
	sei();
}

/*
 *	Function:	scheduleRemoveFunc
 *	Desc:		Remove func fom schedule task queue
 *	Input:		void* func: ptr to func
 *	Output:		none
 */
void scheduleRemoveFunc(void(* func)())
{
	ATOMIC_SMART
	(
		for(uint8_t i = 0; i < scheduleQueueLen; i++)
		{
			if(scheduleQueue[i] == func)
			{
				scheduleRemoveFunc(i);
				break;
			}
		}
	)
}

void schFuckDelay(void)
{
	delay(250);
}

/*void schIdle(void)//do idle work
{
	//this func will never be called
	PORTB &= ~(1 << 7);
	USART0Send('i');
}*/
#define schIdle	0


/*
 *	Function:	schedule
 *	Desc:		If have new bytes to read return 1(t), else 0(f)
 *	Input:		none
 *	Output:		none
 */
void schedule(void)
{
	if(scheduleQueue[scheduleCounter] != 0)
	{
		PORTB |= 1 << 7;//enable in-fg
		scheduleQueue[scheduleCounter++]();
	}
	else
		scheduleCounter++;

	if(scheduleCounter >= scheduleQueueLen)
		scheduleCounter = 0;

	PORTB &= ~(1 << 7);//disable in-fg
}

void usartSchSend(void)
{
	USART0Println();
}

void ledSchToggle(void)
{
	PINB = 1 << 4;
}

uint16_t vlMess = -1;

void vlStartMeasure(void)
{
	uint8_t* p = (uint8_t*)malloc(5 * sizeof(uint8_t));
	p[0] = SYSRANGE_START;
	p[1] = 0x01;
	for(uint8_t i = 0; i < NUM_OF_TOFS; i++)
	{
		twiAddPack(addrs[i], p, 2, I2C_WRITE);
	}
	twiStart();
	free(p);
}

void vlReqReadMeasure(void)
{
	uint8_t* p = (uint8_t*)malloc(2 * sizeof(uint8_t));
	for(uint8_t i = 0; i < NUM_OF_TOFS; i++)
	{
		p[0] = RESULT_RANGE_STATUS + 10;
		twiAddPack(addrs[i], p, 1, I2C_WRITE);
		p[0] = 2;
		twiAddPack(addrs[i], p, 1, I2C_READ);
		p[0] = SYSTEM_INTERRUPT_CLEAR;
		p[1] = 0x01;
		twiAddPack(addrs[i], p, 2, I2C_WRITE);
		/*p[0] = RESULT_RANGE_STATUS + 10;
		twiAddPack(addrs[i], p, 1, I2C_WRITE);
		p[0] = 2;
		twiAddPack(addrs[i], p, 1, I2C_WRITE);
		p[0] = SYSTEM_INTERRUPT_CLEAR;
		p[1] = 0x01;
		twiAddPack(addrs[i], p, 2, I2C_WRITE);*/
		twiStart();
	}
	free(p);
}

void vlSaveMess(void)
{
	//USART0Println("save");
	if(twiHadRead)
	{
		ATOMIC_FORCED
		(
			for(uint8_t i = 0; i < NUM_OF_TOFS; i++)
			{
				uint16_t buf = twiGetByte();
				buf <<= 8;
				buf |= twiGetByte();
				//buf -= 30;
				if((uint16_t)buf - 30 < 2000)
				{
					//measures[i] = buf;
					if((measures[i] > buf && measures[i] - buf < 30)
						|| (measures[i] < buf && buf - measures[i] < 30))
					{
						//USART0Println("smoothing data");
						measures[i] = ((uint32_t)measures[i] +  (uint32_t)buf) / 2;
					}
					else
					{
						measures[i] = buf;
					}
					setTofRangeouted(i, 0);
				}
				else
					setTofRangeouted(i, 1);
					//measures[i] = 0xFFF;
			}
		)
		//_twi_in_len = 0;
	}
	else
	{
		USART0Println("fuck...");
	}
}

void vlPrint()
{
	/*for(uint8_t i = 0; i < NUM_OF_TOFS; i++)
	{
		USART0Print(i);
		USART0Print("\t\t\t");
		USART0Print(measures[i]);
		if(isTofRangeouted(i))
			USART0Print("\t\tR!");
		USART0Println();
	}*/
	//sendArrDynamic(1, measures, NUM_OF_TOFS);
	char* _t = _prepareArrayMessage(DISTANCE_METER_ARR_INDEX, measures, 8);
	USART0Println(_t);
	free(_t);
	USART0Println();
}


#define calcMacroPeriod(vcsel_period_pclks) ((((uint32_t)2304 * (vcsel_period_pclks) * 1655) + 500) / 1000)


char usartInBuf[512];
volatile uint16_t usartInBufCounter = 0;

bool contains(char* _inbuf, uint16_t _len, char _ch)
{
	for(uint16_t i = 0; i < _len; i++)
	{
		if(_inbuf[i] == _ch)
		{
			return true;
		}
	}
	return false;
}


void recvUsart()
{
	usartInBuf[usartInBufCounter++] = USART0Read();
}


void runControlCmd(char* _in)
{
	USART0Print("CMD: ");
	USART0Println(_in);
}

void setArr(char* _in)
{
	USART0Print("ARR: ");
	USART0Println(_in);
}

void setVar(char* _in)
{
	USART0Print("VAR: ");
	USART0Println(_in);
}



void parseInputCmds(void)
{
	if((	contains(usartInBuf, usartInBufCounter, '(') && contains(usartInBuf, usartInBufCounter, ')')) 
		|| (contains(usartInBuf, usartInBufCounter, '{') && contains(usartInBuf, usartInBufCounter, '}'))
		|| (contains(usartInBuf, usartInBufCounter, '[') && contains(usartInBuf, usartInBufCounter, ']')))
	{
		//USART0Println("contains data");
		//USART0Println(usartInBufCounter - 2);
		char* _arr = (char*)malloc((usartInBufCounter * sizeof(char)) - 1);
		_arr[usartInBufCounter- 2 ] = '\0';
		usartInBufCounter -= 1;
		while(usartInBufCounter-- > 1)
		{
			_arr[usartInBufCounter - 1] = usartInBuf[usartInBufCounter];
		}

		usartInBufCounter = 0;
		if(usartInBuf[0] == '(')
		{
			runControlCmd(_arr);
		}
		else if(usartInBuf[0] == '{')
		{
			setVar(_arr);
		}
		else if(usartInBuf[0] == '[')
		{
			setArr(_arr);
		}

		//USART0Println(_arr);
		free(_arr);
	}
}

int main()
{
	DDRH = (1 << 5) | (1 << 7);
	//DDRB = (1 << 7);
	DDRB = 0xFF;
	DDRK = 255;
	PORTK = 0;
	PORTH = 0;
	/*delay(100);
	PORTH = 1 << 5;
	delay(100);
	PORTH = 0;
	delay(100);
	PORTH = 1 << 5;
	delay(100);*/
	sei();


	//ATOMIC_FORCED(USART0Println("AAA");)

	/*ATOMIC_SMART_1
	(
		USART0Println("a");
	)
	ATOMIC_SMART_2
	(
		USART0Println("a");
	)
	ATOMIC_FORCED
	(
		USART0Println("a");
	)
	ATOMIC_SMART
	(
		USART0Println("a");
	)*/

	setCustomFunc(INTERRUPT_CUSTOMFUNC_USART0_RX, recvUsart);


	USART0Begin(115200);


	USART0Println("starting init");



	uint64_t var = 0xFFFE;
	//uint16_t ar = getCountsOfBits(var);
	//USART0Println(ar);
	USART0Print(var, BIN);
	while(1){asm("NOP");}


	uint16_t arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	//sendArr(1, arr);
	//sendSomeData([]()->char*{return prepareCmdMessage("command_sample");});
	//sendCmd("cmd");
	/*uint16_t* a = (uint16_t)malloc(500*sizeof(uint16_t));
	for(int i = 0; i < 500; i++)
	{
		a[i] = i;
	}
	//char* aa = prepareArrayMessage(1, a, 500);
	char* aa = prepareCmdMessage("fuckuuuuu");
	USART0Println(aa);
	//free(a);
	free(aa);*/
	//uint32_t var = 0;
	//while(1)
	//{
	//	delay(200);
		//USART0Println(++var);
	//}
	I2C_SetFreq(0x40);
	uint8_t* p = (uint8_t*)malloc(sizeof(uint8_t) * 4);
	for(uint8_t i = 0; i < NUM_OF_TOFS; i++)
	{
		addrs[i] = 0x29;
		measures[i] = 0;
	}


	for(uint8_t i = 0; i < NUM_OF_TOFS && false; i++)
	{
		PORTK = (1 << (i + 1)) - 1;
		delay(100);
		addrs[i] += (i + 1)*2;
		p[0] = 0x8A;
		p[1] = addrs[i];
		USART0Print("\t\t");
		USART0Print("i:");
		USART0Print(i);
		USART0Print("\t\t\t\t");
		USART0Println((1 << i) | ((1 << (i - 1)) - 1));
		USART0Print("\t\t\t\t\t\t");
		USART0Println(addrs[i]);
		twiAddPack(0x29, p, 2, I2C_WRITE);//change vl53l0x addr

		auto writeReg = [&](uint8_t a, uint8_t b)
		{
			p[0] = a;
			p[1] = b;
			twiAddPack(addrs[i], p, 2, I2C_WRITE);
			twiStart();
		};


		p[0] = 0x88;
		p[1] = 0x00;
		twiAddPack(addrs[i], p, 2, I2C_WRITE);
		p[0] = 0x80;
		p[1] = 0x01;
		twiAddPack(addrs[i], p, 2, I2C_WRITE);
		p[0] = 0xFF;
		p[1] = 0x01;
		twiAddPack(addrs[i], p, 2, I2C_WRITE);
		p[0] = 0x00;
		p[1] = 0x00;
		twiAddPack(addrs[i], p, 2, I2C_WRITE);

		p[0] = 0x91;
		twiAddPack(addrs[i], p, 1, I2C_WRITE);
		p[0] = 1;
		twiAddPack(addrs[i], p, 1, I2C_READ);
		p[0] = 0x00;
		p[1] = 0x01;
		twiAddPack(addrs[i], p, 2, I2C_WRITE);
		p[0] = 0xFF;
		p[1] = 0x00;
		twiAddPack(addrs[i], p, 2, I2C_WRITE);
		p[0] = 0x80;
		p[1] = 0x00;
		twiAddPack(addrs[i], p, 2, I2C_WRITE);
		//p[0] = FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT;
		//p[1] = ((float)0.5) * (1 << 7);
		//twiAddPack(0x20, p, 2, I2C_WRITE);
		twiStart();
		USART0Println("waiting for stop var");
		sei();
		
		while(!twiHadRead())
		{
			asm("NOP");//do nothing
			asm("NOP");//do nothing
			asm("NOP");//do nothing
		}
		
		//delay(50);
		stopVars[i] = ((int)twiGetByte());
		USART0Print("stop var:");
		USART0Println(stopVars[i]);
		auto decodeTimeout = [&](uint16_t reg_val) -> uint16_t
		{
			return (uint16_t)((reg_val & 0x00FF) << 
				(uint16_t)((reg_val & 0xFF00) >> 8)) + 1;
		};
		auto encodeTimeout = [&](uint16_t _t) -> uint16_t
		{
			uint32_t ls = 0;
			uint32_t ms = 0;
			if(_t > 0)
			{
				ls = _t - 1;
				while((ls & 0xFFFFFF00) > 0)
				{
					ls >>= 1;
					ms++;
				}
				return (ms << 8) | (ls & 0xFF);
			}
			else
			{
				return 0;
			}
		};

		auto readReg16B = [&](uint8_t reg) -> uint16_t
		{
			p[0] = reg;
			twiAddPack(addrs[i], p, 1, I2C_WRITE);
			p[0] = 2;
			twiAddPack(addrs[i], p, 1, I2C_READ);
			twiStart();
			USART0Println("waiting for 16 bit num...");
			while(!twiHadRead())
			{
				asm("NOP");//do nothing
			}
			return (uint16_t)((twiGetByte() << 8) | twiGetByte());
		};
		oscCalVal[i] = readReg16B(OSC_CALIBRATE_VAL);
		//p[0] = FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI;
		//p[1] = encodeTimeout(1000) & 0xFF;
		//p[2] = (encodeTimeout(1000) >> 8) & 0xFF;
		//twiAddPack(addrs[i], p, 3, I2C_WRITE);
		//twiStart();
		p[0] = FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT;
		p[1] = ((int)150*(1 << 7)) & 0xFF;
		p[2] = (((int)150*(1 << 7)) >> 8) & 0xFF;
		twiAddPack(addrs[i], p, 3, I2C_WRITE);
		twiStart();

		auto timeoutMicrosecondsToMclks = [&](uint32_t timeout_period_us, uint8_t vcsel_period_pclks) -> uint32_t
		{
		  uint32_t macro_period_ns = calcMacroPeriod(vcsel_period_pclks);

		  return (((timeout_period_us * 1000) + (macro_period_ns / 2)) / macro_period_ns);
		};


	}







	setCustomFunc(INTERRUPT_CUSTOMFUNC_TC0_COMPA, schedule);
	TIMER0Init(TIMER0_COMA_NPWM_NORMAL, TIMER0_WF_CTC, TIMER0_CLK_SRC_1024);
	TIMER0EnableCOMPAInterrupt();
	TIMER0SetA(255);

	scheduleAddFunc(vlPrint);
	scheduleAddFunc(parseInputCmds);
	//scheduleAddFunc(vlStartMeasure);

	//scheduleAddFunc(schIdle);
	//scheduleAddFunc(schIdle);
	//scheduleAddFunc(schIdle);
	//scheduleAddFunc(schIdle);
	//scheduleAddFunc(schIdle);
	
	

	//scheduleAddFunc(vlReqReadMeasure);

	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);


	//scheduleAddFunc(vlSaveMess);

	/*scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);
	scheduleAddFunc(schIdle);*/

	loop:
	asm("NOP");//do nothing
	asm("NOP");//do nothing
	asm("NOP");//do nothing
	asm("NOP");//do nothing
	asm("NOP");//do nothing
	goto loop;
	return 0;
}

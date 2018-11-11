#include <avr/io.h>			//include for base avr funcs
#define F_CPU 16000000		//define with freq
#include <util/delay.h> 	//include for delay func
#include <avr/interrupt.h>	//include interrupt funcs
#include <stdlib.h>

#define NUM_OF_ANALOG_PINS 7
#define ARDUINO_SUPPORT 0
#define USE_ADC 1
#define USE_FUNC_INPUT_PROTECTOR 0

//---------TIMERS----------
#define USE_TIMERS 1
#define TIMER0_USE_COMPA 1
#define TIMER5_USE_COMPA 1

//---------USART----------
#define EOL "\r\n"
#define USE_USART 1
#define USE_USART0 1
#define USE_USART0_OUTPUT 1
#define USE_USART0_INPUT 1
#define USE_SERIAL_FASTBAUD 0

//---------CUSTOM_INTERRUPTS----------
#define USE_CUSTOM_INTERRUPTS 1

#include "api.h"//custom lib for AVR
#define DEBUG					1


#define _TWI_ACK				1
#define _TWI_NACK				0
#define _TWI_MASTER_BUF_LEN		255
#define _TWI_TX_BUF_LEN		255
//#define _TWI_TX_OUT_BUF_LEN		255
#define _TWI_RX_BUF_LEN		255
//#define _TWI_RX_OUT_BUF_LEN		255
#define I2C_WRITE				0
#define I2C_READ				1
//#define I2C_ERROR_


volatile uint8_t _twi_master_buf [_TWI_MASTER_BUF_LEN];
volatile uint8_t _twi_tx_buf	 [_TWI_TX_BUF_LEN];
volatile uint8_t _twi_tx_lens_buf[_TWI_TX_BUF_LEN];
volatile uint8_t _twi_rx_buf	 [_TWI_RX_BUF_LEN];
volatile uint8_t _twi_rx_lens_buf[_TWI_RX_BUF_LEN];
volatile uint8_t _twi_master_index		= 0;
volatile uint8_t _twi_tx_index			= 0;
volatile uint8_t _twi_tx_lens_index 	= 0;
volatile uint8_t _twi_rx_index			= 0;
volatile uint8_t _twi_rx_lens_index 	= 0;
volatile uint8_t _twi_initial_packet	= 0;
volatile uint8_t _twi_err				= 0;
volatile uint8_t _twi_rx_len			= 0;
volatile uint8_t _twi_tx_len			= 0;
volatile uint8_t _twi_action			= 0;



void I2C_SetFreq(uint8_t _freq)
{
	TWBR = _freq;
}


void _twi_start(void)
{
	#if DEBUG == 1
		USART0Println("start");
		//USART0Println(_twi_tx_lens_index);
		//USART0Println(_twi_tx_lens_buf[_twi_tx_lens_index - 1]);
	#endif //if DEBUG == 1
	_twi_tx_lens_index--;
	_twi_tx_len = _twi_tx_lens_buf[_twi_tx_lens_index];
	_twi_err = 0;
	for(_twi_master_index = 0; _twi_master_index < _twi_tx_len; _twi_master_index++)
	{
		_twi_tx_index--;
		_twi_master_buf[_twi_master_index] = _twi_tx_buf[_twi_tx_index];
	}
	//USART0Println(_twi_master_buf[0]);
	_twi_tx_index--;
	_twi_initial_packet = _twi_tx_buf[_twi_tx_index];
	_twi_action = (_twi_initial_packet & 1)? I2C_READ : I2C_WRITE;
	_twi_tx_lens_buf[_twi_tx_lens_index] = 0;
	if(_twi_action == I2C_READ)
	{
		//_twi_rx_lens_index--;
		_twi_rx_len = 1;//_twi_rx_lens_buf[_twi_rx_lens_index];
	}
	TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
}

void _twi_stop(void)
{
	#if DEBUG == 1
		USART0Println("stop");
	#endif
	//_twi_idle = true;
	TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWSTO);
	if(_twi_action == I2C_READ)
	{
		_twi_rx_index = _twi_master_index;
		_twi_rx_lens_buf[_twi_rx_lens_index] = 0;
		while(_twi_master_index)
		{
			_twi_rx_buf[_twi_rx_index] = _twi_master_buf[_twi_master_index];
			_twi_rx_index--;
			_twi_master_index--;
			_twi_rx_lens_buf[_twi_rx_lens_index]++;
		}
		_twi_rx_index = _twi_rx_lens_index;
	}
	_twi_master_index = 0;
}

inline void I2C_Write(uint8_t _val)
{
	#if DEBUG == 1
		USART0Print("i2c_write ");
		USART0Print(_val);
		USART0Print(" to ");
		USART0Println(_twi_tx_index);
	#endif
	_twi_tx_buf[_twi_tx_index] = _val;
	_twi_tx_index++;
	_twi_tx_lens_buf[_twi_tx_lens_index - 1]++;
}

inline void I2C_BuildPacket(uint8_t _addr, uint8_t _mode)
{
	_twi_tx_lens_index++;
	I2C_Write((_addr << 1) | (_mode & 1));
	_twi_tx_lens_buf[_twi_tx_lens_index - 1]--;
	//_twi_tx_buf[_twi_tx_index] = (_addr << 1) | (_mode & 1);
	//_twi_tx_index++;
}


uint8_t I2C_Read(void)
{
	if(_twi_rx_index > 0)
	{
		_twi_rx_index--;
		return _twi_rx_buf[_twi_rx_index];
	}
	else
	{
		return 0;
	}
}

uint8_t I2C_GetError(void)
{
	return _twi_err;
}

inline void I2C_SetRXLen(uint8_t _len)
{
	_twi_rx_len = _len;
}

void I2C_Flush(void)
{
	//_twi_master_in_index = 0;
	//_twi_master_out_index = 0;
	I2C_SetRXLen(1);
}

/*uint8_t I2C_IsReady(void)
{
	return _twi_idle;
}*/

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

void _twi_send_debug(void)
{
	USART0Print("TWCR:");
	USART0Println((int)TWCR);
	USART0Print("TWSR:");
	USART0Println((int)TWSR);
	USART0Print("TWDR:");
	USART0Println((int)TWDR);
	USART0Print("TWBR:");
	USART0Println((int)TWBR);
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
			#if DEBUG == 1
				USART0Println("BUSFAIL");
			#endif
			_twi_err = 1;
			break;
		}
		case 0x08://start
		{
			#if DEBUG == 1
				USART0Println("START");
				USART0Print("addr:");
				USART0Println(_twi_initial_packet >> 1);
				USART0Print("mode:");
				USART0Println((char*)((_twi_initial_packet & 1 == I2C_READ)? "READ" : "WRITE"));
			#endif
			TWDR = _twi_initial_packet;
			_twi_reply(_TWI_ACK);
			break;
		}
		case 0x10://reStart
		{
			#if DEBUG == 1
				USART0Println("(RE)START");
			#endif
			_twi_stop();
			break;
		}
		case 0x28://byte+ACK
		{
			#if DEBUG == 1
				USART0Println("BYTE+ACK");
			#endif
		}
		case 0x18://SLA+W+ACK
		{
			#if DEBUG == 1
				USART0Println("SLA+W+ACK");	
			#endif
			if(_twi_master_index >= 1 && _twi_master_index < _TWI_MASTER_BUF_LEN - 1
			&& _twi_master_index <= _twi_tx_len)
			{
				#if DEBUG == 1
					USART0Println("SEND DATA");
					USART0Print("send ");
					USART0Println(_twi_master_buf[_twi_master_index - 1]);
					USART0Print("index ");
					USART0Println((int)(_twi_master_index - 1));
					USART0Print("tx_len ");
					USART0Println((int)_twi_tx_len);
				#endif //if DEBUG == 1
				_twi_master_index--;
				TWDR = _twi_master_buf[_twi_master_index];
				_twi_reply(_TWI_ACK);
			}
			else
			{
				#if DEBUG == 1
					USART0Println("STOP");
				#endif
				_twi_stop();
			}
			break;
		}
		case 0x20://SLA+W+NACK
		{
			#if DEBUG == 1
				USART0Println("SLA+W+NACK");
			#endif
			_twi_err = 0x20;
			_twi_stop();
			break;
		}
		case 0x30://byte+NACK
		{
			#if DEBUG == 1
				USART0Println("Byte+NACK");
			#endif
			_twi_err = 0x30;
			_twi_stop();
			break;
		}
		case 0x38://collision
		{
			#if DEBUG == 1
				USART0Println("COLLISION");
			#endif
			_twi_err = 0x38;
			_twi_stop();
			break;
		}
		case 0x40://SLA+R+ACK
		{
			#if DEBUG == 1
				USART0Println("SLA+R+ACK");
				USART0Print("sending ");
				USART0Println(_twi_master_buf[_twi_master_index - 1]);
				_twi_send_debug();
			#endif //if DEBUF == 1
			_twi_master_index--;
			TWDR = 138;
			//TWDR = _twi_master_buf[_twi_master_index];
			if(_twi_rx_len <= 1)
			{
				#if DEBUG == 1
					USART0Println("NACK");
				#endif // if DEBUG == 1
				_twi_reply(_TWI_NACK);
			}
			else
			{
				#if DEBUG == 1
					USART0Println("ACK");
				#endif //if DEBUG == 1
				_twi_reply(_TWI_ACK);
			}
			break;
		}
		case 0x48://SLA+R+NACK
		{
			#if DEBUG == 1
				USART0Println("SLA+R+NACK");
				_twi_send_debug();
			#endif
			_twi_err = 0x48;
			_twi_stop();
			break;
		}
		case 0x50://recive byte
		{
			#if DEBUG == 1
				USART0Println("RECIEVE_BYTE");
				_twi_send_debug();
			#endif
			_twi_master_buf[_twi_master_index] = TWDR;
			_twi_master_index++;
			_twi_rx_len--;
			_twi_reply(_TWI_NACK);
			break;
		}
		case 0x58://recive byte+NACK
		{
			#if DEBUG == 1
				USART0Println("RECIVE_BYTE+NACK");
				_twi_send_debug();
				USART0Print("recieved ");
				USART0Println(TWDR);
			#endif
			_twi_master_buf[_twi_master_index] = TWDR;
			_twi_master_index++;
			_twi_stop();
			break;
		}
		default:
		{
			USART0Print("DEFAULT");
			_twi_send_debug();
			USART0Println(TWSR);
		}
	}
	#if DEBUG == 1
		USART0Print("TWDR:");
		USART0Println(TWDR);
	#endif
	
	//USART0Println(TWCR & (1<<TWINT));
}


uint8_t addr = 0x29;


void writeReg(uint8_t _addr, uint8_t _reg, uint8_t _val)
{
	I2C_BuildPacket(_addr, I2C_WRITE);
	I2C_Write(_reg);
	I2C_Write(_val);
	_twi_start();
}

void writeReg(uint8_t _reg, uint8_t _val)
{
	writeReg(addr, _reg, _val);
}


void writeReg16B(uint8_t _addr, uint8_t _reg, uint16_t _val)
{
	I2C_BuildPacket(_addr, I2C_WRITE);
	I2C_Write(_reg);
	I2C_Write((_val >> 8) & 0xFF);
	I2C_Write((_val)	  & 0xFF);
	_twi_start();
}

void writeReg16Bit(uint8_t _reg, uint16_t _val)
{
	writeReg16B(addr, _reg, _val);
}


void writeReg32B(uint8_t _addr, uint8_t _reg, uint32_t _val)
{
	I2C_BuildPacket(_addr, I2C_WRITE);
	I2C_Write(_reg);
	I2C_Write((_val >> 24) & 0xFF);
	I2C_Write((_val >> 16) & 0xFF);
	I2C_Write((_val >> 8 ) & 0xFF);
	I2C_Write((_val)	   & 0xFF);
	_twi_start();	
}

void writeReg32Bit(uint8_t _reg, uint32_t _val)
{
	writeReg32B(addr, _reg, _val);
}


uint8_t readReg(uint8_t _addr, uint8_t _reg)
{
	I2C_BuildPacket(_addr, I2C_READ);
	I2C_Write(_reg);
	I2C_SetRXLen(1);
	_twi_start();
	return I2C_Read();
}

uint8_t readReg(uint8_t _reg)
{
	return readReg(addr, _reg);
}

uint16_t readReg16B(uint8_t _addr, uint8_t _reg)
{
	uint16_t _ret;
	I2C_BuildPacket(_addr, I2C_READ);
	I2C_Write(_reg);
	I2C_SetRXLen(2);
	_twi_start();
	_ret  = I2C_Read() << 8;
	_ret |= I2C_Read();
	return _ret;
}

uint16_t readReg16Bit(uint8_t _reg)
{
	return readReg16B(addr, _reg);
}

void writeMulti(uint8_t _addr, uint8_t _reg, uint8_t const * _src, uint8_t _count)
{
	I2C_BuildPacket(_addr, I2C_WRITE);
	I2C_Write(_reg);
	while(_count-- > 0)
	{
		I2C_Write(*(_src++));
	}
	_twi_start();
}

void writeMulti(uint8_t _reg, uint8_t const * _src, uint8_t _count)
{
	writeMulti(addr, _reg, _src, _count);
}

void readMulti(uint8_t _addr, uint8_t _reg, uint8_t * _dst, uint8_t _count)
{
	I2C_BuildPacket(_addr, I2C_READ);
	I2C_Write(_reg);
	I2C_SetRXLen(_count);
	_twi_start();
	while(_count-- > 0)
	{
		*(_dst++) = I2C_Read();
	}
}

void readMulti(uint8_t _reg, uint8_t * _dst, uint8_t _count)
{
	readMulti(addr, _reg, _dst, _count);
}

int main()
{
    DDRE = (1 << PE4);
    PORTE = 0;
    delay(100);
    PORTE = 1 << PE4;
    PORTD = (1 << PD0) | (1 << PD1);
    delay(100);
    sei();
	USART0Begin(115200);
	//_twi_stop();
	I2C_SetFreq(0x20);
	/*I2C_BuildPacket(0x29, I2C_WRITE);
	I2C_Write(I2C_SLAVE_DEVICE_ADDRESS);
	I2C_Write(0x30);
	_twi_start();
	
	I2C_BuildPacket(0x30, I2C_WRITE);
	I2C_Write(I2C_SLAVE_DEVICE_ADDRESS);
	I2C_Write(0x29);
	_twi_start();*/
	/*
	USART0Print("S");
	USART0Println((int)256, BIN);
	USART0Print("S");
	USART0Println((int)255, BIN);
	USART0Print("S");
	USART0Println((int)254, BIN);
	USART0Print("S");
	USART0Println((int)5, BIN);
	*/
	
	I2C_BuildPacket(0x29, I2C_READ);
	I2C_Write(I2C_SLAVE_DEVICE_ADDRESS);
	_twi_start();
	delay(10);
	
	mainloop:
	
	goto mainloop;
	
	/*writeReg(SYSRANGE_START, 0x01);
	USART0Send(0);
	
	while(readReg(SYSRANGE_START) & 0x01);
	//USART0Println("FUCK");
	
	while(readReg(RESULT_INTERRUPT_STATUS) & 0x07 == 0);
	USART0Print("F");
	USART0Println(readReg16Bit(RESULT_RANGE_STATUS + 10));
	//I2C_Flush();
	writeReg(SYSTEM_INTERRUPT_CLEAR, 0x01);
	
	//while(1);
	
	I2C_Flush();
	delay(100);
	goto mainloop;
	while(1);
	for(int i = 0; i <= 0xFF; i++)
	{
		USART0Print(i);
		USART0Print(" ");
		USART0Println(readReg(addr, i));
		I2C_Flush();
	}*/
	/*USART0Println("START");
	writeReg(addr, SYSRANGE_START, 0x01);
	if(I2C_GetError() != 0)
	{
		USART0Println("ERROR!");
		while(1);
	}
	USART0Println("WAITING...");
	while(readReg(addr, RESULT_INTERRUPT_STATUS) & 0x07 == 0)
	{
		if(I2C_GetError() != 0)
		{
			USART0Println("ERROR!");
			while(1);
		}
	}
	USART0Println("READING...");
	USART0Println(readReg(addr, RESULT_RANGE_STATUS));
	if(I2C_GetError() != 0)
	{
		USART0Println("ERROR!");
		while(1);
	}
	USART0Println("RESETTING...");
	writeReg(addr, SYSTEM_INTERRUPT_CLEAR, 0x01);
	if(I2C_GetError() != 0)
	{
		USART0Println("ERROR!");
		while(1);
	}*/
	
	// "Set I2C standard mode"
  //writeReg(0x88, 0x00);

  //writeReg(0x80, 0x01);
  //writeReg(0xFF, 0x01);
  //writeReg(0x00, 0x00);
  //int stop_variable = readReg(0x91);
  //writeReg(0x00, 0x01);
  //writeReg(0xFF, 0x00);
  //writeReg(0x80, 0x00);

  //// disable SIGNAL_RATE_MSRC (bit 1) and SIGNAL_RATE_PRE_RANGE (bit 4) limit checks
  //writeReg(MSRC_CONFIG_CONTROL, readReg(MSRC_CONFIG_CONTROL) | 0x12);

  //// set final range signal rate limit to 0.25 MCPS (million counts per second)
  ////setSignalRateLimit(0.25);

  //writeReg(SYSTEM_SEQUENCE_CONFIG, 0xFF);

  //// VL53L0X_DataInit() end

  //// VL53L0X_StaticInit() begin

  //uint8_t spad_count;
  //bool spad_type_is_aperture;
  ////if (!getSpadInfo(&spad_count, &spad_type_is_aperture)) { return false; }

  //// The SPAD map (RefGoodSpadMap) is read by VL53L0X_get_info_from_device() in
  //// the API, but the same data seems to be more easily readable from
  //// GLOBAL_CONFIG_SPAD_ENABLES_REF_0 through _6, so read it from there
  //uint8_t ref_spad_map[6];
  //readMulti(GLOBAL_CONFIG_SPAD_ENABLES_REF_0, ref_spad_map, 6);

  //// -- VL53L0X_set_reference_spads() begin (assume NVM values are valid)

  //writeReg(0xFF, 0x01);
  //writeReg(DYNAMIC_SPAD_REF_EN_START_OFFSET, 0x00);
  //writeReg(DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD, 0x2C);
  //writeReg(0xFF, 0x00);
  //writeReg(GLOBAL_CONFIG_REF_EN_START_SELECT, 0xB4);

  //uint8_t first_spad_to_enable = spad_type_is_aperture ? 12 : 0; // 12 is the first aperture spad
  //uint8_t spads_enabled = 0;

  //for (uint8_t i = 0; i < 48; i++)
  //{
    //if (i < first_spad_to_enable || spads_enabled == spad_count)
    //{
      //// This bit is lower than the first one that should be enabled, or
      //// (reference_spad_count) bits have already been enabled, so zero this bit
      //ref_spad_map[i / 8] &= ~(1 << (i % 8));
    //}
    //else if ((ref_spad_map[i / 8] >> (i % 8)) & 0x1)
    //{
      //spads_enabled++;
    //}
  //}

  //writeMulti(GLOBAL_CONFIG_SPAD_ENABLES_REF_0, ref_spad_map, 6);

  //// -- VL53L0X_set_reference_spads() end

  //// -- VL53L0X_load_tuning_settings() begin
  //// DefaultTuningSettings from vl53l0x_tuning.h

  //writeReg(0xFF, 0x01);
  //writeReg(0x00, 0x00);

  //writeReg(0xFF, 0x00);
  //writeReg(0x09, 0x00);
  //writeReg(0x10, 0x00);
  //writeReg(0x11, 0x00);

  //writeReg(0x24, 0x01);
  //writeReg(0x25, 0xFF);
  //writeReg(0x75, 0x00);

  //writeReg(0xFF, 0x01);
  //writeReg(0x4E, 0x2C);
  //writeReg(0x48, 0x00);
  //writeReg(0x30, 0x20);

  //writeReg(0xFF, 0x00);
  //writeReg(0x30, 0x09);
  //writeReg(0x54, 0x00);
  //writeReg(0x31, 0x04);
  //writeReg(0x32, 0x03);
  //writeReg(0x40, 0x83);
  //writeReg(0x46, 0x25);
  //writeReg(0x60, 0x00);
  //writeReg(0x27, 0x00);
  //writeReg(0x50, 0x06);
  //writeReg(0x51, 0x00);
  //writeReg(0x52, 0x96);
  //writeReg(0x56, 0x08);
  //writeReg(0x57, 0x30);
  //writeReg(0x61, 0x00);
  //writeReg(0x62, 0x00);
  //writeReg(0x64, 0x00);
  //writeReg(0x65, 0x00);
  //writeReg(0x66, 0xA0);

  //writeReg(0xFF, 0x01);
  //writeReg(0x22, 0x32);
  //writeReg(0x47, 0x14);
  //writeReg(0x49, 0xFF);
  //writeReg(0x4A, 0x00);

  //writeReg(0xFF, 0x00);
  //writeReg(0x7A, 0x0A);
  //writeReg(0x7B, 0x00);
  //writeReg(0x78, 0x21);

  //writeReg(0xFF, 0x01);
  //writeReg(0x23, 0x34);
  //writeReg(0x42, 0x00);
  //writeReg(0x44, 0xFF);
  //writeReg(0x45, 0x26);
  //writeReg(0x46, 0x05);
  //writeReg(0x40, 0x40);
  //writeReg(0x0E, 0x06);
  //writeReg(0x20, 0x1A);
  //writeReg(0x43, 0x40);

  //writeReg(0xFF, 0x00);
  //writeReg(0x34, 0x03);
  //writeReg(0x35, 0x44);

  //writeReg(0xFF, 0x01);
  //writeReg(0x31, 0x04);
  //writeReg(0x4B, 0x09);
  //writeReg(0x4C, 0x05);
  //writeReg(0x4D, 0x04);

  //writeReg(0xFF, 0x00);
  //writeReg(0x44, 0x00);
  //writeReg(0x45, 0x20);
  //writeReg(0x47, 0x08);
  //writeReg(0x48, 0x28);
  //writeReg(0x67, 0x00);
  //writeReg(0x70, 0x04);
  //writeReg(0x71, 0x01);
  //writeReg(0x72, 0xFE);
  //writeReg(0x76, 0x00);
  //writeReg(0x77, 0x00);

  //writeReg(0xFF, 0x01);
  //writeReg(0x0D, 0x01);

  //writeReg(0xFF, 0x00);
  //writeReg(0x80, 0x01);
  //writeReg(0x01, 0xF8);

  //writeReg(0xFF, 0x01);
  //writeReg(0x8E, 0x01);
  //writeReg(0x00, 0x01);
  //writeReg(0xFF, 0x00);
  //writeReg(0x80, 0x00);

  //// -- VL53L0X_load_tuning_settings() end

  //// "Set interrupt config to new sample ready"
  //// -- VL53L0X_SetGpioConfig() begin

  //writeReg(SYSTEM_INTERRUPT_CONFIG_GPIO, 0x04);
  //writeReg(GPIO_HV_MUX_ACTIVE_HIGH, readReg(GPIO_HV_MUX_ACTIVE_HIGH) & ~0x10); // active low
  //writeReg(SYSTEM_INTERRUPT_CLEAR, 0x01);
  
   //writeReg(SYSTEM_INTERRUPT_CONFIG_GPIO, 0x04);
  //writeReg(GPIO_HV_MUX_ACTIVE_HIGH, readReg(GPIO_HV_MUX_ACTIVE_HIGH) & ~0x10); // active low
	//writeReg(SYSTEM_INTERRUPT_CLEAR, 0x01);
	
	  //writeReg(0x80, 0x01);
  //writeReg(0xFF, 0x01);
  //writeReg(0x00, 0x00);
  //writeReg(0x91, stop_variable);
  //writeReg(0x00, 0x01);
  //writeReg(0xFF, 0x00);
  //writeReg(0x80, 0x00);

	//writeReg(SYSRANGE_START, 0x01);
	
	
	//USART0Println("waiting...");
	//while ((readReg(RESULT_INTERRUPT_STATUS) & 0x07) == 0);
	
	//USART0Println(readReg16Bit(RESULT_RANGE_STATUS + 10));
	
	//writeReg(SYSTEM_INTERRUPT_CLEAR, 0x01);
	
	
	
	/*													I2C SCANNER	
	uint8_t found = false;
	USART0Println("I2C Scanner");
	loop:
	found = false;
	USART0Println("Scanning...");
	for(int i = 0; i < 128; i++)
	{
		I2C_BuildPacket(i, I2C_WRITE);
		_twi_start();
		while(!I2C_IsReady());
		if(_twi_err == 0)
		{
			found = true;
			USART0Print("Device found: ");
			USART0Println(i);
		}
		else
		{
			I2C_Flush();
		}
	}
	
	if(!found)
	{
		USART0Println("No I2C Devices found!");
	}
	
	USART0Println();
	delay(100);
	goto loop;*/
	
	
	/*USART0Println("Changing addr from 0x29 to 0x30...");
	writeReg(0x29, 0x8A, 0x30);
	if(!I2C_GetError())
	{
		USART0Println("Addr successfully changed!");
	}
	else
	{
		USART0Println("Error, exiting...");
		USART0Println(I2C_GetError());
		while(1);
	}
	USART0Println("Reading slave addr...");
	readReg(0x30, 0x8A);
	if(I2C_GetError() == 0)
	{
		USART0Print("Slave addr:");
		USART0Println(I2C_Read());
	}
	else
	{
		USART0Println("Error, exiting...");
		USART0Println(I2C_GetError());
		while(1);
	}*/
	
	
	while(1);

	
	//writeReg(SYSTEM_SEQUENCE_CONFIG, 0xE8);
	
	//I2C_Init(0x20);
	/*
	I2C_StartCondition();
	USART0Println(TWSR);
	I2C_SendByte(0x52);
	USART0Println(TWSR);
	I2C_SendByte(I2C_SLAVE_DEVICE_ADDRESS);
	USART0Println(TWSR);
	I2C_SendByte(0x30 & 0x7F);
	USART0Println(TWSR);
	I2C_StopCondition();
	USART0Println(TWSR);
	
	I2C_StartCondition();
	USART0Println(TWSR);
	I2C_SendByte(0x30 << 1);
	USART0Println(TWSR);
	I2C_StopCondition();
	USART0Println(TWSR);*/
	
	
	while(1);
	ADCInit();
	sei();
	ADCSRA |= (1 << ADSC);	//start conversion
	
	
	int del = 800;
	
	USART0Println(ADCSRA, BIN);
	
	loop:
	USART0Println(analogRead(0));
	/*USART0Println("4");
	PORTB = 1 << PB4;
	USART0Println(analogRead(0));
	USART0Println();
	_delay_ms(del);
	USART0Println("5");
	PORTB = 1 << PB5;
	USART0Println(analogRead(0));
	USART0Println();
	_delay_ms(del);
	USART0Println("6");
	PORTB = 1 << PB6;
	USART0Println(analogRead(0));
	USART0Println();
	_delay_ms(del);
	USART0Println("0");
	PORTB = 0;
	USART0Println(analogRead(0));
	USART0Println();
	USART0Println();
	_delay_ms(del);
	*/
	/*enableWheelAC();
	USART0Println("AC");
	_delay_ms(del);
	disableWheelAC();
	USART0Println("STOP");
	_delay_ms(del);
	enableWheelACC();
	USART0Println("ACC");
	_delay_ms(del);
	disableWheelACC();
	USART0Println("STOP");
	_delay_ms(del);
	
	enableWheelBC();
	USART0Println("BC");
	_delay_ms(del);
	disableWheelBC();
	USART0Println("STOP");
	_delay_ms(del);
	enableWheelBCC();
	USART0Println("BCC");
	_delay_ms(del);
	disableWheelBCC();
	USART0Println("STOP");
	_delay_ms(del);
	
	enableWheelCC();
	USART0Println("CC");
	_delay_ms(del);
	disableWheelCC();
	USART0Println("STOP");
	_delay_ms(del);
	enableWheelCCC();
	USART0Println("CCC");
	_delay_ms(del);
	disableWheelCCC();
	USART0Println("STOP");
	_delay_ms(del);
	
	enableWheelDC();
	USART0Println("DC");
	_delay_ms(del);
	disableWheelDC();
	USART0Println("STOP");
	_delay_ms(del);
	enableWheelDCC();
	USART0Println("DCC");
	_delay_ms(del);
	disableWheelDCC();
	USART0Println("STOP");
	_delay_ms(del);
//*/

	/*USART0Println("F");
	startForward();
	_delay_ms(del);
	USART0Println("STOP");
	stopForward();
	_delay_ms(del);

	USART0Println("R");
	startRight();
	_delay_ms(del);
	USART0Println("STOP");
	stopRight();
	_delay_ms(del);

	USART0Println("L");
	startLeft();
	_delay_ms(del);
	USART0Println("STOP");
	stopLeft();
	_delay_ms(del);

	USART0Println("B");
	startBackward();
	_delay_ms(del);
	USART0Println("STOP");
	stopBackward();
	_delay_ms(del);//*/
	
	/*USART0Println("FR");
	startFR();
	_delay_ms(del);
	USART0Println("STOP");
	stopFR();
	_delay_ms(del);
	
	USART0Println("FL");
	startFL();
	_delay_ms(del);
	USART0Println("STOP");
	stopFL();
	_delay_ms(del);
	
	USART0Println("BR");
	startBR();
	_delay_ms(del);
	USART0Println("STOP");
	stopBR();
	_delay_ms(del);
	
	USART0Println("BL");
	startBL();
	_delay_ms(del);
	USART0Println("STOP");
	stopBL();
	_delay_ms(del);//*/
	
	
	/*startTurnC();
	USART0Println("C");
	_delay_ms(del);
	stopTurnC();
	USART0Println("STOP");
	_delay_ms(del);
	
	startTurnCC();
	USART0Println("CC");
	_delay_ms(del);
	stopTurnCC();
	USART0Println("STOP");
	_delay_ms(del);//*/
	
	_delay_ms(1);
	
	goto loop;//endless loop
	
	return 0;
}

#include "TWI.h"
#include "customFuncAddr.h"
#define DEBUG 0
#if DEBUG == 1
#include "USART.h"
#endif //if DEBUG == 1

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
//inline void I2C_SetFreq(uint8_t _freq)
//{
//	TWBR = _freq;
//}







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
 *	Function:	twiAddPack
 *	Desc:		Add package to user queue
 *	Input:		uint8_t  addr:		what addr of slave set to
 				uint16_t data:		byte send to
 				uint8_t mode:		read or write mode use to
 *	Output:		none
 */
void twiAddPack(uint8_t addr, uint16_t data, uint8_t mode)
{
	addr <<= 1;
	addr |= mode & 1;
	cli();											//block interrupts, must be atomic
	_twi_usr_packs++;
	_twi_usr_in_queue[_twi_usr_len++] = addr;		//add addr of slave device
	_twi_usr_in_queue[_twi_usr_len++] = data & 0xFF;//,byte to send
	_twi_usr_in_queue[_twi_usr_len++] = (data >> 8) & 0xFF;
	_twi_usr_in_lens[_twi_usr_lens++] = 2;			//				and num of bytes in pack
	sei();											//allow interrupts, atomic block ended
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
//inline bool twiHadRead(void)
//{
//	return (_twi_in_len > 0);
//}




/*
 *	Function: 	twiWrite
 *	Desc:		Write a byte to reg on slave device
 *	Input:		uint8_t addr: slave device addr
 				uint8_t reg: what reg write to
 				uint8_t data: what write to
 *	Output:		none
 */
void twiWrite(uint8_t addr, uint8_t reg, uint8_t data)
{
	twiAddPack(addr, (uint16_t)((reg << 8) | data), I2C_WRITE);
	twiStart();
}


/*
 *	Function: 	twiReqRead
 *	Desc:		Request a byte from reg on slave device
 *	Input:		uint8_t addr: slave device addr
 				uint8_t reg: what reg read from
 				uint8_t len: len of data in bytes
 *	Output:		none
 */
void twiReqRead(uint8_t addr, uint8_t reg, uint8_t len)
{
	twiAddPack(addr, reg, I2C_WRITE);
	twiAddPack(addr, len, I2C_READ);
	twiStart();
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
				//USART0Println((long)_twi_out_len);
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
				//USART0Println(( long)_twi_out_len);
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
			#if DEBUG == 1
				USART0Print("DEFAULT");
			#endif //if DEBUG == 1
			_twi_status = I2C_FAIL;
			twiStop();
		}
	}
	callCustomFunc(INTERRUPT_CUSTOMFUNC_TWI);
}

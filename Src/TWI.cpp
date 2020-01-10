#include "TWI.hpp"
#include "customFuncAddr.hpp"
#include <util/atomic.h>
#define DEBUG 0
#if DEBUG == 1
	#include "USART.hpp"
#endif //if DEBUG == 1

namespace twi
{
	uint16_t	_out_len = 0;															//2 bytes
	uint8_t		_out_curr = 0;														//1 byte
	uint16_t	_in_len = 0;															//2 bytes
	uint16_t	_usr_len = 0;															//2 bytes
	uint8_t		_usr_packs = 0;														//1 byte
	uint8_t		_usr_lens = 0;														//1 byte
	uint8_t 	_out_queue[_OUT_BUF_LEN];							//_OUT_BUF_LEN bytes
	uint8_t 	_in_queue[_IN_BUF_LEN];								//_IN_BUF_LEN bytes
	uint8_t 	_usr_in_queue[_USR_IN_BUF_LEN];				//_USR_IN_BUF_LEN bytes
	uint8_t		_usr_in_lens[_USR_IN_BUF_LEN];				//_USR_IN_BUF_LEN bytes

	uint8_t		_status = 0xFF;														//1 byte
	//--------------------------------------------------------------------------------------------
	//																											10 + _OUT_BUF_LEN + _IN_BUF_LEN + 2*_USR_IN_BUF_LEN bytes
	//																											190 here






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
	*	Function:	addPack
	*	Desc:		Add package to user queue
	*	Input:		uint8_t  addr:			what addr of slave set to
					const uint8_t* data:	pointer to data array
					uint8_t len:			num of bytes in data array
					uint8_t mode:			read or write mode use to
	*	Output:		none
	*/
	void addPack(uint8_t addr, const uint8_t* data, uint8_t len, uint8_t mode)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			//cli();										//block interrupts, must be atomic
			addr <<= 1;
			addr |= mode & 1;

			#if DEBUG == 1
				//USART0Print("addr:");
				//USART0Println(addr);
			#endif //if DEBUG == 1
			_usr_packs++;
			_usr_in_queue[_usr_len++] = addr;	//add addr of slave device to queue
			for(int i = 0; i < len; i++)				//iterate in data array and add all bytes in usr queue
			{
				#if DEBUG == 1
					//USART0Print("CP:");
					//USART0Println(data[i]);
				#endif //if DEBUG == 1
				_usr_in_queue[_usr_len++] = data[i];
			}
			_usr_in_lens[_usr_lens++] = len + 1;	//set num of bytes in pack
			//sei();										//allow interrupts, atomic block ended
		}
	}






	/*
	*	Function:	addPack
	*	Desc:		Add package to user queue
	*	Input:		uint8_t  addr:		what addr of slave set to
					uint8_t data:		byte send to
					uint8_t mode:		read or write mode use to
	*	Output:		none
	*/
	void addPack(uint8_t addr, uint8_t data, uint8_t mode)
	{
		addr <<= 1;
		addr |= mode & 1;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			//cli();										//block interrupts, must be atomic
			_usr_packs++;
			_usr_in_queue[_usr_len++] = addr;	//add addr of slave device
			_usr_in_queue[_usr_len++] = data;	//				,byte to send
			_usr_in_lens[_usr_lens++] = 2;		//				and num of bytes in pack
			//sei();										//allow interrupts, atomic block ended
		}
	}


	/*
	*	Function:	addPack
	*	Desc:		Add package to user queue
	*	Input:		uint8_t  addr:		what addr of slave set to
					uint16_t data:		byte send to
					uint8_t mode:		read or write mode use to
	*	Output:		none
	*/
	void addPack(uint8_t addr, uint16_t data, uint8_t mode)
	{
		addr <<= 1;
		addr |= mode & 1;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			//cli();											//block interrupts, must be atomic
			_usr_packs++;
			_usr_in_queue[_usr_len++] = addr;		//add addr of slave device
			_usr_in_queue[_usr_len++] = data & 0xFF;//,byte to send
			_usr_in_queue[_usr_len++] = (data >> 8) & 0xFF;
			_usr_in_lens[_usr_lens++] = 2;			//				and num of bytes in pack
			//sei();											//allow interrupts, atomic block ended
		}
	}






	/*
	*	Function:	twiGetByte
	*	Desc:		Get byte from input array(if have)
	*	Input:		none
	*	Output:		uint8_t: readed byte (0xFF if nothing to read)
	*/
	uint8_t getByte(void)
	{
		//USART0Println("reading byte from buf...");
		if(_in_len > 0)
		{
			uint8_t _buf = _in_queue[0];
			shiftLeft(_in_queue, _in_len--, 1);
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
	*	Function:	 _reply
	*	Desc:		Send reply to TWI (ACK or NACK)
	*	Input:		uint8_t _ack: send ACK or NACK
	*	Output:		none
	*/
	void _reply(Responce _ack)
	{
		if(_ack == ACK)
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
	*	Function:	_start
	*	Desc:		Start TWI for state machine
	*	Input:		none
	*	Output:		none
	*/
	inline void _start(void)
	{
		TWCR 	= (1 << TWSTA)	//forming start
				| (1 << TWINT)	//set interrupt flag
				| (1 << TWEN) 	//enable TWI
				| (1 << TWIE);	//allow interrupts
	}






	/*
	*	Function:	_stop
	*	Desc:		Stop TWI for state machine
	*	Input:		none
	*	Output:		none
	*/
	inline void _stop(void)
	{
		TWCR 	= (1 << TWEN)	//enable TWI
				| (1 << TWIE)	//allow interrupts
				| (1 << TWINT)	//set interrupt flag
				| (1 << TWSTO);	//forming stop
	}






	/*
	*	Function:	start
	*	Desc:		Start TWI state machine
	*	Input:		none
	*	Output:		none
	*/
	void start(void)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			//cli();												//block interrupts, must be atomic

			if(_status != I2C_READ
				&& _status != I2C_WRITE)
			{
				uint8_t bytes = _usr_in_lens[0];				//get num of bytes to send
				shiftLeft(_usr_in_lens, _usr_lens--, 1);	//shift array with lens of packs to left for 1 element
				//cli();		//TODO: fix
				for(uint8_t i = 0; i < bytes; i++)
				{													//iterate "bytes" times and copy package
					#if DEBUG == 1
						USART0Print("CP:");
						USART0Println(_usr_in_queue[i]);
					#endif //if DEBUG == 1
					_out_queue[i] = _usr_in_queue[i];
				}
				shiftLeft(_usr_in_queue, _usr_len, bytes);//remove from user queue
				//cli();		//TODO: fix

				_usr_len -= bytes;
				_out_len = bytes;
				_status = (_out_queue[0] & 1)? I2C_READ : I2C_WRITE;//save status
				_usr_packs--;
				_start();										//kick the TWI machine
			}
			else
			{
				#if DEBUG == 1
					USART0Println("\t\t\t\t\t\t\t\ttrying to restart");
					USART0Print("status:");
					USART0Println(_status);
				#endif //if DEBUG == 1
			}
			//sei();												//allow interrupts, atomic block ended
		}
	}





	/*
	*	Function:	stop
	*	Desc:		Stop TWI state machine
	*	Input:		none
	*	Output:		none
	*/
	void stop(void)
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			//cli();							//block interrupts, must be atomic

			#if DEBUG == 1
				USART0Println("to stb");
			#endif //if DEBUG == 1
			_stop();					//go to standby
			_status = I2C_STANDBY;
			_out_len = 0;
			if(_usr_packs > 0)
			{
				#if DEBUG == 1
					USART0Println("R_ESTART");
				#endif //if DEBUG == 1
				start();					//kick state machine for new start
			}

			//sei();							//allow interrupts, atomic block ended
		}
	}






	/*
	*	Function:	twiHadRead
	*	Desc:		If have new bytes to read return 1(t), else 0(f)
	*	Input:		none
	*	Output:		bool
	*/
	//inline bool twiHadRead(void)
	//{
	//	return (_in_len > 0);
	//}




	/*
	*	Function: 	write
	*	Desc:		Write a byte to reg on slave device
	*	Input:		uint8_t addr: slave device addr
					uint8_t reg: what reg write to
					uint8_t data: what write to
	*	Output:		none
	*/
	void write(uint8_t addr, uint8_t reg, uint8_t data)
	{
		addPack(addr, (uint16_t)((reg << 8) | data), I2C_WRITE);
		start();
	}


	/*
	*	Function: 	reqRead
	*	Desc:		Request a byte from reg on slave device
	*	Input:		uint8_t addr: slave device addr
					uint8_t reg: what reg read from
					uint8_t len: len of data in bytes
	*	Output:		none
	*/
	void reqRead(uint8_t addr, uint8_t reg, uint8_t len)
	{
		addPack(addr, reg, I2C_WRITE);
		addPack(addr, len, I2C_READ);
		start();
	}







	void _ISR()
	{
		switch(TWSR)
		{
			case 0x00:												//bus fail
			{
				#if DEBUG == 1
					USART0Println("_0x00");
				#endif //if DEBUG == 1
				_status = I2C_FAIL;
				stop();
				break;
			}
			case 0x08:												//start
			{
				#if DEBUG == 1
					USART0Println("0x08");
					USART0Println(_out_queue[0]);
					USART0Print("len:");
					//USART0Println((long)_out_len);
				#endif //if DEBUG == 1
				_out_curr = 0;
				TWDR = _out_queue[_out_curr++];
				_reply(ACK);
				break;
			}
			case 0x10:												//reStart
			{
				#if DEBUG == 1
					USART0Println("0x10");
					USART0Println(_out_queue[0]);
					USART0Print("len:");
					//USART0Println(( long)_out_len);
				#endif //if DEBUG == 1
				_out_curr = 0;
				TWDR = _out_queue[_out_curr++];
				_reply(ACK);
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
				if(_out_curr < _out_len)
				{
					#if DEBUG == 1
						USART0Print("S:");
						USART0Println(_out_queue[_out_curr]);
					#endif //if DEBUG == 1
					TWDR = _out_queue[_out_curr++];
					_reply(ACK);
				}
				else
				{
					if(_usr_packs == 0 || ((_usr_in_queue[0])&1) == 0)
					{
						#if DEBUG == 1
							USART0Println("STOP");
						#endif //if DEBUG == 1
						stop();
					}
					else
					{
						#if DEBUG == 1
							USART0Println("Switching to read mode...");
						#endif //if DEBUG == 1
						//_start();
						_status = I2C_STANDBY;
						start();
					}
					//_reply(NACK);
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
				if(_status == I2C_READ) //TODO: TEST IT!
				{
					//for(uint8_t i = 0; i < _out_queue[1]; i++)
						//_in_queue[_in_len++] = -1;
				}
				else if((_usr_in_queue[0] & 1) == 0)
				{
					//USART0Println("bypassing errors on try-to-read");
					//for(uint8_t i = 0; i < _usr_in_queue[1]; i++)
					//	_in_queue[_in_len++] = -1;
				}
				_status = I2C_FAIL;
				stop();
				break;
			}
			case 0x30:												//byte+NACK
			{
				#if DEBUG == 1
					USART0Println("0x30");
				#endif //if DEBUG == 1
				_status = I2C_FAIL;
				stop();
				break;
			}
			case 0x38:												//collision
			{
				#if DEBUG == 1
					USART0Println("0x38");
				#endif //if DEBUG == 1
				_status = I2C_FAIL;
				stop();
				break;
			}
			case 0x40:												//SLA+R+ACK
			{
				#if DEBUG == 1
					USART0Println("0x40");
				#endif //if DEBUG == 1
				if(_out_queue[1] <= 1)
					_reply(NACK);
				else
					_reply(ACK);
				break;
			}
			case 0x48:												//SLA+R+NACK
			{
				#if DEBUG == 1
					USART0Println("0x48");
				#endif //if DEBUG == 1
				_status = I2C_FAIL;
				stop();
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
				//USART0Println(_in_len);
				_in_queue[_in_len++] = TWDR;
				//USART0Print("\t\tq");
				//USART0Println(_out_queue[1]);
				_out_queue[1]--;
				if(_out_queue[1] <= 1)
					_reply(NACK);
				else
					_reply(ACK);
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
				//USART0Println(_in_len);
				//USART0Print("\t\t\t");
				//USART0Println((int)TWDR);
				_in_queue[_in_len++] = TWDR;
				_status = I2C_STANDBY;
				stop();
				break;
			}
			default:
			{
				#if DEBUG == 1
					USART0Print("DEFAULT");
				#endif //if DEBUG == 1
				_status = I2C_FAIL;
				stop();
			}
		}
		interrupt::call(interrupt::TWI);
	}

	
} // namespace twi


ISR(TWI_vect)
{
	twi::_ISR();
}
#pragma once
#include "USART.h"
#include "stringFuncs.h"

/*
 * Function getCountsOfDigits
 * Desc     Return num of digits
 * Input    __number: num for counting digits
 * Output   num of digits
*/
byte getCountsOfDigits(int __number) //get count of digits for int
{
	int __count = __number == 0;
	while (__number != 0)
	{
		__count++;
		__number /= 10;
	}
	return __count;
}

/*
 * Function getCountsOfDigits
 * Desc     Return num of digits
 * Input    __number: num for counting digits
 * Output   num of digits
*/
byte getCountsOfDigits(long __number) //get count of digits for long
{
	int __count = __number == 0;
	while (__number != 0)
	{
		__count++;
		__number /= 10;
	}
	return __count;
}

/*
 * Function getCountsOfDigits
 * Desc     Return num of digits
 * Input    __number: num for counting digits
 * Output   num of digits
*/
byte getCountsOfDigits(unsigned long __number) //get count of digits for long
{
	unsigned int __count = __number == 0;
	while (__number != 0)
	{
		__count++;
		__number /= 10;
	}
	return __count;
}

/*
 * Function getCountsOfDigits
 * Desc     Return num of digits
 * Input    __number: num for counting digits
 * Output   num of digits
*/
byte getCountsOfDigits(byte __number) //get count of digits for byte
{
	byte __count = __number == 0;
	while (__number != 0)
	{
		__count++;
		__number /= 10;
	}
	return __count;
}

/*
 * Function getCountsOfDigits
 * Desc     Return num of digits
 * Input    __number: num for counting digits
 * Output   num of digits
*/
byte getCountsOfDigits(uint16_t __number) //get count of digits for byte
{
	int __count = __number == 0;
	while (__number != 0)
	{
		__count++;
		__number /= 10;
	}
	return __count;
}

/*
 * Function getCountsOfBits
 * Desc     Return num of bits in num
 * Input    __in: num for counting
 * Output   num of bits
*/
int getCountsOfBits(uint64_t __in)//get count if digits for int
{
	byte __counter = 0;
	while(__in)
	{
		__counter++;
		__in >>= 1;
	}
	return __counter;
}

/*
 * Function dec2bin
 * Desc     convert dec num to byte char array
 * 			WARNING! Function is allocating memory!
 * Input    __in: dec num for converting
 * Output   ptr to char array with bin num
*/
char* dec2bin(uint64_t __in)
{

	byte __len = getCountsOfBits(__in);
	if(__in == 0)
	{
		__len = 1;
	}
	char *__res = (char*)malloc(__len + 1);
	__res[__len] = '\0';
	while(__len)
	{
		__len--;
		__res[__len] = ((__in & 1) == 1)? '1' : '0';// + '0';
		__in >>= 1;
	}
	return __res;
}

/*
 * Function bin2dec
 * Desc     convert binary char array to dec num
 * Input    __in: ptr to char array with binary num
 * Output   dec num
*/
int bin2dec(const char* __in)//convert bin num to dec int
{
	int __ret = 0;			//unsafe func! check for "none-numeric input
	while(*__in >= '0'
	&& *__in <= '9'
	&& *__in != 0x00)//WARNING! test this part
	{
		__ret <<= 1;
		__ret |= ((*__in)) - '0';
		__in++;
	}
	return __ret;
}

/*
 * Function str2int
 * Desc     convert C-string to integer num
 * Input    __in: ptr to char array with dec num
 * Output   dec num
*/
int str2int(const char* __in)//convert C-string to int
{
	int __ret = 0;			//unsafe func! check for "none-numeric input
	while(*__in >= '0'
	&& *__in <= '9'
	&& *__in != 0x00)//WARNING! test this part
	{
		__ret *= 10;
		__ret += (*__in) - '0';
		__in++;
	}
	return __ret;
}
/*
 * Function str2long
 * Desc     convert C-string to integer num
 * Input    __in: ptr to char array with dec num
 * Output   dec num
*/
long str2long(const char* __in)//convert C-string to long
{
	long __ret = 0;			//unsafe func! check for "none-numeric input
	while(*__in >= '0'
	&& *__in <= '9'
	&& *__in != 0x00)//WARNING! test this part
	{
		__ret *= 10;
		__ret += (*__in) - '0';
		__in++;
	}
	return __ret;
}
/*
 * Function str2byte
 * Desc     convert C-string to integer num
 * Input    __in: ptr to char array with dec num
 * Output   dec num
*/
byte str2byte(char* __in)//convert C-string to byte
{
	byte __ret = 0;			//unsafe func! check for "none-numeric input"
	while(*__in >= '0'
	&& *__in <= '9'
	&& *__in != 0x00)//WARNING! test this part
	{
		__ret *= 10;
		__ret += (*__in) - '0';
		__in++;
	}
	return __ret;
}

/*
 * Function int2str
 * Desc     convert int var to C-string
 * Input    __in: num for converting
 * Output   ptr to char array with num
*/
char* int2str(int __in)//convert int var to char array
{
	uint8_t __len = getCountsOfDigits(__in);
	char* __ret = (char*)malloc(__len + 1);//WARNING! memory leak!
	__ret[__len] = 0x00;
	while(__len)
	{
		__len--;
		__ret[__len] = (__in % 10) + '0';
		__in /= 10;
	}
	return __ret;
}
/*
 * Function long2str
 * Desc     convert int var to C-string
 * 			WARNING! Function is allocating memory!
 * Input    __in: num for converting
 * Output   ptr to char array with num
*/
char* long2str(long __in)//convert long var to char array
{
	uint8_t __len = getCountsOfDigits(__in);
	bool a = false;
	if(__in < 0)
	{
		__in = ~__in;
		__in++;
		__len++;
		a = true;
	}
	char* __ret = (char*)malloc(__len + 1);//WARNING! memory leak!
	__ret[__len] = 0x00;
	while(__len)
	{
		__len--;
		__ret[__len] = (__in % 10) + '0';
		__in /= 10;
	}
	if(a)
	{
		__ret[0] = '-';
	}
	return __ret;
}
/*
 * Function ulong2str
 * Desc     convert int var to C-string
 * 			WARNING! Function is allocating memory!
 * Input    __in: num for converting
 * Output   ptr to char array with num
*/
char* ulong2str(unsigned long __in)//convert long var to char array
{
	uint8_t __len = getCountsOfDigits(__in);
	char* __ret = (char*)malloc(__len + 1);//WARNING! memory leak!
	__ret[__len] = 0x00;
	while(__len)
	{
		__len--;
		__ret[__len] = (__in % 10) + '0';
		__in /= 10;
	}
	return __ret;
}
/*
 * Function byte2str
 * Desc     convert int var to C-string
 * 			WARNING! Function is allocating memory!
 * Input    __in: num for converting
 * Output   ptr to char array with num
*/
char* byte2str(byte __in)//convert byte var to char array
{
	uint8_t __len = getCountsOfDigits(__in);
	char* __ret = (char*)malloc(__len);//WARNING! memory leak!
	while(__len)
	{
		__len--;
		__ret[__len] = (__in % 10) + '0';
		__in /= 10;
	}
	return __ret;
}
/*
 * Function bool2str
 * Desc     convert int var to C-string
 * Input    __in: num for converting
 * Output   ptr to char array with num
*/
char* bool2str(bool __in)//convert bool var to char array
{
	if(__in)
	{
		return (char*)"true";
	}
	else
	{
		return (char*)"false";
	}
}

/*
 *	Function:	contains
 *	Desc:		Check input cstr for containing a char
 *	Input:		const char* _inbuf: input string(char array)
 				uint16_t _len: len of input char array
 				char _ch: what char search to
 *	Output:		bool
 */
bool contains(const char* _inbuf, uint16_t _len, char _ch)
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

/*
 *	Function:	contains
 *	Desc:		Check input cstr for containing a char
 *	Input:		char* _inbuf: input cstr
 				char _ch: what char search to
 *	Output:		bool
 */
bool contains(const char* _inbuf, char _ch)
{
	while(*_inbuf)
	{
		if(*_inbuf == _ch)
			return true;
		_inbuf++;
	}
	return false;
}

/*
 *	Function:	indexOf
 *	Desc:		Search for char in cstr and return index of char
 *	Input:		const char* _in: cstr
 				char _c: what char search to
 *	Output:		uint16_t: index of char
 */
uint16_t indexOf(const char* _in, char _c)
{
	uint16_t _ret = 0;
	while(*_in != 0)
	{
		if(*_in == _c)
			return _ret;
		_in++;
		_ret++;
	}
	return 0xFFFF;
}
/*
 *	Function:	indexOf
 *	Desc:		Search for char in cstr and return index of char
 *	Input:		const char* _in: cstr
 				uint16_t _len: len of cstr
 				char _c: what char search to
 *	Output:		uint16_t: index of char
 */
uint16_t indexOf(const char* _in, uint16_t _len, char _c)
{
	uint16_t _ret = 0;

	while(--_len)
	{
		if(_in[_len] == _c)
			return _len;
	}
	return 0xFFFF;
}
/*
 *	Function:	strCut
 *	Desc:		Cut substr from start index to end index
 *	Input:		const char* _in: cstr
 				uint16_t start: index of start
 				uint16_t end: index of end
 *	Output:		char*: ptr on cutted substr
 */
char* strCut(const char* _in, uint16_t start, uint16_t end)
{
	if(end >= start)
	{
		char* _arr = malloc(sizeof(char) * (end - start + 1));
		uint16_t i = 1;
		while(i <= end - start)
		{
			_arr[i - 1] = _in[start + i];
			i++;
		}
		_arr[end - start] = 0;
		return _arr;
	}
	else
		return 0;
}
/*
 *	Function:	strSplit
 *	Desc:		Cut substr from start char to end char
 				Example:	callling strSplit("qwerty(abc)uiop", '(', ')') will return "abc"
 *	Input:		const char* _in: cstr
 				char _opening: opening char
 				char _closing: closing char
 *	Output:		char*: ptr on cutted substr
 */
char* strSplit(const char* _in, char _opening, char _closing)
{
	uint16_t	opening = indexOf(_in, _opening),
				closing = indexOf(_in, _closing);
	// USART0Println((long)opening);
	// USART0Println((long)closing);
	if(closing - opening > 1)
	{
		char* _arr = strCut(_in, opening, closing - 1);
		return _arr;
	}
	else
		return 0;
}
/*
 *	Function:	strSplit
 *	Desc:		Cut substr from start char to end char
 				Example:	callling strSplit("qwerty(abc)uiop", strlen("qwerty(abc)uiop"), '(', ')') will return "abc"
 *	Input:		const char* _in: cstr
 				uint16_t _len: len of input cstr
 				char _opening: opening char
 				char _closing: closing char
 *	Output:		char*: ptr on cutted substr
 */
char* strSplit(const char* _in, uint16_t _len, char _opening, char _closing)
{
	uint16_t opening = indexOf(_in, _len, _opening);
	uint16_t closing = indexOf(_in, _len, _closing);
	if(closing - opening > 1)
	{
		char* _arr = strCut(_in, opening, closing - 1);
		return _arr;
	}
	else
		return 0;
}

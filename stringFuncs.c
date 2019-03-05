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
int getCountsOfBits(int __in)//get count if digits for int
{
	int __counter = 0;
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
char* dec2bin(int __in)
{
	
	byte __len = (int)getCountsOfBits(__in);
	if(__in == 0)
	{
		__len = 1;
	}
	char *__res = (char*)malloc(__len);
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
long str2long(char* __in)//convert C-string to long
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

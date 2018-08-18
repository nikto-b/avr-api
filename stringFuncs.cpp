

byte getCountsOfDigits(int __number__) //get count of digits for int
{
	int __count__ = __number__ == 0;
	while (__number__ != 0) 
	{
		__count__++;
		__number__ /= 10;
	}
	return __count__;
}
byte getCountsOfDigits(long __number__) //get count of digits for long
{
	int __count__ = __number__ == 0;
	while (__number__ != 0) 
	{
		__count__++;
		__number__ /= 10;
	}
	return __count__;
}
byte getCountsOfDigits(byte __number__) //get count of digits for byte
{
	int __count__ = __number__ == 0;
	while (__number__ != 0) 
	{
		__count__++;
		__number__ /= 10;
	}
	return __count__;
}

int getCountsOfBits(int __in__)//get count if digits for int
{
	int __counter__ = 0;
	while(__in__)
	{
		__counter__++;
		__in__ >>= 1;
	}
	return __counter__;
}
    
char* dec2bin(int __in__)//convert dec num to bin C-string
{
	if(__in__ == 0)
		return (char*)"0";//don't wanna to save warnings
	
	byte __len__ = (int)getCountsOfBits(__in__);
	char *__res__ = (char*)malloc(__len__);
	while(__len__)	
	{
		__len__--;
		__res__[__len__] = (__in__ & 1) + '0';
		__in__ >>= 1;
	}
	return __res__;
}

int bin2dec(char* __in__)//convert bin num to dec int
{
	int __ret__ = 0;			//unsafe func! check for "none-numeric input
	while(*__in__ >= '0' 
	&& *__in__ <= '9'
	&& *__in__ != 0x00)//WARNING! test this part
	{
		__ret__ <<= 1;
		__ret__ |= ((*__in__)) - '0';
		__in__++;
	}
	return __ret__;
}

int str2int(char* __in__)//convert C-string to int
{
	int __ret__ = 0;			//unsafe func! check for "none-numeric input
	while(*__in__ >= '0' 
	&& *__in__ <= '9'
	&& *__in__ != 0x00)//WARNING! test this part
	{
		__ret__ *= 10;
		__ret__ += (*__in__) - '0';
		__in__++;
	}
	return __ret__;
}
long str2long(char* __in__)//convert C-string to long
{
	long __ret__ = 0;			//unsafe func! check for "none-numeric input
	while(*__in__ >= '0' 
	&& *__in__ <= '9'
	&& *__in__ != 0x00)//WARNING! test this part
	{
		__ret__ *= 10;
		__ret__ += (*__in__) - '0';
		__in__++;
	}
	return __ret__;
}
byte str2byte(char* __in__)//convert C-string to byte
{
	byte __ret__ = 0;			//unsafe func! check for "none-numeric input
	while(*__in__ >= '0' 
	&& *__in__ <= '9'
	&& *__in__ != 0x00)//WARNING! test this part
	{
		__ret__ *= 10;
		__ret__ += (*__in__) - '0';
		__in__++;
	}
	return __ret__;
}

char* int2str(int __in__)//convert int var to char array
{
	uint8_t __len__ = getCountsOfDigits(__in__);
	char* __ret__ = (char*)malloc(__len__ + 1);
	__ret__[__len__] = 0x00;
	while(__len__)
	{
		__len__--;
		__ret__[__len__] = (__in__ % 10) + '0';
		__in__ /= 10;
	}
	return __ret__;
}
char* long2str(long __in__)//convert long var to char array
{
	uint8_t __len__ = getCountsOfDigits(__in__);
	char* __ret__ = (char*)malloc(__len__ + 1);
	__ret__[__len__] = 0x00;
	while(__len__)
	{
		__len__--;
		__ret__[__len__] = (__in__ % 10) + '0';
		__in__ /= 10;
	}
	return __ret__;
}
char* byte2str(byte __in__)//convert byte var to char array
{
	uint8_t __len__ = getCountsOfDigits(__in__);
	char* __ret__ = (char*)malloc(__len__);
	while(__len__)
	{
		__len__--;
		__ret__[__len__] = (__in__ % 10) + '0';
		__in__ /= 10;
	}
	return __ret__;
}
char* bool2str(bool __in__)//convert bool var to char array
{
	if(__in__)
	{
		return (char*)"true";
	}
	else
	{
		return (char*)"false";
	}
}

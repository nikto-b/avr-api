#include <iostream>

#define byte uint8_t

using namespace std;


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

int getCountsOfBits(int __in__)
{
	int __counter__ = 0;
	while(__in__)
	{
		__counter__++;
		__in__ >>= 1;
	}
	return __counter__;
}
    
char* dec2bin(int __in__)
{
	byte __len__ = (int)getCountsOfBits(__in__);
	char *__res__ = (char*)malloc(__len__);
	while(__len__)	
	{
		__res__[__len__] = (__in__ & 1) + '0';
		cout << (char)__res__[__len__] << endl;
		__in__ >>= 1;
		__len__--;
	}
	return __res__;
}

int str2int(char* __in__)//convert C-string to int
{
	int __ret__ = 0;
	while(*__in__ != 0x00)
	{
		__ret__ *= 10;
		__ret__ += (*__in__) - '0';
		__in__++;
	}
	return __ret__;
}

int main()
{
	//cout << (str2int("1") + str2int("2"));
	cout << dec2bin(2) << endl;
	//cout << getCountsOfBits(0) << endl;
	return 0;
}

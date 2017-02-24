#include "Helper.h"
#include "Common.h"

Helper::Helper()
{
}


Helper::~Helper()
{
}

string Helper::integerToBinary(int n, int maxBit)
{
	string result;
	for (int i = maxBit - 1; i >= 0; i--)
	{
		result += to_string(n >> i & 1);
	}
	return result;
}

unsigned int Helper::binaryToInteger(string str)
{
	unsigned int n = 0;
	for (int i = 0; i < INT4_BIT && str[i]; i++)
	{
		n *= 2;
		if (str[i] == '1')
		{
			n++;
		}
	}
	return n;
}

bool Helper::isEven(int n)
{
	return n % 2 == 0;
}

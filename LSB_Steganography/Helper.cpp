#include <string>
#include "Common.h"

using namespace std;

class Helper
{
public:
	static string integerToBinary(int n, int maxBit)
	{
		string result;
		for (int i = maxBit - 1; i >= 0; i--)
		{
			result += to_string(n >> i & 1);
		}
		return result;
	}

	static int binaryToInteger(string str)
	{
		int n = 0;
		for (int i = 0; i < 32 && str[i]; i++)
		{
			n *= 2;
			if (str[i] == '1')
			{
				n++;
			}
		}
		return n;
	}

	static bool isEven(int n)
	{
		return n % 2 == 0;
	}

	static bool isOdd(int n)
	{
		return !isEven(n);
	}
};

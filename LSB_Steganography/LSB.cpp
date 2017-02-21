#include <fstream>
#include "Common.h"
#include "Bitmap.cpp"
#include "Message.cpp"

using namespace std;
class LSB
{
public:
	static bool LSB::encrypt(Bitmap *bitmap, string inputFileName)
	{
		Message message;
		if (!message.readFile(inputFileName))
			return false;

		for (int i = 0; i < SIGNATURE_SIZE; i++)
			hide(bitmap->signature[i], SIGNATURE[i]);

		string messageLenght = Helper::integerToBinary(message.data.length(), INT4_BIT);
		for (int i = 0; i < INT4_BIT; i++)
			hide(bitmap->messageLenght[i], messageLenght[i]);
		
		string bits = convertToBits(message.data);
		for (int i = 0; i < bitmap->data.length(); i++)
		{
			if (i < bits.length())
				hide(bitmap->data[i], bits[i]);
		}

		return true;
	}
	static bool decrypt(const Bitmap *bitmap)
	{
		ofstream ofs("Images/decrypt.txt");

		if (!ofs.is_open())
		{
			return false;
		}

		string bits;
		for (int i = 0; i < INT4_BIT; i++)
		{
			bits += Helper::integerToBinary(bitmap->messageLenght[i], CHAR_BIT)[CHAR_BIT - 1];
		}
		int messageLenght = Helper::binaryToInteger(bits);

		bits = "";
		string message;
		for (int i = 0; i < messageLenght * CHAR_BIT;)
		{
			for (int j = 0; j < CHAR_BIT; j++)
			{
				bits += Helper::integerToBinary(bitmap->data[i++], CHAR_BIT)[CHAR_BIT - 1];
			}
			//message += char(Helper::binaryToInteger(bits));
			ofs << char(Helper::binaryToInteger(bits));
			bits = "";
		}
		
		ofs.close();
		return true;
	};
private:
	static string convertToBits(string str)
	{
		string result;
		for (int i = 0; i < str.length(); i++)
			result += Helper::integerToBinary(str[i], CHAR_BIT);
		return result;
	}

	// hide char b to ASCII a
	static void hide(char &a, char b)
	{
		if (Helper::isEven(a))
		{
			if (b == '1')
				a++;
		}
		else
		{
			if (b == '0')
				a--;
		}
	}
};

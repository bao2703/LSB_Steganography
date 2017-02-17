#include <fstream>
#include "Common.h"
#include "Bitmap.cpp"
#include "Helper.cpp"

using namespace std;
class LSB
{
public:
	static bool LSB::encrypt(Bitmap bitmap, char* inputFileName, char* outputFileName)
	{
		ofstream ofs(outputFileName, ios::binary);

		if (!ofs.is_open())
		{
			return false;
		}

		for (int i = 0; i < HEADER_SIZE; i++)
		{
			ofs << char(bitmap.header[i]);
		}

		for (int i = 0; i < SIGNATURE_SIZE; i++)
		{
			ofs << char(bitmap.signature[i]);
		}

		string message = readMessage(inputFileName);
		string bits = Helper::integerToBinary(message.length(), INT4_BIT);
		bits += convertToBits(message);

		for (int i = 0; i < bitmap.data.length(); i++)
		{
			if (i < bits.length())
			{
				if (Helper::isEven(bitmap.data[i]))
				{
					if (bits[i] == '1')
					{
						bitmap.data[i]++;
					}
				}
				else
				{
					if (bits[i] == '0')
					{
						bitmap.data[i]--;
					}
				}
			}
			ofs << bitmap.data[i];
		}

		ofs.close();

		return true;
	}
	static bool decrypt(Bitmap bitmap, char* outputFileName)
	{
		ofstream ofs(outputFileName, ios::binary);

		if (!ofs.is_open())
		{
			return false;
		}

		for (int i = 0; i < HEADER_SIZE; i++)
		{
			ofs << char(bitmap.header[i]);
		}

		for (int i = 0; i < SIGNATURE_SIZE; i++)
		{
			ofs << char(bitmap.signature[i]);
		}

		string bits;
		for (int i = 0; i < INT4_BIT; i++)
		{
			bits += Helper::integerToBinary(bitmap.data[i], CHAR_BIT)[CHAR_BIT - 1];
		}
		int messageLenght = Helper::binaryToInteger(bits);

		bits = "";
		string message;
		for (int i = INT4_BIT; i < messageLenght * CHAR_BIT + INT4_BIT;)
		{
			for (int j = 0; j < CHAR_BIT; j++)
			{
				bits += Helper::integerToBinary(bitmap.data[i++], CHAR_BIT)[CHAR_BIT - 1];
			}
			message += Helper::binaryToInteger(bits);
			bits = "";
		}

		ofs.close();
		return true;
	};
private:
	static string readMessage(char* fileName)
	{
		ifstream ifs(fileName);

		if (!ifs.is_open())
		{
			return "";
		}

		string result;
		int c;
		while ((c = ifs.get()) != EOF)
		{			
			result += c;
		}

		ifs.close();
		return result;
	}
	static string convertToBits(string str)
	{
		string result;
		for (int i = 0; i < str.length(); i++)
		{
			result += Helper::integerToBinary(str[i], CHAR_BIT);
		}
		return result;
	}
};

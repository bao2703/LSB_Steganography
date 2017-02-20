#include <fstream>
#include "Common.h"
#include "Bitmap.cpp"
#include <iostream>

using namespace std;
class LSB
{
public:
	static bool LSB::encrypt(Bitmap bitmap, string inputFileName, string outputFileName)
	{
		ofstream ofs(outputFileName, ios::binary);
		string message;
		try
		{
			message = readMessage(inputFileName);
		}
		catch (exception e)
		{
			cout << "Cannot open file: " + inputFileName << endl;
			return false;
		}

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
			if (Helper::isEven(bitmap.signature[i]))
			{
				if (SIGNATURE[i] == '1')
				{
					bitmap.signature[i]++;
				}
			}
			else
			{
				if (SIGNATURE[i] == '0')
				{
					bitmap.signature[i]--;
				}
			}
			ofs << char(bitmap.signature[i]);
		}
		
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
	static bool decrypt(Bitmap bitmap)
	{
		ofstream ofs("Images/decrypt.txt");

		if (!ofs.is_open())
		{
			return false;
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
			//message += char(Helper::binaryToInteger(bits));
			ofs << char(Helper::binaryToInteger(bits));
			bits = "";
		}
		
		ofs.close();
		return true;
	};
private:
	static string readMessage(string fileName)
	{
		ifstream ifs(fileName);

		if (!ifs.is_open())
		{
			throw exception();
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

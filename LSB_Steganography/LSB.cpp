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
			ofs << bitmap.header[i];
		}

		for (int i = 0; i < SIGNATURE_SIZE; i++)
		{
			hide(bitmap.signature[i], SIGNATURE[i]);
			ofs << bitmap.signature[i];
		}

		string messageLenght = Helper::integerToBinary(message.length(), INT4_BIT);
		for (int i = 0; i < INT4_BIT; ++i)
		{
			hide(bitmap.messageLenght[i], messageLenght[i]);
			ofs << bitmap.messageLenght[i];
		}
		
		string bits = convertToBits(message);
		for (int i = 0; i < bitmap.data.length(); i++)
		{
			if (i < bits.length())
			{
				hide(bitmap.data[i], bits[i]);
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
			bits += Helper::integerToBinary(bitmap.messageLenght[i], CHAR_BIT)[7];
		}
		int messageLenght = Helper::binaryToInteger(bits);

		bits = "";
		string message;
		for (int i = 0; i < messageLenght * CHAR_BIT;)
		{
			for (int j = 0; j < CHAR_BIT; j++)
			{
				bits += Helper::integerToBinary(bitmap.data[i++], CHAR_BIT)[7];
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

	// hide char b to ASCII a
	static void hide(char &a, char b)
	{
		if (Helper::isEven(a))
		{
			if (b == '1')
			{
				a++;
			}
		}
		else
		{
			if (b == '0')
			{
				a--;
			}
		}
	}
};

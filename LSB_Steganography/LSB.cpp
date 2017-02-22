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
			encode(bitmap->signature[i], SIGNATURE[i]);

		string fileNameBits = convertToBits(message.fileName);
		for (int i = 0; i < FILE_NAME_LENGHT * CHAR_BIT; i++)
			encode(bitmap->messageFileName[i], fileNameBits[i]);

		string fileExtensionBits = convertToBits(message.fileExtension);
		for (int i = 0; i < FILE_EXTENSION_LENGHT * CHAR_BIT; i++)
			encode(bitmap->messageExtension[i], fileExtensionBits[i]);

		string messageLenght = Helper::integerToBinary(message.data.length(), INT4_BIT);
		for (int i = 0; i < INT4_BIT; i++)
			encode(bitmap->messageLenght[i], messageLenght[i]);
		
		string bits = convertToBits(message.data);
		for (int i = 0; i < bitmap->data.length(); i++)
		{
			if (i < bits.length())
				encode(bitmap->data[i], bits[i]);
		}

		return true;
	}
	static bool decrypt(const Bitmap *bitmap)
	{
		string bits;
		Message message;
		int j = 0;
		
		for (int i = 0; i < INT4_BIT; i++)
			bits += decode(bitmap->messageLenght[i]);
		int messageLenght = Helper::binaryToInteger(bits);

		int index = 0;
		bits = "";
		for (int i = 0; i < FILE_NAME_LENGHT * CHAR_BIT; i++)
		{
			bits += decode(bitmap->messageFileName[i]);
			if (++j == 8)
			{
				message.fileName[index++] = char(Helper::binaryToInteger(bits));
				j = 0;
				bits = "";
			}
		}

		index = 0;
		bits = "";
		for (int i = 0; i < FILE_EXTENSION_LENGHT * CHAR_BIT; i++)
		{
			bits += decode(bitmap->messageExtension[i]);
			if (++j == 8)
			{
				message.fileExtension[index++] = char(Helper::binaryToInteger(bits));
				j = 0;
				bits = "";
			}
		}

		string fullFileName = message.fileName;
		fullFileName += ".";
		fullFileName += message.fileExtension;
		ofstream ofs(fullFileName);
		if (!ofs.is_open())
			return false;

		bits = "";
		for (int i = 0; i < messageLenght * CHAR_BIT; i++)
		{	
			bits += decode(bitmap->data[i]);	
			if (++j == 8)
			{
				message.data += char(Helper::binaryToInteger(bits));
				j = 0;
				bits = "";
				ofs << char(Helper::binaryToInteger(bits));
			}
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
	static void encode(char &a, char b)
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

	static char decode(char a)
	{
		return Helper::isEven(a) ? '0' : '1';
	}
};

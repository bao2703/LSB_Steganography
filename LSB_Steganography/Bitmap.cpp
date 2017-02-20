#include <fstream>
#include "Common.h"
#include "Helper.cpp"
using namespace std;

class Bitmap
{
public:
	int header[HEADER_SIZE];
	int signature[SIGNATURE_SIZE];
	//int messageFileName[FILE_NAME_LENGHT * 8];
	//int messageExtension[FILE_EXTENSION_LENGHT * 8];
	//int messageLenght[32];
	string data;
	bool readFile(string fileName)
	{
		ifstream ifs(fileName, ios::binary);

		if (!ifs.is_open())
		{
			return false;
		}

		for (int i = 0; i < HEADER_SIZE; i++)
		{
			header[i] = ifs.get();
		}

		for (int i = 0; i < SIGNATURE_SIZE; i++)
		{
			signature[i] = ifs.get();
		}

		data = "";
		int c;
		while ((c = ifs.get()) != EOF)
		{
			data += c;
		}

		ifs.close();
		return true;
	}

	bool isEncrypted() const
	{
		for (int i = 0; i < SIGNATURE_SIZE; i++)
		{
			if (Helper::integerToBinary(signature[i], CHAR_BIT)[CHAR_BIT - 1] != SIGNATURE[i])
			{
				return false;
			}
		}
		return true;
	}
};
#include <fstream>
#include "Common.h"
#include "Helper.cpp"
using namespace std;

class Bitmap
{
public:
	char header[HEADER_SIZE];
	char signature[SIGNATURE_SIZE];
	char messageFileName[FILE_NAME_LENGHT * CHAR_BIT];
	char messageExtension[FILE_EXTENSION_LENGHT * CHAR_BIT];
	char messageLenght[INT4_BIT];
	string data;
	bool readFile(string fileName)
	{
		ifstream ifs(fileName, ios::binary);

		if (!ifs.is_open())
			return false;

		for (int i = 0; i < HEADER_SIZE; i++)
			header[i] = ifs.get();

		for (int i = 0; i < SIGNATURE_SIZE; i++)
			signature[i] = ifs.get();

		for (int i = 0; i < FILE_NAME_LENGHT * CHAR_BIT; i++)
			messageFileName[i] = ifs.get();

		for (int i = 0; i < FILE_EXTENSION_LENGHT * CHAR_BIT; i++)
			messageExtension[i] = ifs.get();

		for (int i = 0; i < INT4_BIT; i++)
			messageLenght[i] = ifs.get();

		data = "";
		int c;
		while ((c = ifs.get()) != EOF)
		{
			data += c;
		}

		ifs.close();
		return true;
	}

	bool writeFile(string fileName)
	{
		ofstream ofs(fileName, ios::binary);

		if (!ofs.is_open())
			return false;

		for (int i = 0; i < HEADER_SIZE; i++)
			ofs << header[i];

		for (int i = 0; i < SIGNATURE_SIZE; i++)
			ofs << signature[i];

		for (int i = 0; i < FILE_NAME_LENGHT * CHAR_BIT; i++)
			ofs << messageFileName[i];

		for (int i = 0; i < FILE_EXTENSION_LENGHT * CHAR_BIT; i++)
			ofs << messageExtension[i];

		for (int i = 0; i < INT4_BIT; ++i)
			ofs << messageLenght[i];

		for (int i = 0; i < data.length(); i++)
			ofs << data[i];

		ofs.close();
		return true;
	}

	bool isEncrypted() const
	{
		for (int i = 0; i < SIGNATURE_SIZE; i++)
		{
			if (Helper::integerToBinary(signature[i], CHAR_BIT)[CHAR_BIT - 1] != SIGNATURE[i])
				return false;
		}
		return true;
	}
};
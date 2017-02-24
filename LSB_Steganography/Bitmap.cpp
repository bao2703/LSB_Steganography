#include "Bitmap.h"
#include <fstream>

Bitmap::Bitmap()
{
}


Bitmap::~Bitmap()
{
}

bool Bitmap::readFile(string fileName)
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

bool Bitmap::writeFile(string fileName)
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

bool Bitmap::isEncrypted()
{
	for (int i = 0; i < SIGNATURE_SIZE; i++)
	{
		if (Helper::integerToBinary(signature[i], CHAR_BIT)[CHAR_BIT - 1] != SIGNATURE[i])
			return false;
	}
	return true;
}

int Bitmap::getCapacity()
{
	return data.length() / CHAR_BIT;
}

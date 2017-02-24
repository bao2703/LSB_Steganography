#pragma once
#include "Common.h"
#include "Helper.h"

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

	Bitmap();
	~Bitmap();
	bool readFile(string fileName);
	bool writeFile(string fileName);
	bool isEncrypted();
	int getCapacity();
};

#pragma once
#include "Common.h"
#include <string>

using namespace std;

class Message
{
public:
	char fileName[FILE_NAME_LENGHT + 1];
	char fileExtension[FILE_EXTENSION_LENGHT + 1];
	string data;

	Message();
	~Message();
	bool readFile(string fileName);
};

#include "Message.h"
#include <fstream>

Message::Message()
{
}


Message::~Message()
{
}

bool Message::readFile(string fileName)
{
	if (fileName.length() != FILE_NAME_LENGHT + FILE_EXTENSION_LENGHT + 1)
		return false;

	ifstream ifs(fileName);

	if (!ifs.is_open())
		return false;

	for (int i = 0; i < FILE_NAME_LENGHT; i++)
		this->fileName[i] = fileName[i];

	for (int i = 0; i < FILE_EXTENSION_LENGHT; i++)
		fileExtension[i] = fileName[FILE_NAME_LENGHT + i + 1];

	data = "";
	int c;
	while ((c = ifs.get()) != EOF)
	{
		data += c;
	}

	ifs.close();
	return true;
}

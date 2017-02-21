#include <fstream>
#include "Common.h"

using namespace std;
class Message
{
public:
	char fileName[FILE_NAME_LENGHT];
	char fileExtension[FILE_EXTENSION_LENGHT];
	string data;

	bool readFile(string fileName)
	{
		if (fileName.length() != FILE_NAME_LENGHT + FILE_EXTENSION_LENGHT + 1)
			return false;

		ifstream ifs(fileName);

		if (!ifs.is_open())
			return false;

		for (int i = 0; i < FILE_NAME_LENGHT; i++)
			this->fileName[i] = fileName[i];

		for (int i = 0; i < FILE_EXTENSION_LENGHT; i++)
			fileExtension[i] = fileName[FILE_NAME_LENGHT + i];

		data = "";
		int c;
		while ((c = ifs.get()) != EOF)
		{
			data += c;
		}

		ifs.close();
		return true;
	}
};
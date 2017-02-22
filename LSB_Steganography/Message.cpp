#include <fstream>
#include "Common.h"

using namespace std;
class Message
{
public:
	char fileName[FILE_NAME_LENGHT + 1];
	char fileExtension[FILE_EXTENSION_LENGHT + 1];
	string data;

	bool readFile(string fileName)
	{
		string shortFileName(strrchr(fileName.c_str(), '/') + 1);
		if (shortFileName.length() != FILE_NAME_LENGHT + FILE_EXTENSION_LENGHT + 1)
			return false;

		ifstream ifs(fileName);

		if (!ifs.is_open())
			return false;

		for (int i = 0; i < FILE_NAME_LENGHT; i++)
			this->fileName[i] = shortFileName[i];

		for (int i = 0; i < FILE_EXTENSION_LENGHT; i++)
			fileExtension[i] = shortFileName[FILE_NAME_LENGHT + i + 1];

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
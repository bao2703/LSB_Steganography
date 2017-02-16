#include <fstream>
#include "Common.h"
#include "Bitmap.cpp"

using namespace std;
class LSB
{
public:
	static bool LSB::encode(Bitmap bitmap, char* outputFileName)
	{
		ofstream ofs(outputFileName, ios::binary);

		if (!ofs.is_open()) return false;

		for (int i = 0; i < HEADER_SIZE; i++)
		{
			ofs << char(bitmap.header[i]);
		}

		for (int i = 0; i < SIGNATURE_SIZE; ++i)
		{
			ofs << char(bitmap.signature[i]);
		}

		for (int i = 0; i < bitmap.data.length(); ++i)
		{
			ofs << char(bitmap.data[i]);
		}

		ofs.close();

		return true;
	}
	static bool decode(char* fileName);
private:
};


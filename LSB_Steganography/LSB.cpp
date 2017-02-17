#include <fstream>
#include "Common.h"
#include "Bitmap.cpp"
#include "Helper.cpp"

using namespace std;
class LSB
{
public:
	static bool LSB::encrypt(Bitmap bitmap, char* inputFileName, char* outputFileName)
	{
		
		ofstream ofs(outputFileName, ios::binary);

		if (ofs.fail()) 
		{
			return false;
		}

		for (int i = 0; i < HEADER_SIZE; i++)
		{
			ofs << char(bitmap.header[i]);
		}

		for (int i = 0; i < SIGNATURE_SIZE; ++i)
		{
			ofs << char(bitmap.signature[i]);
		}

		string bits = readMessage(inputFileName);

		bits = Helper::integerToBinary(bits.length(), INT4_BIT) + bits;

		for (int i = 0; i < bitmap.data.length(); ++i)
		{
			if (i < bits.length())
			{
				if (Helper::isEven(bitmap.data[i]))
				{
					if (bits[i] == '1')
					{
						bitmap.data[i]++;
					}
				}
				else
				{
					if (bits[i] == '0')
					{
						bitmap.data[i]--;
					}
				}
			}
			ofs << bitmap.data[i];
		}

		ofs.close();

		return true;
	}
	static bool decode(char* fileName);
private:
	static string readMessage(char* fileName)
	{
		ifstream ifs(fileName);

		if (ifs.fail())
		{
			throw exception();
		}

		string str;
		int c;
		while ((c = ifs.get()) != EOF)
		{			
			str += Helper::integerToBinary(c, CHAR_BIT);
		}

		ifs.close();
		return str;
	}
};


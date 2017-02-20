#include <iostream>
#include <fstream>
#include "LSB.cpp"

using namespace std;

void main()
{
	Bitmap bitmap;	

	cout << "1. Encrypt" << endl;
	cout << "2. Decrypt" << endl;

	int choose;
	cin >> choose;

	cout << "Input bitmap location: " << endl;
	string bitmapFileName;
	//cin >> bitmapFileName;

	cout << "Input message file location: " << endl;
	string messageFileName;
	//cin >> messageFileName;

	cout << "Input output file location: " << endl;
	string outputFileName;
	//cin >> outputFileName;

	//if (!bitmap.readFile("Images/bitmap.bmp"))
	if (!bitmap.readFile("Images/encrypted.bmp"))
	//if (!bitmap.readFile(bitmapFileName))
	{
		cout << "Cannot open file: " + bitmapFileName;
		system("PAUSE");
		return;
	}

	if (choose == 1)
	{
		//LSB::encrypt(bitmap, messageFileName, outputFileName);
		LSB::encrypt(bitmap, "Images/text.txt", "Images/encrypted.bmp");
	}
	else if (choose == 2)
	{
		if (!bitmap.isEncrypted())
		{
			cout << "Bitmap file is not encrypted, please check message input location!";
			system("PAUSE");
			return;
		}
		LSB::decrypt(bitmap);
	}

	system("PAUSE");
}
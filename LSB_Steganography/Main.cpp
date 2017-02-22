#include <iostream>
#include <fstream>
#include "LSB.cpp"

using namespace std;

void main()
{
	Bitmap *bitmap = new Bitmap();	

	cout << "1. Encrypt" << endl;
	cout << "2. Decrypt" << endl;

	int choose;
	cin >> choose;

	//cout << "Input bitmap location: " << endl;
	//string bitmapFileName;
	//cin >> bitmapFileName;

	//cout << "Input message file location: " << endl;
	//string messageFileName;
	//cin >> messageFileName;

	//cout << "Input output file location: " << endl;
	//string outputFileName;
	//cin >> outputFileName;

	/*if (!bitmap.readFile(bitmapFileName))
	{
		cout << "Cannot open file: " + bitmapFileName;
		system("PAUSE");
		return;
	}*/

	if (choose == 1)
	{
		bitmap->readFile("Images/bitmap.bmp");
		//LSB::encrypt(bitmap, messageFileName, outputFileName);
		if(LSB::encrypt(bitmap, "Images/12345678.txt"))
			bitmap->writeFile("Images/encrypted.bmp");
	}
	else if (choose == 2)
	{
		bitmap->readFile("Images/encrypted.bmp");
		if (!bitmap->isEncrypted())
		{
			cout << "Bitmap file is not encrypted, please check message input location!";
			system("PAUSE");
			return;
		}
		LSB::decrypt(bitmap);
	}

	delete bitmap;
	system("PAUSE");
}
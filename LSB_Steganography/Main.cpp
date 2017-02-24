#include <iostream>
#include "LSB.h"

using namespace std;

Bitmap* bitmap = new Bitmap();

void encrypt()
{
	cout << "Nhap ten file thong tin can giau: " << endl;
	string messageFileName;
	cin >> messageFileName;

	Message* message = new Message();

	if (!message->readFile(messageFileName))
	{
		cout << "Khong the doc file thong tin can giau: " + messageFileName << endl;
		return;
	}
	if (!LSB::encrypt(bitmap, message))
	{
		cout << "Suc chua file bitmap khong du." << endl;
		return;
	}

	cout << "Nhap ten file bitmap output: " << endl;
	string outputFileName;
	cin >> outputFileName;

	if (!bitmap->writeFile(outputFileName))
	{
		cout << "Khong the ghi file bitmap: " + outputFileName << endl;
		return;
	}
}

void decrypt()
{
	if (!bitmap->isEncrypted())
	{
		cout << "File bitmap chua duoc giau thong tin." << endl;
		return;
	}
	if (!LSB::decrypt(bitmap))
	{
		cout << "Giai nen that bai." << endl;
		return;
	}
}

void main()
{
	cout << "1. Encrypt" << endl;
	cout << "2. Decrypt" << endl;

	int choose;
	cin >> choose;

	cout << "Nhap ten file bitmap: " << endl;
	string bitmapFileName;
	cin >> bitmapFileName;

	if (!bitmap->readFile(bitmapFileName))
	{
		cout << "Khong the doc file bitmap: " + bitmapFileName << endl;
		delete bitmap;
		system("PAUSE");
		return;
	}

	if (choose == 1)
	{
		encrypt();
	}
	else if (choose == 2)
	{
		decrypt();
	}

	delete bitmap;
	system("PAUSE");
}

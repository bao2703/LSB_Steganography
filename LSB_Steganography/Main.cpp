#include <iostream>
#include <fstream>
#include "LSB.cpp"

using namespace std;

void main()
{
	Bitmap bitmap;
	bitmap.readFile("Images/bitmap.bmp");
	LSB::encrypt(bitmap, "Images/text.txt", "Images/encrypt_test.bmp");

	bitmap.readFile("Images/bitmap_encrypted.bmp");
	LSB::decrypt(bitmap, "Images/decrypt_test.bmp");

	//cout << Helper::integerToBinary(19, 8);
	//cout << Helper::binaryToInteger("00010011");
	system("PAUSE");
}
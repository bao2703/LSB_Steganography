#include <iostream>
#include <fstream>
#include "LSB.cpp"
#include "Helper.cpp"

using namespace std;

void main()
{
	Bitmap bitmap;
	bitmap.readFile("Images/bitmap.bmp");
	LSB::encode(bitmap, "Images/test.bmp");

	//LSB::decode(nullptr);
	//cout << Helper::integerToBinary(255);
	//cout << Helper::binaryToInteger("11111111111111111111111111111111");
	system("PAUSE");
}
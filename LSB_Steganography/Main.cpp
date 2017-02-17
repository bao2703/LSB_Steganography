#include <iostream>
#include <fstream>
#include "LSB.cpp"

using namespace std;

void main()
{
	Bitmap bitmap;
	bitmap.readFile("Images/bitmap.bmp");
	LSB::encrypt(bitmap, "Images/text.txt", "Images/test.bmp");
	
	//LSB::decode(nullptr);
	//cout << Helper::integerToBinary(255, 8);
	//cout << Helper::binaryToInteger("11111111111111111111111111111111");
	system("PAUSE");
}
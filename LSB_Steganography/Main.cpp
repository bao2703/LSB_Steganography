#include <iostream>
#include <fstream>
#include "LSB.cpp"

using namespace std;

void main()
{
	LSB::encode("Images/bitmap3.bmp", "Images/test.bmp");
	//LSB::decode(nullptr);

	system("PAUSE");
}
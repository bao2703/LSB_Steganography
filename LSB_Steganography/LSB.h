#pragma once
#include "Bitmap.h"
#include "Message.h"

class LSB
{
public:
	LSB();
	~LSB();
	static bool encrypt(Bitmap* bitmap, const Message* message);
	static bool decrypt(const Bitmap* bitmap);
private:
	/**
	* \brief Convert string to string bits
	* \param str
	* \return
	*/
	static string convertToBits(string str);
	/**
	* \brief Hide 1 bit to char ch
	* \param ch
	* \param bit
	*/
	static void encode(char& ch, char bit);
	static char decode(char a);
};

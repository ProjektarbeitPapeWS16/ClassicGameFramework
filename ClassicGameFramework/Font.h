#pragma once
#include <map>

class Font
{
	int fontSize, fontWidth;
	
	//std::map<char, char*>* letterImagePathBinding;
	std::map<char, unsigned char*>* letterImageBytes;
	unsigned short transR;
	unsigned short transG;
	unsigned short transB;
	char* folder;
public:
	Font(char* folder, int fontSize, int fontWidth, unsigned short transR, unsigned short transG, unsigned short transB);
	unsigned char* getImageBytesForLetter(char letter) const;
	int getFontSize() const;
	int getFontWidth() const;
	unsigned short getTransR() const;
	unsigned short getTransG() const;
	unsigned short getTransB() const;
};

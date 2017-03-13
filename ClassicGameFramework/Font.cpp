#include "Font.h"
#include <fstream>

Font::Font(char* folder, int fontSize, int fontWidth, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256) :
	fontSize(fontSize),
	fontWidth(fontWidth),
	transR(transR),
	transG(transG),
	transB(transB),
	folder(folder)
{
}
/*
unsigned char* Font::getImageBytesForLetter(char letter) const
{
	if (letterImageBytes->find(letter) == letterImageBytes->end())
	{
		auto length = fontSize * fontWidth * 4;
		auto ret = new unsigned char[length];
		auto imagePath = std::string(folder) + letter + ".bmp";

		auto f = std::ifstream(imagePath);

		if (imagePath[0] == '\0' || !f.good())
		{
			f.close();

			for (auto i = 0; i < length; i++)
			{
				ret[i] = 0x00;
			}
		}
		else
		{
			f.close();

			FILE* file;
			fopen_s(&file, imagePath.c_str(), "rb");

			if (file == nullptr)
			{
				return nullptr;
			}

			// obtain file size:
			fseek(file, 0, SEEK_END);
			auto lSize = ftell(file);
			rewind(file);

			auto data = new unsigned char[lSize];
			fread(data, lSize, 1, file);
			fclose(file);


			// extract image height and width from header 
			auto imageWidth = *reinterpret_cast<int*>(&data[18]);
			auto imageHeight = *reinterpret_cast<int*>(&data[22]);
			if (imageWidth != fontWidth || imageHeight != fontSize)
			{
				return ret;
			}


			auto padding = 0;
			while ((imageWidth * 3 + padding) % 4 != 0)
			{
				padding++;
			}
			auto widthnew = imageWidth * 3 + padding;

			//auto endPos = 54 + (widthnew * height);

			for (auto line = 0; line < imageHeight; line++)
			{
				for (auto column = 0, retcolumn = 0; column < widthnew - padding; column += 3 , retcolumn += 4)
				{
					auto ri = line * (imageWidth * 4) + retcolumn;
					auto gi = ri + 1;
					auto bi = ri + 2;
					auto ai = ri + 3;

					ret[ri] = data[line * widthnew + column + 54 + 2];
					ret[gi] = data[line * widthnew + column + 54 + 1];
					ret[bi] = data[line * widthnew + column + 54 + 0];

					if (transR != 256 && transB != 256 && transG != 256 && ret[ri] == static_cast<unsigned char>(transR) && ret[gi] == static_cast<unsigned char>(transG) && ret[bi] == static_cast<unsigned char>(transB))
					{
						ret[ai] = 0;
					}
					else
					{
						ret[ai] = 255;
					}
				}
			}

			delete[] data;
		}


		letterImageBytes->insert(std::make_pair(letter, ret));
	}

	return letterImageBytes->at(letter);
}
*/

int Font::getFontSize() const
{
	return fontSize;
}

int Font::getFontWidth() const
{
	return fontWidth;
}

unsigned short Font::getTransR() const
{
	return transR;
}

unsigned short Font::getTransG() const
{
	return transG;
}

unsigned short Font::getTransB() const
{
	return transB;
}

Image* Font::getImageForLetter(char letter)
{
	if(images.find(letter) == images.end())
	{
		images.insert_or_assign(letter, new Image(getPathFor(letter), 200, 80, 0));
	}
	return images.at(letter);
}

const char* Font::getPathFor(char letter) const
{
	std::string replacement;
	switch(letter)
	{
	case '?': replacement = "questionmark"; break;
	case '(': replacement = "paran_open"; break;
	case ')': replacement = "paran_close"; break;
	case ',': replacement = "comma"; break;
	case '.': replacement = "point"; break;
	case '-': replacement = "dash"; break;
	case ' ': replacement = "space"; break;

	default: replacement = letter; break;
	}



	std::string str_path = std::string(folder) + replacement + ".bmp";
	char* c_path = new char[str_path.length() + 1];
	for(int i = 0; i < str_path.length(); i++)
	{
		c_path[i] = str_path[i];
	}
	c_path[str_path.length()] = '\0';

	return c_path;
}

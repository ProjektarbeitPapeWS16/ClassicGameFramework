#include "Font.h"
#include <fstream>

Font::Font(char* folder, int fontSize, int fontWidth, unsigned short transR = 256, unsigned short transG = 256, unsigned short transB = 256) :
	fontSize(fontSize),
	fontWidth(fontWidth),
	letterImageBytes(new std::map<char, unsigned char*>()),
	transR(transR),
	transG(transG),
	transB(transB),
	folder(folder)
{
}

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

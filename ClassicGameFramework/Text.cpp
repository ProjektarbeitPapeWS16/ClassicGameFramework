#include "Text.h"
#include "Font.h"
#include "Position.h"
#include "Image.h"
#include <locale>

void Text::setWidth(int width)
{
	return; //already set through font-width
}

void Text::setHeight(int height)
{
	return; //already set through font-size
}

void Text::setPosX(int posX)
{
	boundaries->position.x = posX;
}

void Text::setPosY(int posY)
{
	boundaries->position.y = posY;
}

int Text::getWidth()
{
	return boundaries->width * scale;
}

int Text::getHeight()
{
	return boundaries->height * scale;
}

int Text::getPosX()
{
	return boundaries->position.x;
}

int Text::getPosY()
{
	return boundaries->position.y;
}

Image* Text::getImage()
{
	if (!isLoaded())
	{
		loadImage();
	}

	return image;
}

void Text::setText(const char* text)
{
	image = nullptr;
	this->text = std::string(text);
	toUpper();
	countLetters();
	generateBoundaries();
	loadImage();
}

void Text::toUpper()
{
	for (auto& c : this->text)
	{
		c = toupper(c);
	}
}

void Text::countLetters()
{
	// count letters
	this->textLength = this->text.length();
}

void Text::generateBoundaries() const
{
	this->boundaries->width = this->textLength * this->font->getFontWidth();
	this->boundaries->height = this->font->getFontSize();
}

Text::Text(Font* font, const char* text, Position* position, Anchor anchor, double scale, unsigned char R, unsigned char G, unsigned char B, unsigned char backR, unsigned char backG, unsigned char backB) :
	Entity(new Image*[0], 0, false, new Boundaries(position->x, position->y, 0, 0), false, 0),
	anchor(anchor),
	textLength(0),
	//textWidth(0),
	//textHeight(font->getFontSize()),
	font(font),
	image(nullptr),
	R(255.0 / R),
	G(255.0 / G),
	B(255.0 / B),
	scale(scale),
	backgroundSet(true),
backR(backR), backG(backG), backB(backB)
{
}

Text::Text(Font* font, const char* text, Position* position, Anchor anchor, double scale, unsigned char R, unsigned char G, unsigned char B) :
	Text(font, text, position, anchor, scale, R, G, B, 0, 0, 0)
{
	backgroundSet = false;
}

Text::Text(Font* font, const char* text, Position* position, double scale = 1.0, unsigned char R = 255, unsigned char G = 255, unsigned char B = 255) :
	Text(font, text, position, LEFT, scale, R, G, B)

{
	setText(text);
}

Text::~Text()
{
	delete image;
}


void Text::loadImage()
{
	if (isLoaded())
	{
		return;
	}

	letters.clear();
	for (auto i = 0; i < textLength; i++)
	{
		letters.push_back(font->getImageForLetter(text[i]));
	}


	auto letterImageBytesLength = font->getFontWidth() * font->getFontSize() * 4;
	auto imageBytes = new unsigned char[textLength * letterImageBytesLength];

	for (auto i = 0; i < textLength; i++)
	{
		auto letterBytes = letters.at(i)->getImageBytes();
		auto offset = i * font->getFontWidth() * 4;

		for (auto relIndex = 0; relIndex < letterImageBytesLength; relIndex+= 4)
		{
			auto absRowLength = textLength * font->getFontWidth() * 4;
			auto row = relIndex / (font->getFontWidth() * 4);
			auto column = relIndex % (font->getFontWidth() * 4);
			auto absIndex = offset + (row * absRowLength) + column;
			//auto channel = relIndex % 4;
			if(!letterBytes)
			{
				imageBytes[absIndex] = 0;
				imageBytes[absIndex+1] = 0;
				imageBytes[absIndex+2] = 0;
				imageBytes[absIndex+3] = 255;
				continue;
			}
			auto colorValueR = letterBytes[relIndex];
			auto colorValueG = letterBytes[relIndex+1];
			auto colorValueB = letterBytes[relIndex+2];
			auto colorValueA = letterBytes[relIndex+3];
			auto colorValueMultiplierR = static_cast<double>(colorValueR) / 255.0;
			auto colorValueMultiplierG = static_cast<double>(colorValueG) / 255.0;
			auto colorValueMultiplierB = static_cast<double>(colorValueB) / 255.0;

			imageBytes[absIndex]   = backgroundSet && colorValueA == 0 ? backR : static_cast<unsigned char>(colorValueMultiplierR * R * 255);
			imageBytes[absIndex+1] = backgroundSet && colorValueA == 0 ? backG : static_cast<unsigned char>(colorValueMultiplierG * G * 255);
			imageBytes[absIndex+2] = backgroundSet && colorValueA == 0 ? backB : static_cast<unsigned char>(colorValueMultiplierB * B * 255);
			imageBytes[absIndex+3] = backgroundSet ? 255 : colorValueA;
		}
	}

	if (image)
	{
		delete image;
	}

	image = new Image(imageBytes, boundaries->width, boundaries->height, font->getTransR(), font->getTransG(), font->getTransB());
}


std::string Text::getText() const
{
	return text;
}

Font* Text::getFont() const
{
	return font;
}

bool Text::isLoaded() const
{
	return image != nullptr;
}

int Text::getTextLength() const
{
	return textLength;
}

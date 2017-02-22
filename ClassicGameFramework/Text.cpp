#include "Text.h"
#include "Font.h"
#include "Position.h"
#include "Image.h"
#include <iostream>
#include "../SpacePanic/GameConfig.h"
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

Text::Text(Font* font, const char* text, Position* position, double scale = 1.0, unsigned char R = 255, unsigned char G = 255, unsigned char B = 255) :
	Entity(nullptr, 0, false, nullptr, false ,0),
textLength(0),
	//textWidth(0),
	//textHeight(font->getFontSize()),
	font(font),
	//position(position),
	image(nullptr),
	text(std::string(text)),
	R(255.0 / R),
	G(255.0 / G),
	B(255.0 / B),
	scale(scale)
{
	for (auto & c : this->text) {
		c = toupper(c);
	}

	// count letters
	while (this->text[this->textLength] != '\0')
	{
		this->textLength++;
	}

	//this->textWidth = this->textLength * font->getFontWidth();

	boundaries = new Boundaries(position->x, position->y, this->textLength * font->getFontWidth(), font->getFontSize());
}

Text::~Text()
{
}


void Text::loadImage()
{
	if (isLoaded())
	{
		return;
	}


	auto letterImageBytesLength = font->getFontWidth() * font->getFontSize() * 4;
	auto imageBytes = new unsigned char[textLength * letterImageBytesLength];

	for (auto i = 0; i < textLength; i++)
	{
		auto letterBytes = font->getImageBytesForLetter(text[i]);
		auto offset = i * font->getFontWidth() * 4;

		for (auto relIndex = 0; relIndex < letterImageBytesLength; relIndex++)
		{
			auto absRowLength = textLength * font->getFontWidth() * 4;
			auto row = relIndex / (font->getFontWidth() * 4);
			auto column = relIndex % (font->getFontWidth() * 4);
			auto absIndex = offset + (row * absRowLength) + column;
			auto channel = relIndex % 4;

			auto colorValue = letterBytes[relIndex];
			auto colorValueMultiplier = static_cast<double>(colorValue) / 255.0;

			switch (channel)
			{
			case 0:
				imageBytes[absIndex] = static_cast<unsigned char>(colorValueMultiplier * R * 255);
				break;
			case 1:
				imageBytes[absIndex] = static_cast<unsigned char>(colorValueMultiplier * G * 255);
				break;
			case 2:
				imageBytes[absIndex] = static_cast<unsigned char>(colorValueMultiplier * B * 255);
				break;
			default:
				imageBytes[absIndex] = colorValue;
			}
		}
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

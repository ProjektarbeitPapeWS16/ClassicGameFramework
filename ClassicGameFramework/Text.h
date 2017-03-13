#pragma once
//#include "Drawable.h"
#include "Entity.h"
#include <string>
#include <vector>
class Font;
struct Position;

class Text : public Entity
{
public:
	typedef enum
	{
		LEFT, CENTER, RIGHT
	} Anchor;

	Anchor anchor;


	void setWidth(int width) override;
	void setHeight(int height) override;
	void setPosX(int posX) override;
	void setPosY(int posY) override;
	int getWidth() override;
	int getHeight() override;
	int getPosX() override;
	int getPosY() override;
	Image* getImage() override;
	void setText(const char* text);
private:
	std::vector<Image*> letters;

	
	int textLength;// , textWidth, textHeight;
	Font* font;

	//Position* position;
	Image* image = nullptr;
	std::string text;
	double R, G, B;
	double scale;
	bool backgroundSet;
	unsigned char backR, backG, backB;
public:

	void toUpper();
	void countLetters();
	void generateBoundaries() const;
	Text(Font* font, const char* text, Position* position, Anchor anchor, double scale, unsigned char R, unsigned char G, unsigned char B, unsigned char backR, unsigned char backG, unsigned char backB);
	Text(Font* font, const char* text, Position* position, Anchor anchor, double scale, unsigned char R, unsigned char G, unsigned char B);
	Text(Font* font, const char* text, Position* position, double scale, unsigned char R, unsigned char G, unsigned char B);
	~Text();

	std::string getText() const;
	Font* getFont() const;
	bool isLoaded() const;
	void loadImage();
	int getTextLength() const;

};

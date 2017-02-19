#pragma once
//#include "Drawable.h"
#include "Entity.h"
class GameConfig;
class Font;
struct Position;

class Text : public Entity
{
public:
	void setWidth(int width) override;
	void setHeight(int height) override;
	void setPosX(int posX) override;
	void setPosY(int posY) override;
	int getWidth() override;
	int getHeight() override;
	int getPosX() override;
	int getPosY() override;
	Image* getImage() override;
private:
	int textLength;// , textWidth, textHeight;
	Font* font;

	//Position* position;
	Image* image;
	char* text;
	double R, G, B;
	double scale;
	GameConfig* config;
public:

	Text(GameConfig* config, Font* font, char* text, Position* position, double scale, unsigned char R, unsigned char G, unsigned short B);
	~Text();

	const char* getText() const;
	Font* getFont() const;
	bool isLoaded() const;
	void loadImage();
	int getTextLength() const;

};

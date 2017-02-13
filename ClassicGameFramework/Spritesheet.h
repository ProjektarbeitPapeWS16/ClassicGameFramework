#include "Renderer.h"
#pragma once

// For retrieving a certain part of a graphic depending on context.
// Example: Looping through three images when walking left/right, two when climbing up a ladder, etc
class Spritesheet
{
	int spriteWidth;	// Width of one sprite within texture
	int spriteHeight;	// Height of one sprite within texture
	int textureWidth;	// Total width of texture
	int textureHeight;	// Total height of texture
	int texture;
public:
	Spritesheet(int texture, int textureWidth, int textureHeight, int spriteWidth, int spriteHeight) :
		texture(texture), textureWidth(textureWidth), textureHeight(textureHeight), spriteWidth(spriteWidth), spriteHeight(spriteHeight)
	{}

	// For drawing a particular frame for a given index.
	// Automatically retrieves proper 2D section of the image by calculating
	// column and row index of the sprite based on size.
	void drawSprite(float xPos, float yPos, int frameIndex); // draws desired frame from spritesheet.
};
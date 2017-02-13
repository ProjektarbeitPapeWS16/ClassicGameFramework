#include "Spritesheet.h"

void Spritesheet::drawSprite(float xPos, float yPos, int frameIndex)
{
	//2D Vertex data for for rendering
	const float vertices[] = {
		xPos,				yPos,					// (0,0)
		xPos + spriteWidth,	yPos,					// (1,0)
		xPos + spriteWidth, yPos + spriteHeight,	// (1,1)
		xPos,				yPos + spriteHeight,	// (0,1)
	};

	// Float values of classes integers:
	const float xEnd = float(spriteWidth) / textureWidth;
	const float yEnd = float(spriteWidth) / textureWidth;
	const int colCount = textureWidth / textureHeight;	// Amount of sprites per row -- depends on given size

	// Calculate 'texture coordinate'
	// Example: 10. frame of 4x3 texture image is at row 3, column 2 (3x3+1)
	const float xStart = (frameIndex % colCount) * xEnd;
	const float yStart = (frameIndex / colCount + 1) * yEnd;
	
	// 2D Texture coordinates for rendering
	const float textureVertices[] = {
		xStart,	yStart,					// (0,0)
		xStart + xEnd,	yStart,			// (1,0)
		xStart + xEnd,	yStart + yEnd,	// (1,1)
		xStart,	yStart + yEnd,			// (0,1)
	};

	// Define vertex data and texture coordinates, then bind texture
	// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glVertexPointer.xml
	glVertexPointer(2, GL_FLOAT, 0, vertices);			//Define array with vertex data for rendering
	glTexCoordPointer(2, GL_FLOAT, 0, textureVertices); //Define array of texture coordinates for rendering
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);				//Renders the sprite on the two defined triangles

}

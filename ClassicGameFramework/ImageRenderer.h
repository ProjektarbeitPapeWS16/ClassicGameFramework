#pragma once
#include <glew.h>
#include "ImageService.h"
class Drawable;
class Image;
class Renderer;
class Shader;




class ImageRenderer
{
	GLuint VBO, VAO, EBO;
	GLuint texture;
	Shader* textureShader;
	Renderer* renderer;

	Drawable* drawable;
	long id;
	long long lastUse;
public:

	ImageRenderer(Renderer* renderer, Drawable* drawable);
	long getLastUse() const;
	~ImageRenderer();

	long getId() const;
	void render();
};

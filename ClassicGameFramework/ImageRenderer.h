#pragma once
#include <glew.h>
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
public:

	ImageRenderer(Renderer* renderer, Drawable* drawable);
	~ImageRenderer();

	void render() const;
};

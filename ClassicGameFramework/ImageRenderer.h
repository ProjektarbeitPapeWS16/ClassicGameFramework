#pragma once
#include <glew.h>
class Image;
class Renderer;
class Shader;




class ImageRenderer
{
	GLuint VBO, VAO, EBO;
	GLuint texture;
	Shader* textureShader;
	Renderer* renderer;

	Image* image;
public:

	ImageRenderer(Renderer* renderer, Image* image);
	~ImageRenderer();

	void render() const;
};

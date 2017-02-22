#include "ImageRenderer.h"
#include "Image.h"
#include "Shader.h"
#include "Renderer.h"
#include "Drawable.h"
#include "EngineModel.h"
#include "Config.h"

ImageRenderer::~ImageRenderer()
{
	glDeleteVertexArrays(1, &(VAO));
	glDeleteBuffers(1, &(VBO));
	glDeleteBuffers(1, &(EBO));
}

long ImageRenderer::getId() const
{
	return id;
}

ImageRenderer::ImageRenderer(Renderer* renderer, Drawable* drawable): renderer(renderer), drawable(drawable)
{
	Image* image = drawable->getImage();
	const char* file = image->getImageFile();
	int transR = image->getTransR();
	int transG = image->getTransG();
	int transB = image->getTransB();
	
	textureShader = new Shader("../ClassicGameFramework/textureShader.vert", "../ClassicGameFramework/textureShader.frag");

	auto start = renderer->translateToWorldCoordinates(
		drawable->getPosX(),
		drawable->getPosY()
	);

	auto end = renderer->translateToWorldCoordinates(
		drawable->getPosX() + drawable->getWidth(),
		drawable->getPosY() + drawable->getHeight()
	);

	GLfloat vertices[] = {
		// Positions					// Colors				// Texture Coords
		end[0], end[1], 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Top Right
		end[0], start[1], 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom Right
		start[0], start[1], 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom Left
		start[0], end[1], 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f // Top Left 
	};

	delete[] start;
	delete[] end;

	GLuint indices[] = {// Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3 // Second Triangle
	};

	glGenVertexArrays(1, &(ImageRenderer::VAO));
	glGenBuffers(1, &(ImageRenderer::VBO));
	glGenBuffers(1, &(ImageRenderer::EBO));

	/*
	Toggle wireframe polygons
	*/
	if (renderer->JUST_WIREFRAMES == GL_TRUE)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	glBindVertexArray(ImageRenderer::VAO);

	glBindBuffer(GL_ARRAY_BUFFER, ImageRenderer::VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ImageRenderer::EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
	glEnableVertexAttribArray(0);
	// COLOR
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO


	// Load and create a texture 
	glGenTextures(1, &(ImageRenderer::texture));
	glBindTexture(GL_TEXTURE_2D, ImageRenderer::texture);// All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps

	
	//image->loadImageBytes();
	//image->setUnusedListener(this);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getImageBytes());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.



	this->id = EngineModel::getInstance()->getImageService()->getIdBySignature(file, transR, transG, transB);
}

long ImageRenderer::getLastUse() const
{
	return lastUse;
}

void ImageRenderer::render()
{
	lastUse = Config::currentTimeMillis();

	auto start = renderer->translateToWorldCoordinates(
		drawable->getPosX(),
		drawable->getPosY()
	);
	auto end = renderer->translateToWorldCoordinates(
		drawable->getPosX() + drawable->getWidth(),
		drawable->getPosY() + drawable->getHeight()
	);

	GLfloat vertices[] = {
		// Positions					// Colors				// Texture Coords
		end[0], end[1], 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Top Right
		end[0], start[1], 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom Right
		start[0], start[1], 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom Left
		start[0], end[1], 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f // Top Left 
	};

	delete[] start;
	delete[] end;
	glBindVertexArray(ImageRenderer::VAO);

	glBindBuffer(GL_ARRAY_BUFFER, ImageRenderer::VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	ImageRenderer::textureShader->Use();

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(textureShader->Program, "textureBmp"), 0);

	// Draw container
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

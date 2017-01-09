#include "Image.h"
#include "Boundaries.h"

unsigned char* Image::readImage2ByteArray(const GLchar* filename, int& width, int& height, unsigned short transR, unsigned short transG, unsigned short transB)
{
	FILE* file;
	fopen_s(&file, filename, "rb");

	if (file == nullptr)
	{
		return nullptr;
	}

	// obtain file size:
	fseek(file, 0, SEEK_END);
	auto lSize = ftell(file);
	rewind(file);

	auto data = new unsigned char[lSize];
	fread(data, lSize, 1, file);
	fclose(file);


	// extract image height and width from header 
	width = *reinterpret_cast<int*>(&data[18]);
	height = *reinterpret_cast<int*>(&data[22]);
	auto padding = 0;
	while ((width * 3 + padding) % 4 != 0)
	{
		padding++;
	}
	auto widthnew = width * 3 + padding;

	auto endPos = 54 + (widthnew * height);

	auto ret = new unsigned char[width * 4 * height];

	for (auto line = 0; line < height; line++)
	{
		for (auto column = 0, retcolumn = 0; column < widthnew - padding; column += 3, retcolumn += 4)
		{
			auto ri = line * (width*4) + retcolumn;
			auto gi = ri + 1;
			auto bi = ri + 2;
			auto ai = ri + 3;

			ret[ri] = data[line * widthnew + column + 54 + 2];
			ret[gi] = data[line * widthnew + column + 54 + 1];
			ret[bi] = data[line * widthnew + column + 54 + 0];

			if(transR != 256 && transB != 265 && transG != 265 && ret[ri] == static_cast<unsigned char>(transR) && ret[gi] == static_cast<unsigned char>(transG) && ret[bi] == static_cast<unsigned char>(transB))
			{
				ret[ai] = 0;
			} else
			{
				ret[ai] = 255;
			}
		}
	}

	delete[] data;
	return ret;
}

Image::Image(Renderer* renderer, const GLchar* imageFile, Boundaries* boundaries, unsigned short transR, unsigned short transG, unsigned short transB) : renderer(renderer), imageFile(imageFile), boundaries(boundaries)
{
	textureShader = new Shader("../ClassicGameFramework/textureShader.vert", "../ClassicGameFramework/textureShader.frag");

	auto start = renderer->translateToWorldCoordinates(boundaries->position.x, boundaries->position.y);
	auto end = renderer->translateToWorldCoordinates(boundaries->position.x + boundaries->width, boundaries->position.y + boundaries->height);

	GLfloat vertices[] = {
		// Positions					// Colors				// Texture Coords
		end[0], end[1], 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 0.0f, // Top Right
		end[0], start[1], 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 1.0f, // Bottom Right
		start[0], start[1], 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 1.0f, // Bottom Left
		start[0], end[1], 0.0f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f // Top Left 
	};

	delete[] start;
	delete[] end;

	GLuint indices[] = {// Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3 // Second Triangle
	};

	glGenVertexArrays(1, &(Image::VAO));
	glGenBuffers(1, &(Image::VBO));
	glGenBuffers(1, &(Image::EBO));

	/*
	Toggle wireframe polygons
	*/
	if (renderer->JUST_WIREFRAMES == GL_TRUE)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	glBindVertexArray(Image::VAO);

	glBindBuffer(GL_ARRAY_BUFFER, Image::VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Image::EBO);
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
	glGenTextures(1, &(Image::texture));//TODO 2
	glBindTexture(GL_TEXTURE_2D, Image::texture);// All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps

	if (image == nullptr)
	{
		image = readImage2ByteArray(imageFile, imageWidth, imageHeight, transR, transG, transB);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);//TODO 3
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Activate shader
}

void Image::render() const
{
	auto start = renderer->translateToWorldCoordinates(boundaries->position.x, boundaries->position.y);
	auto end = renderer->translateToWorldCoordinates(boundaries->position.x + boundaries->width, boundaries->position.y + boundaries->height);

	GLfloat vertices[] = {
		// Positions					// Colors				// Texture Coords
		end[0], end[1], 0.0f,		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Top Right
		end[0], start[1], 0.0f,		0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom Right
		start[0], start[1], 0.0f,	 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom Left
		start[0], end[1], 0.0f,		1.0f, 1.0f, 0.0f, 0.0f, 0.0f // Top Left 
	};

	delete[] start;
	delete[] end;

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	Image::textureShader->Use();

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(textureShader->Program, "textureBmp"), 0);

	// Draw container
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}


Image::~Image()
{
	delete image;
	glDeleteVertexArrays(1, &(VAO));
	glDeleteBuffers(1, &(VBO));
	glDeleteBuffers(1, &(EBO));
}

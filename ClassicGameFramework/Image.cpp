#include "Image.h"
#include "Config.h"

unsigned char* ReadBMP(const GLchar* filename, int* array, int& height, int& width) {
	FILE* img;
	fopen_s(&img, filename, "rb");   //read the file


	unsigned char header[54];
	fread(header, sizeof(unsigned char), 54, img); // read the 54-byte header


												   // extract image height and width from header 
	width = *(int*)&header[18];
	height = *(int*)&header[22];
	int padding = 0;

	while ((width * 3 + padding) % 4 != 0) {
		padding++;
	}

	int widthnew = width * 3 + padding;

	unsigned char* data = new unsigned char[widthnew];

	for (int i = 0; i<height; i++) {

		fread(data, sizeof(unsigned char), widthnew, img);

		for (int j = 0; j<width * 3; j += 3)
		{ //Convert BGR to RGB and store
			array[i*width + j + 0] = data[j + 2];
			array[i*width + j + 1] = data[j + 1];
			array[i* width + j + 2] = data[j + 0];
		}
	}

	fclose(img); //close the file 

	return data;
}

unsigned char * readImage2ByteArray(const GLchar* filename, int& width, int& height)
{
	
	FILE * file;
	fopen_s(&file, filename, "rb");

	if (file == nullptr) {
		return nullptr;
	}

	// obtain file size:
	fseek(file, 0, SEEK_END);
	long lSize = ftell(file);
	rewind(file);

	unsigned char * data = new unsigned char[lSize];
	fread(data, lSize, 1, file);
	fclose(file);

		
	// extract image height and width from header 
	width = *(int*)&data[18];
	height = *(int*)&data[22];
	int padding = 0;

	while ((width * 3 + padding) % 4 != 0) {
		padding++;
	}

	int widthnew = width * 3 + padding;

	int endPos = 54 + (widthnew * height);
		
	unsigned char * ret = new unsigned char[endPos - 54];
	
	for(int line = 0; line < height; line++)
	{
		for(int column = 0; column < widthnew-padding; column+=3)
		{
			ret[line * widthnew + column + 0] = data[line * widthnew + column + 54 + 2];
			ret[line * widthnew + column + 1] = data[line * widthnew + column + 54 + 1];
			ret[line * widthnew + column + 2] = data[line * widthnew + column + 54 + 0];
		}
	}

	delete[] data;
	return ret;
}

Image::Image(Renderer* renderer, const GLchar* imageFile, Boundaries* boundaries) : renderer(renderer), imageFile(imageFile), boundaries(boundaries)
{
	Image::textureShader = new Shader("textureShader.vert", "textureShader.frag");

	GLfloat* start = renderer->translateToWorldCoordinates(boundaries->position.x, boundaries->position.y);
	GLfloat* end = renderer->translateToWorldCoordinates(boundaries->position.x + boundaries->width, boundaries->position.y + boundaries->height);

	GLfloat vertices[] = {
		// Positions					// Colors				// Texture Coords
		end[0],  end[1], 0.0f,			1.0f, 0.0f, 0.0f,		1.0f, 0.0f,		// Top Right
		end[0], start[1], 0.0f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,		// Bottom Right
		start[0], start[1], 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,		// Bottom Left
		start[0],  end[1], 0.0f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f		// Top Left 
	};

	delete[] start;
	delete[] end;

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	
	glGenVertexArrays(1, &(Image::VAO));
	glGenBuffers(1, &(Image::VBO));
	glGenBuffers(1, &(Image::EBO));

	/*
	Toggle wireframe polygons
	*/
	if (renderer->JUST_WIREFRAMES == GL_TRUE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	glBindVertexArray(Image::VAO);

	glBindBuffer(GL_ARRAY_BUFFER, Image::VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Image::EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO



	// Load and create a texture 
	glGenTextures(1, &(Image::texture));//TODO 2
	glBindTexture(GL_TEXTURE_2D, Image::texture);// All upcoming GL_TEXTURE_2D operations now have effect on our texture object
												 // Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	//int _width, _height;
	//int* array = new int[3000000];

	if (image == nullptr)
	{
		image = readImage2ByteArray(imageFile, imageWidth, imageHeight);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);//TODO 3
	glGenerateMipmap(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // Activate shader
	
}

void Image::render()
{
	GLfloat* start = renderer->translateToWorldCoordinates(boundaries->position.x, boundaries->position.y);
	GLfloat* end = renderer->translateToWorldCoordinates(boundaries->position.x + boundaries->width, boundaries->position.y + boundaries->height);

	GLfloat vertices[] = {
		// Positions					// Colors				// Texture Coords
		end[0],  end[1], 0.0f,			1.0f, 0.0f, 0.0f,		1.0f, 0.0f,		// Top Right
		end[0], start[1], 0.0f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,		// Bottom Right
		start[0], start[1], 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,		// Bottom Left
		start[0],  end[1], 0.0f,		1.0f, 1.0f, 0.0f,		0.0f, 0.0f		// Top Left 
	};

	delete[] start;
	delete[] end;

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	Image::textureShader->Use();

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(Image::textureShader->Program, "texture"), 0);

	// Draw container
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	
}


Image::~Image()
{
	free(image);
	glDeleteVertexArrays(1, &(Image::VAO));
	glDeleteBuffers(1, &(Image::VBO));
	glDeleteBuffers(1, &(Image::EBO));
}

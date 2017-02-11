#version 330 core
in vec2 TexCoord;
in vec3 ourColor;

out vec4 color;

// Texture samplers
uniform sampler2D textureBmp;


void main()
{
	//vec4 temp = texture(textureBmp, TexCoord);
	// Linearly interpolate between both textures (second texture is only slightly combined)
	//color = vec4(temp[0], temp[1], temp[2], 0.5f);
	color = texture(textureBmp, TexCoord);// * ourColor;

	//color.a = 0.0f;
	//color = vec4(textureBmp.r, textureBmp.g, textureBmp.b, 0.5f);
}
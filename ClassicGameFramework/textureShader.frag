#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture samplers
uniform sampler2D texture;

void main()
{
	// Linearly interpolate between both textures (second texture is only slightly combined)
	color = texture(texture, TexCoord);
}
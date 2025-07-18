#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 uColor;
uniform sampler2D uTexture;

void main()
{
	FragColor = texture(uTexture, TexCoord) * uColor;
}
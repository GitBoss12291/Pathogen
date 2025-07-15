#version 330 core

layout (location = 0) in vec2 aPos;

uniform vec2 uPos;
uniform vec2 uSize;
uniform vec2 uResolution;

out vec2 TexCoord;

void main()
{
	vec2 scaled = aPos * uSize + uPos;
	vec2 ndc = (scaled / uResolution) * 2.0 - 1.0;
	gl_Position = vec4(ndc.x, -ndc.y, 0.0, 1.0);
}
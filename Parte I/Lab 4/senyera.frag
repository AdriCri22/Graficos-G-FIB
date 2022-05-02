#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

void main()
{
	float a = 1./9.;
	if (mod(floor(vtexCoord.s * 9.), 2) == 0) fragColor = vec4(1, 1, 0, 1);
	else fragColor = vec4(1, 0, 0, 1);
}

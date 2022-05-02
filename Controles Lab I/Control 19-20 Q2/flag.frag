#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;
const float PI = 3.141592;

void main()
{
	if (vtexCoord.s < 0.5 && vtexCoord.t > 0.5)
		fragColor = vec4(0, 1, 0, 1);

	else if (vtexCoord.t > 0.5)
		fragColor = vec4(1, 1, 0, 1);

	else
		fragColor = vec4(0, 0, 1, 1);

}

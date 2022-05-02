#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform float n;

void main()
{
	bool parS = mod(floor(vtexCoord.s * n), 2) == 0;
	bool parT = mod(floor(vtexCoord.t * n), 2) == 0;
	vec4 color;
	if (parS == parT) 	color = vec4(0.8, 0.8, 0.8, 1);
	else 				color = vec4(0, 0, 0, 1);

    fragColor = color;
}

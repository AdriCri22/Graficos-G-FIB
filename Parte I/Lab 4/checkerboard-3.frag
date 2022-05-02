#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform float n = 8;

void main()
{
	float parS = mod(floor(vtexCoord.s * n*10), 10);
	float parT = mod(floor(vtexCoord.t * n*10), 10);
	vec4 color;	
	if (parT == 0 || parS == 0) color = vec4(0, 0, 0, 1);
	else color = vec4(0.8, 0.8, 0.8, 1);
    
	fragColor = color;
}


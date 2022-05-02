#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

void main()
{
	float dist = length(vec2(vtexCoord.s -0.35, 3./4. * (vtexCoord.t - 0.5)));
	float res = step(dist, 0.3);

	dist = length(vec2(vtexCoord.s - 0.5, 3./4. * (vtexCoord.t - 0.5)));
	float res2 = step(dist, 0.3);

	bool cuadrado = vtexCoord.s > 0.5 && vtexCoord.s < 0.8 && vtexCoord.t > 0.3 && vtexCoord.t < 0.7;
	if (res != 0 && res2 == 0 || cuadrado)
    		fragColor = vec4(1, 1, 1, 1);	
	else
    		fragColor = vec4(1, 1, 0, 1) * 0.8;	
}

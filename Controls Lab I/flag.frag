#version 330 core

out vec4 fragColor;

in vec2 vtexCoord;

const vec4 COLOR_FONS = vec4(0, 1, 0, 0);
const vec4 COLOR_FONS2 = vec4(1, 1, 0, 0);
const vec4 COLOR_CERCLE = vec4(0, 0, 1, 0);

void main()
{
	float x = vtexCoord.s;
	float y = vtexCoord.t;

	float centre1 = length(vec2(x - 0.5, (y - 0.5) * 1./2.));
	float cercle1 = step(centre1, 0.12);

	float centre2 = length(vec2(x - 0.52, (y - 0.75) * 1./2.));
	float cercle2 = step(centre2, 0.2);

	float centre3 = length(vec2(x - 0.5, (y - 0.5) * 1./2.));
	float cercle3 = step(centre3, 0.12);

	float centre4 = length(vec2(x - 0.52, (y - 0.7) * 1./2.));
	float cercle4 = step(centre4, 0.2);

	if (cercle3 != 0 && cercle2 != 0)
		fragColor = COLOR_CERCLE;
	else if (cercle2 != 0.0 && y < 0.85)
		fragColor = COLOR_FONS2;
	else if (cercle4 != 0 && y < 0.85)
		fragColor = COLOR_FONS2;
	else if (cercle1 != 0.0)
		fragColor = COLOR_CERCLE;
	else if (x > 0.15 && x < 0.85 && y > 0.15 && y < 0.85)	
		fragColor = COLOR_FONS2;
	else
    	fragColor = COLOR_FONS;
}

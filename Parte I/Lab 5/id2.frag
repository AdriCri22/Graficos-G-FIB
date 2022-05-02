#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;
uniform sampler2D colorMap;

void main()
{
	vec4 color;

	float numero = floor(vtexCoord.s*6);
	float ntc = fract(vtexCoord.s * 6);
	float set = ntc / 10. + 7./10.;
	float zero = ntc / 10.;
	float tres = ntc / 10. + 3./10.;
	float nou = ntc / 10. + 9./10.;
	if (numero == 0)
		color = texture(colorMap, vec2(set, vtexCoord.t));
	else if (numero == 1)
		color = texture(colorMap, vec2(zero, vtexCoord.t));
	else if (numero == 2)
		color = texture(colorMap, vec2(zero, vtexCoord.t));
	else if (numero == 3)
		color = texture(colorMap, vec2(tres, vtexCoord.t));
	else if (numero == 4)
		color = texture(colorMap, vec2(nou, vtexCoord.t));
	else
		color = texture(colorMap, vec2(set, vtexCoord.t));
		
	
	if (color.a < 0.5)
		fragColor = vec4(1, 1, 0, 0);
	else {
		fragColor = vec4(0, 0, 1, 0);
	}
}

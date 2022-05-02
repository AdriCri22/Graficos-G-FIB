#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;
uniform sampler2D colorMap;

void main()
{
	vec4 color;
	
	if (vtexCoord.s < 1./6.)
    	color = texture(colorMap, vec2((vtexCoord.s * 6./10. + 7./10.), vtexCoord.t));
	else if (vtexCoord.s < 2./6.)
		color = texture(colorMap, vec2((vtexCoord.s * 6./10. - 1./10.), vtexCoord.t));
	else if (vtexCoord.s < 3./6.)
		color = texture(colorMap, vec2((vtexCoord.s * 6./10. - 2./10.), vtexCoord.t));
	else if (vtexCoord.s < 4./6.)
		color = texture(colorMap, vec2((vtexCoord.s * 6./10. + 0./10.), vtexCoord.t));
	else if (vtexCoord.s < 5./6.)
		color = texture(colorMap, vec2((vtexCoord.s * 6./10. + 5./10.), vtexCoord.t));
	else 
		color = texture(colorMap, vec2((vtexCoord.s * 6./10. + 2./10.), vtexCoord.t));
	
	if (color.a < 0.5)
		fragColor = vec4(1, 1, 0, 0);
	else {
		fragColor = vec4(0, 0, 1, 0);
	}
}

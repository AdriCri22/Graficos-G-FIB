#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D map;
uniform float time;
uniform float a = 1;
const float PI = 3.141592;

float maximum(vec4 color) {
	float r = color.x;
	float g = color.y;
	float b = color.z;

	if (r > g && r > b) return r;
	if (g > r && g > b) return g;
	return b;
}

void main()
{
	vec4 c = texture(map, vtexCoord);
	float m = maximum(c);
	vec2 u = vec2(m, m);
	float theta = 2 * PI * time;
	mat2 rot = mat2(cos(theta), sin(theta),
			-sin(theta), cos(theta));
	u = rot * u;
	vec2 offset = (a/100.0) * u;
    fragColor = texture(map, vtexCoord + offset);
}

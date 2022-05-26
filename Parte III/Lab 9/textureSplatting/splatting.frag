#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;


void main()
{
	vec4 tn = texture(noise0, vtexCoord);
	vec4 tr = texture(rock1, vtexCoord);
	vec4 tg = texture(grass2, vtexCoord);
    fragColor = mix(tr, tg, tn);
}

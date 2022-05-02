#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform float slice=0.1;
uniform float time;
uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform sampler2D sampler3;

void main()
{
	float samp = mod(floor(time / slice), 4);
	if (samp == 0)
		fragColor = frontColor * texture(sampler0, vtexCoord);
	else if (samp == 1)
		fragColor = frontColor * texture(sampler1, vtexCoord);
	else if (samp == 2)
		fragColor = frontColor * texture(sampler2, vtexCoord);
	else
		fragColor = frontColor * texture(sampler3, vtexCoord);
}

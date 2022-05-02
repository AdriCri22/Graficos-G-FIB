#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

void main()
{
	float dist = length(vtexCoord.xy - 0.5);
	float res = step(dist, 0.2);
	
	if (res == 0)
    	fragColor = vec4(1, 1, 1, 1);
	else
		fragColor = vec4(1, 0, 0, 1);
}

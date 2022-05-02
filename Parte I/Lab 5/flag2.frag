#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

void main()
{

	float dist = length(vec2(vtexCoord.s -0.25, 3./4. * (vtexCoord.t - 0.5)));
	float res = step(dist, 0.15);

	if (res != 0)
    	fragColor = vec4(1, 1, 1, 1);	

	else if (vtexCoord.s < 0.5)
    	fragColor = vec4(0, 0, 1, 0);

	else if (vtexCoord.t > 0.5)
    	fragColor = vec4(1, 0, 0, 0);

	else
		fragColor = vec4(1, 1, 0, 0);

	
}

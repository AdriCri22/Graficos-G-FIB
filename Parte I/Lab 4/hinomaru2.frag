#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
const float PI = 3.141592;

uniform bool classic;

void main()
{
	float dist = length(vtexCoord.xy - 0.5);
	float res = step(dist, 0.2);
	
	if (res == 0)
    	fragColor = vec4(1, 1, 1, 1);
	else
		fragColor = vec4(1, 0, 0, 1);

	if (!classic) {
		float phi = PI / 16;
		float theta = atan(vtexCoord.t - 0.5, vtexCoord.s - 0.5);
		float res2 = mod(theta/phi + 0.5, 2);
		
		if (res > 0 || res2 < 1)
			fragColor = vec4(1, 0, 0, 1);
		else
			fragColor = vec4(1, 1, 1, 1);
	}
}


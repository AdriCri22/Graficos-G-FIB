#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

void main()
{
	float fade = 0.05;
	float dist = length(vtexCoord.xy - 0.5);
	float res = smoothstep(dist - fade, dist + fade, 0.2);
	
	fragColor = vec4(res, 0, 0, 1);
}


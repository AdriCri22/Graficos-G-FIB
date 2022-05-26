#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;
in vec3 N;

uniform sampler2D window;      // interior
uniform sampler2D palm1;       // palm-tree
uniform sampler2D background2; // dunes

uniform float time;

void main()
{
    vec4 C = texture(window, vtexCoord);
    vec4 D = texture(palm1, vtexCoord + 0.25*N.xy + vec2(0.1*sin(2*time)*vtexCoord.t, 0));
    vec4 E = texture(background2, vtexCoord + 0.5*N.xy);

	if (C.a == 1)
		fragColor = C;
	else if (D.a >= 0.5)
		fragColor = D;
	else
		fragColor = E;
}
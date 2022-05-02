#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform sampler2D explosion;
uniform float time;


void main()
{
	float slice = 1./30.;
	float temps = 30*time;
	float x = -1. - floor(temps/8.);
    fragColor = frontColor * texture(explosion, vec2(vtexCoord.s / 1./8. + floor(temps)/8., vtexCoord.t / 1./6. + x/6.));
	fragColor *= fragColor.w;
}

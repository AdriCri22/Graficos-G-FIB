#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec4 pos;
uniform float time;

void main()
{
	float res = pos.x / pos.w + 1;
	if (res > time) discard;
	else fragColor = vec4(0, 0, 1, 1);
}

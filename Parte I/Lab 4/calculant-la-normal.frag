#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 vertex2;

void main()
{
	vec3 normal = normalize(cross(dFdx(vertex2), dFdy(vertex2)));
    fragColor = frontColor * normal.z;
}

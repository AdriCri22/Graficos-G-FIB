#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 normal2;
in vec3 color2;
uniform mat3 normalMatrix;

void main()
{
	vec3 N = normalize(normalMatrix * normal2);
    fragColor = vec4(color2,1.0) * N.z;;
}

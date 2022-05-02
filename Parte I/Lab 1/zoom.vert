#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time;

void main()
{
	float s = 0.5 + abs(sin(time));
	mat4 scale = mat4(	vec4(s, 0, 0, 0),
						vec4(0, s, 0, 0),
						vec4(0, 0, 1, 0),
						vec4(0, 0, 0, 1));
	vec4 newVertex = scale * modelViewProjectionMatrix * vec4(vertex, 1.0);
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = newVertex;
}

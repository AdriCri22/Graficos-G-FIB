#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
out vec3 N;
out vec3 V;
out vec3 L;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrixInverse;
uniform vec4 lightPosition; // similar a gl_LightSource[0].position

uniform bool world;

void main()
{
	if (world) {
		N = normal;
		V = (modelViewMatrixInverse * vec4(0,0,0,1)).xyz - vertex.xyz;
		L = normalize((modelViewMatrixInverse * lightPosition).xyz  - vertex.xyz);
	} else {
		N = normalize(normalMatrix * normal);
		V = (modelViewMatrix * vec4(vertex, 1.0)).xyz;
		L = normalize(lightPosition.xyz - V);
		V = -V;
	}

    vtexCoord = texCoord;
	gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}


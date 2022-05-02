#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

uniform vec3 boundingBoxMin; // cantonada de la capsa englobant
uniform vec3 boundingBoxMax; // cantonada de la capsa englobant
uniform bool eyespace;
uniform float time;

void main()
{
	float r = length(boundingBoxMax - boundingBoxMin) / 2;
	float y = vertex.y;
	if (eyespace)
		y = (modelViewMatrix * vec4(vertex, 1)).y;
	float d = (r / 10) * y;
	vec3 newVertex = vertex + normal * d * sin(time);
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(newVertex, 1.0);
}

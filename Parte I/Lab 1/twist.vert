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
    // thetaY = 0.4 * y * sin(t)
	float theatY = 0.4 * vertex.y * sin(time);
	// Construimos la matrix de rotación en y
	mat3 rotY = mat3(vec3(cos(theatY), 0, -sin(theatY)), 
					vec3(0, 1, 0), 
					vec3(sin(theatY), 0, cos(theatY)));
	// Calclamos el nuevo vértice
    vec3 newVertex = rotY * vertex;
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(newVertex, 1.0);
}
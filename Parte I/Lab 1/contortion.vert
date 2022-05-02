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
	float thetaX = (vertex.y - 0.5) * sin(time);
	mat3 rotX = mat3(vec3(1, 0, 0),
					vec3(0, cos(thetaX), sin(thetaX)),
					vec3(0, -sin(thetaX), cos(thetaX)));
	vec3 p = vec3(0, 1, 0);
	vec3 newVertex = vertex;
	if (vertex.y >= 0.5)
		newVertex = rotX * (vertex - p) + p;
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(newVertex, 1.0);
}
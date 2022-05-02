#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float speed = 0.5;
uniform float time;

void main()
{
	// Obtenemos los radianes
	float alpha = speed * time;
	// Construimos la matrix de rotación
	mat3 rotY = mat3(vec3(cos(alpha), 0, -sin(alpha)), 
					vec3(0, 1, 0), 
					vec3(sin(alpha), 0, cos(alpha)));
	// Obtenemos los nuevos vertices
	vec3 newVertex =  rotY * vertex;
		
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(newVertex, 1.0);
}
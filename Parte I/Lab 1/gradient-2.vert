#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin; // cantonada de la capsa englobant 
uniform vec3 boundingBoxMax; // cantonada de la capsa englobant
const vec3 red = vec3(1, 0, 0);
const vec3 yellow = vec3(1, 1, 0);
const vec3 green = vec3(0, 1, 0);
const vec3 cian = vec3(0, 1, 1);
const vec3 blue = vec3(0, 0, 1);

void main()
{
	
		
    vec3 N = normalize(normalMatrix * normal);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    
    float y = gl_Position.y / gl_Position.w;
	vec3 color2;
	if (y < -0.5) 
		color2 = mix(red, yellow, fract(y/0.5));
	else if (y < 0) 
		color2 = mix(yellow, green, fract(y/0.5));
	else if (y < 0.5) 
		color2 = mix(green, cian, fract(y/0.5));
	else if (y < 1)
		color2 = mix(cian, blue, fract(y/0.5));
	else
		color2 = blue;
		
	frontColor = vec4(color2, 1.0);
}
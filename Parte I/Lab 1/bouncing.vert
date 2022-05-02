#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float scale = 8.0;
uniform float time;
const vec3 T0 = vec3(-1, -1, 0);
const vec3 V = vec3(2, 2, 0);

float triangleWave(float x) { 
    return abs(mod(x, 2) - 1.0); 
}

void main()
{
	vec3 t = vec3(triangleWave(time / 1.618), triangleWave(time), 0);
	vec3 T = scale * (T0 + V * t);
	vec3 newVertex = (vertex + T) / scale;
	
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(0.3, 0.3, 0.9, 1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(newVertex, 1.0);
}

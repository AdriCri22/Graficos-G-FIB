#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform float amplitude = 0.1;
uniform float freq = 1; 		// expressada en Hz
uniform float time;
const float PI = 3.141592;

void main()
{

	float d = amplitude * sin(freq * 2 * PI * time);
    vec3 N = normalize(normalMatrix * normal);
	// Pos' = Pos + dt * Nos
	// dt = A * sin(freq * 2 * PI + time)
	// glP = MVM * Pos
	vec3 newVertex = vertex + vec3(d) * normal;
	vec4 color2 = modelViewMatrix * vec4(normal, 0);
    frontColor = vec4(vec3(color2.z), 1.0);
    gl_Position = modelViewProjectionMatrix * vec4(newVertex, 1.0);
}

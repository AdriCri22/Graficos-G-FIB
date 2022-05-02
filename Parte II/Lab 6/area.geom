#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;

const vec4 RED 		= vec4(1, 0, 0, 1);
const vec4 YELLOW 	= vec4(1, 1, 0, 1);
const float areamax = 0.0005;
uniform mat4 projectionMatrix;

void main(void) {
	vec3 u = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 v = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	
	// Calculem l'area
	float area = length(cross(u, v)) / 2.;
	gfrontColor = mix(RED, YELLOW, clamp(area / areamax, 0, 1));

	for (int i = 0; i < 3; i++) {
		gl_Position = projectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}

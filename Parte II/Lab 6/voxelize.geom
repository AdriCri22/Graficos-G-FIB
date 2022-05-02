#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;
in vec3 vnormal[];

uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform float step = 0.13;

void setColor(vec3 normal) {
	vec3 N = normalize(normalMatrix * normal);
	gfrontColor = vec4(vec3(0.6), 1.0) * N.z;
}

void setFace(vec3 v1, vec3 v2, vec3 v3, vec3 v4, vec3 normal) {
	
	setColor(normal);
	// Baricentre
	vec3 bar = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz) / 3.0;
    bar /= step;
    bar = vec3(int(bar.x), int(bar.y), int(bar.z));
    bar *= step;

	gl_Position = modelViewProjectionMatrix * vec4(v1+bar,1); 
	EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(v2+bar,1); 
	EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(v3+bar,1); 
	EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(v4+bar,1); 
	EmitVertex();
    
	EndPrimitive();
}

void setCub() {
	
	float R = step / 2.;

	// front face
	setFace(vec3(R, R, R), vec3(R, -R, R), vec3(-R, R, R), vec3(-R, -R, R), vec3(0, 0, 1));
	// back face
	setFace(vec3(-R, R, -R), vec3(-R, -R, -R), vec3(R, R, -R), vec3(R, -R, -R), vec3(0, 0, -1));
	// right face
	setFace(vec3(R, R, -R), vec3(R, -R, -R), vec3(R, R, R), vec3(R, -R, R), vec3(0, 1, 0));
	// left face 
	setFace(vec3(-R, R, -R), vec3(-R, -R, -R), vec3(-R, R, R), vec3(-R, -R, R), vec3(0, -1, 0));
	// up face
	setFace(vec3(-R, R, R), vec3(-R, R, -R), vec3(R, R, R), vec3(R, R, -R), vec3(1, 0, 0));
	// down face
	setFace(vec3(-R, -R, R), vec3(-R, -R, -R), vec3(R, -R, R), vec3(R, -R, -R), vec3(-1, 0, 0));
}

void main( void )
{	
	setCub();
}

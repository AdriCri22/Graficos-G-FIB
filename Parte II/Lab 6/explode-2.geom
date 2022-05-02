#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform float time;
const float speed = 1.2;
const float angSpeed = 8.0;

mat4 rotateZ(float a) {
	    return mat4 (   vec4(cos(a), -sin(a), 0.0,0.0),
	                    vec4(sin(a), cos(a), 0.0,0.0),
	                    vec4(0.0, 0.0, 1.0,0.0),
	                    vec4(0.0,0.0,0.0,1.0));
}
	
mat4 translate(vec3 t) {
	    return mat4 (   vec4(1.0, 0.0, 0.0, 0.0),
	                    vec4(0.0, 1.0, 0.0, 0.0),
	                    vec4(0.0, 0.0, 1.0, 0.0),
	                    vec4(t.x, t.y, t.z, 1.0));
}

void main( void ) {

	vec3 t = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz)/3;
    vec3 n = (vnormal[0]+vnormal[1]+vnormal[2])/3;
	for( int i = 0 ; i < 3 ; i++ ) {
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix*translate(speed*time*n)*translate(t)*rotateZ(angSpeed*time)*translate(-t)*gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}

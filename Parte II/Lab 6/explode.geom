#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

in vec3 vnormal[];
const float speed = 0.5;
uniform float time;
uniform mat4 modelViewProjectionMatrix;

void main( void )
{
	vec4 n = vec4(0);
	for( int i = 0 ; i < 3 ; i++ ) {
		n += vec4(vnormal[i], 0);
	}

	n = n * 1./ 3.; // deberia ser normalize(n / 3.)
	vec4 res = speed * time * n;
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * (gl_in[i].gl_Position + res);
		EmitVertex();
	}
    EndPrimitive();
}

#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0, 0, 0, 1);
		vec4 pos = gl_in[i].gl_Position;
		gl_Position = modelViewProjectionMatrix * vec4(pos.x, boundingBoxMin.y, pos.z, pos.w);
		EmitVertex();
	}
    EndPrimitive();

	if (gl_PrimitiveIDIn == 0) {
		gfrontColor = vec4(0, 1, 1, 1);
		float r = length(boundingBoxMax - boundingBoxMin) / 2;
		vec4 C = vec4((boundingBoxMin + boundingBoxMax) / 2, 1);
		gl_Position = modelViewProjectionMatrix * vec4(C.x + r, boundingBoxMin.y - 0.01, C.z - r, 1);
		EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x + r, boundingBoxMin.y - 0.01, C.z + r, 1);
		EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x - r, boundingBoxMin.y - 0.01, C.z - r, 1);
		EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x - r, boundingBoxMin.y - 0.01, C.z + r, 1);
		EmitVertex();
		EndPrimitive();
	}
} 


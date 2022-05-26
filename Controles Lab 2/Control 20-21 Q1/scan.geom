#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin, boundingBoxMax;
uniform float time;
const float gruix = 0.1;

void printFace(vec3 v1, vec3 v2, vec3 v3, vec3 v4, vec4 color) {
    gfrontColor = color;
    gl_Position = modelViewProjectionMatrix * vec4(v1, 1.);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(v2, 1.);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(v3, 1.);
	EmitVertex();
    gl_Position = modelViewProjectionMatrix * vec4(v4, 1.);
	EmitVertex();
    EndPrimitive();
}

void drawCube() {
    vec3 res = mix(boundingBoxMin, boundingBoxMax, fract(time));

    //      v8|--------|\v7
    //        | \      | \
    //       v|3|------|--|v4
    //     v5 |-|------|v6|
    //        \ |       \ |
    //         \|---------|
    //         v1         v2

    vec3 v1 = vec3(res.x, boundingBoxMin.y, boundingBoxMax.z);
    vec3 v2 = vec3(res.x + gruix, boundingBoxMin.y, boundingBoxMax.z);
    vec3 v3 = vec3(res.x, boundingBoxMax.y, boundingBoxMax.z);
    vec3 v4 = vec3(res.x + gruix, boundingBoxMax.y, boundingBoxMax.z);
    vec3 v5 = vec3(res.x, boundingBoxMin.y, boundingBoxMin.z);
    vec3 v6 = vec3(res.x + gruix, boundingBoxMin.y, boundingBoxMin.z);
    vec3 v7 = vec3(res.x + gruix, boundingBoxMax.y, boundingBoxMin.z);
    vec3 v8 = vec3(res.x, boundingBoxMax.y, boundingBoxMin.z);

    printFace(v1, v3, v5, v8, vec4(1, 0, 0, 0));
    printFace(v2, v6, v4, v7, vec4(1, 0, 0, 0));
    printFace(v1, v2, v3, v4, vec4(0, 0, 1, 0));
    printFace(v5, v8, v6, v7, vec4(0, 0, 1, 0));
    printFace(v3, v4, v8, v7, vec4(0, 1, 0, 0));
    printFace(v1, v5, v2, v6, vec4(0, 1, 0, 0));
}

void main( void )
{
    if (gl_PrimitiveIDIn == 0)
        drawCube();
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}

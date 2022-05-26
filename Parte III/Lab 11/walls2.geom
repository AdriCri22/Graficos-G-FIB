#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrixInverse;
uniform mat4 modelMatrix;

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

void printCube() {
    //      v8|--------|\v7
    //        | \      | \
    //       v|3|------|--|v4
    //     v5 |-|------|v6|
    //        \ |       \ |
    //         \|---------|
    //         v1         v2

    vec3 v1 = vec3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z);
    vec3 v2 = vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z);
    vec3 v3 = vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z);
    vec3 v4 = vec3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z);
    vec3 v5 = vec3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z);
    vec3 v6 = vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z);
    vec3 v7 = vec3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z);
    vec3 v8 = vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z);

    printFace(v1, v3, v5, v8, vec4(1, 0, 0, 0));
    printFace(v2, v6, v4, v7, vec4(1, 0, 0, 0));
    printFace(v5, v8, v6, v7, vec4(0, 0, 1, 0));
    printFace(v1, v5, v2, v6, vec4(0, 1, 0, 0));
}

void main( void )
{
    printCube();
        
    for( int i = 0 ; i < 3 ; i++ )
    {
        gfrontColor = vfrontColor[i];
        vec4 eyeBoundingBoxMax = modelMatrix * vec4(boundingBoxMax, 1);
        vec4 eyeBoundingBoxMin = modelMatrix * vec4(boundingBoxMin, 1);
	vec4 camera = modelViewMatrixInverse * vec4(0, 0, 0, 1);
        if (eyeBoundingBoxMin.x < camera.x && eyeBoundingBoxMax.x > camera.x && eyeBoundingBoxMin.y < camera.y && eyeBoundingBoxMax.y > camera.y && eyeBoundingBoxMin.z < camera.z && eyeBoundingBoxMax.z > camera.z)
            gfrontColor = vfrontColor[i] * 2;

        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}

#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

mat3 rotateZ(float theta) {
    return mat3(cos(theta), sin(theta), 0,
                -sin(theta), cos(theta), 0,
                0, 0, 1);
}

void printFace(vec3 v1, vec3 v2, vec3 v3, vec3 v4, vec4 color) {
    gfrontColor = color;
    if (gl_PrimitiveIDIn < 4) {
        gl_Position = modelViewProjectionMatrix * vec4(rotateZ(time) *v1, 1.);
        gtexCoord = vec2(0, 0);
	    EmitVertex();
        gl_Position = modelViewProjectionMatrix * vec4(rotateZ(time) * v2, 1.);
        gtexCoord = vec2(1, 0);
	    EmitVertex();
        gl_Position = modelViewProjectionMatrix * vec4(rotateZ(time) * v3, 1.);
        gtexCoord = vec2(0, 1);
	    EmitVertex();
        gl_Position = modelViewProjectionMatrix * vec4(rotateZ(time) * v4, 1.);
        gtexCoord = vec2(1, 1);
	    EmitVertex();
    } else {
        gl_Position = modelViewProjectionMatrix * vec4(v1, 1.);
        gtexCoord = vec2(0, 0);
	    EmitVertex();
        gl_Position = modelViewProjectionMatrix * vec4(v2, 1.);
        gtexCoord = vec2(1, 0);
	    EmitVertex();
        gl_Position = modelViewProjectionMatrix * vec4(v3, 1.);
        gtexCoord = vec2(0, 1);
	    EmitVertex();
        gl_Position = modelViewProjectionMatrix * vec4(v4, 1.);
        gtexCoord = vec2(1, 1);
	    EmitVertex();
    }
    EndPrimitive();
}

void drawCube(vec3 centre) {
    //      v8|--------|\v7
    //        | \      | \
    //       v|3|------|--|v4
    //     v5 |-|------|v6|
    //        \ |       \ |
    //         \|---------|
    //         v1         v2

    vec3 v1 = centre + vec3(-1, -1, 1);
    vec3 v2 = centre + vec3(1, -1, 1);
    vec3 v3 = centre + vec3(-1, 1, 1);
    vec3 v4 = centre + vec3(1, 1, 1);
    vec3 v5 = centre + vec3(-1, -1, -1);
    vec3 v6 = centre + vec3(1, -1, -1);
    vec3 v7 = centre + vec3(1, 1, -1);
    vec3 v8 = centre + vec3(-1, 1, -1);

    printFace(v1, v3, v5, v8, vec4(0, 1, 0, 0));    // cara esquerra
    printFace(v2, v6, v4, v7, vec4(0, 0, 1, 0));    // cara dreta
    printFace(v1, v2, v3, v4, vec4(1, 1, 0, 0));    // cara front
    printFace(v5, v8, v6, v7, vec4(1, 1, 1, 0));    // cara darrere
    printFace(v3, v4, v8, v7, vec4(1, 0, 0, 0));    // cara amunt
    printFace(v1, v5, v2, v6, vec4(1, 0.6, 0, 0));    // cara abaix
}

void main( void )
{
    if (gl_PrimitiveIDIn == 0)
        drawCube(vec3(-1, -1, -1));
    else if (gl_PrimitiveIDIn == 1)
        drawCube(vec3(1, -1, -1));
    else if (gl_PrimitiveIDIn == 2)
        drawCube(vec3(-1, 1, -1));
    else if (gl_PrimitiveIDIn == 3)
        drawCube(vec3(1, 1, -1));
    else if (gl_PrimitiveIDIn == 4)
        drawCube(vec3(-1, -1, 1));
    else if (gl_PrimitiveIDIn == 5)
        drawCube(vec3(1, -1, 1));
    else if (gl_PrimitiveIDIn == 6)
        drawCube(vec3(-1, 1, 1));
    else if (gl_PrimitiveIDIn == 7)
        drawCube(vec3(1, 1, 1));
}

#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec2 mousePosition;
uniform float mouseOverrideX = -1;
uniform vec2 viewport = vec2(800, 600);

void main()
{

    float alpha;
    if (mouseOverrideX == -1)
        alpha = (mousePosition.x / viewport.x) * 2 - 1;
    else
        alpha = (mouseOverrideX / viewport.x) * 2 - 1;

    mat4 rotY = mat4(cos(alpha), 0, -sin(alpha), 0,
                    0, 1, 0, 0,
                    sin(alpha), 0, cos(alpha), 0,
                    0, 0, 0, 1);

    
    vec4 P = modelViewProjectionMatrix * vec4(vertex, 1.0);
    vec4 P2 = modelViewProjectionMatrix * rotY * vec4(vertex, 1.0);

    float t = smoothstep(1.45, 1.55, vertex.y);

    vec3 N = normal;
    vec3 N2 = (rotY * vec4(normal, 1.)).xyz;
    vec3 N3 = normalize(normalMatrix * mix(N, N2, t));
    frontColor = vec4(1, 1, 1, 1.0) * N3.z;
    vtexCoord = texCoord;
    gl_Position = mix(P, P2, t);
}

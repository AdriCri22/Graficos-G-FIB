#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin; 
uniform vec3 boundingBoxMax;

uniform float t = .4;
uniform float scale = 4.0;

void main()
{
    float c = mix(boundingBoxMin.y, boundingBoxMax.y, t);

    if (vertex.y < c)
        gl_Position = modelViewProjectionMatrix * vec4(vertex.x, vertex.y * scale, vertex.z, 1.0);
    else
        gl_Position = modelViewProjectionMatrix * vec4(vertex.x, vertex.y + c * scale - c, vertex.z, 1.0);

    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    
}

#version 330 core
layout (location = 0) in vec3 vertex;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

out vec3 viewDir;

void main()
{

    vec3 posWS = (inverse(modelViewProjectionMatrix) * vec4(vertex,1)).xyz;
    vec3 cameraWS = (inverse(modelViewMatrix) * vec4(0,0,0,1)).xyz;
    
    viewDir = normalize(posWS - cameraWS);
    
    gl_Position    = vec4(vertex,1.0);
}



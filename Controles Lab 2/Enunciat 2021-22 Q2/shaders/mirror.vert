#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;


out vec3 samplingDirWS;

void main()
{

    vec3 posWS = vertex;
    vec3 cameraWS = (inverse(modelViewMatrix) * vec4(0,0,0,1)).xyz;
    
    vec3 viewDir = normalize(posWS - cameraWS);
    samplingDirWS = reflect(viewDir, normal);

    gl_Position    = modelViewProjectionMatrix * vec4(vertex,1.0);
}



#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 N;
out vec3 V;
out vec3 vert;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrixInverse;

void main() {
  V = (modelViewMatrixInverse * vec4(0.0, 0.0, 0.0, 1.0)).xyz-vertex;
  N=normalize(normal);
  vert = vertex;
  gl_Position = modelViewProjectionMatrix * vec4(vertex.xyz, 1.0);
}
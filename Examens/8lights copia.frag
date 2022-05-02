#version 330 core

uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

in vec3 N;
in vec3 V;
in vec3 vert;
out vec4 fragColor;

vec4 Phong(vec3 N, vec3 V, vec3 L){
    L = normalize(L);
    vec3 R = normalize(2.0 * dot(N,L) * N-L);
    float NdotL = max(0.0, dot(N,L));
    float RdotV = max(0.0, dot(R,V));
    float Idiff = NdotL;
    float Ispec = 0;
    if (NdotL>0) Ispec=pow(RdotV,  matShininess);
    return (matDiffuse * lightDiffuse * Idiff )/2.0 + matSpecular * lightSpecular * Ispec;
}

void main() {  
  vec3 lights[8];
  lights[0] = vec3(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMax.z);
  lights[1] = vec3(boundingBoxMin.x,boundingBoxMax.y,boundingBoxMin.z);
  lights[2] = vec3(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMax.z);
  lights[3] = vec3(boundingBoxMin.x,boundingBoxMin.y,boundingBoxMin.z);
  lights[4] = vec3(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMax.z);
  lights[5] = vec3(boundingBoxMax.x,boundingBoxMax.y,boundingBoxMin.z);
  lights[6] = vec3(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMax.z);
  lights[7] = vec3(boundingBoxMax.x,boundingBoxMin.y,boundingBoxMin.z);
  fragColor = vec4(0);

  vec3 nV=normalize(V);
  for(int i = 0; i < 8; ++i)
  {
    fragColor+=Phong(N, nV, lights[i]-vert);
  }
}
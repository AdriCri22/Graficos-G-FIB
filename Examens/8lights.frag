#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 N;
in vec3 V;
in vec3 vvertex;

uniform mat4 modelViewMatrixInverse;
uniform mat4 modelView;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform vec4 lightAmbient;	// similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;	// similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular; // similar a gl_LightSource[0].specular
uniform vec4 lightPosition; // similar a gl_LightSource[0].position

uniform vec4 matAmbient; 	// similar a gl_FrontMaterial.ambient
uniform vec4 matDiffuse; 	// similar a gl_FrontMaterial.diffuse
uniform vec4 matSpecular; 	// similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess

uniform vec3 boundingBoxMin; 
uniform vec3 boundingBoxMax;

vec4 light(vec3 N, vec3 V, vec3 L) {
    N=normalize(N); V=normalize(V); L=normalize(L);
    vec3 R = normalize( 2.0*dot(N,L)*N-L );
    float NdotL = max( 0.0, dot( N,L ) );
    float RdotV = max( 0.0, dot( R,V ) );
    float Idiff = NdotL;
    float Ispec = 0;
    if (NdotL>0) Ispec=pow( RdotV, matShininess );
    return
      (matDiffuse  * lightDiffuse * Idiff) / 2. +
      matSpecular * lightSpecular * Ispec;
}

void main()
{
    vec3 L0 = boundingBoxMax - vvertex;
    vec3 L1 = vec3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z) - vvertex;
    vec3 L2 = vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z) - vvertex;
    vec3 L3 = vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z) - vvertex;
    vec3 L4 = vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z) - vvertex;
    vec3 L5 = vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z) - vvertex;
    vec3 L6 = vec3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z) - vvertex;
    vec3 L7 = boundingBoxMin - vvertex;

    //fragColor = light(N, V, L0);
    fragColor = light(N, V, L0) + light(N, V, L1) + light(N, V, L2) + light(N, V, L3) + light(N, V, L4) + light(N, V, L5) + light(N, V, L6) + light(N, V, L7);
}

#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 N;
in vec3 V;

in vec2 vtexCoord;

uniform vec4 lightAmbient;	// similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;	// similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular; // similar a gl_LightSource[0].specular
uniform vec4 lightPosition; // similar a gl_LightSource[0].position

uniform vec4 matAmbient; 	// similar a gl_FrontMaterial.ambient
uniform vec4 matDiffuse; 	// similar a gl_FrontMaterial.diffuse
uniform vec4 matSpecular; 	// similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess

uniform float time;
uniform sampler2D colorMap;

vec4 light(vec3 N, vec3 V, vec3 L) {
	N=normalize(N); V=normalize(V); L=normalize(L);
	vec3 R = normalize( 2.0*dot(N,L)*N-L );
	float NdotL = max( 0.0, dot( N,L ) );
	float RdotV = max( 0.0, dot( R,V ) );
	float Idiff = NdotL;
	float Ispec = 0;
	if (NdotL>0) Ispec=pow( RdotV, matShininess );

    vec4 lightDiffuse2; 
    if (mod(floor(time), 2) == 0)
        lightDiffuse2 = mix(vec4(0), vec4(0.8), fract(time));
    else
        lightDiffuse2 = mix(vec4(0.8), vec4(0), fract(time));

    vec4 matDiffuse2 = texture(colorMap, vec2(vtexCoord.s/4. + floor(time/2./3.)/4., vtexCoord.t/3. - 1./3. - floor(time/2.)/3.));

	return
        matDiffuse2 * lightDiffuse2 * Idiff +
        matSpecular * lightSpecular * Ispec;
}

void main()
{
    vec3 L = normalize(lightPosition.xyz - V);
    fragColor = light(N, -V, L);
}

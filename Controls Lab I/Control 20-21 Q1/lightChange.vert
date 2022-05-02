#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

out vec3 N;
out vec3 V;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main()
{
    N = normalize(normalMatrix * normal);
    V = (modelViewMatrix * vec4(vertex, 1.0)).xyz;
    frontColor = vec4(color,1.0) * N.z;
    // vtexCoord = vec2(texCoord.s/4. + floor(time/2.)/4., texCoord.t/3. - 1./3. - floor(time/2./4.) / 3.);
    // vtexCoord = vec2(texCoord.s/4. + 1./8. + floor(time/2.)/4., texCoord.t/3. + 1./6. - 1./3. - floor(time/2./4.) / 3.) / 2.;
    // vtexCoord = vec2(texCoord.s/4./2. + 1./8., texCoord.t/3./2. + 1./6.);
    vtexCoord = vec2(fract(texCoord.s), fract(texCoord.t));
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}

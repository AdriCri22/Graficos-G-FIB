#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform float time;
uniform sampler2D sampler;

void main()
{
    fragColor = texture(sampler, vtexCoord);
}

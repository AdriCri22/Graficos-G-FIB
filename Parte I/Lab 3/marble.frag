#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D noise;

void main()
{
    fragColor = frontColor * texture(noise, vtexCoord);
}

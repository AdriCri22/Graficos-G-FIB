#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform float speed=0.1;
uniform float time;
uniform sampler2D colorMap;

void main()
{
    fragColor = frontColor * texture(colorMap, vec2(speed * time) + vtexCoord);
}

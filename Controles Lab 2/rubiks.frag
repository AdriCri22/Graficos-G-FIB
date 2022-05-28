#version 330 core

in vec4 gfrontColor;
out vec4 fragColor;

in vec2 gtexCoord;

void main()
{
    if (0.05 < gtexCoord.s && gtexCoord.s < 0.95 && 0.05 < gtexCoord.t && gtexCoord.t < 0.95)
        fragColor = gfrontColor;
    else
        fragColor = vec4(0, 0, 0, 0);
}

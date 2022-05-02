#version 330 core

out vec4 fragColor;

in vec2 vtexCoord;
in vec3 N;

uniform sampler2D smile;

void main()
{
    float x = vtexCoord.s;
    float y = vtexCoord.t;

    float centerLeft = length(vec2(x - 0.34, y - 0.65) + 0.1 * N.xy);
    float leftEye = step(centerLeft, 0.05);

    float centerRight = length(vec2(x - 0.66, y - 0.65) + 0.1 * N.xy);
    float rightEye = step(centerRight, 0.05);

    if (leftEye != 0 || rightEye != 0)
        fragColor = vec4(0, 0, 0, 0);
    else
        fragColor = texture(smile, vtexCoord);
}
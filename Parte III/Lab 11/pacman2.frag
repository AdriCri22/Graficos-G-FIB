#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D colormap;
const float PI = 3.1415;
const mat2 rot = mat2(cos(PI/2.), sin(PI/2.), -sin(PI/2.), cos(PI/2.));

void main()
{
    float x = floor(vtexCoord.s * 12.);
    float y = floor(vtexCoord.t * 12.);
    vec2 vtexCoord2 = vtexCoord * rot;
    vec2 vtexCoord3 = vtexCoord * rot * rot;
    vec2 vtexCoord4 = vtexCoord * rot * rot * rot;
    float ntcS = fract(vtexCoord.s * 12.);
    float ntcT = fract(vtexCoord.t * 12.);
    float ntcS2 = fract(vtexCoord2.s * 12.);
    float ntcT2 = fract(vtexCoord2.t * 12.);
    float ntcS3 = fract(vtexCoord3.s * 12.);
    float ntcT3 = fract(vtexCoord3.t * 12.);
    float ntcS4 = fract(vtexCoord4.s * 12.);
    float ntcT4 = fract(vtexCoord4.t * 12.);
    vec2 turn0 = vec2(ntcS / 6. + 4./6., ntcT);
    vec2 turn1 = vec2(ntcS2 / 6. + 4./6., ntcT2);
    vec2 turn2 = vec2(ntcS3 / 6. + 4./6., ntcT3);
    vec2 turn3 = vec2(ntcS4 / 6. + 4./6., ntcT4);
    vec2 lineH = vec2(ntcS / 6. + 3./6., ntcT);
    vec2 lineV = vec2(ntcS2 / 6. + 3./6., ntcT2);
    vec2 point = vec2(ntcS / 6. + 5./6., ntcT);
    vec2 pacman = vec2(ntcS / 6. + 1./6., ntcT);
    vec2 ghost = vec2(ntcS / 6. + 0./6., ntcT);

    if (x == 0 && y == 0)
        fragColor = texture(colormap, turn2);
    else if (x == 11 && y == 0)
        fragColor = texture(colormap, turn3);
    else if (x == 0 && y == 11)
        fragColor = texture(colormap, turn1);
    else if (x == 11 && y == 11)
        fragColor = texture(colormap, turn0);
    else if (y == 0 || y == 11)
        fragColor = texture(colormap, lineH);
    else if (x == 0 || x == 11)
        fragColor = texture(colormap, lineV);
    else if ((x >= 2 && x <= 4) && (y == 9 || y == 7 || y == 5 || y == 3))
        fragColor = texture(colormap, lineH);
    else if ((x >= 7 && x <= 9) && (y == 9 || y == 7 || y == 5 || y == 3))
        fragColor = texture(colormap, lineH);
    else if (((x == 2 || x == 6) && y == 1) || ((x == 4 || x == 8) && y == 2))
        fragColor = texture(colormap, lineV);
    else if (x == 4 && y == 1)
        fragColor = texture(colormap, pacman);
    else if ((x == 7 && y == 1) || (x == 3 && y == 8))
        fragColor = texture(colormap, ghost);
    else
        fragColor = texture(colormap, point);
}

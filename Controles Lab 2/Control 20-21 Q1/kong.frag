#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D colormap;

const float PI = 3.1415;
const mat2 rot = mat2(cos(PI/2.), sin(PI/2.), -sin(PI/2.), cos(PI/2.));
const float PARTS = 14;

void main()
{
    float x = floor(vtexCoord.s * PARTS);
    float y = floor(vtexCoord.t * PARTS);
    vec2 vtexCoord2 = vtexCoord * rot;
    vec2 vtexCoord3 = vtexCoord * rot * rot;
    vec2 vtexCoord4 = vtexCoord * rot * rot * rot;
    float ntcS = fract(vtexCoord.s * PARTS);
    float ntcT = fract(vtexCoord.t * PARTS);
    float ntcS2 = fract(vtexCoord2.s * PARTS);
    float ntcT2 = fract(vtexCoord2.t * PARTS);
    float ntcS3 = fract(vtexCoord3.s * PARTS);
    float ntcT3 = fract(vtexCoord3.t * PARTS);
    float ntcS4 = fract(vtexCoord4.s * PARTS);
    float ntcT4 = fract(vtexCoord4.t * PARTS);
    vec2 barrilV = vec2(ntcS / 7. + 0./7., ntcT);
    vec2 barrilH = vec2(ntcS2 / 7. + 0./7., ntcT2);
    vec2 kong = vec2(ntcT2 / 7. + 1./7., ntcS2);
    vec2 viga = vec2(ntcS / 7. + 2./7., ntcT);
    vec2 escales = vec2(ntcS / 7. + 3./7., ntcT);
    vec2 princesa = vec2(ntcT2 / 7. + 4./7., ntcS2);
    vec2 mario = vec2(ntcS / 7. + 5./7., ntcT);
    vec2 blank = vec2(ntcS / 7. + 6./7., ntcT);

    if (x > 0 && x < 13 && (y == 0 || y == 3 || y == 6 || y == 9))
        fragColor = texture(colormap, viga);
    else if ((x > 3 && x < 7) && y == 11)
        fragColor = texture(colormap, viga);
    else if ((x == 11 || x == 12) && (y == 10 || y == 11 ))
        fragColor = texture(colormap, barrilV);
    else if ((x == 2 || x == 5 || x == 8) && y == 4)
        fragColor = texture(colormap, barrilH);
    else if ((x == 3 || x == 6 || x == 9) && (y == 1 || y == 2 || y == 7 || y == 8))
        fragColor = texture(colormap, escales);
    else if ((x == 2 || x == 5 || x == 8) && y == 5)
        fragColor = texture(colormap, escales);
    else if ((x == 3 || x == 7 || x == 8) && (y >= 10 && y < 13))
        fragColor = texture(colormap, escales);
    else if (x == 5 && y == 12)
        fragColor = texture(colormap, princesa);
    else if (x == 9 && y == 10)
        fragColor = texture(colormap, kong);
    else if (x == 2 && y == 7)
        fragColor = texture(colormap, mario);
    else
        fragColor = texture(colormap, blank);
}

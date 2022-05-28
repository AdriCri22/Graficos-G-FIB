#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

const float PARTS = 14;
uniform sampler2D colormap;

void main()
{
    float x = floor(vtexCoord.s * PARTS);
    float y = floor(vtexCoord.t * PARTS);
    float ntcS = fract(vtexCoord.s * PARTS);
    float ntcT = fract(vtexCoord.t * PARTS);
    vec2 marciano41 = vec2(ntcS / 4. + 0./4., ntcT / 4. + 0./4.);
    vec2 marciano42 = vec2(ntcS / 4. + 1./4., ntcT / 4. + 0./4.);
    vec2 marciano43 = vec2(ntcS / 4. + 2./4., ntcT / 4. + 0./4.);
    vec2 escudo = vec2(ntcS / 4. + 3./4., ntcT / 4. + 0./4.);
    vec2 marciano31 = vec2(ntcS / 4. + 0./4., ntcT / 4. + 1./4.);
    vec2 marciano32 = vec2(ntcS / 4. + 1./4., ntcT / 4. + 1./4.);
    vec2 marciano33 = vec2(ntcS / 4. + 2./4., ntcT / 4. + 1./4.);
    vec2 canon = vec2(ntcS / 4. + 3./4., ntcT / 4. + 1./4.);
    vec2 marciano21 = vec2(ntcS / 4. + 0./4., ntcT / 4. + 2./4.);
    vec2 marciano22 = vec2(ntcS / 4. + 1./4., ntcT / 4. + 2./4.);
    vec2 marciano23 = vec2(ntcS / 4. + 2./4., ntcT / 4. + 2./4.);
    vec2 marciano24 = vec2(ntcS / 4. + 3./4., ntcT / 4. + 2./4.);
    vec2 marciano11 = vec2(ntcS / 4. + 0./4., ntcT / 4. + 3./4.);
    vec2 marciano12 = vec2(ntcS / 4. + 1./4., ntcT / 4. + 3./4.);
    vec2 marciano13 = vec2(ntcS / 4. + 2./4., ntcT / 4. + 3./4.);
    vec2 marciano14 = vec2(ntcS / 4. + 3./4., ntcT / 4. + 3./4.);

    if (x == 6 && y == 1)
        fragColor = texture(colormap, canon);
    else if ((x == 1 || x == 5 || x == 8 || x == 12) && y == 3)
        fragColor = texture(colormap, escudo);
    else if ((x > 0 && x < 13) && y == 5)
        fragColor = texture(colormap, marciano41);
    else if ((x > 0 && x < 13) && y == 6)
        fragColor = texture(colormap, marciano31);
    else if ((x > 0 && x < 13) && y == 7)
        fragColor = texture(colormap, marciano21);
    else if ((x > 0 && x < 13) && y == 8)
        fragColor = texture(colormap, marciano11);
    else if ((x > 0 && x < 13) && y == 9)
        fragColor = texture(colormap, marciano42);
    else if ((x > 0 && x < 13) && y == 10)
        fragColor = texture(colormap, marciano32);
    else if ((x > 0 && x < 13) && y == 11)
        fragColor = texture(colormap, marciano22);
    else if ((x > 0 && x < 13) && y == 12)
        fragColor = texture(colormap, marciano12);
    else
        fragColor = vec4(0, 0, 0, 0);
}

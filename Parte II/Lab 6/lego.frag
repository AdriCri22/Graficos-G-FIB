#version 330 core

out vec4 fragColor;

in vec2 gtexCoord;
in vec4 gfrontColor;
uniform sampler2D colorMap;
in float top;

const vec4 RED      = vec4(1, 0, 0, 1);
const vec4 GREEN    = vec4(0, 1, 0, 1);
const vec4 BLUE     = vec4(0, 0, 1, 1);
const vec4 CIAN     = vec4(0, 1, 1, 1);
const vec4 YELLOW   = vec4(1, 1, 0, 1);

void main() {
    float r = distance(RED, gfrontColor);
    float g = distance(GREEN, gfrontColor);
    float b = distance(BLUE, gfrontColor);
    float c = distance(CIAN, gfrontColor);
    float y = distance(YELLOW, gfrontColor);

    vec4 textura = vec4(1, 1, 1, 1);

    if (top == 1.)
        textura = texture(colorMap, gtexCoord);

    if (4 * r < g + b + c + y)
        fragColor = RED * textura;
    else if (4 * g < r + b + c + y)
        fragColor = GREEN * textura;
    else if (4 * b < r + g + c + y)
        fragColor = BLUE * textura;
    else if (4 * c < r + g + b + y)
        fragColor = CIAN * textura;
    else 
        fragColor = YELLOW * textura;

    //fragColor = gfrontColor * texture(colorMap, gtexCoord);

}

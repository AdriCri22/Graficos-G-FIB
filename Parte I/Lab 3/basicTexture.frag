#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;
uniform sampler2D colorMap;

// La normal z es 0 en eyespace quan la normal de l'objecte apunta a la cara i 0 quan és paralel a aquests

void main()
{
    fragColor = frontColor * texture(colorMap, vtexCoord);
}

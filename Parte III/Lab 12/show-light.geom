#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 projectionMatrix;
uniform vec4 lightPosition;
uniform float w = 0.3;

void drawSquare() {
    vec4 lightPositionClip = projectionMatrix * lightPosition;
	vec4 lpNDC = lightPositionClip / lightPositionClip.w;
    vec4 v1 = vec4(lpNDC.x - w, lpNDC.y - w, lpNDC.z, lpNDC.w);
    vec4 v2 = vec4(lpNDC.x + w, lpNDC.y - w, lpNDC.z, lpNDC.w);
    vec4 v3 = vec4(lpNDC.x - w, lpNDC.y + w, lpNDC.z, lpNDC.w);
    vec4 v4 = vec4(lpNDC.x + w, lpNDC.y + w, lpNDC.z, lpNDC.w);
    
    gfrontColor = vec4(1, 0, 0, 0);
    gl_Position = v1;
    gtexCoord = vec2(0, 0);
	EmitVertex();
    gl_Position = v2;
    gtexCoord = vec2(1, 0);
	EmitVertex();
    gl_Position = v3;
    gtexCoord = vec2(0, 1);
	EmitVertex();
    gl_Position = v4;
    gtexCoord = vec2(1, 1);
	EmitVertex();
}

void main( void )
{
	if (gl_PrimitiveIDIn == 0)
		drawSquare();	
	else {
		for( int i = 0 ; i < 3 ; i++ )
		{
			gfrontColor = vfrontColor[i];
			gtexCoord = vec2(-1.0, -1.0);
			gl_Position = gl_in[i].gl_Position;
			EmitVertex();
		}
	}
    EndPrimitive();
}

#version 330 core
out vec4 fragColor;

uniform sampler2D sampler0;

in vec3 viewDir;

#define PI 3.1415926538

void main()
{
     
    float longRad = atan(viewDir.z, viewDir.x);
    float latRad = asin(viewDir.y);
    
    float s = longRad/(2*PI)+0.5;
    float t = latRad/PI+0.5;
    
    vec2 st = vec2(s,t);

        
    fragColor = texture2D(sampler0, st);

}



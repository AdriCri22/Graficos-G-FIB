#version 330 core
out vec4 fragColor;

uniform sampler2D sampler0;

in vec3 samplingDirWS;

#define PI 3.1415926538

void main()
{   
    float longRad = atan(samplingDirWS.z, samplingDirWS.x);
    float latRad = asin(samplingDirWS.y);
    
    float s = longRad/(2*PI)+0.5;
    float t = latRad/PI+0.5;
    
    vec2 st = vec2(s,t);

        
    fragColor = texture2D(sampler0, st);

}



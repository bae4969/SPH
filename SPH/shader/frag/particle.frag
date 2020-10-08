#version 140
#extension GL_ARB_compatibility: enable
#define PI 3.1415926535897932384626433832795

in vec3 vertex;
in vec3 center;

uniform vec3 camLocUni;

void main()
{
	vec3 toCam = normalize(camLocUni - center);
	vec3 toVer = normalize(vertex - center);
	float cosVal = dot(toCam, toVer);
	float sinVal = sqrt(1 - pow(cosVal, 2));
	float constant = exp(-pow(sinVal,2) * 8);
	
	//if(constant < 0.6)
	//	discard;
	gl_FragColor = vec4(0.3,0.6,0.9,1);
}
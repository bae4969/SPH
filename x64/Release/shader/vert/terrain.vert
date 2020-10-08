#version 140
//#define GL_compatibility_profile 1
#extension GL_ARB_compatibility: enable

in vec3 terAtt;

out vec2 valueYZ;

uniform mat4 sizeUni;

void main()
{	
	gl_Position = gl_ModelViewProjectionMatrix * sizeUni * vec4(terAtt, 1.0);
	valueYZ.xy = terAtt.yz;
}

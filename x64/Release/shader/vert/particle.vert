#version 140
//#define GL_compatibility_profile 1
#extension GL_ARB_compatibility: enable

in vec3 verAtt;

out vec3 vertex;
out vec3 center;

uniform mat4 tranUni;

void main()
{	
	gl_Position = gl_ModelViewProjectionMatrix * tranUni * vec4(verAtt, 1.0);
	vertex = (tranUni * vec4(verAtt,1.0)).xyz;
	center = (tranUni * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
}

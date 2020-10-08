#version 140
#extension GL_ARB_compatibility: enable

in vec2 valueYZ;

uniform float colorUni;
uniform sampler2D tex;

void main()
{
	float dis = sqrt(pow(valueYZ.x,2)+pow(valueYZ.y,2));
	vec2 pos = vec2(valueYZ.y, valueYZ.x) / dis;
	if(colorUni > 0)
		gl_FragColor = texture(tex, pos);
	else
		gl_FragColor = vec4(1.0-valueYZ.x/9, 0, valueYZ.x/9, 1);
}
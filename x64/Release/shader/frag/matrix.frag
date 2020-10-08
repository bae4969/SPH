#version 140
#extension GL_ARB_compatibility: enable

in vec3 pixelPosition;
uniform vec3 eyePos;
uniform vec3 matMin;
uniform vec3 matMax;
uniform vec3 eyeUp;
uniform sampler3D tex;
uniform float terrUni;

void main(){
    vec3 right=normalize(cross(-eyePos,eyeUp));
    vec3 virtualScreenCoord=eyePos*0.5+
                                right*pixelPosition.x+
                                eyeUp*pixelPosition.y;
    vec3 rayDirection=normalize(virtualScreenCoord-eyePos); 
	vec3 endPoint[2];

	bool check[6];
	float c[6];
	vec3 temp[6];
	vec3 temp_EP[2];

	for(int i = 0; i < 6; i++){
		check[i] = false;
		temp[i] = eyePos;
	}

	if(rayDirection.x != 0){
		c[0] = (matMin.x - eyePos.x) / rayDirection.x;
		c[3] = (matMax.x - eyePos.x) / rayDirection.x;
		temp[0] += rayDirection * c[0];
		temp[3] += rayDirection * c[3];
		if(temp[0].y >= matMin.y && temp[0].y < matMax.y
		&& temp[0].z >= matMin.z && temp[0].z < matMax.z)
			check[0] = true;
		if(temp[3].y >= matMin.y && temp[3].y < matMax.y
		&& temp[3].z >= matMin.z && temp[3].z < matMax.z)
			check[3] = true;
	}
	if(rayDirection.y != 0){
		c[1] = (matMin.y - eyePos.y) / rayDirection.y;
		c[4] = (matMax.y - eyePos.y) / rayDirection.y;
		temp[1] += rayDirection * c[1];
		temp[4] += rayDirection * c[4];
		if(temp[1].x >= matMin.x && temp[1].x < matMax.x
		&& temp[1].z >= matMin.z && temp[1].z < matMax.z)
			check[1] = true;
		if(temp[4].x >= matMin.x && temp[4].x <= matMax.x
		&& temp[4].z >= matMin.z && temp[4].z <= matMax.z)
			check[4] = true;
	}
	if(rayDirection.z != 0){
		c[2] = (matMin.z - eyePos.z) / rayDirection.z;
		c[5] = (matMax.z - eyePos.z) / rayDirection.z;
		temp[2] += rayDirection * c[2];
		temp[5] += rayDirection * c[5];
		if(temp[2].x >= matMin.x && temp[2].x < matMax.x
		&& temp[2].y >= matMin.y && temp[2].y < matMax.y)
			check[2] = true;
		if(temp[5].x >= matMin.x && temp[5].x < matMax.x
		&& temp[5].y >= matMin.y && temp[5].y < matMax.y)
			check[5] = true;
	}
	
	int index = 0;
	for(int i = 0; i < 6; i++){
		if(check[i]){
			temp_EP[index] = temp[i];
			index++;
			if(index == 2)
				break;
		}
	}

	if(index == 0 || index == 1){
		discard;
	}
	else if(distance(eyePos, temp_EP[0]) < distance(eyePos, temp_EP[1])){
		endPoint[0] = temp_EP[0];
		endPoint[1] = temp_EP[1];
	}
	else{
		endPoint[0] = temp_EP[1];
		endPoint[1] = temp_EP[0];
	}

	
    vec4 composedColor=vec4(0,0,0,0);
	float tempValue;
    vec3 norDir = endPoint[1] - endPoint[0];
	vec3 tempPoint;
	vec4 texColor;

	for(int i = 0; i < 200; i++){
		tempPoint = endPoint[0] + (i * 0.005 * norDir) - matMin;
		tempPoint.x /= (matMax.x - matMin.x);
		tempPoint.y /= (matMax.y - matMin.y);
		tempPoint.z /= (matMax.z - matMin.z);
		texColor = texture(tex, tempPoint);
		if(composedColor.r < texColor.r)
			composedColor = texColor;
	}

	if(composedColor.r > 0.5){
		if(terrUni > 0)
			gl_FragColor = vec4(0.5,0.6,0.2,1);
		else
			gl_FragColor = composedColor.r * vec4(0.3,0.6,0.9,1);
	}
	else
		discard;
}
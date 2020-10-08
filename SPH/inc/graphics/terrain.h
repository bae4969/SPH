#pragma once

#include <math.h>

#define NUMPOINT 106
#define NUMTRIANGLE 157

struct vec3_ {
	float x;
	float y;
	float z;
};

float valueX[NUMPOINT] = {
	0.0,
	0.0,	0.7,					//중앙 위 아래 순
	1.4,	1.75,
	2.1,	2.5,
	2.9,	3.3,
	3.7,	4.15,
	4.6,	4.6,	6.0,
	6.0,	6.0,	6.65,	6.65,	//윗길 위 아랫길 위, 윗길 아래 아랫길 아래
	7.3,	7.3,	7.8,	7.8,
	8.3,	8.3,	8.8,	8.8,
	9.3,	9.3,	9.9,	9.9,
	10.5,	10.5,	11.0,	11.0,
	11.4,	11.4,	11.4,	11.4,

	0.0,	1.4,	2.1,	2.9,	//위 위 경계면
	3.7,	4.6,	6.0,	7.3,
	8.3,	9.3,	10.5,	11.4,

	0.0,
	0.7,	1.75,	2.5,	3.3,	//위 아래 경계면
	4.15,	5.1,	6.65,	7.8,
	8.8,	9.9,	11.0,	11.4,

	0.0,	0.7,	1.75,	2.5,	//아래 아래 경계면
	3.3,	4.15,	5.1,	6.65,
	7.8,	8.8,	9.95,	11.0,
	11.4,

	0.0,	1.4,	2.1,	2.9,	//아래 위 경계면
	3.7,	4.6,	6.0,	7.3,
	8.3,	9.3,	10.5,	11.4,

	7.0,	8.05,	9.05,	10.2,
	11.2,	11.4,

	11.4,	11.4,	0.0,	0.0,
	11.4,	11.4,	0.0,	0.0,
	0.0,	0.0,	0.0,	0.0
};

float valueY[NUMPOINT] = {
	2.4,
	4.8,	2.4,
	5.0,	2.8,
	5.6,	3.3,
	6.0,	3.3,
	5.6,	2.95,
	5.3,	2.8,	6.0,
	4.0,	1.0,	4.25,	0.75,
	6.7,	3.0,	4.45,	0.45,
	7.2,	2.9,	4.95,	0.45,
	7.7,	3.0,	5.35,	0.75,
	8.0,	3.5,	5.5,	1.1,
	8.0,	3.7,	5.5,	1.2,

	9.0,	9.0,	9.0,	9.0,	//위 위 경계면
	9.0,	9.0,	9.0,	9.0,
	9.0,	9.0,	9.0,	9.0,

	5.4,
	5.4,	5.8,	6.3,	6.3,	//위 아래 경계면
	5.9,	6.15,	6.85,	7.85,
	7.95,	8.35,	8.5,	8.5,

	0.0,	0.0,	0.0,	0.0,	//아래 아래 경계면
	0.0,	0.0,	0.0,	0.0,
	0.0,	0.0,	0.0,	0.0,
	0.0,

	1.8,	2.0,	2.6,	3.0,	//아래 위 경계면
	2.6,	2.3,	0.5,	0.0,
	0.0,	0.0,	0.5,	0.7,

	3.42,	3.67,	4.0,	4.4,
	4.6,	4.6,

	0.0,	0.0,	0.0,	0.0,
	9.0,	9.0,	9.0,	9.0,
	0.0,	0.0,	9.0,	9.0
};

float valueZ[NUMPOINT] = {
	9.0,
	9.0,	6.7,
	4.3,	4.3,
	4.2,	4.2,
	4.1,	4.1,
	4.0,	4.0,
	3.9,	3.9,	3.8,
	3.8,	3.8,	3.0,	2.6,	//윗길 아랫길
	2.7,	2.8,	2.4,	3.0,
	1.95,	2.75,	1.5,	2.5,
	1.3,	1.75,	1.1,	1.0,
	0.9,	0.8,	0.7,	0.6,
	0.5,	0.5,	0.5,	0.5,

	9.0,	9.0,	9.0,	9.0,
	9.0,	9.0,	9.0,	9.0,
	9.0,	9.0,	9.0,	9.0,

	9.0,
	7.4,	7.3,	7.2,	7.1,
	7.0,	6.9,	6.8,	5.7,
	4.95,	4.3,	3.9,	3.5,

	9.0,	9.0,	9.0,	9.0,
	9.0,	9.0,	9.0,	9.0,
	9.0,	9.0,	9.0,	9.0,
	9.0,

	9.0,	7.3,	7.2,	7.1,
	7.0,	6.9,	6.8,	5.8,
	5.75,	4.75,	3.8,	3.5,

	6.0,	6.5,	7.0,	7.5,
	8.0,	8.0,

	9.0,	0.0,	9.0,	0.0,
	9.0,	0.0,	9.0,	0.0,
	9.0,	0.0,	9.0,	0.0
};

int index[NUMTRIANGLE * 3] = {
	0,2,1,		1,2,3,		2,4,3,		3,4,5,		//중앙길
	4,6,5,		5,6,7,		6,8,7,		7,8,9,
	8,10,9,		9,10,11,	10,12,11,	11,12,14,	//갈림길

	11,14,13,	13,14,16,	13,16,18,	16,20,18,	//윗쪽길
	18,20,22,	20,24,22,	22,24,26,	24,28,26,
	26,28,30,	28,32,30,	30,32,34,	32,36,34,

	12,15,14,	15,17,14,	14,17,19,	17,21,19,	//아랫길
	19,21,23,	21,25,23,	23,25,27,	25,29,27,
	27,29,31,	29,33,31,	31,33,35,	33,37,35,

	50,51,38,	38,51,39,	51,52,39,	39,52,40,	//윗길 윗벽
	52,53,40,	40,53,41,	53,54,41,	41,54,42,
	54,55,42,	42,55,43,	55,56,43,	56,44,43,	//반
	56,57,44,	44,57,45,	57,58,45,	45,58,46,
	58,59,46,	46,59,47,	59,60,47,	47,60,48,
	60,61,48,	48,61,49,	61,62,49,

	1,51,50,	1,3,51,		51,3,52,	3,5,52,		//윗길 아래벽
	52,5,53,	5,7,53,		53,7,54,	7,9,54,
	54,9,55,	9,11,55,	55,11,56,	11,13,56,	//반
	56,13,57,	13,18,57,	57,18,58,	18,22,58,
	58,22,59,	22,26,59,	59,26,60,	26,60,30,
	60,30,61,	61,30,34,	61,34,62,

	63,64,76,	76,64,77,	64,65,77,	77,65,78,	//아랫길 아래벽
	65,66,78,	78,66,79,	66,67,79,	79,67,80,
	67,68,80,	80,68,81,	68,69,81,	81,69,82,	//반
	69,70,82,	82,70,83,	70,71,83,	83,71,84,
	71,72,84,	84,72,85,	72,73,85,	85,73,86,
	73,74,86,	86,74,87,	74,75,87,

	0,76,2,		76,77,2,	2,77,4,		77,78,4,	//아랫길 윗벽
	4,78,6,		78,79,6,	6,79,8,		79,80,8,
	8,80,10,	80,81,10,	10,81,12,	12,81,15,	//반
	81,82,15,	15,82,17,	82,83,17,	17,83,21,
	83,84,21,	21,84,25,	84,85,25,	25,85,29,
	85,86,29,	29,86,33,	86,87,33,	33,87,37,

	14,88,16,	88,89,16,	16,89,20,	89,90,20,	//윗아래 벽
	20,90,24,	90,91,24,	24,91,28,	91,92,28,
	28,92,32,	92,93,32,	32,93,36,

	14,88,19,	88,19,89,	19,23,89,	89,23,90,	//아래위벽
	23,27,90,	90,27,91,	27,31,91,	91,31,92,
	31,35,92,	92,35,93,

	94,96,95,	95,97,96,	98,100,99,	99,101,100,
	102,103,104,103,104,105,35,36,93
};

float forGraphicPart[NUMPOINT * 3];
float normal[NUMTRIANGLE * 3];


vec3_ getDirection(vec3_ p1, vec3_ p2) {
	vec3_ dir;
	dir.x = p2.x - p1.x;
	dir.y = p2.y - p1.y;
	dir.z = p2.z - p1.z;
	return dir;
}

float dotProduct(vec3_ v1, vec3_ v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3_ crossProduct(vec3_ v1, vec3_ v2) {
	vec3_ normal;
	normal.x = v1.y * v2.z - v1.z * v2.y;
	normal.y = v1.z * v2.x - v1.x * v2.z;
	normal.z = v1.x * v2.y - v1.y * v2.x;
	return normal;
}

float length(vec3_ v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}


vec3_ normalize(vec3_ loc) {
	float l = length(loc);
	vec3_ r;

	r.x = loc.x / l;
	r.y = loc.y / l;
	r.z = loc.z / l;

	return r;
}
vec3_ getNormal(vec3_ p1, vec3_ p2, vec3_ p3) {
	vec3_ normal;
	vec3_ v1 = getDirection(p2, p1);
	vec3_ v2 = getDirection(p2, p3);

	normal = crossProduct(v2, v1);
	normal = normalize(normal);

	return normal;
}
vec3_ threeFloat2vec3(int i) {
	vec3_ v;
	v.x = valueX[i];
	v.y = valueY[i];
	v.z = valueZ[i];
	return v;
}
vec3_* index2Triangle(int i) {
	int p[3];
	vec3_ t[3];

	for (int j = 0; j < 3; j++) {
		p[j] = index[3 * i + j];
		t[j] = threeFloat2vec3(p[j]);
	}

	return t;
}

void setForGraphic(float scale) {
	for (int i = 0; i < NUMPOINT; i++) {
		forGraphicPart[3 * i] = valueX[i] / 12 * 40 * scale;
		forGraphicPart[3 * i + 1] = valueZ[i] / 4.4 * 5 * scale;
		forGraphicPart[3 * i + 2] = valueY[i] / 9 * 20 * scale;
	}
}
void setNormal() {
	int indexNum[3];
	vec3_ temp[3], result;
	for (int i = 0; i < NUMTRIANGLE; i++) {
		for (int j = 0; j < 3; j++)
			indexNum[j] = index[3 * i + j];
		for (int j = 0; j < 3; j++) {
			temp[j].x = forGraphicPart[3 * indexNum[j]];
			temp[j].y = forGraphicPart[3 * indexNum[j] + 2];
			temp[j].z = forGraphicPart[3 * indexNum[j] + 1];
		}
		result = getNormal(temp[0], temp[1], temp[2]);

		normal[3 * i] = result.x;
		normal[3 * i + 1] = result.y;
		normal[3 * i + 2] = result.z;
	}
}

float isInTriangle(int i, float x, float y, float z) {
	int point[3];
	float c[3];
	vec3_ p;
	vec3_ t[3];
	vec3_ dir[3];
	p.x = x;
	p.y = y;
	p.z = z;
	for (int j = 0; j < 3; j++)
		point[j] = index[3 * i + j];
	for (int j = 0; j < 3; j++) {
		t[j].x = forGraphicPart[3 * point[j]];
		t[j].y = forGraphicPart[3 * point[j] + 2];
		t[j].z = forGraphicPart[3 * point[j] + 1];
	}
	dir[0] = getDirection(t[2], t[0]);
	dir[1] = getDirection(t[2], t[1]);
	dir[2] = getDirection(t[2], p);

	if (dir[0].x == 0) {
		c[1] = dir[2].x / dir[1].x;
		if (dir[1].y == 0)
			c[0] = dir[2].y / dir[0].y;
		else {
			c[0] = dir[2].y - c[1] * dir[1].y;
			c[0] /= dir[0].y;
		}
	}
	else if (dir[0].y == 0) {
		c[1] = dir[2].y / dir[1].y;
		if (dir[1].x == 0)
			c[0] = dir[2].x / dir[0].x;
		else {
			c[0] = dir[2].x - c[1] * dir[1].x;
			c[0] /= dir[0].x;
		}
	}
	else {
		c[1] = dir[2].x / dir[0].x - dir[2].y / dir[0].y;
		c[1] /= dir[1].x / dir[0].x - dir[1].y / dir[0].y;
		c[0] = dir[2].x / dir[0].x - c[1] * dir[1].x / dir[0].x;
	}

	c[2] = c[0] + c[1];
	if (c[2] < 0 || c[2] > 1 || c[0] < 0 || c[1] < 0)
		return -1;
	else
		return dir[0].z * c[0] + dir[1].z * c[1] + t[2].z;
}

vec3_* tri2PDD(int i) {
	int triIndex[3];
	vec3_ triPoint[3];
	vec3_* ret = new vec3_[3];

	for (int j = 0; j < 3; j++)
		triIndex[j] = index[3 * i + j];
	for (int j = 0; j < 3; j++) {
		triPoint[j].x = forGraphicPart[3 * triIndex[j]];
		triPoint[j].y = forGraphicPart[3 * triIndex[j] + 2];
		triPoint[j].z = forGraphicPart[3 * triIndex[j] + 1];
	}
	ret[0] = triPoint[0];
	ret[1] = getDirection(triPoint[0], triPoint[1]);
	ret[2] = getDirection(triPoint[0], triPoint[2]);

	return ret;
}

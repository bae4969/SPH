#include "particle.h"


particle::particle() {
	id = 0;
	for (int i = 0; i < 3; i++) {
		loc[i] = 0;
		vel[i] = 0;
	}
	density = 0;
	pressure = 0;
	vis = 0;
	pre = NULL;
	next = NULL;
	outputPre = NULL;
	outputNext = NULL;
}
particle::particle(int id_num, float* l, float* v, float d, float vi) {
	id = id_num;
	for (int i = 0; i < 3; i++) {
		loc[i] = l[i];
		vel[i] = v[i];
	}
	density = d;
	pressure = 0;
	vis = vi;
	pre = NULL;
	next = NULL;
	outputPre = NULL;
	outputNext = NULL;
}
particle::~particle() {

}

float particle::distance(particle* p) {
	return sqrt(pow(this->loc[0] - p->loc[0], 2)
		+ pow(this->loc[1] - p->loc[1], 2)
		+ pow(this->loc[2] - p->loc[2], 2));
}
float particle::velocity() {
	return sqrt(pow(vel[0], 2)
		+ pow(vel[1], 2)
		+ pow(vel[2], 2));
}
unsigned char particle::getOutputValue(float x, float y, float z) {
	float t = pow(this->loc[0] - x, 2)
		+ pow(this->loc[1] - y, 2)
		+ pow(this->loc[2] - z, 2);
	return exp(-t) * 255.0;
}

void particle::move(bool box, float time, int* size) {
	for (int i = 0; i < 3; i++)
		loc[i] += time * vel[i];

	if (box) {
		for (int i = 0; i < 3; i++) {
			if (loc[i] > size[i] - 1) {
				loc[i] = 2 * size[i] - 2 - loc[i];
				vel[i] = -(vel[i] * 0.7);
			}
			else if (loc[i] <= 0) {
				loc[i] = -loc[i];
				vel[i] = -(vel[i] * 0.7);
			}
		}
	}
}
void particle::addGravity(float time) {
	vel[1] -= time * GRAVITY_ACC;
}
bool particle::collisionP2P(float r, particle* p) {
	float normal[3], a[2], b[2];
	float v_this[3], v_arg[3];
	float normalSize = 0;
	float dot = 0;
	float dis = this->distance(p);

	if (p->getId() != -1) {
		if (dis < 2 * r) {
			for (int i = 0; i < 3; i++) {
				normal[i] = p->loc[i] - this->loc[i];
				normalSize += normal[i] * normal[i];
			}
			normalSize = sqrt(normalSize);

			if (normal[0] != 0) {
				a[0] = normal[1] / normal[0];
				a[1] = a[0] * a[0];
				b[0] = normal[2] / normal[0];
				b[1] = b[0] * b[0];

				v_this[0] = (vel[0] + vel[1] * a[0] + vel[2] * b[0]);
				v_this[0] /= 1 + a[1] + b[1];
				v_this[1] = a[0] * v_this[0];
				v_this[2] = b[0] * v_this[0];

				v_arg[0] = (p->vel[0] + p->vel[1] * a[0] + p->vel[2] * b[0]);
				v_arg[0] /= 1 + a[1] + b[1];
				v_arg[1] = a[0] * v_arg[0];
				v_arg[2] = b[0] * v_arg[0];
			}
			else if (normal[1] != 0) {
				a[0] = normal[0] / normal[1];
				a[1] = a[0] * a[0];
				b[0] = normal[2] / normal[1];
				b[1] = b[0] * b[0];

				v_this[1] = (vel[0] + vel[0] * a[0] + vel[2] * b[0]);
				v_this[1] /= 1 + a[1] + b[1];
				v_this[0] = a[0] * v_this[1];
				v_this[2] = b[0] * v_this[1];

				v_arg[1] = (p->vel[0] + p->vel[0] * a[0] + p->vel[2] * b[0]);
				v_arg[1] /= 1 + a[1] + b[1];
				v_arg[0] = a[0] * v_arg[1];
				v_arg[2] = b[0] * v_arg[1];
			}
			else if (normal[2] != 0) {
				a[0] = normal[0] / normal[2];
				a[1] = a[0] * a[0];
				b[0] = normal[1] / normal[2];
				b[1] = b[0] * b[0];

				v_this[2] = (vel[0] + vel[0] * a[0] + vel[1] * b[0]);
				v_this[2] /= 1 + a[1] + b[1];
				v_this[0] = a[0] * v_this[2];
				v_this[1] = b[0] * v_this[2];

				v_arg[2] = (p->vel[0] + p->vel[0] * a[0] + p->vel[1] * b[0]);
				v_arg[2] /= 1 + a[1] + b[1];
				v_arg[0] = a[0] * v_arg[2];
				v_arg[1] = b[0] * v_arg[2];
			}
			else {
				return false;
			}

			for (int i = 0; i < 3; i++) {
				this->vel[i] += 0.7 * (v_arg[i] - v_this[i]);
				p->vel[i] += 0.7 * (v_this[i] - v_arg[i]);
			}

			float t = (2 * r) - dis;
			t /= 2 * r * normalSize;
			if (loc[1] > p->loc[1])
				for (int i = 0; i < 3; i++)
					this->loc[i] -= normal[i] * t * 1.01;
			else
				for (int i = 0; i < 3; i++)
					p->loc[i] += normal[i] * t * 1.01;
			return true;
		}
	}
	else {
		if (dis < 2 * r) {
			float tempNor[3];

			for (int i = 0; i < 3; i++) {
				tempNor[i] = this->loc[i] - p->loc[i];
				normal[i] = p->vel[i];
				dot += tempNor[i] * normal[i];
				normalSize += normal[i] * normal[i];
			}

			normalSize = sqrt(normalSize);
			if (normal[0] != 0) {
				a[0] = normal[1] / normal[0];
				a[1] = a[0] * a[0];
				b[0] = normal[2] / normal[0];
				b[1] = b[0] * b[0];

				v_this[0] = (vel[0] + vel[1] * a[0] + vel[2] * b[0]);
				v_this[0] /= 1 + a[1] + b[1];
				v_this[1] = a[0] * v_this[0];
				v_this[2] = b[0] * v_this[0];
			}
			else if (normal[1] != 0) {
				a[0] = normal[0] / normal[1];
				a[1] = a[0] * a[0];
				b[0] = normal[2] / normal[1];
				b[1] = b[0] * b[0];

				v_this[1] = (vel[0] + vel[0] * a[0] + vel[2] * b[0]);
				v_this[1] /= 1 + a[1] + b[1];
				v_this[0] = a[0] * v_this[1];
				v_this[2] = b[0] * v_this[1];
			}
			else if (normal[2] != 0) {
				a[0] = normal[0] / normal[2];
				a[1] = a[0] * a[0];
				b[0] = normal[1] / normal[2];
				b[1] = b[0] * b[0];

				v_this[2] = (vel[0] + vel[0] * a[0] + vel[1] * b[0]);
				v_this[2] /= 1 + a[1] + b[1];
				v_this[0] = a[0] * v_this[2];
				v_this[1] = b[0] * v_this[2];
			}
			else {
				return false;
			}

			for (int i = 0; i < 3; i++)
				this->vel[i] -= v_this[i];

			float t = (2 * r) - dis;
			t /= 2 * r * normalSize;
			for (int i = 0; i < 3; i++)
				this->loc[i] += normal[i] * t * 1.01;

			return true;
		}
	}
	return false;
}
bool particle::viscosity(float s, float vis, float time, particle* p) {
	float dis = this->distance(p);
	float normal[3], a, t;
	if (p->getId() != -1) {
		if (dis < 2 * vis && dis > dis > 2 * s) {
			a = dis / (2 * vis);
			a = GRAVITY_ACC / a;

			t = 0;
			for (int i = 0; i < 3; i++) {
				normal[i] = p->loc[i] - this->loc[i];
				t += normal[i] * normal[i];
			}
			t = sqrt(t);
			for (int i = 0; i < 3; i++) {
				normal[i] /= t;
				this->vel[i] += normal[i] * a * time;
				p->vel[i] -= normal[i] * a * time;
			}
			return true;
		}
	}
	else {

	}

	return false;
}

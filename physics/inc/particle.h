#pragma once
#include <math.h>

#define GRAVITY_ACC 9.80665


class particle {
private:
	int id;
	float loc[3];
	float vel[3];
	float density;
	float pressure;
	float vis;
	particle* pre;
	particle* next;
	particle* outputPre;
	particle* outputNext;

public:
	particle();
	particle(int, float*, float*, float, float);
	~particle();

	void setId(int i) { id = i; }
	void setLoc(float x, float y, float z) { loc[0] = x; loc[1] = y; loc[2] = z; }
	void setLoc(float* l) { loc[0] = l[0]; loc[1] = l[1]; loc[2] = l[2]; }
	void setVel(float* v) { vel[0] = v[0]; vel[1] = v[1]; vel[2] = v[2]; }
	void setPre(particle* p) { pre = p; }
	void setNext(particle* p) { next = p; }
	void setOutputPre(particle* p) { outputPre = p; }
	void setOutputNext(particle* p) { outputNext = p; }

	int getId() { return id; }
	float getLoc(int i) { return loc[i]; }
	float getVel(int i) { return vel[i]; }
	particle* getPre() { return pre; }
	particle* getNext() { return next; }
	particle* getOutputPre() { return outputPre; }
	particle* getOutputNext() { return outputNext; }

	float distance(particle*);
	float velocity();
	unsigned char getOutputValue(float, float, float);

	void move(bool, float, int*);
	void addGravity(float);
	bool collisionP2P(float, particle*);
	bool viscosity(float, float, float, particle*);
};

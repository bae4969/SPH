#pragma once
#define DllExport __declspec(dllexport)

#include "particle.h"


class DllExport p_matrix {
private:
	bool box = false;
	int quality;
	int numThread;
	int numParticles;
	int matrixSize[3];
	int outputSize;
	float particleSize;
	float visualSize;
	float timeSpeed;
	unsigned char* output;
	unsigned char* terrOutput;
	particle*** matrix;

	int outputListNum;
	int* numOutputList;
	particle* outputList;
	particle** outputList_ptr;

	particle* terrList;
	particle* terrList_ptr;

public:
	p_matrix();
	~p_matrix();

	void setMatrix(int, int*, float, float, float);
	void setTerrain(int, int, float, float*);
	void setBox(bool b) { box = b; }
	void setQuality(int q) { if (q >= 1)quality = q; }
	void setOutput(int, particle*);
	void setTerrOutput(int, particle*);

	int getNumThread() { return numThread; }
	int getNumParticles() { return numParticles; }
	int getNumOutputLIst(int i) { return numOutputList[i]; }
	int getSizeMatXYZ(int, int, int);
	particle* getEndParticle(int, int, int);
	particle* getOutputList(int i) { return &outputList[i]; }
	particle* getTerrList() { return terrList; }
	int getOutputLoc(int, int, int);
	unsigned char* getOutput() { return output; }
	unsigned char* getTerrOutput() { return terrOutput; }

	void pop(particle*);
	bool pushback(particle*, int, int, int);

	void createNewParticle(float*, float*, float, float, bool);
	void matrixNextState(bool);
};
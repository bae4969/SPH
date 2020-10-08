#include "physics.h"


p_matrix::p_matrix() {
	numThread = 0;
	numParticles = 0;
	for (int i = 0; i < 3; i++)
		matrixSize[i] = 0;
	outputSize = 0;
	particleSize = 0;
	visualSize = 0;
	timeSpeed = 0;
	output = NULL;
	terrOutput = NULL;
	matrix = NULL;

	outputListNum = 0;
	numOutputList = NULL;
	outputList = NULL;
	outputList_ptr = NULL;
}
p_matrix::~p_matrix() {
	for (int x = 0; x < matrixSize[0]; x++) {
		for (int y = 0; y < matrixSize[1]; y++) {
			delete[] matrix[x][y];
		}
		delete[] matrix[x];
	}
	delete[] matrix;
	delete[] output;
	delete[] terrOutput;
	delete[] numOutputList;
	delete[] outputList;
	delete[] outputList_ptr;
}

void p_matrix::setMatrix(int thread, int* size, float ts, float r, float vs) {
	quality = 5;
	numThread = thread;
	numParticles = 0;
	for (int i = 0; i < 3; i++)
		matrixSize[i] = size[i];
	outputListNum = 0;
	particleSize = r;
	visualSize = vs;
	timeSpeed = ts;

	matrix = new particle * *[matrixSize[0]];
	for (int x = 0; x < matrixSize[0]; x++) {
		matrix[x] = new particle * [matrixSize[1]];
		for (int y = 0; y < matrixSize[1]; y++) {
			matrix[x][y] = new particle[matrixSize[2]]();
		}
	}

	numOutputList = new int[numThread];
	outputList = new particle[numThread]();
	outputList_ptr = new particle * [numThread];
	for (int i = 0; i < numThread; i++) {
		numOutputList[i] = 0;
		outputList_ptr[i] = &outputList[i];
	}

	terrList = new particle();
	terrList_ptr = terrList;

	outputSize = size[0] * size[1] * size[2] * 27;
	output = new unsigned char[outputSize];
	terrOutput = new unsigned char[outputSize];
	for (int i = 0; i < outputSize; i++) {
		output[i] = 0;
		terrOutput[i] = 0;
	}
}
void p_matrix::setTerrain(int x, int y, float z, float* nor) {
	int t = z;
	matrix[x][t][y].setId(-1);
	matrix[x][t][y].setLoc(x, z, y);
	matrix[x][t][y].setVel(nor);
}
void p_matrix::setOutput(int q, particle* p) {
	unsigned char value, temp;
	int outputIndex[4];
	outputIndex[0] = 3 * p->getLoc(0);
	outputIndex[1] = 3 * p->getLoc(1);
	outputIndex[2] = 3 * p->getLoc(2);
	for (int _x = outputIndex[0] - q; _x < outputIndex[0] + q; _x++) {
		if (!(_x >= 0 && _x < 3 * matrixSize[0])) continue;
		for (int _y = outputIndex[1] - q; _y < outputIndex[1] + q; _y++) {
			if (!(_y >= 0 && _y < 3 * matrixSize[1])) continue;
			for (int _z = outputIndex[2] - q; _z < outputIndex[2] + q; _z++) {
				if (!(_z >= 0 && _z < 3 * matrixSize[2])) continue;

				outputIndex[3] = getOutputLoc(_x, _y, _z);
				value = p->getOutputValue(_x / 3.0, _y / 3.0, _z / 3.0);
				temp = 255 - output[outputIndex[3]];
				if (value > temp)
					output[outputIndex[3]] = 255;
				else
					output[outputIndex[3]] += value;
			}
		}
	}
}
void p_matrix::setTerrOutput(int q, particle* p) {
	unsigned char value, temp;
	int outputIndex[4];
	outputIndex[0] = 3 * p->getLoc(0);
	outputIndex[1] = 3 * p->getLoc(1);
	outputIndex[2] = 3 * p->getLoc(2);
	for (int _x = outputIndex[0] - q; _x < outputIndex[0] + q; _x++) {
		if (!(_x >= 0 && _x < 3 * matrixSize[0])) continue;
		for (int _y = outputIndex[1] - q; _y < outputIndex[1] + q; _y++) {
			if (!(_y >= 0 && _y < 3 * matrixSize[1])) continue;
			for (int _z = outputIndex[2] - q; _z < outputIndex[2] + q; _z++) {
				if (!(_z >= 0 && _z < 3 * matrixSize[2])) continue;

				outputIndex[3] = getOutputLoc(_x, _y, _z);
				value = p->getOutputValue(_x / 3.0, _y / 3.0, _z / 3.0);
				temp = 255 - terrOutput[outputIndex[3]];
				if (value > temp)
					terrOutput[outputIndex[3]] = 255;
				else
					terrOutput[outputIndex[3]] += value;
			}
		}
	}
}

int p_matrix::getSizeMatXYZ(int x, int y, int z) {
	int result = 0;
	particle* p_ptr = matrix[x][y][z].getNext();

	if (p_ptr == NULL)
		return result;

	while (p_ptr != NULL) {
		p_ptr = p_ptr->getNext();
		result++;
	}

	return result;
}
particle* p_matrix::getEndParticle(int x, int y, int z) {
	particle* temp = matrix[x][y][z].getNext();
	if (temp == NULL)
		return &matrix[x][y][z];

	while (temp->getNext() != NULL)
		temp = temp->getNext();
	return temp;
}
int p_matrix::getOutputLoc(int x, int y, int z) {
	return (9 * matrixSize[0] * matrixSize[1] * z) + (3 * matrixSize[0] * y) + x;
}

void p_matrix::pop(particle* p) {
	particle* pre, * next;
	pre = p->getPre();
	next = p->getNext();
	p->setPre(NULL);
	p->setNext(NULL);

	if (next == NULL) {
		pre->setNext(NULL);
	}
	else {
		next->setPre(pre);
		pre->setNext(next);
	}
}
bool p_matrix::pushback(particle* p, int x, int y, int z) {
	if (p->getId() == -1) {
		if (x < 0 || x >= matrixSize[0]
			|| y < 0 || y >= matrixSize[1]
			|| z < 0 || z >= matrixSize[2]) {
			int index;
			particle* pre, * next;
			pre = p->getOutputPre();
			next = p->getOutputNext();
			terrList_ptr = pre;

			if (next == NULL)
				pre->setOutputNext(NULL);
			else {
				pre->setOutputNext(next);
				next->setOutputPre(pre);
			}

			delete p;
			return false;
		}
		else {
			particle* index_particle = getEndParticle(x, y, z);
			index_particle->setNext(p);
			p->setPre(index_particle);

			return true;
		}
	}
	else {
		if (x < 0 || x >= matrixSize[0]
			|| y < 0 || y >= matrixSize[1]
			|| z < 0 || z >= matrixSize[2]) {
			int index;
			particle* pre, * next;
			pre = p->getOutputPre();
			next = p->getOutputNext();
			if (next == NULL)
				pre->setOutputNext(NULL);
			else {
				pre->setOutputNext(next);
				next->setOutputPre(pre);
			}

			index = (p->getId() - 1) % 6;
			numOutputList[index]--;

			delete p;
			return false;
		}
		else {
			particle* index_particle = getEndParticle(x, y, z);
			index_particle->setNext(p);
			p->setPre(index_particle);

			return true;
		}
	}
}

void p_matrix::createNewParticle(float* l, float* v, float d, float vis, bool par) {
	if (par) {
		particle* p = new particle(++numParticles, l, v, d, vis);
		outputList_ptr[outputListNum]->setOutputNext(p);
		p->setOutputPre(outputList_ptr[outputListNum]);
		outputList_ptr[outputListNum] = p;
		numOutputList[outputListNum]++;
		outputListNum++;
		if (outputListNum == numThread)
			outputListNum = 0;

		int index[3];
		index[0] = p->getLoc(0);
		index[1] = p->getLoc(1);
		index[2] = p->getLoc(2);

		pushback(p, index[0], index[1], index[2]);
	}
	else {
		particle* p = new particle(-1, l, v, d, vis);
		terrList_ptr->setOutputNext(p);
		p->setOutputPre(terrList_ptr);
		terrList_ptr = p;
		int index[3];
		index[0] = p->getLoc(0);
		index[1] = p->getLoc(1);
		index[2] = p->getLoc(2);
		pushback(p, index[0], index[1], index[2]);
		setTerrOutput(quality, p);
	}
}
void p_matrix::matrixNextState(bool type) {
	int index[3];
	float loc[3];
	particle* p, * _p;

	//output reset
	if (type) {
		for (int i = 0; i < outputSize; i++)
			output[i] = 0;
	}

	//gravity
	for (int x = 0; x < matrixSize[0]; x++) {
		for (int y = 0; y < matrixSize[1]; y++) {
			for (int z = 0; z < matrixSize[2]; z++) {
				p = matrix[x][y][z].getNext();
				while (p != NULL) {
					if (p->getId() != -1)
						p->addGravity(timeSpeed);
					p = p->getNext();
				}
			}
		}
	}

	/*//vis
	for (int x = 0; x < matrixSize[0]; x++) {
		for (int y = 0; y < matrixSize[1]; y++) {
			for (int z = 0; z < matrixSize[2]; z++) {
				p = matrix[x][y][z].getNext();
				while (p != NULL) {
					if (p->getId() != -1)
						for (int _x = x - 2; _x < x + 2; _x++) {
							if (!(_x >= 0 && _x < matrixSize[0])) continue;
							for (int _y = y - 2; _y < y + 2; _y++) {
								if (!(_y >= 0 && _y < matrixSize[1])) continue;
								for (int _z = z - 2; _z < z + 2; _z++) {
									if (!(_z >= 0 && _z < matrixSize[2])) continue;

									if (x == _x && y == _y && z == _z)
										_p = p->getNext();
									else
										_p = matrix[_x][_y][_z].getNext();
									while (_p != NULL) {
										p->viscosity(particleSize, visualSize, timeSpeed, _p);
										_p = _p->getNext();
									}
								}
							}
						}

					p = p->getNext();
				}
			}
		}
	}
	*/

	//collision
	for (int x = 0; x < matrixSize[0]; x++) {
		for (int y = 0; y < matrixSize[1]; y++) {
			for (int z = 0; z < matrixSize[2]; z++) {
				p = matrix[x][y][z].getNext();
				while (p != NULL) {
					if (p->getId() != -1)
						for (int _x = x - 1; _x < x + 1; _x++) {
							if (!(_x >= 0 && _x < matrixSize[0])) continue;
							for (int _y = y - 1; _y < y + 1; _y++) {
								if (!(_y >= 0 && _y < matrixSize[1])) continue;
								for (int _z = z - 1; _z < z + 1; _z++) {
									if (!(_z >= 0 && _z < matrixSize[2])) continue;

									if (x == _x && y == _y && z == _z)
										_p = p->getNext();
									else
										_p = matrix[_x][_y][_z].getNext();
									while (_p != NULL) {
										p->collisionP2P(particleSize, _p);
										_p = _p->getNext();
									}
								}
							}
						}

					p = p->getNext();
				}
			}
		}
	}

	//move
	for (int x = 0; x < matrixSize[0]; x++) {
		for (int y = 0; y < matrixSize[1]; y++) {
			for (int z = 0; z < matrixSize[2]; z++) {
				p = matrix[x][y][z].getNext();
				while (p != NULL) {
					if (p->getId() != -1) {
						p->move(box, timeSpeed, matrixSize);
						if (type)
							setOutput(quality, p);
					}
					p = p->getNext();
				}
			}
		}
	}

	//reallocate
	for (int x = 0; x < matrixSize[0]; x++) {
		for (int y = 0; y < matrixSize[1]; y++) {
			for (int z = 0; z < matrixSize[2]; z++) {
				p = matrix[x][y][z].getNext();
				while (p != NULL) {
					_p = p->getNext();
					if (p->getId() != -1) {
						for (int i = 0; i < 3; i++)
							index[i] = p->getLoc(i);
						if (index[0] != x || index[1] != y || index[2] != z) {
							pop(p);
							pushback(p, index[0], index[1], index[2]);
						}
					}
					p = _p;
				}
			}
		}
	}
}

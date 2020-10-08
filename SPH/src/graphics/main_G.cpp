// You can change shading method.
//////////////////////////////////////////////////
//			#define SPHERE_SHADING				//
			#define VOLUME_SHADING				//
//////////////////////////////////////////////////

#include "graphics/main_G.h"
#include "graphics/terrain.h"
#include "graphics/bmploader.h"

//////////////////////////////////////////////////
//				Graphics Variable				//
//////////////////////////////////////////////////

#ifdef SPHERE_SHADING

bool pause = false;
float zoom = 1;
float degree[3] = { 0,0,0 };
float camLocForm[3] = { 0,0,40 };
float camLocForm_init[3] = { 0,0,40 };
float camUp[3] = { 0,1,0 };
float camUp_init[3] = { 0,1,0 };

GLuint camLocUni;
GLfloat** locationInfo;

#endif

#ifdef VOLUME_SHADING

bool pause = false;
float terr = 1;
float zoom = 2;
float degree[3] = { 0,0,0 };
float camLocForm[3] = { 0,0,5 };
float camLocForm_init[3] = { 0,0,5 };
float camUp[3] = { 0,1,0 };
float camUp_init[3] = { 0,1,0 };

GLuint camLocUni, terrUni;
GLfloat** locationInfo;
unsigned char* terrData;

#endif

//				Terrain Variable				//

float terrainOriginSize[3] = { 40,20,5 };
float terrainScale = 1;
float terrainTransMat[16] = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	-terrainOriginSize[0] / 2,
	-terrainOriginSize[2] * 3,
	-terrainOriginSize[1] / 2,
	1
};
float colorV = 1;
GLuint terrainSp;
GLuint terrainVAO, terrainVBO, terrainEBO;
GLuint terAtt, sizeUni, colorUni, terrTex;

//				 Sphere Variable				//

GLuint particleSp;
GLuint VAO, VBO, EBO;
GLuint verAtt, tranUni;
GLfloat sphereCoor[1080];

//////////////////////////////////////////////////
//				Physics Variable				//
//////////////////////////////////////////////////

int qua = 5;
int numThread = 1;
int matrixSize[3] = { terrainOriginSize[0], 6 * terrainOriginSize[2], terrainOriginSize[1] + 1 };
float timeSpeed = 0.0004;
float density = 1;
float particleRadian = 0.5;
float visualSize = 1.0;
p_matrix pm;

int volSize[3] = { matrixSize[0], matrixSize[2], matrixSize[1] };
GLuint matrixSp;
GLuint matrixTex;
GLuint eyePosUni, texUni, matMinUni, matMaxUni, eyeUpUni, transMatUni;

////////////////////////////////////////////////////
//					Test Variable				  //
////////////////////////////////////////////////////

bool terrVai = true;
bool go = true;
int count = 0;
int numLayer = 7;
int numLine = 5;
float*** parLoc, *** parVel;

void test_init()
{
	parLoc = new float** [numLayer];
	parVel = new float** [numLayer];
	for (int i = 0; i < numLayer; i++) {
		parLoc[i] = new float* [5];
		parVel[i] = new float* [5];
		for (int j = 0; j < numLine; j++) {
			parLoc[i][j] = new float[3];
			parVel[i][j] = new float[3];
			parLoc[i][j][0] = 1;
			parLoc[i][j][1] = 20 + i;
			parLoc[i][j][2] = 7 + j;
			parVel[i][j][0] = 3;
			parVel[i][j][1] = 0;
			parVel[i][j][2] = 0;
		}
	}
}

void sphere_init()
{
	particleSp = createGLSLProgram((char*)"shader/vert/particle.vert", NULL, (char*)"shader/frag/particle.frag");
	verAtt = glGetAttribLocation(particleSp, "verAtt");
	tranUni = glGetUniformLocation(particleSp, "tranUni");
	camLocUni = glGetUniformLocation(particleSp, "camLocUni");

	//float r = particleRadian;
	float r = visualSize;
	float r30 = r * sin(PI / 6);
	float r60 = r * sin(PI / 3);
	for (int i = 0; i < 12; i++) {
		sphereCoor[18 * i] = 0;
		sphereCoor[18 * i + 1] = r;
		sphereCoor[18 * i + 2] = 0;
		sphereCoor[18 * i + 3] = r30 * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 4] = r60;
		sphereCoor[18 * i + 5] = r30 * sin(PI / 6 * (i + 1));
		sphereCoor[18 * i + 6] = r30 * cos(PI / 6 * i);
		sphereCoor[18 * i + 7] = r60;
		sphereCoor[18 * i + 8] = r30 * sin(PI / 6 * i);

		sphereCoor[18 * i + 9] = 0;
		sphereCoor[18 * i + 10] = -r;
		sphereCoor[18 * i + 11] = 0;
		sphereCoor[18 * i + 12] = r30 * cos(PI / 6 * i);
		sphereCoor[18 * i + 13] = -r60;
		sphereCoor[18 * i + 14] = r30 * sin(PI / 6 * i);
		sphereCoor[18 * i + 15] = r30 * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 16] = -r60;
		sphereCoor[18 * i + 17] = r30 * sin(PI / 6 * (i + 1));
	}
	for (int i = 12; i < 24; i++) {
		sphereCoor[18 * i] = r * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 1] = 0;
		sphereCoor[18 * i + 2] = r * sin(PI / 6 * (i + 1));
		sphereCoor[18 * i + 3] = r * cos(PI / 6 * i);
		sphereCoor[18 * i + 4] = 0;
		sphereCoor[18 * i + 5] = r * sin(PI / 6 * i);
		sphereCoor[18 * i + 6] = r60 * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 7] = r30;
		sphereCoor[18 * i + 8] = r60 * sin(PI / 6 * (i + 1));

		sphereCoor[18 * i + 9] = r * cos(PI / 6 * i);
		sphereCoor[18 * i + 10] = 0;
		sphereCoor[18 * i + 11] = r * sin(PI / 6 * i);
		sphereCoor[18 * i + 12] = r * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 13] = 0;
		sphereCoor[18 * i + 14] = r * sin(PI / 6 * (i + 1));
		sphereCoor[18 * i + 15] = r60 * cos(PI / 6 * i);
		sphereCoor[18 * i + 16] = -r30;
		sphereCoor[18 * i + 17] = r60 * sin(PI / 6 * i);
	}
	for (int i = 24; i < 36; i++) {
		sphereCoor[18 * i] = r60 * cos(PI / 6 * i);
		sphereCoor[18 * i + 1] = r30;
		sphereCoor[18 * i + 2] = r60 * sin(PI / 6 * i);
		sphereCoor[18 * i + 3] = r60 * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 4] = r30;
		sphereCoor[18 * i + 5] = r60 * sin(PI / 6 * (i + 1));
		sphereCoor[18 * i + 6] = r * cos(PI / 6 * i);
		sphereCoor[18 * i + 7] = 0;
		sphereCoor[18 * i + 8] = r * sin(PI / 6 * i);

		sphereCoor[18 * i + 9] = r60 * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 10] = -r30;
		sphereCoor[18 * i + 11] = r60 * sin(PI / 6 * (i + 1));
		sphereCoor[18 * i + 12] = r60 * cos(PI / 6 * i);
		sphereCoor[18 * i + 13] = -r30;
		sphereCoor[18 * i + 14] = r60 * sin(PI / 6 * i);
		sphereCoor[18 * i + 15] = r * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 16] = 0;
		sphereCoor[18 * i + 17] = r * sin(PI / 6 * (i + 1));
	}
	for (int i = 36; i < 48; i++) {
		sphereCoor[18 * i] = r30 * cos(PI / 6 * i);
		sphereCoor[18 * i + 1] = r60;
		sphereCoor[18 * i + 2] = r30 * sin(PI / 6 * i);
		sphereCoor[18 * i + 3] = r30 * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 4] = r60;
		sphereCoor[18 * i + 5] = r30 * sin(PI / 6 * (i + 1));
		sphereCoor[18 * i + 6] = r60 * cos(PI / 6 * i);
		sphereCoor[18 * i + 7] = r30;
		sphereCoor[18 * i + 8] = r60 * sin(PI / 6 * i);

		sphereCoor[18 * i + 9] = r30 * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 10] = -r60;
		sphereCoor[18 * i + 11] = r30 * sin(PI / 6 * (i + 1));
		sphereCoor[18 * i + 12] = r30 * cos(PI / 6 * i);
		sphereCoor[18 * i + 13] = -r60;
		sphereCoor[18 * i + 14] = r30 * sin(PI / 6 * i);
		sphereCoor[18 * i + 15] = r60 * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 16] = -r30;
		sphereCoor[18 * i + 17] = r60 * sin(PI / 6 * (i + 1));
	}
	for (int i = 48; i < 60; i++) {
		sphereCoor[18 * i] = r60 * cos(PI / 6 * i);
		sphereCoor[18 * i + 1] = r30;
		sphereCoor[18 * i + 2] = r60 * sin(PI / 6 * i);
		sphereCoor[18 * i + 3] = r60 * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 4] = r30;
		sphereCoor[18 * i + 5] = r60 * sin(PI / 6 * (i + 1));
		sphereCoor[18 * i + 6] = r30 * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 7] = r60;
		sphereCoor[18 * i + 8] = r30 * sin(PI / 6 * (i + 1));

		sphereCoor[18 * i + 9] = r60 * cos(PI / 6 * (i + 1));
		sphereCoor[18 * i + 10] = -r30;
		sphereCoor[18 * i + 11] = r60 * sin(PI / 6 * (i + 1));
		sphereCoor[18 * i + 12] = r60 * cos(PI / 6 * i);
		sphereCoor[18 * i + 13] = -r30;
		sphereCoor[18 * i + 14] = r60 * sin(PI / 6 * i);
		sphereCoor[18 * i + 15] = r30 * cos(PI / 6 * i);
		sphereCoor[18 * i + 16] = -r60;
		sphereCoor[18 * i + 17] = r30 * sin(PI / 6 * i);
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphereCoor), sphereCoor, GL_STATIC_DRAW);
	glVertexAttribPointer(verAtt, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(verAtt);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void terrain_init()
{
	terrainSp = createGLSLProgram((char*)"shader/vert/terrain.vert", NULL, (char*)"shader/frag/terrain.frag");
	terAtt = glGetAttribLocation(terrainSp, "terAtt");
	colorUni = glGetUniformLocation(terrainSp, "colorUni");
	sizeUni = glGetUniformLocation(terrainSp, "sizeUni");

	setForGraphic(terrainScale);
	setNormal();

	glGenVertexArrays(1, &terrainVAO);
	glBindVertexArray(terrainVAO);

	glGenBuffers(1, &terrainVBO);
	glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(forGraphicPart), forGraphicPart, GL_STATIC_DRAW);
	glVertexAttribPointer(terAtt, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(terAtt);
	glGenBuffers(1, &terrainEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	int width, height;
	uchar4* dst;
	LoadBMPFile(&dst, &width, &height, "res/terrTex.bmp");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &terrTex);
	glBindTexture(GL_TEXTURE_2D, terrTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
	glUniform1i(glGetUniformLocation(terrainSp, "terrTex"), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void matrix_init()
{
	float z;
	float l[2];
	float loc[3];
	float vel[3];
	vec3_* PDD;
	vec3_ norDD[2];

	pm.setMatrix(numThread, matrixSize, timeSpeed, particleRadian, visualSize);

	for (int i = 0; i < NUMTRIANGLE - 7; i++) {
		PDD = tri2PDD(i);
		norDD[0] = normalize(PDD[1]);
		norDD[1] = normalize(PDD[2]);
		l[0] = length(PDD[1]);
		l[1] = length(PDD[2]);
		for (float j = 0.4; j < l[1]; j += 0.5) {
			for (float k = 0.4; k < l[0]; k += 0.5) {
				if (j / l[1] + k / l[0] <= 1.0) {
					loc[0] = PDD[0].x + (norDD[0].x * k) + (norDD[1].x * j);
					loc[1] = PDD[0].z + (norDD[0].z * k) + (norDD[1].z * j);
					loc[2] = PDD[0].y + (norDD[0].y * k) + (norDD[1].y * j);
					vel[0] = normal[3 * i];
					vel[1] = normal[3 * i + 2];
					vel[2] = normal[3 * i + 1];
					pm.createNewParticle(loc, vel, density, 1, false);
				}
				else
					break;
			}
		}
		delete[] PDD;
	}

#ifdef VOLUME_SHADING

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	unsigned char* data;
	data = pm.getOutput();
	terrData = pm.getTerrOutput();

	matrixSp = createGLSLProgram((char*)"shader/vert/matrix.vert", NULL, (char*)"shader/frag/matrix.frag");

	glGenTextures(1, &matrixTex);
	glBindTexture(GL_TEXTURE_3D, matrixTex);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, matrixSize[0] * 3, matrixSize[1] * 3, matrixSize[2] * 3, 0, GL_RED, GL_UNSIGNED_BYTE, data);

	eyePosUni = glGetUniformLocation(matrixSp, "eyePos");
	texUni = glGetUniformLocation(matrixSp, "tex");
	matMinUni = glGetUniformLocation(matrixSp, "matMin");
	matMaxUni = glGetUniformLocation(matrixSp, "matMax");
	eyeUpUni = glGetUniformLocation(matrixSp, "eyeUp");
	terrUni = glGetUniformLocation(matrixSp, "terrUni");

#endif
}

void init(void) 
{
	std::cout << "Initilizing glew ...";
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	srand(time(0));
	std::cout << " Done!\n";

	std::cout << "Initilizing Test Set ...";
	test_init();
	std::cout << " Done!\n";

#ifdef SPHERE_SHADING
	std::cout << "Initilizing Sphere ...";
	sphere_init();
	std::cout << " Done!\n";
#endif

	std::cout << "Initilizing Terrain ...";
	terrain_init();
	std::cout << " Done!\n";

	std::cout << "Initilizing Data Matrix ...";
	matrix_init();
	std::cout << " Done!\n";
}

void idle()
{
	glutPostRedisplay();
}

void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef SPHERE_SHADING

	glLoadIdentity();
	gluLookAt(
		camLocForm[0], camLocForm[1], camLocForm[2],
		0, 0, 0,
		camUp[0], camUp[1], camUp[2]);

	if (terrVai) {
		glUseProgram(terrainSp);
		glBindVertexArray(terrainVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
		glBindTexture(GL_TEXTURE_2D, terrTex);
		glUniform1f(colorUni, colorV);
		glUniformMatrix4fv(sizeUni, 1, GL_FALSE, terrainTransMat);
		glDrawElements(GL_TRIANGLES, NUMTRIANGLE * 3, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	glUseProgram(particleSp);
	glUniform3fv(camLocUni, 1, camLocForm);

	for (int i = 0; i < numThread; i++) {
		GLfloat tranMat[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
		particle* particle_ptr = pm.getOutputList(i);
		while (particle_ptr->getOutputNext() != NULL) {
			particle_ptr = particle_ptr->getOutputNext();
			for (int i = 0; i < 3; i++)
				tranMat[i + 12] = particle_ptr->getLoc(i) - matrixSize[i] / 2;
			glBindVertexArray(VAO);
			glUniformMatrix4fv(tranUni, 1, GL_FALSE, tranMat);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glDrawArrays(GL_TRIANGLES, 0, 360);
		}
	}

	if (!pause)
		pm.matrixNextState(0);

#endif

#ifdef VOLUME_SHADING

	glUseProgram(matrixSp);
	unsigned char* data;
	data = pm.getOutput();

	glBindTexture(GL_TEXTURE_3D, matrixTex);
	glUniform3fv(eyePosUni, 1, camLocForm);
	float temp = sqrt(matrixSize[0] * matrixSize[0] + matrixSize[1] * matrixSize[1] + matrixSize[2] * matrixSize[2]);
	float objectMin[3] = { -matrixSize[0] / temp * zoom, -matrixSize[1] / temp * zoom, -matrixSize[2] / temp * zoom };
	float objectMax[3] = { matrixSize[0] / temp * zoom, matrixSize[1] / temp * zoom, matrixSize[2] / temp * zoom };
	glUniform3fv(matMinUni, 1, objectMin);
	glUniform3fv(matMaxUni, 1, objectMax);
	glUniform3fv(eyeUpUni, 1, camUp);

	terr = -1;
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, matrixSize[0] * 3, matrixSize[1] * 3, matrixSize[2] * 3, 0, GL_RED, GL_UNSIGNED_BYTE, data);
	glUniform1f(terrUni, terr);

	glBegin(GL_QUADS);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glEnd();


	terr = 1;
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, matrixSize[0] * 3, matrixSize[1] * 3, matrixSize[2] * 3, 0, GL_RED, GL_UNSIGNED_BYTE, terrData);
	glUniform1f(terrUni, terr);

	glBegin(GL_QUADS);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glEnd();

	if (!pause)
		pm.matrixNextState(1);

#endif

	if (go && !pause) {
		count++;
		if (count > 3 / timeSpeed / 10) {
			count = 0;

			float ran;
			ran = sin(rand());

			for (int i = 0; i < numLayer; i++) {
				for (int j = 0; j < numLine; j++) {
					for (int k = 0; k < 3; k++)
						parVel[i][j][k] = 0.3 * ran;
					parLoc[i][j][0] = 1 + 0.1 * abs(sin(rand()));
					parVel[i][j][0] += 3;
					pm.createNewParticle(parLoc[i][j], parVel[i][j], density, 1, true);
				}
			}
		}
	}

	glutSwapBuffers();
}

void reshape(int w, int h) 
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 's':
	case 'S':
		degree[0] += 5;
		if (degree[0] > 360) { degree[0] -= 360; }
		break;
	case 'w':
	case 'W':
		degree[0] -= 5;
		if (degree[0] < 0) { degree[0] += 360; }
		break;
	case 'd':
	case 'D':
		degree[1] += 5;
		if (degree[1] > 360) { degree[1] -= 360; }
		break;
	case 'a':
	case 'A':
		degree[1] -= 5;
		if (degree[1] < 0) { degree[1] += 360; }
		break;
	case 'q':
	case 'Q':
		degree[2] += 5;
		if (degree[2] > 360) { degree[2] -= 360; }
		break;
	case 'e':
	case 'E':
		degree[2] -= 5;
		if (degree[2] < 0) { degree[2] += 360; }
		break;
	case 'z':
	case 'Z':
		zoom *= 1.5;
		break;
	case 'c':
	case 'C':
		zoom *= 0.666667;
		break;
	case 'p':
	case 'P':
		pause = !pause;
		break;
	case 'o':
	case 'O':
		go = !go;
		break;
	case 'n':
	case 'N':
		std::cout << "Num of Particles : " << pm.getNumParticles() << std::endl;
		break;
	case 'T':
	case 't':
		terrVai = !terrVai;
		break;
	case 'X':
	case 'x':
		colorV = -colorV;
		break;
	case '<':
	case ',':
		if (qua > 1) {
			std::cout << --qua << std::endl;
			pm.setQuality(qua);
		}
		break;
	case '>':
	case '.':
		std::cout << ++qua << std::endl;
		pm.setQuality(qua);
		break;
	}

	float _sin[3], _cos[3], tempLoc[2][3], tempUp[2][3];
	for (int i = 0; i < 3; i++) {
		if (i != 2) {
			_sin[i] = sin(-degree[i] * PI / 180);
			_cos[i] = cos(-degree[i] * PI / 180);
		}
		else {
			_sin[i] = sin(degree[i] * PI / 180);
			_cos[i] = cos(degree[i] * PI / 180);
		}
	}
	float Rx[3][3] = {
		1, 0, 0,
		0, _cos[0], -_sin[0],
		0, _sin[0], _cos[0]
	};
	float Ry[3][3] = {
		_cos[1], 0, _sin[1],
		0, 1, 0,
		-_sin[1], 0, _cos[1]
	};
	float Rz[3][3] = {
		_cos[2], -_sin[2], 0,
		_sin[2], _cos[2], 0,
		0, 0, 1
	};
	for (int i = 0; i < 3; i++) {
		tempLoc[0][i] = 0;
		tempUp[0][i] = 0;
		for (int j = 0; j < 3; j++) {
			tempLoc[0][i] += Rx[i][j] * camLocForm_init[j];
			tempUp[0][i] += Rx[i][j] * camUp_init[j];
		}
	}
	for (int i = 0; i < 3; i++) {
		tempLoc[1][i] = 0;
		tempUp[1][i] = 0;
		for (int j = 0; j < 3; j++) {
			tempLoc[1][i] += Ry[i][j] * tempLoc[0][j];
			tempUp[1][i] += Ry[i][j] * tempUp[0][j];
		}
	}
	for (int i = 0; i < 3; i++) {
		camLocForm[i] = 0;
		camUp[i] = 0;
		for (int j = 0; j < 3; j++) {
			camLocForm[i] += Rz[i][j] * tempLoc[1][j];
			camUp[i] += Rz[i][j] * tempUp[1][j];
		}
	}

#ifdef SPHERE_SHADING

	for (int i = 0; i < 3; i++)
		camLocForm[i] *= zoom;

#endif
}

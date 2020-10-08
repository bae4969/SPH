#pragma once

#include <stdio.h>
#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <GL/glut.h>
#include "graphics/textfile.h"
#include "physics.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define PI 3.141592653589793238


void test_init();
void matrix_init();
void terrain_init();
void sphere_init();

void init(void);
void idle();
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);
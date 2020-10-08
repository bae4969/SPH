#pragma once

char* textFileRead(char* fn);
int textFileWrite(char* fn, char* s);
GLuint createGLSLProgram(char* vs = NULL, char* gs = NULL, char* fs = NULL);
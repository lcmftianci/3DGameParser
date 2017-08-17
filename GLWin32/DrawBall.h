#pragma once
// Windows Header Files
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>

#include <GL/glut.h>

#define pi 3.1415926
#define SOLID 3000
#define WIRE  3001

typedef int SPHERE_MODE;

typedef struct Point3f
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}point;

void init(void);
void reshape(int w, int h);
void display(void);
int getPoint(GLfloat radius, GLfloat a, GLfloat b, point &p);
void drawSlice(point &p1, point &p2, point &p3, point &p4, SPHERE_MODE mode);
point* getPointMatrix(GLfloat radius, GLint slices);
int drawSphere(GLfloat radius, GLint slices, SPHERE_MODE mode);
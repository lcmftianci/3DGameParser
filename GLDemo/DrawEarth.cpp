#include <windows.h>  
#include <gl/GL.h>  
#include <gl/glu.h>  
#include <gl/glut.h>  
#include <cstdlib>  
#include <gl/GLAUX.h>
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib") //解决glaux.lib(tk.obj) : error LNK2019: 无法解析的外部符号 _sscanf，该符号在函数 _GetRegistrySysColors@8 中被
GLuint mytexture = 0;
GLUquadricObj* qobj;
const GLfloat lightPosition[] = { 10.0, 10.0, 10.0, 0.0 };
const GLfloat whiteLight[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat matSpecular[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat matShininess[] = { 20.0 };
GLfloat matEmission[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat spin = 0;
void drawfloor();

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();;
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

	gluQuadricTexture(qobj, GL_TRUE);//纹理函数
	glRotatef(spin, 0.0, 0.0, 1.0);
	gluSphere(qobj, 0.75f, 60, 60);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	//glutSolidSphere(3.0, 16, 16);
	//glFlush();
}
void init()
{
	glClearColor(0.3, 0.3, 0.3, 1.0);
	glClearDepth(1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);


	glEnable(GL_TEXTURE_2D);
	auto pimage = auxDIBImageLoad(TEXT("ppcover.BMP"));
	int weight = pimage->sizeX;
	int height = pimage->sizeY;
	//获得一个纹理对象
	glGenTextures(1, &mytexture);
	//将其绑定为2D纹理
	glBindTexture(GL_TEXTURE_2D, mytexture);
	//设置缩放器
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//为纹理指定图像数据
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, weight, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pimage->data);
	//生成一个球
	qobj = gluNewQuadric();
}
void myIdle()
{
	spin += 0.1;
	display();
}
void reshape(int w, int h)
{
	glViewport(0.0, 0.0, (GLsizei)w, (GLsizei)h);
}

void mouseFunc(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			matEmission[0] += 1.0;
			if (matEmission[0] > 1.0)
				matEmission[0] -= 1.1;
			break;
		case GLUT_MIDDLE_BUTTON:
			matEmission[1] += 1.0;
			if (matEmission[1] > 1.0)
				matEmission[1] -= 1.1;
			break;
		case GLUT_RIGHT_BUTTON:
			matEmission[2] += 1.0;
			if (matEmission[2] > 1.0)
				matEmission[2] -= 1.1;
			break;
		}
		glutPostRedisplay();
	}
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(450, 450);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("rotate sphere");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(myIdle);
	glutMouseFunc(mouseFunc);
	init();
	glutMainLoop();
	return EXIT_SUCCESS;
}
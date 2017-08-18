#pragma once
#include "DrawBall.h"

//#pragma comment(lib,"libSOIL.a")

GLuint texture_earth;
GLUquadricObj *quadPlanet;


int g_mateial;			//绘制图片的材质
//键盘事件
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		//drawSphere(200, 20, WIRE);
		g_mateial = 0;
		break;
	case 'l':
		g_mateial = 1;
		//drawSphere(200, 20, SOLID);
		break;
	case 'y':
		exit(0);
		break;
	default:
		break;
	}
}
//主函数
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	g_mateial = 0;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ball");
	LoadGLTextures("NinjaComp.BMP");
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}

//加载普通图片
void LoadGLTextures(CString path)
{
	glGenTextures(1, &g_textures);
	CImage img;
	img.Load(path); //  通过图片文件名字来加在
	int width = img.GetWidth();
	int height = img.GetHeight();
	unsigned char *pData = NULL;
	if (img.GetPitch() < 0) //GetBits的作用就是获得纹理的位信息缓冲区指针，如果位图是从下到上， 则指向缓冲区末端，否则指向缓冲区首端。而img.GetPitch 就是起这个判断作用，小于 0 指向末端
		pixeldata = (unsigned char *)img.GetBits() + (img.GetPitch()*(img.GetHeight() - 1));
	else
		pixeldata = (unsigned char *)img.GetBits();
	glBindTexture(GL_TEXTURE_2D, g_textures);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
}

//初始化渲染机制
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1);
	glShadeModel(GL_SMOOTH);
	GLfloat _ambient[] = { 1.0,1.0,1.0,1.0 };
	GLfloat _diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat _specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat _position[] = { 200,200,200,0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, _ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, _diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, _specular);
	glLightfv(GL_LIGHT0, GL_POSITION, _position);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//int earthHeight, earthWidth;
	//unsigned char *earth = SOIL_load_image("../images/earth.jpg", &earthWidth, &earthHeight, 0, SOIL_LOAD_RGB);
	//glGenTextures(1, &texture_earth);
	//glBindTexture(GL_TEXTURE_2D, texture_earth);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, earthWidth, earthHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, earth);
	//SOIL_free_image_data(earth);*/
	quadPlanet = gluNewQuadric();
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


//绘制
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 500, 0.0, 500, -500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static float rotate = 0;
static int times = 0;


//显示
void display(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslated(250, 250, 0);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//gluQuadricTexture(quadPlanet, GLU_TRUE);
	//glRotated(30, 1, 0, 0);
	//glRotated(60, 0, 1, 0);
	//glRotated(90, 0, 0, 1);
	times++;
	if (times > 100)
	{
		times = 0;
	}
	if (times % 100 == 0)
	{
		rotate += 0.3;
	}
	glRotated(rotate, 1, 0, 0);
	glRotated(rotate, 0, 1, 0);
	glRotated(rotate, 0, 0, 1);
	glColor3f(1.0, 1.0, 1.0);
	if(g_mateial == 0)
		drawSphere(200, 20, WIRE);
	else
		drawSphere(200, 20, SOLID);

	//绘制图片内容
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
	glFlush();
	glutSwapBuffers();
}

//获取点
int getPoint(GLfloat radius, GLfloat a, GLfloat b, point &p)
{
	p.x = radius*sin(a*pi / 180.0)*cos(b*pi / 180.0);
	p.y = radius*sin(a*pi / 180.0)*sin(b*pi / 180.0);
	p.z = radius*cos(a*pi / 180.0);
	return 1;
}

//绘制slice
void drawSlice(point &p1, point &p2, point &p3, point &p4, SPHERE_MODE mode)
{
	switch (mode)
	{
	case SOLID:
		glBegin(GL_QUADS);
		break;
	case WIRE:
		glBegin(GL_LINE_LOOP);
		break;
	}
	glColor3f(1, 0, 0);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glVertex3f(p3.x, p3.y, p3.z);
	glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
}

//计算点
point* getPointMatrix(GLfloat radius, GLint slices)
{
	int i, j, w = 2 * slices, h = slices;
	float a = 0.0, b = 0.0;
	float hStep = 180.0 / (h - 1);
	float wStep = 360.0 / w;
	int length = w*h;
	point *matrix;
	matrix = (point *)malloc(length * sizeof(point));
	if (!matrix)return NULL;
	for (a = 0.0, i = 0; i < h; i++, a += hStep)
		for (b = 0.0, j = 0; j < w; j++, b += wStep)
			getPoint(radius, a, b, matrix[i*w + j]);
	return matrix;
}

//绘制弧线
int drawSphere(GLfloat radius, GLint slices, SPHERE_MODE mode)
{
	int i = 0, j = 0, w = 2 * slices, h = slices;
	point *mx;
	mx = getPointMatrix(radius, slices);
	if (!mx)return 0;
	for (; i < h - 1; i++)
	{
		for (j = 0; j < w - 1; j++)
			drawSlice(mx[i*w + j], mx[i*w + j + 1], mx[(i + 1)*w + j + 1], mx[(i + 1)*w + j], mode);
		drawSlice(mx[i*w + j], mx[i*w], mx[(i + 1)*w], mx[(i + 1)*w + j], mode);
	}
	free(mx);
	return 1;
}
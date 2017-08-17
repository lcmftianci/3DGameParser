//#include <stdio.h>    
//#define GLUT_DISABLE_ATEXIT_HACK    
//#include <gl/glut.h>    
////#pragma comment(lib, "glut32.lib")    
//
//GLfloat AngleX;
//GLfloat AngleY;
//
//void display(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glPushMatrix();
//	{
//		glRotatef(AngleX, 1.0f, 0.0f, 0.0f);
//		glRotatef(AngleY, 0.0f, 1.0f, 0.0f);
//
//		glBegin(GL_POLYGON); //前表面    
//		glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);//颜色设置为白色    
//		glVertex3f(50.0f, 50.0f, 50.0f);
//
//		glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);//颜色设置为黄色    
//		glVertex3f(50.0f, -50.0f, 50.0f);
//
//		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);//颜色设置为红色    
//		glVertex3f(-50.0f, -50.0f, 50.0f);
//
//		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);//颜色设置为白色    
//		glVertex3f(-50.0f, 50.0f, 50.0f);
//		glEnd();
//
//		glBegin(GL_POLYGON); //后表面    
//		glColor3f(0.0f, 1.0f, 1.0f);//颜色设置为青色    
//		glVertex3f(50.0f, 50.0f, -50.0f);
//
//		glColor3f(0.0f, 1.0f, 0.0f);//颜色设置为绿色    
//		glVertex3f(50.0f, -50.0f, -50.0f);
//
//		glColor3f(0.0f, 0.0f, 0.0f);//颜色设置为黑色    
//		glVertex3f(-50.0f, -50.0f, -50.0f);
//
//		glColor3f(0.0f, 0.0f, 1.0f);//颜色设置为蓝色    
//		glVertex3f(-50.0f, 50.0f, -50.0f);
//		glEnd();
//
//		glBegin(GL_POLYGON); //上表面    
//		glColor3d(0.0, 1.0, 1.0);//颜色设置为青色    
//		glVertex3f(50.0f, 50.0f, -50.0f);
//
//		glColor3d(1.0, 1.0, 1.0);//颜色设置为白色    
//		glVertex3f(50.0f, 50.0f, 50.0f);
//
//		glColor3d(1.0, 0.0, 1.0);//颜色设置为品红色    
//		glVertex3f(-50.0f, 50.0f, 50.0f);
//
//		glColor3d(0.0, 0.0, 1.0);//颜色设置为蓝色    
//		glVertex3f(-50.0f, 50.0f, -50.0f);
//		glEnd();
//
//		glBegin(GL_POLYGON); //下表面    
//		glColor3ub(0u, 255u, 0u);//颜色设置为绿色    
//		glVertex3f(50.0f, -50.0f, -50.0f);
//
//		glColor3ub(255u, 255u, 0u);//颜色设置为黄色    
//		glVertex3f(50.0f, -50.0f, 50.0f);
//
//		glColor3ub(255u, 0u, 0u);//颜色设置为红色    
//		glVertex3f(-50.0f, -50.0f, 50.0f);
//
//		glColor3ub(0u, 0u, 0u);//颜色设置为黑色    
//		glVertex3f(-50.0f, -50.0f, -50.0f);
//		glEnd();
//
//		glBegin(GL_POLYGON); //左表面    
//		glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);//颜色设置为白色    
//		glVertex3f(50.0f, 50.0f, 50.0f);
//
//		glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)255);//颜色设置为青色    
//		glVertex3f(50.0f, 50.0f, -50.0f);
//
//		glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);//颜色设置为绿色    
//		glVertex3f(50.0f, -50.0f, -50.0f);
//
//		glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);//颜色设置为黄色    
//		glVertex3f(50.0f, -50.0f, 50.0f);
//		glEnd();
//
//		glBegin(GL_POLYGON); //右表面    
//		glColor3f(1.0f, 0.0f, 1.0f);//颜色设置为品红色    
//		glVertex3f(-50.0f, 50.0f, 50.0f);
//
//		glColor3f(0.0f, 0.0f, 1.0f);//颜色设置为蓝色    
//		glVertex3f(-50.0f, 50.0f, -50.0f);
//
//		glColor3f(0.0f, 0.0f, 0.0f);//颜色设置为黑色    
//		glVertex3f(-50.0f, -50.0f, -50.0f);
//
//		glColor3f(1.0f, 0.0f, 0.0f);//颜色设置为红色    
//		glVertex3f(-50.0f, -50.0f, 50.0f);
//		glEnd();
//	}
//	glPopMatrix();
//
//
//	glutSwapBuffers();
//}
//
//void reshape(int w, int h)
//{
//	GLfloat aspect = (GLfloat)w / (GLfloat)h;
//	GLfloat nRange = 100.0f;
//
//	glViewport(0, 0, w, h);
//
//	glMatrixMode(GL_PROJECTION); //将当前矩阵指定为投影模式    
//	glLoadIdentity();
//
//	//设置三维投影区    
//
//	if (w <= h)
//	{
//		glOrtho(-nRange, nRange, -nRange * aspect, nRange * aspect, -nRange, nRange);
//	}
//	else
//	{
//		glOrtho(-nRange, nRange, -nRange / aspect, nRange / aspect, -nRange, nRange);
//	}
//}
//
//void key_board(GLint key, GLint x, GLint y)
//{
//	if (key == GLUT_KEY_UP)
//	{
//		AngleX -= 5.0f;
//	}
//	if (key == GLUT_KEY_DOWN)
//	{
//		AngleX += 5.0f;
//	}
//	if (key == GLUT_KEY_LEFT)
//	{
//		AngleY -= 5.0f;
//	}
//	if (key == GLUT_KEY_RIGHT)
//	{
//		AngleY += 5.0f;
//	}
//	if (AngleX > 355.0f)
//	{
//		AngleX = 0.0f;
//	}
//	if (AngleX < 0.0f)
//	{
//		AngleX = 355.0f;
//	}
//	if (AngleY > 355.0f)
//		AngleY = 0.0f;
//
//	if (AngleY < 0.0f)
//	{
//		AngleY = 355.0f;
//	}
//	glutPostRedisplay();
//}
//
//void init()
//{
//	AngleX = 45.0f;
//	AngleY = 315.0f;
//
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_DITHER);
//	glShadeModel(GL_SMOOTH);
//}
//
//void main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(480, 480);
//	glutCreateWindow("OpenGL颜色立方体");
//
//	glutReshapeFunc(reshape);
//	glutDisplayFunc(display);
//	glutSpecialFunc(key_board); //设置处理特殊击键的回调函数    
//
//	init();
//
//	glutMainLoop();
//}
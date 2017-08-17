//#include <GLTools.h>	// OpenGL toolkit
//#include <GLMatrixStack.h>
//#include <GLFrame.h>
//#include <GLFrustum.h>
//#include <math.h>
//#include <GL/math3d.h>
//#include <GLGeometryTransform.h>
//#include <GLShaderManager.h>
//#include <GL/GL.h>
//#include<GL/glut.h>
//
//// 用线绘制立方体
//
//// 将立方体的八个顶点保存到一个数组里面 
//static const float vertex_list[][3] =
//{
//	-0.5f, -0.5f, -0.5f,
//	0.5f, -0.5f, -0.5f,
//	-0.5f, 0.5f, -0.5f,
//	0.5f, 0.5f, -0.5f,
//	-0.5f, -0.5f, 0.5f,
//	0.5f, -0.5f, 0.5f,
//	-0.5f, 0.5f, 0.5f,
//	0.5f, 0.5f, 0.5f,
//};
//
//// 将要使用的顶点的序号保存到一个数组里面 
//static const GLint index_list[][2] =
//{
//	{ 0, 1 },
//	{ 2, 3 },
//	{ 4, 5 },
//	{ 6, 7 },
//	{ 0, 2 },
//	{ 1, 3 },
//	{ 4, 6 },
//	{ 5, 7 },
//	{ 0, 4 },
//	{ 1, 5 },
//	{ 7, 3 },
//	{ 2, 6 }
//};
//
//const int n = 20;
//const GLfloat R = 0.5f;
//const GLfloat Pi = 3.14159265358979f;
//GLGeometryTransform transformPipeline;
//GLShaderManager     shaderManager;
//
//// 绘制立方体
//void DrawCube(void)
//{
//	int i, j;
//	glBegin(GL_LINES);
//	for (i = 0; i < 12; ++i) // 12 条线段
//	{
//		for (j = 0; j < 2; ++j) // 每条线段 2个顶点
//		{
//			glVertex3fv(vertex_list[index_list[i][j]]);
//		}
//	}
//	for (int i = 0; i < n; ++i)
//	{
//		glVertex2f(R*cos(2 * Pi / n*i), R*sin(2 * Pi / n*i));
//	}
//
//	//GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//	//shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vRed);
//	//shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);
//
//	glEnd();
//}
//
//static float rotate = 0;
//static int times = 0;
//
//
//void renderScene(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glPushMatrix();
//	//glTranslatef(-0.2, 0, 0); // 平移
//	//glScalef(2, 1, 1);    // 缩放
//	times++;
//	if (times > 100)
//	{
//		times = 0;
//	}
//	if (times % 100 == 0)
//	{
//		rotate += 0.3;
//	}
//	glRotatef(rotate, 0, 1, 0);
//	glRotatef(rotate, 1, 0, 0);
//	glColor3f(1, 0, 1);
//	DrawCube();
//	glPopMatrix();
//	glutSwapBuffers();
//}
//
//void main(int argc, char **argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("GLDemo");
//	glutDisplayFunc(renderScene);
//	glutIdleFunc(renderScene);
//	glutMainLoop();
//}
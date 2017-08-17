//#define _CRT_SECURE_NO_WARNINGS
//#include <GLTools.h>	// OpenGL toolkit
//#include <GLMatrixStack.h>
//#include <GLFrame.h>
//#include <GLFrustum.h>
//#include <GLBatch.h>
//#include <GLGeometryTransform.h>
//
//#define FREEGLUT_STATIC
//
//#include <math.h>
//#ifdef __APPLE__
//#include <glut/glut.h>
//#else
//#define FREEGLUT_STATIC
//#include <GL/glut.h>
//#endif
//
//#define bmpFileName "NinjaComp.BMP"
//#define jpegFileName "ttcover.jpeg"
//#define bmpjpegfileName "ppcover.bmp"
//static GLint imagewidth;
//static GLint imageheight;
//static GLint pixellength;
//static GLubyte* pixeldata;
//static GLubyte* jpglpdata;
//GLuint g_textures;				//存储图片纹理
//#include<stdio.h>
//#include<stdlib.h>
//#include <atlimage.h>
//#include < Gdiplus.h>  
//#pragma comment(lib, "Gdiplus.lib")  
//using namespace Gdiplus;
//#include <Objbase.h>  
//#include <Objidl.h>  
//#pragma comment(lib, "Ole32.lib")  
//#pragma comment(lib, "Uuid.lib") 
//void display(void)
//{
//	//glClear(GL_COLOR_BUFFER_BIT);
//	//绘制像素
//	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
//	//glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, jpglpdata);
//	//---------------------------------
//	glFlush();
//	glutSwapBuffers();
//}
//
////加载普通图片
//void LoadGLTextures(CString path)
//{
//	glGenTextures(1, &g_textures);
//	CImage img;
//	img.Load(path); //  通过图片文件名字来加在
//	int width = img.GetWidth();
//	int height = img.GetHeight();
//	unsigned char *pData = NULL;
//	if (img.GetPitch() < 0) //GetBits的作用就是获得纹理的位信息缓冲区指针，如果位图是从下到上， 则指向缓冲区末端，否则指向缓冲区首端。而img.GetPitch 就是起这个判断作用，小于 0 指向末端
//		jpglpdata = (unsigned char *)img.GetBits() + (img.GetPitch()*(img.GetHeight() - 1));
//	else
//		jpglpdata = (unsigned char *)img.GetBits();
//	glBindTexture(GL_TEXTURE_2D, g_textures);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, jpglpdata);
//}
//
//int main(int argc, char* argv[])
//{
//	//打开文件
//	//FILE* pfile = fopen(bmpFileName, "rb");
//	FILE* pfile = fopen(bmpjpegfileName, "rb");
//	if (pfile == 0)	exit(0);
//
//	//LoadGLTextures(jpegFileName);
//
//	//读取图像大小
//	fseek(pfile, 0x0012, SEEK_SET);
//	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
//	fread(&imageheight, sizeof(imageheight), 1, pfile);
//	//计算像素数据长度
//	pixellength = imagewidth * 3;
//	while (pixellength % 4 != 0)pixellength++;
//	pixellength *= imageheight;
//	//读取像素数据
//	pixeldata = (GLubyte*)malloc(pixellength);
//	if (pixeldata == 0) exit(0);
//	fseek(pfile, 54, SEEK_SET);
//	fread(pixeldata, pixellength, 1, pfile);
//
//	//关闭文件
//	fclose(pfile);
//	//初始化glut运行
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(imagewidth, imageheight);
//	glutCreateWindow(bmpFileName);
//	glutDisplayFunc(&display);
//	glutMainLoop();
//	//-------------------------------------
//	free(pixeldata);
//	//free(jpglpdata);
//	return 0;
//}
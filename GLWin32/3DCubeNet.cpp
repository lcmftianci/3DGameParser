///**
//* function：动态3D立方体
//*/
//#define GLUT_DISABLE_ATEXIT_HACK
//#include <windows.h>  
//#include <gl/gl.h>  
//#include <gl/glu.h>  
//#pragma comment(lib,"glut32.lib")
//#pragma comment(lib,"glu32.lib")
//#pragma comment(lib,"opengl32.lib")
//
//wchar_t *className = L"OpenGL";
//wchar_t *windowName = L"OpenGL Cube";
//int winX = 0, winY = 0;
//int winWidth = 300, winHeight = 300;
//HDC hDC;
//HGLRC hGLRC;
//HPALETTE hPalette;
//void init(void) {
//	//设置视图投影  
//	glMatrixMode(GL_PROJECTION);
//	glFrustum(-0.5F, 0.5F, -0.5F, 0.5F, 1.0F, 3.0F);
//	//视区定位  
//	glMatrixMode(GL_MODELVIEW);
//	glTranslatef(0.0F, 0.0F, -2.0F);
//	//物体定位  
//	glRotatef(30.0F, 1.0F, 0.0F, 0.0F);
//	glRotatef(30.0F, 0.0F, 1.0F, 0.0F);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//}
//void redraw(HDC hDC) {
//	//清除颜色和深度缓冲区  
//	//glClearColor(1.0f, 0.0f, 0.0f, 0.0f);  
//	//glClearDepth(2.0);  
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	//画立方体的6个面  
//	glBegin(GL_QUADS);
//	glNormal3f(0.0F, 0.0F, 1.0F);
//	glVertex3f(0.5f, 0.5f, 0.5f);
//	glVertex3f(-0.5f, 0.5f, 0.5f);
//	glVertex3f(-0.5f, -0.5f, 0.5f);
//	glVertex3f(0.5f, -0.5f, 0.5f);
//	//1----------------------------  
//	glNormal3f(0.0F, 0.0F, -1.0F);
//	glVertex3f(-0.1f, -0.5f, -0.5f);
//	glVertex3f(-0.5f, 0.5f, -0.5f);
//	glVertex3f(0.5f, 0.5f, -0.5f);
//	glVertex3f(0.5f, -0.5f, -0.5f);
//	//2----------------------------  
//	glNormal3f(0.0F, 1.0F, 0.0F);
//	glVertex3f(0.5f, 0.5f, 0.5f);
//	glVertex3f(0.5f, 0.5f, -0.5f);
//	glVertex3f(-0.5f, 0.5f, -0.5f);
//	glVertex3f(-0.5f, 0.5f, 0.5f);
//	//3----------------------------  
//	glNormal3f(0.0F, -1.0F, 0.0F);
//	glVertex3f(-0.5f, -0.5f, -0.5f);
//	glVertex3f(0.5f, -0.5f, -0.5f);
//	glVertex3f(0.5f, -0.5f, 0.5f);
//	glVertex3f(-0.5f, -0.5f, 0.5f);
//	//4----------------------------  
//	glNormal3f(1.0F, 0.0F, 0.0F);
//	glVertex3f(0.5f, 0.5f, 0.5f);
//	glVertex3f(0.5f, -0.5f, 0.5f);
//	glVertex3f(0.5f, -0.5f, -0.5f);
//	glVertex3f(0.5f, 0.5f, -0.5f);
//	//5----------------------------  
//	glNormal3f(-1.0F, 0.0F, 0.0F);
//	glVertex3f(-0.5f, -0.5f, -0.5f);
//	glVertex3f(-0.5f, -0.5f, 0.5f);
//	glVertex3f(-0.5f, 0.5f, 0.5f);
//	glVertex3f(-0.5f, 0.5f, -0.5f);
//	//6----------------------------*/  
//	glEnd();
//	SwapBuffers(hDC);
//}
//void resize(void) {
//	//设置视区，使之覆盖整个窗口  
//	glViewport(0, 0, winWidth, winHeight);
//}
//void setupPixelFormat(HWND hwnd, HDC* hDC, HGLRC* hRC) {
//	PIXELFORMATDESCRIPTOR pfd;
//
//	int iFormat;
//
//	/* get the device context (DC) */
//	*hDC = GetDC(hwnd);
//
//	/* set the pixel format for the DC */
//	ZeroMemory(&pfd, sizeof(pfd));
//
//	pfd.nSize = sizeof(pfd);//结构的大小  
//	pfd.nVersion = 1;//版本  
//	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
//		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;//支持双缓存  
//	pfd.iPixelType = PFD_TYPE_RGBA;//颜色模式  
//	pfd.cColorBits = 24;
//	pfd.cDepthBits = 16;//颜色深度  
//	pfd.iLayerType = PFD_MAIN_PLANE;//主层  
//
//	iFormat = ChoosePixelFormat(*hDC, &pfd);//确定pfd结构是否存在  
//
//	SetPixelFormat(*hDC, iFormat, &pfd);
//
//	/* create and enable the render context (RC) */
//	*hRC = wglCreateContext(*hDC);
//
//	wglMakeCurrent(*hDC, *hRC);
//
//
//	/*if(iFormat == 0){
//	MessageBox(WindowFromDC(hDC),"ChoosePixelFormat failed.",
//	"Error",MB_ICONERROR|MB_OK);
//	exit(1);
//	}
//	if(SetPixelFormat(hDC,iFormat,&pfd)!=TRUE){
//	MessageBox(WindowFromDC(hDC),"SetPixelFormat failed.",
//	"Error",MB_ICONERROR|MB_OK);
//	exit(1);
//	}*/
//}
//void setupPalette(HDC hDC) {
//	int pixelFormat = GetPixelFormat(hDC);
//	PIXELFORMATDESCRIPTOR pfd;
//	LOGPALETTE* pPal;
//	int paletteSize;
//	DescribePixelFormat(hDC, pixelFormat,
//		sizeof(PIXELFORMATDESCRIPTOR), &pfd);
//	if (pfd.dwFlags & PFD_NEED_PALETTE) {
//		paletteSize = 1 << pfd.cColorBits;
//	}
//	else {
//		return;
//	}
//	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
//	pPal->palVersion = 0x300;
//	pPal->palNumEntries = paletteSize;
//	//建一个简单的RGB调色板  
//	{
//		int redMask = (1 << pfd.cRedBits) - 1;
//		int greemMask = (1 << pfd.cGreenBits) - 1;
//		int blueMask = (1 << pfd.cBlueBits) - 1;
//		int i;
//		for (i = 0; i<paletteSize; i++) {
//			pPal->palPalEntry[i].peRed =
//				(((i >> pfd.cRedShift) & redMask) * 255) / greemMask;
//			//pPal->palPalEntry[i]-peGreen =  
//
//		}
//	}
//
//}
//
//
//
//
//LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
//void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
//void DisableOpenGL(HWND, HDC, HGLRC);
//
//
//int WINAPI WinMain(HINSTANCE hInstance, 	HINSTANCE hPrevInstance,  LPSTR lpCmdLine,	int nCmdShow)
//{
//	WNDCLASSEX wcex;
//	HWND hwnd;
//	HDC hDC;
//	HGLRC hRC;
//	MSG msg;
//	BOOL bQuit = FALSE;
//	float theta = 0.0f;
//
//	/* register window class */
//	wcex.cbSize = sizeof(WNDCLASSEX);
//	wcex.style = CS_HREDRAW | CS_VREDRAW;//CS_OWNDC;  
//	wcex.lpfnWndProc = WindowProc;
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = 0;
//	wcex.hInstance = hInstance;
//	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
//	wcex.lpszMenuName = NULL;
//	wcex.lpszClassName = L"GLSample";
//	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;
//
//
//	if (!RegisterClassEx(&wcex))
//		return 0;
//
//	/* create main window */
//	hwnd = CreateWindowEx(0, L"GLSample", windowName,//"OpenGL Sample",  
//		WS_OVERLAPPEDWINDOW/*后面是后来加的*/ | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
//		winX,//CW_USEDEFAULT,  
//		winY,//CW_USEDEFAULT,  
//		winWidth,//256,  
//		winHeight,//256,  
//		NULL,
//		NULL,
//		hInstance,
//		NULL);
//
//	ShowWindow(hwnd, nCmdShow);
//
//	/* enable OpenGL for the window */
//	//setupPixelFormat(hwnd, &hDC, &hRC);  
//	EnableOpenGL(hwnd, &hDC, &hRC);
//	init();
//
//	/* program main loop */
//	while (!bQuit)
//	{
//		/* check for messages */
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			/* handle or dispatch messages */
//			if (msg.message == WM_QUIT)
//			{
//				bQuit = TRUE;
//			}
//			else
//			{
//				TranslateMessage(&msg);
//				DispatchMessage(&msg);
//			}
//		}
//		else if (0)
//		{
//			/* OpenGL animation code goes here */
//
//			glClearColor(0.5f, 1.0f, 0.5f, 0.5f);
//			glClear(GL_COLOR_BUFFER_BIT);
//
//
//			glPushMatrix();
//			glRotatef(theta, 0.0f, 0.0f, 1.0f);
//
//			glBegin(GL_TRIANGLES);
//
//			glColor3f(0.5f, 5.0f, 1.0f);   glVertex2f(0.0f, 1.0f);
//			glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.87f, -0.5f);
//			glColor3f(1.0f, 5.0f, 0.5f);   glVertex2f(-0.87f, -0.5f);
//
//			glEnd();
//
//			glPopMatrix();
//
//			SwapBuffers(hDC);
//
//			theta += 1.0f;
//			//Sleep (1);  
//		}
//		else {
//			glPushMatrix();
//			glRotatef(theta, 0.0f, 0.0f, 1.0f);
//			redraw(hDC);//立方体  需要初始化init（）函数  
//			glPopMatrix();
//			theta += 1.0f;
//		}
//	}
//
//	/* shutdown OpenGL */
//	DisableOpenGL(hwnd, hDC, hRC);
//
//	/* destroy the window explicitly */
//	DestroyWindow(hwnd);
//
//	return msg.wParam;
//}
//
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (uMsg)
//	{
//		/*case WM_CREATE:
//		hDC = GetDC(hwnd);
//		setupPalette(hDC);
//		hGLRC=wglCreateContext(hDC);
//		wglMakeCurrent(hDC,hGLRC);
//		init();
//		return 0;*/
//	case WM_CLOSE:
//		PostQuitMessage(0);
//		break;
//
//	case WM_DESTROY:
//		/*//------------------
//		if(hGLRC){
//		wglMakeCurrent(NULL,NULL);
//		wglDeleteContext(hGLRC);
//		}
//		if(hPalette){
//		DeleteObject(hPalette);
//		}
//		ReleaseDC(hwnd,hDC);
//		PostQuitMessage(0);
//		//====================*/
//		return 0;
//		//------------------------  
//	case WM_SIZE:
//		//跟踪窗口大小改变  
//		hGLRC = (struct HGLRC__ *)1;
//		if (hGLRC) {
//			winWidth = (int)LOWORD(lParam);
//			winHeight = (int)LOWORD(lParam);
//			resize();
//			return 0;
//		}
//	case WM_PALETTECHANGED:
//		//如果它不是当前窗口，则实现调色板与hDC的对应  
//		if (hGLRC && hPalette && (HWND)wParam != hwnd) {
//			UnrealizeObject(hPalette);
//			SelectPalette(hDC, hPalette, FALSE);
//			//ReadlizePalette(hDC);  
//			redraw(hDC);
//			break;
//		}
//		break;
//		//=========================  
//	case WM_KEYDOWN:
//	{
//		switch (wParam)
//		{
//		case VK_ESCAPE:
//			PostQuitMessage(0);
//			break;
//		}
//	}
//	break;
//
//	default:
//		return DefWindowProc(hwnd, uMsg, wParam, lParam);
//	}
//	return 0;
//}
//
//void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
//{
//	PIXELFORMATDESCRIPTOR pfd;
//
//	int iFormat;
//
//	/* get the device context (DC) */
//	*hDC = GetDC(hwnd);
//
//	/* set the pixel format for the DC */
//	ZeroMemory(&pfd, sizeof(pfd));
//
//	pfd.nSize = sizeof(pfd);
//	pfd.nVersion = 1;
//	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
//		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
//	pfd.iPixelType = PFD_TYPE_RGBA;
//	pfd.cColorBits = 24;
//	pfd.cDepthBits = 16;
//	pfd.iLayerType = PFD_MAIN_PLANE;
//
//	iFormat = ChoosePixelFormat(*hDC, &pfd);
//
//	SetPixelFormat(*hDC, iFormat, &pfd);
//
//	/* create and enable the render context (RC) */
//	*hRC = wglCreateContext(*hDC);
//
//	wglMakeCurrent(*hDC, *hRC);
//}
//
//void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
//{
//	wglMakeCurrent(NULL, NULL);
//	wglDeleteContext(hRC);
//	ReleaseDC(hwnd, hDC);
//}
#include "Show.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <atlstr.h>
#include <time.h>
#include <iostream>

using namespace std;


//create main function
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	CString strTitle = "CHINA";
	CString strCon = "CHN";
	//MessageBox(NULL, strTitle,  strCon, MB_OKCANCEL);
	//register Wind
	GameMyRegisterClass(hInstance);

	if (!GameInitInstance(hInstance, nShowCmd))
		return 0;

	if (!Game_Init()) return 0;

	MSG msg;
	while (!gameover)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Game_Run();
	}
	/*while (GetMessage(&msg, NULL, 0, 0))
	{
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}*/
	Game_End();
	return msg.wParam;
}
#include "stdafx.h"
#include "filemanager.h"
using namespace std;

void FindFile(string strFilePath, std::vector<string>& m_arrFilePath)
{
	CFileFind finder;
	CString str = (LPCTSTR)strFilePath.c_str();//乱码
	char ch[2048] = "";
	sprintf(ch, "%s", strFilePath.c_str());
	int num = MultiByteToWideChar(0, 0, ch, -1, NULL, 0);
	wchar_t *lpstr1 = new wchar_t[num];
	MultiByteToWideChar(0, 0, ch, -1, lpstr1, num);
	CString strPath = GetFilePath(strFilePath);
	strPath += _T("*.*");
	BOOL bWorking = finder.FindFile(strPath);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsDots() && finder.IsDirectory())
		{
			USES_CONVERSION;
			CString str = finder.GetFilePath();
			string strFilePath = W2A(str.GetBuffer());
			strFilePath += "\\";
			FindFile(strFilePath, m_arrFilePath);
		}
		else
		{
			char ch[2048] = "";
			USES_CONVERSION;
			CString str = finder.GetFilePath();
			string strFilePath = W2A(str.GetBuffer());
			m_arrFilePath.push_back(strFilePath);
		}
	}
}

//获取文件目录
CString GetFilePath(string strPathBuf)
{
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath(strPathBuf.c_str(), drive, dir, fname, ext); // C4996
	_makepath(path_buffer, drive, dir, "", ""); // C4996
	wchar_t *lpstr1 = new wchar_t[2048];
	MultiByteToWideChar(0, 0, path_buffer, -1, lpstr1, 2048);
	return lpstr1;
}
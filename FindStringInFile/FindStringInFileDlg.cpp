
// FindStringInFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FindStringInFile.h"
#include "FindStringInFileDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <vector>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFindStringInFileDlg dialog



CFindStringInFileDlg::CFindStringInFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FINDSTRINGINFILE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFindStringInFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STR, m_EditStr);
	DDX_Control(pDX, IDC_EDIT_PATH, m_EditPath);
}

BEGIN_MESSAGE_MAP(CFindStringInFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PATH, &CFindStringInFileDlg::OnBnClickedBtnPath)
	ON_BN_CLICKED(ID_FIND, &CFindStringInFileDlg::OnBnClickedFind)
END_MESSAGE_MAP()


// CFindStringInFileDlg message handlers

BOOL CFindStringInFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFindStringInFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFindStringInFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFindStringInFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//查找字符串
bool FindString(std::string strData, string strFilePath)
{
	//打开文件,查找字符串，关闭文件返回值
	FILE* fp = fopen(strFilePath.c_str(), "rt");
	if (fp == NULL)
{
fclose(fp);
		return false;
}

	//查找字符串
	char chValue[2048] = "";
	while (!feof(fp))
	{
		fgets(chValue, 2047, fp);
		if (strstr(chValue, strData.c_str()) != NULL)
{
fclose(fp);
			return true;
}
	}
fclose(fp);
	return false;
}


//文件路径写入文件并打开
int DisplayFilePath(std::vector<string> mVec)
{
	if (mVec.size() <= 0)
		return 0;

	AllocConsole();
	freopen("C:\\Users\\Administrator\\Desktop\\col.txt", "wt", stdout);
	std::vector<string>::iterator iter = mVec.begin();
	for (; iter != mVec.end(); iter++)
	{
		printf("%s\n", iter->data());
	}
	fclose(stdout);
	FreeConsole();
	WinExec("notepad.exe C:\\Users\\Administrator\\Desktop\\col.txt", SW_SHOW);
	return (int)mVec.size();
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

//获取根目录
CString GetRootPath(string strRootPath)
{
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath(strRootPath.c_str(), drive, dir, fname, ext); // C4996
	_makepath(path_buffer, drive, "", "", ""); // C4996
	wchar_t *lpstr1 = new wchar_t[2048];
	MultiByteToWideChar(0, 0, path_buffer, -1, lpstr1, 2048);
	return lpstr1;
}

//获取父目录
CString GetParentPath(string strPathFather)
{
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath(strPathFather.c_str(), drive, dir, fname, ext); // C4996
	_makepath(path_buffer, drive, dir, "", ""); // C4996
	wchar_t *lpstr1 = new wchar_t[2048];
	MultiByteToWideChar(0, 0, path_buffer, -1, lpstr1, 2048);
	return lpstr1;
}

//遍历文件夹
void CFindStringInFileDlg::FindFile(string strFilePath)
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
			FindFile(strFilePath);
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

//将查找到的文件复制到现有字符串中
void CFindStringInFileDlg::InputArr(string strData)
{
	//查找字符串并将存在相应字符串的文件写入到写入到指定字符数组
	std::vector<string>::iterator iter = m_arrFilePath.begin();
	for (; iter != m_arrFilePath.end(); iter++)
	{
		if (FindString(strData, iter->data()))
			m_arrNewStrPath.push_back(iter->data());
	}
}

//获取文件夹
void CFindStringInFileDlg::OnBnClickedBtnPath()
{
	// TODO: Add your control notification handler code here
	//选择文件夹文件
#define MAX_CFileDialog_FILE_COUNT 99
#define FILE_LIST_BUFFER_SIZE ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1)

	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);
	CFileDialog dlgFile(TRUE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.Flags |= OFN_ALLOWMULTISELECT;
	ofn.lpstrFile = p;
	ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;

	dlgFile.DoModal();
	m_strFindPath = ofn.lpstrFile;
	m_EditPath.SetWindowText(m_strFindPath);
	fileName.ReleaseBuffer();
}


/*查找按钮*/
void CFindStringInFileDlg::OnBnClickedFind()
{
	// TODO: Add your control notification handler code here
	m_EditStr.GetWindowText(m_strFind);
	USES_CONVERSION;
	string strFileStr = W2A(m_strFind.GetBuffer());
	if (strFileStr == "")
	{
		MessageBox(_T("字符串为空,请重新输入！"), _T("提示"), MB_OK);
		return;
	}
	string strFilePath = W2A(m_strFindPath.GetBuffer());
	if (strFilePath == "")
	{
		MessageBox(_T("文件路径为空,请重新选择！"), _T("提示"), MB_OK);
		return;
	}

	//检查不出来空字符串，可能写的有问题
	//if (m_strFind == _T("")||m_strFind.IsEmpty())
	//{
	//	return;
	//}

	//遍历文件夹
	FindFile(strFilePath);

	//查找字符串
	InputArr(strFileStr);

	//打印字符串
	DisplayFilePath(m_arrNewStrPath);
}

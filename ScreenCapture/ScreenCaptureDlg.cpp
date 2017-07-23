
// ScreenCaptureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenCapture.h"
#include "ScreenCaptureDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CM_NOTIFY  WM_USER+1 //用户自定义消息

// #pragma comment(lib,"vfw32") 
// #pragma comment(lib,"winmm")


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


// CScreenCaptureDlg dialog



CScreenCaptureDlg::CScreenCaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCREENCAPTURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCEFILE, m_SourceFile);
	DDX_Control(pDX, IDC_DESFILE, m_DesFile);
	DDX_Control(pDX, IDC_COMBO1, m_combodecode);
}

BEGIN_MESSAGE_MAP(CScreenCaptureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo)
	ON_BN_CLICKED(IDC_SOURCEBROWN, OnSourcebrown)
	ON_BN_CLICKED(IDC_DESBROWN2, OnDesbrown)
	ON_BN_CLICKED(IDC_STARTCOMPRESS, OnStartcompress)
	ON_BN_CLICKED(IDC_BUTTON5, OnCancle)
	ON_COMMAND(ID_CAP, &CScreenCaptureDlg::OnCap)
	ON_COMMAND(ID_FULL, &CScreenCaptureDlg::OnFull)
	ON_COMMAND(ID_CAPVIDEO, &CScreenCaptureDlg::OnCapvideo)
	ON_MESSAGE(CM_NOTIFY, &CScreenCaptureDlg::OnGraphNotify)
END_MESSAGE_MAP()


// CScreenCaptureDlg message handlers

void CScreenCaptureDlg::SetImage(const CString &strPath)
{
	if (!m_image.IsNull())
		m_image.Destroy();

	HRESULT hr = m_image.Load(strPath);
	if (FAILED(hr)) {
		TRACE("Image Load Failed: %x\n", hr);
	}
	Invalidate();
}

BOOL CScreenCaptureDlg::OnInitDialog()
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
	//添加Menu
	m_Menu.LoadMenu(IDR_MENU1);  //  IDR_MENU1为你加入的菜单的ID，在Resource视图的Menu文件夹下可以找到
	SetMenu(&m_Menu);

	//SetWindowLong(this->GetSafeHwnd(), GWL_STYLE, GetWindowLong(this->GetSafeHwnd(), GWL_STYLE) - WS_CAPTION);
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	GetDecodeList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScreenCaptureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScreenCaptureDlg::OnPaint()
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
		CPaintDC dc(this); // device context for painting
		CDC MemDC;
		CBitmap   MemBitmap;//定义一个位图对象
		MemDC.CreateCompatibleDC(NULL);
		if (m_image.IsNull())
			return;
		CRect rect;
		GetClientRect(rect);
		MemBitmap.CreateCompatibleBitmap(GetDC(), rect.Width(), rect.Height());
		CBitmap   *pOldBit = MemDC.SelectObject(&MemBitmap);
		MemDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

		MemDC.SetStretchBltMode(HALFTONE);
		m_image.StretchBlt(MemDC, rect);

		GetDC()->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
		MemBitmap.DeleteObject();
		MemDC.DeleteDC();

		//绘制图像

		// TODO: Add your message handler code here
		/*
			移动窗口是图片闪烁
			CDC   MemDC;   //首先定义一个显示设备对象
			CBitmap   MemBitmap;//定义一个位图对象
			//随后建立与屏幕显示兼容的内存显示设备
			MemDC.CreateCompatibleDC(NULL);
			//这时还不能绘图，因为没有地方画   ^_^
			//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
			MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);

			//将位图选入到内存显示设备中
			//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
			CBitmap   *pOldBit=MemDC.SelectObject(&MemBitmap);
			//先用背景色将位图清除干净，这里我用的是白色作为背景
			//你也可以用自己应该用的颜色
			MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));
			//绘图
			MemDC.MoveTo(……);
			MemDC.LineTo(……);

			//将内存中的图拷贝到屏幕上进行显示
			pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
			//绘图完成后的清理
			MemBitmap.DeleteObject();
			MemDC.DeleteDC();
		*/
		// In a real app you would probably want to maintain aspect ratio.
	/*	if (m_image.IsNull())
			return;
		CRect rect;
		GetClientRect(rect);
		dc.SetStretchBltMode(HALFTONE);
		m_image.StretchBlt(dc, rect);*/
		//Invalidate(FALSE);//闪烁
	//	CDialogEx::OnPaint();//有重影
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScreenCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CScreenCaptureDlg::OnCap()
{
	// TODO: Add your command handler code here
	ShowWindow(SW_HIDE);
	Sleep(500);
	ConfigureCapture(GetSafeHwnd(), &m_CapData);
	CaptureScreen(&m_CapData);
	ShowWindow(SW_SHOW);

	if (m_CapData.szCaptureFilename[0] != '\0') {
		// In a real application that had interest in the
		// actual image and not just a screen capture
		// we would want to pass the Bitmap/CImage back
		// and forth directly, but for screen capture
		// sample purposes, this works fine.
		CString strPathName(m_CapData.szCapturePath);
		if (strPathName.Right(1) != "\\")
			strPathName += '\\';
		strPathName += m_CapData.szCaptureFilename;
		SetImage(strPathName);
	}
}


void CScreenCaptureDlg::OnFull()
{
	// TODO: Add your command handler code here
}


/*
1、 选择一个压缩过滤器
有许多种方法可以压缩视频或者音频，比如：
a、 本地DirectShow过滤器
b、 视频压缩管理编码器（VCM）
c、 音频压缩管理编码器（ACM）
d、 DirectX媒体对象（DMOs）
*/

void CScreenCaptureDlg::OnCapvideo()
{
	// TODO: Add your command handler code here
	//录屏功能实现
	ShowWindow(SW_HIDE);
	for (int i = 0; i < 200; i++)
	{
		Sleep(50);
		ConfigureCapture(GetSafeHwnd(), &m_CapData);
		CaptureScreen(&m_CapData);
	}
	ShowWindow(SW_SHOW);
}

//void CScreenCaptureDlg::AVItoBmp(CString strAVIFileName, CString   strBmpDir)
//{
//	// TODO: 在此添加控件通知处理程序代码  
//	AVIFileInit();
//	PAVIFILE avi;
//	int res = AVIFileOpen(&avi, strAVIFileName, OF_READ, NULL);
//	int n = GetLastError();
//	if (res != AVIERR_OK)
//	{
//		//an error occures  
//		if (avi != NULL)
//			AVIFileRelease(avi);
//		return;
//	}
//	AVIFILEINFO avi_info;
//	AVIFileInfo(avi, &avi_info, sizeof(AVIFILEINFO));
//	PAVISTREAM pStream;
//	res = AVIFileGetStream(avi, &pStream, streamtypeVIDEO /*video stream*/,
//		0 /*first stream*/);
//	if (res != AVIERR_OK)
//	{
//		if (pStream != NULL)
//			AVIStreamRelease(pStream);
//		AVIFileExit();
//		return;
//	}
//
//	//do some task with the stream  
//	int iNumFrames;
//	int iFirstFrame;
//	iFirstFrame = AVIStreamStart(pStream);
//	if (iFirstFrame == -1)
//	{
//		//Error getteing the frame inside the stream  
//		if (pStream != NULL)
//			AVIStreamRelease(pStream);
//		AVIFileExit();
//		return;
//	}
//	iNumFrames = AVIStreamLength(pStream);
//	if (iNumFrames == -1)
//	{
//		//Error getteing the number of frames inside the stream  
//		if (pStream != NULL)
//			AVIStreamRelease(pStream);
//		AVIFileExit();
//		return;
//	}
//
//	//getting bitmap from frame  
//	BITMAPINFOHEADER bih;
//	ZeroMemory(&bih, sizeof(BITMAPINFOHEADER));
//
//	bih.biBitCount = 24;    //24 bit per pixel  
//	bih.biClrImportant = 0;
//	bih.biClrUsed = 0;
//	bih.biCompression = BI_RGB;
//	bih.biPlanes = 1;
//	bih.biSize = 40;
//	bih.biXPelsPerMeter = 0;
//	bih.biYPelsPerMeter = 0;
//	//calculate total size of RGBQUAD scanlines (DWORD aligned)  
//	bih.biSizeImage = (((bih.biWidth * 3) + 3) & 0xFFFC) * bih.biHeight;
//
//	PGETFRAME pFrame;
//	pFrame = AVIStreamGetFrameOpen(pStream, NULL);
//
//	AVISTREAMINFO streaminfo;
//	AVIStreamInfo(pStream, &streaminfo, sizeof(AVISTREAMINFO));
//
//	//Get the first frame  
//	BITMAPINFOHEADER bih2;
//	long lsize = sizeof(bih2);
//	int index = 0;
//	for (int i = iFirstFrame; i < iNumFrames; i++)
//	{
//		index = i - iFirstFrame;
//		BYTE* pDIB = (BYTE*)AVIStreamGetFrame(pFrame, index);                   //  
//		AVIStreamReadFormat(pStream, index, &bih2, &lsize);
//		BITMAPFILEHEADER stFileHdr;
//
//
//		BYTE* Bits = new BYTE[bih2.biSizeImage];
//		AVIStreamRead(pStream, index, 1, Bits, bih2.biSizeImage, NULL, NULL);
//		//RtlMoveMemory(Bits, pDIB + sizeof(BITMAPINFOHEADER), bih2.biSizeImage);  
//
//		bih2.biClrUsed = 0;
//		stFileHdr.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
//		stFileHdr.bfSize = sizeof(BITMAPFILEHEADER);
//		stFileHdr.bfType = 0x4d42;
//
//		CString FileName;
//		FileName.Format("Frame-%05d.bmp", index);
//		CString strtemp = strBmpDir;
//		strtemp += "\\";
//		strtemp += FileName;
//		FILE* fp = _tfopen(strtemp, _T("wb"));
//		fwrite(&stFileHdr, 1, sizeof(BITMAPFILEHEADER), fp);
//		fwrite(&bih2, 1, sizeof(BITMAPINFOHEADER), fp);
//		int ff = fwrite(Bits, 1, bih2.biSizeImage, fp);
//		int e = GetLastError();
//		fclose(fp);
//		/////  
//		delete Bits;
//		//CreateFromPackedDIBPointer(pDIB, index);  
//	}
//
//	AVIStreamGetFrameClose(pFrame);
//
//	//close the stream after finishing the task  
//	if (pStream != NULL)
//		AVIStreamRelease(pStream);
//
//	AVIFileExit();
//}
//
//void CScreenCaptureDlg::BMPtoAVI(CString szAVIName, CString strBmpDir)
//{
//	CFileFind finder;
//	strBmpDir += _T("\\*.*");
//	AVIFileInit();
//	AVISTREAMINFO strhdr;
//	PAVIFILE pfile;
//	PAVISTREAM ps;
//	int nFrames = 0;
//	HRESULT hr;
//
//	BOOL bFind = finder.FindFile(strBmpDir);
//	while (bFind)
//	{
//		bFind = finder.FindNextFile();
//		if (!finder.IsDots() && !finder.IsDirectory())
//		{
//			CString str = finder.GetFilePath();
//			FILE *fp = fopen(str, "rb");
//			BITMAPFILEHEADER bmpFileHdr;
//			BITMAPINFOHEADER bmpInfoHdr;
//			fseek(fp, 0, SEEK_SET);
//			fread(&bmpFileHdr, sizeof(BITMAPFILEHEADER), 1, fp);
//			fread(&bmpInfoHdr, sizeof(BITMAPINFOHEADER), 1, fp);
//
//			BYTE *tmp_buf = NULL;
//			if (nFrames == 0)
//			{
//				AVIFileOpen(&pfile, szAviName, OF_WRITE | OF_CREATE, NULL);
//				_fmemset(&strhdr, 0, sizeof(strhdr));
//				strhdr.fccType = streamtypeVIDEO;// stream type  
//				strhdr.fccHandler = 0;
//				strhdr.dwScale = 1;
//				strhdr.dwRate = 15;                 // 15 fps  
//				strhdr.dwSuggestedBufferSize = bmpInfoHdr.biSizeImage;
//				SetRect(&strhdr.rcFrame, 0, 0, bmpInfoHdr.biWidth, bmpInfoHdr.biHeight);
//
//				// And create the stream;  
//				hr = AVIFileCreateStream(pfile, &ps, &strhdr);
//				// hr = AVIStreamSetFormat(ps,nFrames,&bmpInfoHdr,sizeof(bmpInfoHdr));  
//			}
//			tmp_buf = new BYTE[bmpInfoHdr.biWidth * bmpInfoHdr.biHeight * 3];
//			fread(tmp_buf, 1, bmpInfoHdr.biWidth * bmpInfoHdr.biHeight * 3, fp);
//			hr = AVIStreamSetFormat(ps, nFrames, &bmpInfoHdr, sizeof(bmpInfoHdr));
//			hr = AVIStreamWrite(ps,       // stream pointer  
//				nFrames,                          // time of this frame  
//				1,                         // number to write  
//				(LPBYTE)tmp_buf,
//				bmpInfoHdr.biSizeImage, // size of this frame  
//				AVIIF_KEYFRAME,                    // flags....  
//				NULL,
//				NULL);
//
//			nFrames++;
//			fclose(fp);
//
//		}
//	}
//
//	AVIStreamClose(ps);
//
//	if (pfile != NULL)
//		AVIFileRelease(pfile);
//
//	AVIFileExit();
//}

//一。jpg，bmp互相转化
///*********************************
//format:bmp转为jpg， format为image/jpeg,jpg转为bmp,format为image/bmp
//strDst为最终转化结果的图片路径
//strSrc为原来图片的路径
//**********************************/
//BOOL ConvertPic(const WCHAR *format, const CString &strDst, const CString &strSrc)
//{
//	BOOL bConvert = false;
//	CLSID clsid;
//	int nRet = 0;
//	nRet = GetEncoderClsid(format, &clsid);  //得到CLSID
//	USES_CONVERSION;
//	if (nRet >= 0)
//	{
//		Image image(A2W(strSrc));
//		image.Save(A2W(strDst), &clsid, NULL);
//		bConvert = true;
//	}
//	return bConvert;
//}
//其中GetEncoderClsid函数如下：
///*****************************************************
//返回值为-1表示失败，其他为成功
//******************************************************/
//int GetEncoderClsid(const WCHAR *format, CLSID *pClsid)
//{
//	int nRet = -1;
//	ImageCodecInfo * pCodecInfo = NULL;
//	UINT nNum = 0, nSize = 0;
//	GetImageEncodersSize(&nNum, &nSize);
//	if (nSize < 0)
//	{
//		return nRet;
//	}
//	pCodecInfo = new ImageCodecInfo[nSize];
//	if (pCodecInfo == NULL)
//	{
//		return nRet;
//	}
//	GetImageEncoders(nNum, nSize, pCodecInfo);
//	for (UINT i = 0; i < nNum; i++)
//	{
//		if (wcscmp(pCodecInfo[i].MimeType, format) == 0)
//		{
//			*pClsid = pCodecInfo[i].Clsid;
//			nRet = i;
//
//			delete[] pCodecInfo;
//			return nRet;
//		}
//		else
//		{
//			continue;
//		}
//	}
//	delete[] pCodecInfo;
//	return nRet;
//}
//bmp转化为jpg
//ConvertPic(L"image/jpeg", "c:\\1.jpg", "c:\\1.bmp")
//jpg转化为bmp
//ConvertPic(L"image/bmp", "c:\\1.bmp", "c:\\1.jpg")
//
//二。bmp图片合并
//BOOL CombinePic(const WCHAR *format, const CString &strDst, const CString &strPic1, \
//	const CString &strPic2)
//{
//	BOOL bCombine = false;
//	int nRet = 0;
//	CLSID clsid;
//	nRet = GetEncoderClsid(format, &clsid);
//	if (nRet >= 0)
//	{
//		USES_CONVERSION;
//		Bitmap bmp1(A2W(strPic1));
//		Bitmap bmp2(A2W(strPic2));
//
//		int nWidth = 0, nHeight = 0;
//		nWidth = bmp1.GetWidth();   //假设两图片大小同
//		nHeight = bmp1.GetHeight();
//		Bitmap bmpCombine(2 * nWidth, nHeight);  //高不变，宽*2，水平合并
//		Graphics * pG = NULL;
//		pG = Graphics::FromImage(&bmpCombine);
//		if (pG != NULL)
//		{
//			pG->DrawImage(&bmp1, 0, 0);
//			pG->DrawImage(&bmp2, nWidth, 0);
//			bmpCombine.Save(A2W(strDst), &clsid, NULL);
//		}
//	}
//	return bCombine;
//}
//例子：
//CombinePic(L"image/bmp", "12.bmp", "1.bmp", "2.bmp");

//
//几张png保存成一张
//可以不依赖任何上下文设备
////创建一个位图,用来保存合成后的图像
//Gdiplus::Bitmap* pBitmap = new Bitmap(合成后宽度, 合成后高度, PixelFormat32bppARGB);
//Gdiplus::Graphics g(pBitmap);
//
//Gdiplus::Bitmap tmp1(L"c:\\001.png");//载入你要合并的PNG
//g.DrawImage(&tmp1, .....);
//
//Gdiplus::Bitmap tmp2(L"c:\\002.png");//载入你要合并的PNG
//g.DrawImage(&tmp2, .....);
//
//pBitmap->Save(....);//保存合并后的图像,完工！

//获取视频采集设备列表
void CScreenCaptureDlg::GetDecodeList()
{
	// 初始化COM  
	HRESULT hr = CoInitialize(NULL);
	ICreateDevEnum *pSysDevEnum = NULL;
	//使用CoCreateInstance函数创建系统枚举器组件对象,并获得ICreateDevEnum接口;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void**)&pSysDevEnum);
	if (FAILED(hr))
	{
		return;
	}
	//使用接口方法ICreateDevEnum::CreateClassEnumerator为指定的Filter注册类型目录
	//创建一个枚举器,并获得IEnumMoniker接口;
	IEnumMoniker *pEnumCat = NULL;
	hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoCompressorCategory,
		&pEnumCat, 0);
	if (hr == S_OK)
	{
		//枚举名称
		IMoniker *pMoniker = NULL;
		ULONG cFetched;
		while (pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
		{
			if (pMoniker)
			{
				WCHAR * wzDisplayName = NULL;
				IPropertyBag *pPropBag;
				IBaseFilter *pFilter = NULL;

				//获取当前设备的显示名字
				//hr = pMoniker->GetDisplayName(NULL,NULL,&wzDisplayName);
				//调用IMoniker::BindToStorage之后,可以访问设备标识的属性集,
				//比如得到Display Name,Friendly Name等;
				hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
					(void **)&pPropBag);
				if (SUCCEEDED(hr))
				{
					//获得Filter的FriendlyName
					VARIANT varName;
					VariantInit(&varName);
					hr = pPropBag->Read(L"FriendlyName", &varName, NULL);

					if (SUCCEEDED(hr))
					{
						//调用IMoniker::BindToOject可以将设备标识生成一个DirectShow Filter,
						//随后调用IFilterGraph::AddFilter,并将之加入到FilterGraph中就可以参与工作了
						//生成一个filter绑定到设备上。
						hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pFilter);
					}
					if (SUCCEEDED(hr))
					{
						m_combodecode.AddString(CString(varName.bstrVal));
					}
					//释放使用过的接口
					if (pFilter)
					{
						pFilter->Release();
						pFilter = NULL;
					}
				}
				pPropBag->Release();
			}
			pMoniker->Release();
		}
		pEnumCat->Release();
	}
	pSysDevEnum->Release();
}

//指定编解码器的友好名字，为它创建一个Filter
IBaseFilter * CScreenCaptureDlg::CreateDecodeDevice(GUID inCategory, const char * inFriendlyName)
{
	return CreateHardwareFilter(inCategory, inFriendlyName);
}

//根据设备的友好名字，创建一个代表该设备的Filter
IBaseFilter * CScreenCaptureDlg::CreateHardwareFilter(GUID inCategory, const char * inFriendlyName)
{
	//创建一个系统枚举组件对象
	ICreateDevEnum * enumHardware = NULL;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_ALL,
		IID_ICreateDevEnum, (void**)&enumHardware);
	if (FAILED(hr))
	{
		return NULL;
	}

	IBaseFilter * hardwareFilter = NULL;
	IEnumMoniker * enumMoniker = NULL;
	//为指定的目录创建枚举器
	hr = enumHardware->CreateClassEnumerator(inCategory, &enumMoniker, 0);
	if (enumMoniker)
	{
		enumMoniker->Reset();

		ULONG	fetched = 0;
		IMoniker * moniker = NULL;
		char friendlyName[256];

		//枚举得到该目录下所有的设备，逐个进行名字匹配
		while (!hardwareFilter && SUCCEEDED(enumMoniker->Next(1, &moniker,
			&fetched)) && fetched)
		{
			if (moniker)
			{
				IPropertyBag * propertyBag = NULL;
				VARIANT		name;
				friendlyName[0] = 0;
				//调用IMoniker::BindToStorage之后,可以访问设备标识的属性集
				hr = moniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)&propertyBag);
				//读取设备的友好名字
				if (SUCCEEDED(hr))
				{
					name.vt = VT_BSTR;
					hr = propertyBag->Read(L"Friendlyname", &name, NULL);
				}
				if (SUCCEEDED(hr))
				{
					WideCharToMultiByte(CP_ACP, 0, name.bstrVal, -1,
						friendlyName, 256, NULL, NULL);
					//如果当前设备的友好名字与用户指定的设备名字相同，
					//则将当前设备标识绑定为Filter形式
					if (strcmp(friendlyName, inFriendlyName) == 0)
					{
						moniker->BindToObject(0, 0, IID_IBaseFilter,
							(void**)&hardwareFilter);
					}
				}
				//释放使用过的接口
				if (propertyBag)
				{
					propertyBag->Release();
					propertyBag = NULL;
				}
				moniker->Release();
			}
		}
		enumMoniker->Release();
	}
	enumHardware->Release();

	return hardwareFilter;
}


//查找引脚
IPin* CScreenCaptureDlg::FindPin(IBaseFilter *pFilter, PIN_DIRECTION dir)
{
	IEnumPins* pEnumPins;
	IPin* pOutpin;
	PIN_DIRECTION pDir;
	pFilter->EnumPins(&pEnumPins);
	while (pEnumPins->Next(1, &pOutpin, NULL) == S_OK)
	{
		pOutpin->QueryDirection(&pDir);
		if (pDir == dir)
		{
			return pOutpin;
		}
	}
	return 0;
}

void CScreenCaptureDlg::OnSelchangeCombo()
{
	m_combodecode.GetLBText(m_combodecode.GetCurSel(), decodeName);
}

void CScreenCaptureDlg::OnSourcebrown()
{
	// TODO: Add your control notification handler code here
	CFileDialog fDlg(TRUE, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "AVI文件|*.avi|all|*.*||");
	if (fDlg.DoModal() == IDOK)
	{
		CString strFile = fDlg.GetPathName();
		m_SourceFile.SetWindowText(strFile);
	}
}

void CScreenCaptureDlg::OnDesbrown()
{
	// TODO: Add your control notification handler code here
	CFileDialog fDlg(FALSE, "avi", "one", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "AVI文件|*.avi");
	CString strFile;

	if (fDlg.DoModal() == IDOK)
	{
		strFile = fDlg.GetPathName();
		DeleteFile(strFile);		//如果文件存在，则先删除文件
		m_DesFile.SetWindowText(strFile);
	}
}

void CScreenCaptureDlg::OnStartcompress()
{
	// TODO: Add your control notification handler code here
	CString srcFile, dstFile;
	m_SourceFile.GetWindowText(srcFile);
	m_DesFile.GetWindowText(dstFile);

	if (srcFile.IsEmpty() || dstFile.IsEmpty())
	{
		MessageBox("源文件或目标文件不能为空!", "提示");
		return;
	}
	if (srcFile == dstFile)
	{
		MessageBox("源文件与目标文件不能相同!", "提示");
		return;
	}

	ICaptureGraphBuilder2 * pBuilder = NULL;
	pGraph = NULL;

	pMediaControl = NULL;
	pCompress = NULL;

	//第一步：创建 ICaptureGraphBuilder2接口
	CoCreateInstance(CLSID_CaptureGraphBuilder2, 0, CLSCTX_INPROC_SERVER,
		IID_ICaptureGraphBuilder2, (void**)&pBuilder);
	//第二步：创建IGraphBuilder接口
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void **)&pGraph);

	//第三步：调用ICaptureBuilder的SetFilterGraph方法将FilterGraph加入到Builder中
	pBuilder->SetFiltergraph(pGraph);
	//查询各个接口，得到媒体控制接口，该接口控制整个Graph状态的
	pGraph->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);

	//使用Capture Graph Builder来建立过滤图形
	//a、 建立部分渲染的过滤图形，它包含AVI Mux 过滤器和File Writer过滤器。
	//创建一个过滤器的实例，调用IMoniker::BindToObject方法。方法会返回一个IBaseFilter接口指针
	pBuilder->SetOutputFileName(&MEDIASUBTYPE_Avi,			//文件类型
		dstFile.AllocSysString(),	//文件名
		&pMux,						// 得到一个指向multiplexer的指针
		NULL);						// 得到一个指向File Write的指针
									//b、 添加源过滤器和压缩过滤器。
									//调用IgraphBuilder::AddSourceFilter方法来添加异步文件源过滤器
	pGraph->AddSourceFilter(srcFile.AllocSysString(), L"Source Filter", &pSrc);

	if (decodeName.IsEmpty())
	{
		MessageBox("请选择编解码器!", "提示");
		return;
	}

	pCompress = CreateDecodeDevice(CLSID_VideoCompressorCategory, decodeName);

	if (pCompress == NULL)
	{
		MessageBox("没有发现该压缩器!", "提示", MB_ICONASTERISK);
		return;
	}

	//b、 添加源过滤器和压缩过滤器。
	//调用IfilterGraph::AddFilter方法来添加视频压缩过滤器
	pGraph->AddFilter(pCompress, L"Compressor");

	IPin* pCompressIn, *pCompressOut;
	// 寻找支持 IAMVideoCompression的引脚
	pCompressIn = FindPin(pCompress, PINDIR_INPUT);
	pCompressOut = FindPin(pCompress, PINDIR_OUTPUT);

	IAMVideoCompression * pAMCompress;
	pCompressOut->QueryInterface(IID_IAMVideoCompression, (void**)&pAMCompress);
	HRESULT hret;
	//调用IAMVideoCompression::get_KeyFrameRate方法来得到关键桢的速率，
	//调用IAMVideoCompression::put_KeyFrameRate来设置桢速率。
	hret = pAMCompress->put_KeyFrameRate(8);

	//c、 连接源过滤器到MUX 过滤器
	//使用IcaptureGraphBuilder2::RenderStream方法来连接源过滤器的输出引脚到指定的过滤器。
	pBuilder->RenderStream(NULL, NULL, pSrc, pCompress, pMux);
	HRESULT hr = pMux->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);

	pGraph->QueryInterface(IID_IMediaEventEx, (void **)&pEvent);
	hret = pEvent->SetNotifyWindow((OAHWND)m_hWnd, CM_NOTIFY, 0);

	pMediaControl->Run();
	m_IsCompressing = TRUE;
}

void CScreenCaptureDlg::OnCancle()
{
	// TODO: Add your control notification handler code here

}

int CScreenCaptureDlg::CompressVideo()
{
	IGraphBuilder *pGraph = NULL;          // 图标管理器接口
	IMediaControl *pControl = NULL;        // 媒体控制器接口
	IMediaEvent *pEvent = NULL;           // 媒体事件接口

		// 初始化com库
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		printf("初始化com组件失败\n");
		return -1;
	}

	// 创建滤波器链表管理器
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);
	if (FAILED(hr))
	{
		printf("初始化com组件失败\n");
		return -1;
	}

	//查询媒体控制和媒体事件接口
	hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

	//建立链表,这里用户可以更改待播放的文件的名称
	hr = pGraph->RenderFile(L"E:\\DXSDK\\DXSDK 9.0B\\Samples\\Media\\ruby.avi", NULL);
	if (SUCCEEDED(hr))
	{
		//运行链表
		hr = pControl->Run();
		if (SUCCEEDED(hr))
		{
			//等待回放结束
			long evCode;
			pEvent->WaitForCompletion(INFINITE, &evCode);
			// 切记：在实际应用中，不能使用INFINITE标识，因为他会不确定的阻塞程序
		}
	}

	// 释放所有资源
	pControl->Release();
	pEvent->Release();
	pGraph->Release();
	CoUninitialize();
	printf("this is example\n");
	return 0;
}

LRESULT CScreenCaptureDlg::OnGraphNotify(WPARAM wParam, LPARAM lParam)
{
	if (pEvent)
	{
		LONG eventcode = 0, param1 = 0, param2 = 0;
		while (SUCCEEDED(pEvent->GetEvent(&eventcode, &param1, &param2, 0)))
		{
			pEvent->FreeEventParams(eventcode, param1, param2);
			switch (eventcode)
			{
			case EC_COMPLETE:
			{
				m_Completed = TRUE;
				m_IsCompressing = FALSE;
				pMediaControl->Stop();
				pMediaControl->Release();

				MessageBox("压缩完成!", "提示");
				break;
			}
			}
		}
		return S_OK;
	}
	return S_OK;
}

void CScreenCaptureDlg::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
}
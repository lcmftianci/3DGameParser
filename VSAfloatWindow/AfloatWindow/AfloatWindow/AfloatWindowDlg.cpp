
// AfloatWindowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AfloatWindow.h"
#include "AfloatWindowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAfloatWindowDlg dialog



CAfloatWindowDlg::CAfloatWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAfloatWindowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAfloatWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAfloatWindowDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CAfloatWindowDlg message handlers

BOOL CAfloatWindowDlg::OnInitDialog()
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

	CRgn rgn;
    rgn. CreateEllipticRgn(0,0,196,196);
    SetWindowRgn(rgn,TRUE);

	UpdateData();
	bool m_bShowTopmost = true;
	if (m_bShowTopmost)              // 窗口最前端显示  
	{
		TRACE("True\n");
		SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	else
	{
		TRACE("False\n");
		SetWindowPos(&this->wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAfloatWindowDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

LRESULT CAfloatWindowDlg::OnNcHitTest(CPoint pt)
{
    LRESULT nHitTest = CDialog::OnNcHitTest(pt);
    if(nHitTest == HTCLIENT)
    {
        nHitTest = HTCAPTION;
    }
    return nHitTest;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAfloatWindowDlg::OnPaint()
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

        ShowPicture();

	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAfloatWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAfloatWindowDlg::ShowPicture()
{
    CImage img;    
    HRESULT result = img.Load(_T("imagemap1.png")); 
    
    for(int i = 0; i < img.GetWidth(); i++)  
    {  
        for(int j = 0; j < img.GetHeight(); j++)  
        {  
            unsigned char* pucColor = reinterpret_cast<unsigned char *>(img.GetPixelAddress(i , j));  
            pucColor[0] = pucColor[0] * pucColor[3] / 255;  
            pucColor[1] = pucColor[1] * pucColor[3] / 255;  
            pucColor[2] = pucColor[2] * pucColor[3] / 255;  
        }  
    } 
    
    CDC *pDC = GetWindowDC();
    int nX = img.GetWidth();
    int nY = img.GetHeight();

    img.Draw( pDC->m_hDC,0,0); 
    ReleaseDC( pDC );
}

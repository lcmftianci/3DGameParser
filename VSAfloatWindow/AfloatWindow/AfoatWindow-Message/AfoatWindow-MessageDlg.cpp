
// AfoatWindow-MessageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AfoatWindow-Message.h"
#include "AfoatWindow-MessageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAfoatWindowMessageDlg dialog

CAfoatWindowMessageDlg::CAfoatWindowMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAfoatWindowMessageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAfoatWindowMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAfoatWindowMessageDlg, CDialogEx)
	ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CAfoatWindowMessageDlg message handlers

BOOL CAfoatWindowMessageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_bmp.LoadBitmap(IDB_BITMAP1);
    BITMAP bm;
    m_bmp.GetBitmap(&bm);
    CClientDC dc(this);
    SetupRegion(&dc,m_bmp,RGB(0,0,255));//remove blue color

	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAfoatWindowMessageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    CDC picDC;	
    picDC.CreateCompatibleDC (&dc);
    
    CBitmap *pOldBmp;
    pOldBmp = picDC.SelectObject (&m_bmp);
    
    BITMAP bm;
    m_bmp.GetBitmap(&bm);
    
    
   	dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight,&picDC,0,0,SRCCOPY);
    dc.SelectObject(pOldBmp); 
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAfoatWindowMessageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAfoatWindowMessageDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    //SendMessage(WM_SYSCOMMAND,0xF012,0);   
    //SendMessage(WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));   
	CDialog::OnLButtonDown(nFlags, point);
}

void CAfoatWindowMessageDlg::SetupRegion(
    CDC *pDC, //DC of this window
    CBitmap &cBitmap, 
    COLORREF TransColor //the color need remove
    )
{    CDC memDC;
    //temporary DC
    memDC.CreateCompatibleDC(pDC);

    CBitmap *pOldMemBmp=NULL;
    //Load bmp file
    pOldMemBmp=memDC.SelectObject(&cBitmap);
   
    CRgn wndRgn; // window region
    //window region init
    wndRgn.CreateRectRgn(0,0,0,0);
 
    BITMAP bit;   
    cBitmap.GetBitmap (&bit);//get the value of bmp file    
   
    int y;
    for(y=0;y<=bit.bmHeight  ;y++)
    {
	    CRgn rgnTemp; //temporary region            
        int iX = 0;
        do
        {
            //skip TransColor
            while (iX <= bit.bmWidth  && memDC.GetPixel(iX, y) == TransColor)
                iX++;

            //record this point
            int iLeftX = iX;

            //Skip none transColor
            while (iX <= bit.bmWidth  && memDC.GetPixel(iX, y) != TransColor)
                ++iX;

            //create temporary “region?
            rgnTemp.CreateRectRgn(iLeftX, y, iX, y+1);

            //combine "region".
            wndRgn.CombineRgn(&wndRgn, &rgnTemp, RGN_OR);
                
		    //delete temporary "region"
            rgnTemp.DeleteObject();
        }while(iX <bit.bmWidth );
        iX = 0;
    }

    if(pOldMemBmp)
        memDC.SelectObject(pOldMemBmp);
    
    CWnd * pWnd = pDC->GetWindow();
    pWnd->SetWindowRgn(wndRgn,TRUE);    
    pWnd->SetForegroundWindow();    
}
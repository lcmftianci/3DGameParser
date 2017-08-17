// MsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QQDemo.h"
#include "MsgDlg.h"
#include "afxdialogex.h"


// CMsgDlg dialog

IMPLEMENT_DYNAMIC(CMsgDlg, CDialogEx)

CMsgDlg::CMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_MSG, pParent)
{

}

CMsgDlg::~CMsgDlg()
{
}

void CMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMsgDlg, CDialogEx)
END_MESSAGE_MAP()


// CMsgDlg message handlers

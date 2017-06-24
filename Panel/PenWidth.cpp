// PenWidth.cpp : implementation file
//

#include "stdafx.h"
#include "Panel.h"
#include "PenWidth.h"
#include "afxdialogex.h"


// CPenWidth dialog

IMPLEMENT_DYNAMIC(CPenWidth, CDialogEx)

CPenWidth::CPenWidth(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PEN_WIDTH, pParent)
{

}

CPenWidth::~CPenWidth()
{
}

void CPenWidth::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPenWidth, CDialogEx)
END_MESSAGE_MAP()


// CPenWidth message handlers

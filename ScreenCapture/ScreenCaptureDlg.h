
// ScreenCaptureDlg.h : header file
//

#pragma once
#include "ScreenUtil.h"
#include <dshow.h>
#pragma comment (lib,"Strmiids")
#pragma comment (lib,"quartz")
#include <uuids.h>
#include <strmif.h>


// CScreenCaptureDlg dialog
class CScreenCaptureDlg : public CDialogEx
{
// Construction
public:
	CScreenCaptureDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREENCAPTURE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CMenu m_Menu;
	CaptureData m_CapData;

private:
	CImage	m_image;
public:
	void SetImage(const CString &strPath);


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCap();
	afx_msg void OnFull();
	afx_msg void OnCapvideo();

// 	void AVItoBmp(CString strAVIFileName, CString   strBmpDir);
// 	void BMPtoAVI(CString szAVIName, CString strBmpDir);

public://将图片压缩成AVI
	LRESULT OnGraphNotify(WPARAM wParam, LPARAM lParam);

	IMediaControl     *pMediaControl;         //媒体控制
	IGraphBuilder     *pGraph;                  //过滤图表
	IBaseFilter       *pSrc, *pPreview, *pCompress, *pMux;         //过滤器
	IMoniker          *pMoniker;                 //监视器

	IMediaEventEx     *pEvent;
	IMediaSeeking     *pSeek;

	BOOL              m_Completed;             //压缩是否完成
	BOOL              m_IsCompressing;         //压缩是否正在进行
	REFERENCE_TIME    m_TotalTime;             //压缩总时间

	CString decodeName;							//编解码器名称

												//获取编码器列表
	void GetDecodeList();

	//指定视频编码器的友好名字，为它创建一个Filter
	static IBaseFilter * CreateDecodeDevice(GUID inCategory, const char * inFriendlyName);

	//根据设备的友好名字，创建一个代表该设备的Filter
	static IBaseFilter * CreateHardwareFilter(GUID inCategory, const char * inFriendlyName);



	//查找Pin
	IPin* FindPin(IBaseFilter *pFilter, PIN_DIRECTION dir);

	CStatic	m_Progress;
	CEdit	m_SourceFile;
	CEdit	m_DesFile;
	CComboBox	m_combodecode;

	afx_msg void OnSelchangeCombo();
	afx_msg void OnSourcebrown();
	afx_msg void OnDesbrown();
	afx_msg void OnStartcompress();

	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancle();

	int CompressVideo();
};

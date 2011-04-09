// contour_track_01Dlg.h : 头文件
//

#pragma once
#include "contour_track.h"

// Ccontour_track_01Dlg 对话框
class Ccontour_track_01Dlg : public CDialog
{
// 构造
public:
	Ccontour_track_01Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CONTOUR_TRACK_01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:

	contr::contour_track ac;
	
	contr::contour_track::iso_lines_type lines;
	
public:
	afx_msg void OnBnClickedButton1();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

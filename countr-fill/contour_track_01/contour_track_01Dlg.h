// contour_track_01Dlg.h : ͷ�ļ�
//

#pragma once
#include "contour_track.h"

// Ccontour_track_01Dlg �Ի���
class Ccontour_track_01Dlg : public CDialog
{
// ����
public:
	Ccontour_track_01Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CONTOUR_TRACK_01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

// MessAtoBDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <string>

using std::vector;using std::string;


// CMessAtoBDlg �Ի���
class CMessAtoBDlg : public CDialog
{
// ����
public:
	CMessAtoBDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MESSATOB_DIALOG };

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
public:
	afx_msg void OnBnClickedChe();
	// �ı��ļ�����
	CEdit m_text;
//	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();

	//����ά��

	vector<vector<string>  > weth;
	vector<vector<double>  > teph;
	const int wht;
	string fhead,fstr;



	afx_msg void OnBnClickedButton1();
//	afx_msg void OnEnChangeEdit1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

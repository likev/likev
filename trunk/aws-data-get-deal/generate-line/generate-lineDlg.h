// generate-lineDlg.h : ͷ�ļ�
//

#pragma once


// CgeneratelineDlg �Ի���
class CgeneratelineDlg : public CDialog
{
// ����
public:
	CgeneratelineDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GENERATELINE_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	int ShowMinMaxTemph(int hour);
	afx_msg void OnBnClickedButtonMeteorStatisA();
	afx_msg void OnBnClickedButton7();
	// �ۼƽ�ˮ����ѯ
	int AccumRainfall(int hour);
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButtonMeteorStatisB();
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
};

// AutoGetAwsFileDlg.h : ͷ�ļ�
//

#pragma once


// CAutoGetAwsFileDlg �Ի���
class CAutoGetAwsFileDlg : public CDialog
{
// ����
public:
	CAutoGetAwsFileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUTOGETAWSFILE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CTime last_time, current_time;
	CString savepath;
public:
	// �������е�״̬
	CString ProgramState;
	//������ͼ����Ϣ
	NOTIFYICONDATA nid;
	// ���ص�������
	void HideToTray(void);

	//��������ʱ���ļ�
	bool GetFtpFile();

	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam); 
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// ���ó���״̬��ˢ��
	void SetProgramState(CString state);
	// �������ļ���ȡ�ϴζ�ȡ�ļ�ʱ��
	void GetLastReadTime(void);
	// ���ö�ȡʱ��
	void SetLastReadTime(CTime last_time);
	// �����Զ�����
	void AutoRunAfterStart(void);
	// ��172.18.172.6���������ļ�
	bool GetFilesFromWeb(void);
};

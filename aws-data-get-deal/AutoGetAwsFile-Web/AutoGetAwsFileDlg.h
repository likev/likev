// AutoGetAwsFileDlg.h : 头文件
//

#pragma once


// CAutoGetAwsFileDlg 对话框
class CAutoGetAwsFileDlg : public CDialog
{
// 构造
public:
	CAutoGetAwsFileDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AUTOGETAWSFILE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CTime last_time, current_time;
	CString savepath;
public:
	// 程序运行的状态
	CString ProgramState;
	//任务栏图标信息
	NOTIFYICONDATA nid;
	// 隐藏到任务栏
	void HideToTray(void);

	//下载最新时次文件
	bool GetFtpFile();

	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam); 
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// 设置程序状态并刷新
	void SetProgramState(CString state);
	// 从配置文件读取上次读取文件时间
	void GetLastReadTime(void);
	// 设置读取时间
	void SetLastReadTime(CTime last_time);
	// 开机自动运行
	void AutoRunAfterStart(void);
	// 从172.18.172.6上面下载文件
	bool GetFilesFromWeb(void);
};

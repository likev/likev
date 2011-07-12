// MessAtoBDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <string>
#include "Sglf.h"

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

	//վ����Ϣ
	std::vector<std::string> station_names;

	//����ת��Ϊ����Ԥ��
	afx_msg void OnBnClickedChe();
	// �ı��ļ�����
	CEdit m_text;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();

	enum ForcastType{SMALLHOURS,MORNING,AM12121,AFTERNOON};
	//����ά��

	std::vector<std::vector<std::string>  > all_weather_str;
	std::vector<std::vector<double>  > all_temph_value;
	ForcastType forcast_type;
	std::string fhead,fstr;

	ForcastType GetForcastType();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	bool FtpDownCzbFile();
	bool is_czb_down_success;

	//�������ݲ�����
	std::vector<Sglf> station_forcasts;
	bool read_trans_data();
	void begin_head(std::string &fhead);
	std::string generate121str();
	std::string generate_forcast_str();
	
	//���24Сʱ����״�����������¶�
	void output_weather(std::stringstream & fout, int n=0);

	//��ȡ��ҩ����
	int GetPYGrade(const Sglf &station_forcast);
	afx_msg void OnBnClickedGeneratePy();
	afx_msg void OnBnClickedButtonSelfforcast();
	// ��ȡ��ǰʱ�γ��򱨵��ļ���
	std::string GetFtpFilename(void);
	afx_msg void OnBnClickedButtonShortforcast();
};

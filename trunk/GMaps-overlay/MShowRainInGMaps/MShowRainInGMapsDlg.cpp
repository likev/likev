// MShowRainInGMapsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MShowRainInGMaps.h"
#include "MShowRainInGMapsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_SHOWTASK (WM_USER + 1000)

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMShowRainInGMapsDlg �Ի���



CMShowRainInGMapsDlg::CMShowRainInGMapsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMShowRainInGMapsDlg::IDD, pParent)
	, interval(2)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	
	end_day = end_time = CTime::GetCurrentTime();
	begin_day = begin_time = end_day - CTimeSpan(1,0,0,0);

	status_info = "�ȴ���ȡ��ҳ";
	server = "172.18.152.239";
	url = "./HNAWS/RTinfo/rtdatadisp.asp?CityFlag=HNLY&CityName=%C2%E5%D1%F4%CA%D0&Top_X=110.9882&Top_Y=35.1468&Bot_X=113.0480&Bot_Y=33.5470";
}

void CMShowRainInGMapsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BeginDay, begin_day);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_EndDay, end_day);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BeginTime, begin_time);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_EndTime, end_time);
	DDX_Text(pDX, IDC_EDIT_Interval, interval);
	DDX_Control(pDX, IDC_SPIN1, spin_interval);
	DDX_Text(pDX, IDC_EDIT_Status, status_info);
	DDV_MinMaxInt(pDX, interval, 1, 90);
}

BEGIN_MESSAGE_MAP(CMShowRainInGMapsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
//	ON_BN_CLICKED(IDC_RADIO4, &CMShowRainInGMapsDlg::OnBnClickedRadio4)
ON_BN_CLICKED(IDC_RADIO_RealRain, &CMShowRainInGMapsDlg::OnBnClickedRadioRealrain)
ON_BN_CLICKED(IDC_RADIO_HistoryRain, &CMShowRainInGMapsDlg::OnBnClickedRadioHistoryrain)
ON_BN_CLICKED(IDC_RADIO_InnerNet, &CMShowRainInGMapsDlg::OnBnClickedRadioInnernet)
ON_BN_CLICKED(IDC_RADIO_OutSideNet, &CMShowRainInGMapsDlg::OnBnClickedRadioOutsidenet)
ON_BN_CLICKED(IDC_BUTTON_Search, &CMShowRainInGMapsDlg::OnBnClickedButtonSearch)
ON_WM_VSCROLL()
ON_WM_TIMER()
END_MESSAGE_MAP()


// CMShowRainInGMapsDlg ��Ϣ�������

BOOL CMShowRainInGMapsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	spin_interval.SetBuddy(GetDlgItem(IDC_EDIT_Interval));
	spin_interval.SetRange(1,90);
	spin_interval.SetPos(2);

	CheckRadioButton(IDC_RADIO_RealRain,IDC_RADIO_HistoryRain,IDC_RADIO_RealRain);
	CheckRadioButton(IDC_RADIO_InnerNet,IDC_RADIO_OutSideNet,IDC_RADIO_InnerNet);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMShowRainInGMapsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ( (nID == SC_MINIMIZE) || (nID == SC_CLOSE)) 
	{ 
		 HideToTray();
		 ShowWindow(SW_HIDE); //����������
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}

}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMShowRainInGMapsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMShowRainInGMapsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���ص�������
void CMShowRainInGMapsDlg::HideToTray(void)
{
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage=WM_SHOWTASK;//�Զ������Ϣ���� 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy_s(nid.szTip,"Google Maps����ʾGPRS����"); //��Ϣ��ʾ�� 
	Shell_NotifyIcon(NIM_ADD,&nid); //�����������ͼ�� 
}

LRESULT CMShowRainInGMapsDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
//wParam���յ���ͼ���ID����lParam���յ���������Ϊ 
{ 
	if(wParam!=IDR_MAINFRAME) 
		return 1; 
	switch(lParam) 
	{ 
	case WM_RBUTTONUP://�Ҽ�����ʱ������ݲ˵�������ֻ��һ�����رա� 
		{ 

			LPPOINT lpoint=new tagPOINT; 
			::GetCursorPos(lpoint);//�õ����λ�� 
			CMenu menu; 
			menu.CreatePopupMenu();//����һ������ʽ�˵� 
			//���Ӳ˵���رա������������ϢWM_DESTROY�������ڣ��� 
			//���أ�������������� 
			menu.AppendMenu(MF_STRING,WM_DESTROY," �˳� "); 
			//ȷ������ʽ�˵���λ�� 
			menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); 
			
			//��Դ���� 
			HMENU hmenu=menu.Detach(); 
			menu.DestroyMenu(); 
			delete lpoint; 
		} 
		break; 
	case WM_LBUTTONDBLCLK://˫������Ĵ��� 
		{ 
			ShowWindow(SW_SHOWNORMAL);//�򵥵���ʾ���������¶� 
		} 
		break; 
	} 
	return 0; 
}


void CMShowRainInGMapsDlg::OnBnClickedRadioRealrain()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	is_real_rain = true;
	ChangeViewType();
}

void CMShowRainInGMapsDlg::OnBnClickedRadioHistoryrain()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	is_real_rain = false;
	ChangeViewType();
}

void CMShowRainInGMapsDlg::OnBnClickedRadioInnernet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	net_type = 0;
	ChangeNetType();
}

void CMShowRainInGMapsDlg::OnBnClickedRadioOutsidenet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	net_type = 1;
	ChangeNetType();
}

void CMShowRainInGMapsDlg::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if(!is_real_rain)
	{
		CString str_begin_day = begin_day.Format("%Y-%#m-%#d"),
			    str_end_day = end_day.Format("%Y-%#m-%#d"),
				str_begin_time = begin_time.Format("%H:%M"),
				str_end_time = end_time.Format("%H:%M");
		url = "./simpleversion/infodisplay.asp?Cityflag=HNLY&InfoT=historical&DispT=intable&StartT="
			+str_begin_day+"%20"+str_begin_time+"&EndT="+str_end_day+"%20"+str_end_time;

		//MessageBox(url.c_str());
	}
	
	UpdateRainValue();
	//�������...
	ShellExecute(NULL,"open","rain-overlay.html",NULL,NULL,SW_SHOW);
	
	if(is_real_rain)
	{
		SetTimer(1,interval*60*1000,NULL);//�������к�5���������ʱ��
	}
}

void CMShowRainInGMapsDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMShowRainInGMapsDlg::ChangeViewType()
{
	bool is_able = !is_real_rain;

	GetDlgItem(IDC_DATETIMEPICKER_BeginDay)->EnableWindow(is_able);
	GetDlgItem(IDC_DATETIMEPICKER_EndDay)->EnableWindow(is_able);
	GetDlgItem(IDC_DATETIMEPICKER_BeginTime)->EnableWindow(is_able);
	GetDlgItem(IDC_DATETIMEPICKER_EndTime)->EnableWindow(is_able);

	if(is_real_rain)
	{
		url = "./HNAWS/RTinfo/rtdatadisp.asp?CityFlag=HNLY&CityName=%C2%E5%D1%F4%CA%D0&Top_X=110.9882&Top_Y=35.1468&Bot_X=113.0480&Bot_Y=33.5470";
	}

}

void CMShowRainInGMapsDlg::ChangeNetType()
{
	if(net_type == 0)
	{
		server = "172.18.152.239";
	}
	else if(net_type == 1)
	{
		server = "www.hnaws.com";
	}
	else
	{}
}

void CMShowRainInGMapsDlg::UpdateRainValue()
{
	status_info = "���ڶ�ȡ��ҳ...";
	UpdateData(FALSE);
	records.get_web_content(server,url);
	
	status_info = "���ڸ�������...";
	UpdateData(FALSE);
	records.update_js_file("script/rain-datas.js",is_real_rain);

	status_info = "���¶�ȡʱ�䣺"+CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S");
	UpdateData(FALSE);
}

void CMShowRainInGMapsDlg::OnTimer(UINT_PTR nIDEvent)
{
	//��ʱ��1
	if(nIDEvent == 1)
	{
		KillTimer(nIDEvent);

		UpdateRainValue();

		//if(is_real_rain)
		//{ ����������ʽ ������ʾ08ʱ������ʱ�̵�����
			SetTimer(1,interval*60*1000,NULL);//����������ʱ��
		//}
	}

	CDialog::OnTimer(nIDEvent);
}
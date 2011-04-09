// DisasterWatchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DisasterWatch.h"
#include "DisasterWatchDlg.h"
#include "string-trans.h"
#include "UsefulFunction.h"
#include <atlbase.h>

extern volatile bool close_alert;

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


// CDisasterWatchDlg �Ի���




CDisasterWatchDlg::CDisasterWatchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDisasterWatchDlg::IDD, pParent)
	, auto_alert(TRUE)
	, auto_send_message(TRUE)
	, interval(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	char numbers_buf[1024] ;
	DWORD result = GetPrivateProfileString("stations","numbers",NULL,numbers_buf,1000,"./dwsetup.ini");
	std::string stations_str = numbers_buf;

	GetPrivateProfileString("alert","send_message_mobile_phone",NULL,numbers_buf,1000,"./dwsetup.ini");
	std::string mobile_phone_str = numbers_buf;

	str_split(stations_str, " ", all_stations);
	
	str_split(mobile_phone_str, " ", all_mobile_phone);

}

void CDisasterWatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_ALERT, auto_alert);
	DDX_Check(pDX, IDC_CHECK_SEND_MESSAGE, auto_send_message);
	DDX_Control(pDX, IDC_DISASTER_VIEW, disa_view);
}

BEGIN_MESSAGE_MAP(CDisasterWatchDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_ALERT, &CDisasterWatchDlg::OnBnClickedCheckAlert)
	ON_BN_CLICKED(IDC_CHECK_SEND_MESSAGE, &CDisasterWatchDlg::OnBnClickedCheckSendMessage)
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
END_MESSAGE_MAP()


// CDisasterWatchDlg ��Ϣ�������

BOOL CDisasterWatchDlg::OnInitDialog()
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

	AutoRunAfterStart();

	//��ʾ��Ϣ
	disa_view.SetWindowTextA("���ڼ�����ҳ");

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetTimer(1,5*1000,NULL);//�������к�5���������ʱ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDisasterWatchDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDisasterWatchDlg::OnPaint()
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
HCURSOR CDisasterWatchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDisasterWatchDlg::OnBnClickedCheckAlert()
{
	// ��������
	UpdateData(TRUE);
	
}

void CDisasterWatchDlg::OnBnClickedCheckSendMessage()
{
	// ��������
	UpdateData(TRUE);
}

void CDisasterWatchDlg::OnTimer(UINT_PTR nIDEvent)
{
	//��ʱ��1
	if(nIDEvent == 1)
	{
		KillTimer(nIDEvent);

		BeginAllProc();
		

		interval = GetPrivateProfileInt("alert","interval",10,"./dwsetup.ini");
		
		
		SetTimer(1,interval*1000*60,NULL);// ʱ�䲻��̫�� ������SetLastReadTime()��ûִ�����
	}

	CDialog::OnTimer(nIDEvent);
}

//��������ʼ
void CDisasterWatchDlg::BeginAllProc()
{
	//http://172.18.152.124/dzsp/index.php?action=DisasterInfo_listbak
	bool is_download = DownloadHttpPage("172.18.152.124","/dzsp/index.php?action=DisasterInfo_listbak","DisasterInfo_listbak");

	if(is_download) CheckNewDisaster();

	CTime curtime = CTime::GetCurrentTime();
	viewtext.Format("���¶�ȡʱ�䣺%s\r\n %d ���Ӻ����¶�ȡ",curtime.Format("%Y-%m-%d %H:%M:%S"), interval);
	disa_view.SetWindowTextA(viewtext);Sleep(1000);
}

//�����������ID
bool CDisasterWatchDlg::CheckNewDisaster()
{
	disa_view.SetWindowText("��ȡ���������ļ�");UpdateData(FALSE);Sleep(2000);
	//MessageBox("good");
	

	char str_buf[100];
	DWORD result = GetPrivateProfileString("alert","last_disaster_id","201004271712570730007002",str_buf,100,"./dwsetup.ini");
	last_disaster_id = str_buf;

	std::string listbak_content;
	filetostr("DisasterInfo_listbak",listbak_content,600);

	size_t last_pos=listbak_content.npos;

	bool have_new_disaster=false;
	while(  (last_pos=listbak_content.rfind("DisasterInfo_viewbak",last_pos))
		  != listbak_content.npos)
	{
		size_t id_pos = listbak_content.find("ID",last_pos);
		std::string IDstr = listbak_content.substr(id_pos+3,24);

		if(IDstr > last_disaster_id)
		{
			bool is_in_region = false;

			for(std::vector<std::string>::iterator it=all_stations.begin();
				it != all_stations.end(); it++)
			{
				if(*it == IDstr.substr(12,5) )
				{
					is_in_region = true;
					break;
				}
			}


			if(is_in_region)
			{
				disa_view.SetWindowTextA("��⵽�µ�����");Sleep(1000);

				have_new_disaster = true;
				last_disaster_id = IDstr;
				WritePrivateProfileString("alert","last_disaster_id",IDstr.c_str(),"./dwsetup.ini");

				disa_view.SetWindowTextA("��ȡ������ϸ��Ϣ");Sleep(1000);
				ReadNewDisaster();
			}

		}

		last_pos--;
	}

	return have_new_disaster;
}

void CDisasterWatchDlg::ReadNewDisaster()
{
	//http://172.18.152.124/dzsp/index.php?action=DisasterInfo_viewbak&ID=201005051329571873005013
	std::string url = "/dzsp/index.php?action=DisasterInfo_viewbak&ID="+last_disaster_id;
	bool is_download = DownloadHttpPage("172.18.152.124",url.c_str(),"DisasterInfo_viewbak");
	
	Sleep(2000);
	if(!is_download) return;

	//������Ϣ��
	DisasterInfo disa_info;
	disa_info.init("DisasterInfo_viewbak");	
	
	//�Զ����Ͷ���
	if(auto_send_message)
	{
		disa_view.SetWindowTextA("��ʼ���Ͷ���");Sleep(1000);
		for(std::vector<std::string>::iterator it=all_mobile_phone.begin();
			it != all_mobile_phone.end(); it++)
		{
			std::string disaster_sms=disa_info.to_sms();
			send_short_message(disaster_sms,*it);
		}
	}
	
	//��ʾ����
	disa_view.SetWindowTextA(disa_info.to_text().c_str());
	
	//�Զ�����
	if(auto_alert)
	{
		close_alert = false;
		AfxBeginThread(MyThreadProc,NULL);
		if(MessageBox(last_disaster_id.c_str(),"�µ�����",MB_OK)==IDOK)
		{
			close_alert = true;
		}
	}

}

// �����Զ�����
void CDisasterWatchDlg::AutoRunAfterStart(void)
{
	char AppName[MAX_PATH];
	GetModuleFileName(NULL,AppName,MAX_PATH);


	CString skey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

	CRegKey writevalue;
	writevalue.Create(HKEY_LOCAL_MACHINE,skey);
	int error = writevalue.SetStringValue("DisasWatch",AppName);
	writevalue.Close();
}

// ���ص�������
void CDisasterWatchDlg::HideToTray(void)
{
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage=WM_SHOWTASK;//�Զ������Ϣ���� 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy_s(nid.szTip,"�Զ��������ֱ����ҳ"); //��Ϣ��ʾ��Ϊ���ƻ��������ѡ� 
	Shell_NotifyIcon(NIM_ADD,&nid); //�����������ͼ�� 
}

LRESULT CDisasterWatchDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
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
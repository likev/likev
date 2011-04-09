// DisasterWatchDlg.cpp : 实现文件
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
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDisasterWatchDlg 对话框




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


// CDisasterWatchDlg 消息处理程序

BOOL CDisasterWatchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	AutoRunAfterStart();

	//显示信息
	disa_view.SetWindowTextA("正在监视网页");

	// TODO: 在此添加额外的初始化代码
	SetTimer(1,5*1000,NULL);//程序运行后5秒后启动定时器

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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
		 ShowWindow(SW_HIDE); //隐藏主窗口
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDisasterWatchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDisasterWatchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDisasterWatchDlg::OnBnClickedCheckAlert()
{
	// 更新数据
	UpdateData(TRUE);
	
}

void CDisasterWatchDlg::OnBnClickedCheckSendMessage()
{
	// 更新数据
	UpdateData(TRUE);
}

void CDisasterWatchDlg::OnTimer(UINT_PTR nIDEvent)
{
	//定时器1
	if(nIDEvent == 1)
	{
		KillTimer(nIDEvent);

		BeginAllProc();
		

		interval = GetPrivateProfileInt("alert","interval",10,"./dwsetup.ini");
		
		
		SetTimer(1,interval*1000*60,NULL);// 时间不能太短 否则函数SetLastReadTime()还没执行完毕
	}

	CDialog::OnTimer(nIDEvent);
}

//处理函数起始
void CDisasterWatchDlg::BeginAllProc()
{
	//http://172.18.152.124/dzsp/index.php?action=DisasterInfo_listbak
	bool is_download = DownloadHttpPage("172.18.152.124","/dzsp/index.php?action=DisasterInfo_listbak","DisasterInfo_listbak");

	if(is_download) CheckNewDisaster();

	CTime curtime = CTime::GetCurrentTime();
	viewtext.Format("最新读取时间：%s\r\n %d 分钟后重新读取",curtime.Format("%Y-%m-%d %H:%M:%S"), interval);
	disa_view.SetWindowTextA(viewtext);Sleep(1000);
}

//返回新灾情的ID
bool CDisasterWatchDlg::CheckNewDisaster()
{
	disa_view.SetWindowText("读取最新灾情文件");UpdateData(FALSE);Sleep(2000);
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
				disa_view.SetWindowTextA("监测到新的灾情");Sleep(1000);

				have_new_disaster = true;
				last_disaster_id = IDstr;
				WritePrivateProfileString("alert","last_disaster_id",IDstr.c_str(),"./dwsetup.ini");

				disa_view.SetWindowTextA("读取灾情详细信息");Sleep(1000);
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

	//灾情信息类
	DisasterInfo disa_info;
	disa_info.init("DisasterInfo_viewbak");	
	
	//自动发送短信
	if(auto_send_message)
	{
		disa_view.SetWindowTextA("开始发送短信");Sleep(1000);
		for(std::vector<std::string>::iterator it=all_mobile_phone.begin();
			it != all_mobile_phone.end(); it++)
		{
			std::string disaster_sms=disa_info.to_sms();
			send_short_message(disaster_sms,*it);
		}
	}
	
	//显示灾情
	disa_view.SetWindowTextA(disa_info.to_text().c_str());
	
	//自动报警
	if(auto_alert)
	{
		close_alert = false;
		AfxBeginThread(MyThreadProc,NULL);
		if(MessageBox(last_disaster_id.c_str(),"新的灾情",MB_OK)==IDOK)
		{
			close_alert = true;
		}
	}

}

// 开机自动运行
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

// 隐藏到任务栏
void CDisasterWatchDlg::HideToTray(void)
{
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage=WM_SHOWTASK;//自定义的消息名称 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy_s(nid.szTip,"自动监测灾情直报网页"); //信息提示条为“计划任务提醒” 
	Shell_NotifyIcon(NIM_ADD,&nid); //在托盘区添加图标 
}

LRESULT CDisasterWatchDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
//wParam接收的是图标的ID，而lParam接收的是鼠标的行为 
{ 
	if(wParam!=IDR_MAINFRAME) 
		return 1; 
	switch(lParam) 
	{ 
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭” 
		{ 

			LPPOINT lpoint=new tagPOINT; 
			::GetCursorPos(lpoint);//得到鼠标位置 
			CMenu menu; 
			menu.CreatePopupMenu();//声明一个弹出式菜单 
			//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已 
			//隐藏），将程序结束。 
			menu.AppendMenu(MF_STRING,WM_DESTROY," 退出 "); 
			//确定弹出式菜单的位置 
			menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); 
			
			//资源回收 
			HMENU hmenu=menu.Detach(); 
			menu.DestroyMenu(); 
			delete lpoint; 
		} 
		break; 
	case WM_LBUTTONDBLCLK://双击左键的处理 
		{ 
			ShowWindow(SW_SHOWNORMAL);//简单的显示主窗口完事儿 
		} 
		break; 
	} 
	return 0; 
}
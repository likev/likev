// MShowRainInGMapsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MShowRainInGMaps.h"
#include "MShowRainInGMapsDlg.h"

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


// CMShowRainInGMapsDlg 对话框



CMShowRainInGMapsDlg::CMShowRainInGMapsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMShowRainInGMapsDlg::IDD, pParent)
	, interval(2)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	
	end_day = end_time = CTime::GetCurrentTime();
	begin_day = begin_time = end_day - CTimeSpan(1,0,0,0);

	status_info = "等待读取网页";
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


// CMShowRainInGMapsDlg 消息处理程序

BOOL CMShowRainInGMapsDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	spin_interval.SetBuddy(GetDlgItem(IDC_EDIT_Interval));
	spin_interval.SetRange(1,90);
	spin_interval.SetPos(2);

	CheckRadioButton(IDC_RADIO_RealRain,IDC_RADIO_HistoryRain,IDC_RADIO_RealRain);
	CheckRadioButton(IDC_RADIO_InnerNet,IDC_RADIO_OutSideNet,IDC_RADIO_InnerNet);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

void CMShowRainInGMapsDlg::OnPaint()
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
HCURSOR CMShowRainInGMapsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 隐藏到任务栏
void CMShowRainInGMapsDlg::HideToTray(void)
{
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage=WM_SHOWTASK;//自定义的消息名称 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy_s(nid.szTip,"Google Maps中显示GPRS雨量"); //信息提示条 
	Shell_NotifyIcon(NIM_ADD,&nid); //在托盘区添加图标 
}

LRESULT CMShowRainInGMapsDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
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


void CMShowRainInGMapsDlg::OnBnClickedRadioRealrain()
{
	// TODO: 在此添加控件通知处理程序代码
	is_real_rain = true;
	ChangeViewType();
}

void CMShowRainInGMapsDlg::OnBnClickedRadioHistoryrain()
{
	// TODO: 在此添加控件通知处理程序代码
	is_real_rain = false;
	ChangeViewType();
}

void CMShowRainInGMapsDlg::OnBnClickedRadioInnernet()
{
	// TODO: 在此添加控件通知处理程序代码
	net_type = 0;
	ChangeNetType();
}

void CMShowRainInGMapsDlg::OnBnClickedRadioOutsidenet()
{
	// TODO: 在此添加控件通知处理程序代码
	net_type = 1;
	ChangeNetType();
}

void CMShowRainInGMapsDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//打开浏览器...
	ShellExecute(NULL,"open","rain-overlay.html",NULL,NULL,SW_SHOW);
	
	if(is_real_rain)
	{
		SetTimer(1,interval*60*1000,NULL);//程序运行后5秒后启动定时器
	}
}

void CMShowRainInGMapsDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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
	status_info = "正在读取网页...";
	UpdateData(FALSE);
	records.get_web_content(server,url);
	
	status_info = "正在更新数据...";
	UpdateData(FALSE);
	records.update_js_file("script/rain-datas.js",is_real_rain);

	status_info = "最新读取时间："+CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S");
	UpdateData(FALSE);
}

void CMShowRainInGMapsDlg::OnTimer(UINT_PTR nIDEvent)
{
	//定时器1
	if(nIDEvent == 1)
	{
		KillTimer(nIDEvent);

		UpdateRainValue();

		//if(is_real_rain)
		//{ 利用搜索方式 可以显示08时至最新时刻的雨量
			SetTimer(1,interval*60*1000,NULL);//重新启动定时器
		//}
	}

	CDialog::OnTimer(nIDEvent);
}
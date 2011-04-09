// AutoGetAwsFileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoGetAwsFile.h"
#include "AutoGetAwsFileDlg.h"
#include "http-deal.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoGetAwsFileDlg 对话框


#define WM_SHOWTASK (WM_USER + 1000)

CAutoGetAwsFileDlg::CAutoGetAwsFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoGetAwsFileDlg::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	GetLastReadTime();
	ProgramState = "程序将从网络下载最新文件...\n"+last_time.Format("最近读取时次：%Y-%m-%d %H时");
}

void CAutoGetAwsFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROGRAM_STATE, ProgramState);
}

BEGIN_MESSAGE_MAP(CAutoGetAwsFileDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAutoGetAwsFileDlg 消息处理程序

BOOL CAutoGetAwsFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	HideToTray();
	//ShowWindow(SW_HIDE);
	
	AutoRunAfterStart();

	SetProgramState("begin set timer");
	SetTimer(1,5*1000,NULL);//程序运行后5秒后启动定时器

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAutoGetAwsFileDlg::OnPaint()
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
HCURSOR CAutoGetAwsFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 隐藏到任务栏
void CAutoGetAwsFileDlg::HideToTray(void)
{
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage=WM_SHOWTASK;//自定义的消息名称 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy_s(nid.szTip,"自动获取自动站资料"); //信息提示条 
	Shell_NotifyIcon(NIM_ADD,&nid); //在托盘区添加图标 
}

void CAutoGetAwsFileDlg::OnDestroy()
{
	Shell_NotifyIcon(NIM_DELETE, &nid);

	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void CAutoGetAwsFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ( (nID == SC_MINIMIZE) || (nID == SC_CLOSE)) 
	{ 
		 HideToTray();
		 ShowWindow(SW_HIDE); //隐藏主窗口
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

LRESULT CAutoGetAwsFileDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
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

//bool GetFtpFile(CTime current_time);
void InsertIntoMysql()
{
	char buf[10];
	GetPrivateProfileString("database","auto-insert-into-mysql","false",buf,10,"./setup.ini");
	
	if(CString(buf).MakeLower() == "true")
	{
		char path_buf[1000], name_buf[1000];
		GetPrivateProfileString("database","program-path",".\\",path_buf,1000,"./setup.ini");
		GetPrivateProfileString("database","program-name","InsertIntoMysql.exe",name_buf,1000,"./setup.ini");

		CString filepath = path_buf, filename = name_buf;
		//执行
		PROCESS_INFORMATION proif;
		STARTUPINFO stif = {sizeof(stif)};

		BOOL res = ::CreateProcess(NULL,(filepath+filename).GetBuffer(),NULL,NULL,FALSE,0,NULL,filepath,&stif,&proif);
	}
}

void CAutoGetAwsFileDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		KillTimer(nIDEvent);
		SetProgramState("begin timer.");

		GetLastReadTime();

		int cur_minute = CTime::GetCurrentTime().GetMinute();
		if(cur_minute>11 && cur_minute<15)
		{
			
			if(GetFilesFromWeb())
			{
				SetProgramState("begin insert to mysql...");
				InsertIntoMysql();
				SetLastReadTime(last_time);
			}
		}
		
		SetProgramState("程序将自动从网络下载最新文件...\n"+last_time.Format("最近读取时次：%Y-%m-%d %H时"));

		SetTimer(1,3*1000*60,NULL);// 时间不能太短 否则函数SetLastReadTime()还没执行完毕
	}

	CDialog::OnTimer(nIDEvent);
}

bool CAutoGetAwsFileDlg::GetFtpFile()
{
	bool isdownload=false;

	try
	{
		CInternetSession sess("My FTP Session");

		SetProgramState("正在登陆服务器...");
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.172.155","lyqxt","lyqxt");//登录
		
		SetProgramState("成功登陆,正在查找文件...");

		pConnect->SetCurrentDirectory("/aws");

		CFtpFileFind finder(pConnect);
		// start looping		 
		
		BOOL working = finder.FindFile("*");

		while(working)
		{
			working = finder.FindNextFileA();
			CString filename=finder.GetFileName();

			CTime LastAccessTime,LastWriteTime,CreationTime;
			//finder.GetLastAccessTime(LastAccessTime); 不能读取
			finder.GetLastWriteTime(LastWriteTime); //最后修改时间
			//finder.GetCreationTime(CreationTime); 不能读取

			CString TimeStr = LastAccessTime.Format("%Y-%m-%d %H:%M:%S")+LastWriteTime.Format("\n%Y-%m-%d %H:%M:%S")+CreationTime.Format("\n%Y-%m-%d %H:%M:%S");
			//MessageBox(TimeStr);

			if(LastWriteTime > this->last_time)
			{
				SetProgramState("找到文件 "+filename+", 开始尝试下载");

				if(pConnect->GetFile(filename,this->savepath+filename,FALSE))
				{
					SetProgramState("下载文件 "+filename+ "成功!");
					last_time = LastWriteTime;
					isdownload = true;
				}
			}
		}

		if (pConnect != NULL) 
		{
			pConnect->Close();
			delete pConnect;
		}

		//cout<<"本次监测结束 将在10分钟后重新登录Ftp服务器查看"<<endl;
	}
	catch (CInternetException* pEx)
	{
		char error[1025];
		pEx->GetErrorMessage(error, 1024);

		SetProgramState("出现错误:"+CString(error));
		//cout<<"ERROR!"<<error<<endl;
		pEx->Delete();
		return false;
	}

	return isdownload ;
}

// 设置程序状态并刷新
void CAutoGetAwsFileDlg::SetProgramState(CString state)
{
	ProgramState = state;
	UpdateData(FALSE);
}

// 从配置文件读取上次读取文件时间
void CAutoGetAwsFileDlg::GetLastReadTime(void)
{
	char filepath[1024];
	DWORD result = GetPrivateProfileString("file","savepath",NULL,filepath,1000,"./setup.ini");

	if(result)
	{
		savepath = filepath;
	}
	else
	{
		CreateDirectory("aws-files",NULL);
		//此函数自动创建文件或者节名
		WritePrivateProfileString("file","savepath","aws-files\\","./setup.ini");
	}

	int year,month,day,hour,minute,second;
	year = GetPrivateProfileInt("lasttime","year",-1,"./setup.ini");
	month= GetPrivateProfileInt("lasttime","month",-1,"./setup.ini");
	day  = GetPrivateProfileInt("lasttime","day",-1,"./setup.ini");
	hour = GetPrivateProfileInt("lasttime","hour",-1,"./setup.ini");
	minute=GetPrivateProfileInt("lasttime","minute",-1,"./setup.ini");
	second=GetPrivateProfileInt("lasttime","second",-1,"./setup.ini");



	if(year<0 || month<0 || day<0 || hour<0 || minute<0 || second<0)
	{
		last_time = CTime::GetCurrentTime()-CTimeSpan(2,10,0,0);
		SetLastReadTime(last_time);
	}
	else
	{
		last_time = CTime(year,month,day,hour,minute,second);
	}
}

// 设置读取时间
void CAutoGetAwsFileDlg::SetLastReadTime(CTime last_time)
{
	WritePrivateProfileString("lasttime","year",last_time.Format("%Y"),"./setup.ini");
	WritePrivateProfileString("lasttime","month",last_time.Format("%#m"),"./setup.ini");
	WritePrivateProfileString("lasttime","day",last_time.Format("%#d"),"./setup.ini");
	WritePrivateProfileString("lasttime","hour",last_time.Format("%#H"),"./setup.ini");
	WritePrivateProfileString("lasttime","minute",last_time.Format("%#M"),"./setup.ini");
	WritePrivateProfileString("lasttime","second",last_time.Format("%#S"),"./setup.ini");
}

// 开机自动运行
void CAutoGetAwsFileDlg::AutoRunAfterStart(void)
{
	char AppName[MAX_PATH];
	GetModuleFileName(NULL,AppName,MAX_PATH);


	CString skey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

	CRegKey writevalue;
	writevalue.Create(HKEY_LOCAL_MACHINE,skey);
	int error = writevalue.SetStringValue("AGAFD",AppName);
	writevalue.Close();
}

//下载单站的数据 [begin, end]
void get_files_by_time(std::string station_num, CTime begin,CTime end)
{
	using namespace std;
	string server="172.18.152.6", weburl,
		   url="/timedata.asp?StationNum="+station_num+"&selecttime=";

	while(begin <= end)
	{
		string selecttime = begin.Format("%Y%m%d%H").GetBuffer();
		weburl = url + selecttime;

		////show current select time
		//cout<<"\r                                                    ";
		//cout<<"\r reading  "<<selecttime;


		//begin download 

		string localfile = "deal-database/webfiles/"+station_num+"--"+selecttime+".txt";

		DownloadHttpPage(server.c_str(), weburl.c_str(), localfile.c_str());

		begin +=  CTimeSpan(0,1,0,0);
	}
}

// 从172.18.172.6上面下载文件
bool CAutoGetAwsFileDlg::GetFilesFromWeb(void)
{
	using namespace std;

	//判断网络
	if(!Fun_InternetGetConnectedState() )
	{
		MessageBox("网络不通，请检查网络连接","错误");
		return false;
	}

	CTime begin = last_time,  cur_time = CTime::GetCurrentTime();
	
	if( (cur_time < last_time) || (cur_time.GetHour() == last_time.GetHour()) )
		return false;

	char * ss[]={"57065","57066","57070","57071","57074","57076","57077","57078","57162"};
	vector<string> stations(ss,ss+9);

	//下载所有站的数据
	for(vector<string>::iterator it=stations.begin();
		it != stations.end(); it++)
	{
		SetProgramState(("downloading "+ *it + "files...").c_str());
		get_files_by_time(*it,begin,cur_time);
	}

	last_time = cur_time;

	return true;
}

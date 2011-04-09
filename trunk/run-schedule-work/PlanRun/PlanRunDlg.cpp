// PlanRunDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PlanRun.h"
#include "PlanRunDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanRunDlg 对话框

#define WM_SHOWTASK (WM_USER + 1000)


CPlanRunDlg::CPlanRunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlanRunDlg::IDD, pParent)
	, command_line(_T("需要执行的命令名称 如 cmd.exe"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPlanRunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COMMAND, command_line);
	DDX_Control(pDX, IDC_DATE, plan_date);
	DDX_Control(pDX, IDC_TIME, plan_time);
	DDX_Control(pDX, IDC_TASKLIST, task_list);
}

BEGIN_MESSAGE_MAP(CPlanRunDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CPlanRunDlg::OnBnClickedCancel)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE, &CPlanRunDlg::OnDtnDatetimechangeDate)
	ON_BN_CLICKED(IDC_ADDTOLIST, &CPlanRunDlg::OnBnClickedAddtolist)
	ON_BN_CLICKED(IDC_SELECTAPP, &CPlanRunDlg::OnBnClickedSelectapp)
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPlanRunDlg 消息处理程序

BOOL CPlanRunDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	task_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	task_list.InsertColumn(0,"计划时间",LVCFMT_LEFT,135,0);
	task_list.InsertColumn(1,"执行命令",LVCFMT_LEFT,370,1);
	task_list.InsertColumn(2,"剩余时间",LVCFMT_LEFT,120,2);

	SetTimer(1,500,NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPlanRunDlg::OnPaint()
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
HCURSOR CPlanRunDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPlanRunDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//if(IDYES == MessageBox("确定要退出么？","退出",MB_YESNO|MB_ICONQUESTION))
		OnCancel();
}

void CPlanRunDlg::OnDtnDatetimechangeDate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CPlanRunDlg::OnBnClickedAddtolist()
{
	// TODO: 在此添加控件通知处理程序代码
	//检查是否有相同的项 如果没有则加入列表
	UpdateData();

	if(command_line.Trim()=="")
	{
		MessageBox("执行的命令不能为空!");
		return;
	}

	CTime date,time;
	
	plan_time.GetTime(time);
	if(plan_date.GetTime(date)==GDT_VALID)
	{
		time = CTime(date.GetYear(),date.GetMonth(),date.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
	}
	
	CString time_str = time.Format("%Y-%m-%d %H:%M:%S");

	bool insert = true;
	for(int i=0;i<task_list.GetItemCount();i++)
	{
		if(task_list.GetItemText(i,0)==time_str && task_list.GetItemText(i,1)==command_line)
		{
			insert = false;
		}
	}

	if(insert)
	{
		int item = task_list.GetItemCount();
		task_list.InsertItem(item,"");
		task_list.SetItemText(item,0,time_str);
		task_list.SetItemText(item,1,command_line);
	}
	else
	{
		MessageBox("列表中已存在相同的任务!");
	}

}

void CPlanRunDlg::OnBnClickedSelectapp()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog file_dialog(TRUE);
	if(IDOK == file_dialog.DoModal())
	{
		command_line = file_dialog.GetPathName();
		UpdateData(FALSE);
	}
}

CTime CStringToCTime(CString str)
{
	//CString   s("2001-8-29 19:06:23");   
	int  nYear, nMonth, nDate, nHour, nMin, nSec;   
	sscanf_s(str,   "%d-%d-%d %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);   
	
	return CTime(nYear, nMonth, nDate, nHour, nMin, nSec);
}

void CPlanRunDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		UpdateData(TRUE);
		

		
		for(int i=0;i<task_list.GetItemCount();i++)
		{
			CString time_str = task_list.GetItemText(i,0);
			CTimeSpan timespan = CStringToCTime(time_str) - CTime::GetCurrentTime();
			
			int  hours   = timespan.GetTotalHours(), 
				minutes = timespan.GetMinutes(), 
				seconds = timespan.GetSeconds();

			time_str.Format("%d:%d:%d",hours,minutes,seconds);

			if(timespan.GetTotalSeconds() > 0)
			{
				task_list.SetItemText(i,2,time_str);
			}
			else //时间已到
			{
				CString this_command = task_list.GetItemText(i,1);
				if(task_list.GetItemText(i,2) != "已执行")
				{
					//执行
					PROCESS_INFORMATION proif;
					STARTUPINFO stif = {sizeof(stif)};

					BOOL res = ::CreateProcess(NULL,this_command.GetBuffer(),NULL,NULL,FALSE,0,NULL,NULL,&stif,&proif);

					if(res)
					{
						task_list.SetItemText(i,2,"已执行");
					}
					else
					{
						task_list.SetItemText(i,2,"执行失败！");
					}
				}
			}
		}
		UpdateData(FALSE);
	}

	CDialog::OnTimer(nIDEvent);
}

void CPlanRunDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

LRESULT CPlanRunDlg::OnShowTask(WPARAM wParam,LPARAM lParam) 
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
void CPlanRunDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(nType == SIZE_MINIMIZED)  
	{  
		HideToTray();
		ShowWindow(SW_HIDE); //隐藏主窗口
	}  
}

void CPlanRunDlg::HideToTray()
{ 
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage=WM_SHOWTASK;//自定义的消息名称 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy_s(nid.szTip,20,"执行计划任务"); //信息提示条为“计划任务提醒” 
	Shell_NotifyIcon(NIM_ADD,&nid); //在托盘区添加图标 

}

void CPlanRunDlg::OnDestroy()
{
	// TODO: 在此处添加消息处理程序代码
	// 在托盘区删除图标

	Shell_NotifyIcon(NIM_DELETE, &nid);             

	return CDialog::OnDestroy();
}

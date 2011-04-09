// PlanRunDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlanRun.h"
#include "PlanRunDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanRunDlg �Ի���

#define WM_SHOWTASK (WM_USER + 1000)


CPlanRunDlg::CPlanRunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlanRunDlg::IDD, pParent)
	, command_line(_T("��Ҫִ�е��������� �� cmd.exe"))
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


// CPlanRunDlg ��Ϣ�������

BOOL CPlanRunDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	task_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	task_list.InsertColumn(0,"�ƻ�ʱ��",LVCFMT_LEFT,135,0);
	task_list.InsertColumn(1,"ִ������",LVCFMT_LEFT,370,1);
	task_list.InsertColumn(2,"ʣ��ʱ��",LVCFMT_LEFT,120,2);

	SetTimer(1,500,NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPlanRunDlg::OnPaint()
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
HCURSOR CPlanRunDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPlanRunDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//if(IDYES == MessageBox("ȷ��Ҫ�˳�ô��","�˳�",MB_YESNO|MB_ICONQUESTION))
		OnCancel();
}

void CPlanRunDlg::OnDtnDatetimechangeDate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CPlanRunDlg::OnBnClickedAddtolist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����Ƿ�����ͬ���� ���û��������б�
	UpdateData();

	if(command_line.Trim()=="")
	{
		MessageBox("ִ�е������Ϊ��!");
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
		MessageBox("�б����Ѵ�����ͬ������!");
	}

}

void CPlanRunDlg::OnBnClickedSelectapp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
			else //ʱ���ѵ�
			{
				CString this_command = task_list.GetItemText(i,1);
				if(task_list.GetItemText(i,2) != "��ִ��")
				{
					//ִ��
					PROCESS_INFORMATION proif;
					STARTUPINFO stif = {sizeof(stif)};

					BOOL res = ::CreateProcess(NULL,this_command.GetBuffer(),NULL,NULL,FALSE,0,NULL,NULL,&stif,&proif);

					if(res)
					{
						task_list.SetItemText(i,2,"��ִ��");
					}
					else
					{
						task_list.SetItemText(i,2,"ִ��ʧ�ܣ�");
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ( (nID == SC_MINIMIZE) || (nID == SC_CLOSE)) 
	{ 
		 HideToTray();
		 ShowWindow(SW_HIDE); //����������
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

LRESULT CPlanRunDlg::OnShowTask(WPARAM wParam,LPARAM lParam) 
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
void CPlanRunDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(nType == SIZE_MINIMIZED)  
	{  
		HideToTray();
		ShowWindow(SW_HIDE); //����������
	}  
}

void CPlanRunDlg::HideToTray()
{ 
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage=WM_SHOWTASK;//�Զ������Ϣ���� 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy_s(nid.szTip,20,"ִ�мƻ�����"); //��Ϣ��ʾ��Ϊ���ƻ��������ѡ� 
	Shell_NotifyIcon(NIM_ADD,&nid); //�����������ͼ�� 

}

void CPlanRunDlg::OnDestroy()
{
	// TODO: �ڴ˴������Ϣ����������
	// ��������ɾ��ͼ��

	Shell_NotifyIcon(NIM_DELETE, &nid);             

	return CDialog::OnDestroy();
}

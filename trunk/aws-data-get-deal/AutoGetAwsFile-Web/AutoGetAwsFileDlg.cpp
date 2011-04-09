// AutoGetAwsFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoGetAwsFile.h"
#include "AutoGetAwsFileDlg.h"
#include "http-deal.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoGetAwsFileDlg �Ի���


#define WM_SHOWTASK (WM_USER + 1000)

CAutoGetAwsFileDlg::CAutoGetAwsFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoGetAwsFileDlg::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	GetLastReadTime();
	ProgramState = "���򽫴��������������ļ�...\n"+last_time.Format("�����ȡʱ�Σ�%Y-%m-%d %Hʱ");
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


// CAutoGetAwsFileDlg ��Ϣ�������

BOOL CAutoGetAwsFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	HideToTray();
	//ShowWindow(SW_HIDE);
	
	AutoRunAfterStart();

	SetProgramState("begin set timer");
	SetTimer(1,5*1000,NULL);//�������к�5���������ʱ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAutoGetAwsFileDlg::OnPaint()
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
HCURSOR CAutoGetAwsFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ���ص�������
void CAutoGetAwsFileDlg::HideToTray(void)
{
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage=WM_SHOWTASK;//�Զ������Ϣ���� 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy_s(nid.szTip,"�Զ���ȡ�Զ�վ����"); //��Ϣ��ʾ�� 
	Shell_NotifyIcon(NIM_ADD,&nid); //�����������ͼ�� 
}

void CAutoGetAwsFileDlg::OnDestroy()
{
	Shell_NotifyIcon(NIM_DELETE, &nid);

	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}

void CAutoGetAwsFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

LRESULT CAutoGetAwsFileDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
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
		//ִ��
		PROCESS_INFORMATION proif;
		STARTUPINFO stif = {sizeof(stif)};

		BOOL res = ::CreateProcess(NULL,(filepath+filename).GetBuffer(),NULL,NULL,FALSE,0,NULL,filepath,&stif,&proif);
	}
}

void CAutoGetAwsFileDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		
		SetProgramState("�����Զ����������������ļ�...\n"+last_time.Format("�����ȡʱ�Σ�%Y-%m-%d %Hʱ"));

		SetTimer(1,3*1000*60,NULL);// ʱ�䲻��̫�� ������SetLastReadTime()��ûִ�����
	}

	CDialog::OnTimer(nIDEvent);
}

bool CAutoGetAwsFileDlg::GetFtpFile()
{
	bool isdownload=false;

	try
	{
		CInternetSession sess("My FTP Session");

		SetProgramState("���ڵ�½������...");
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.172.155","lyqxt","lyqxt");//��¼
		
		SetProgramState("�ɹ���½,���ڲ����ļ�...");

		pConnect->SetCurrentDirectory("/aws");

		CFtpFileFind finder(pConnect);
		// start looping		 
		
		BOOL working = finder.FindFile("*");

		while(working)
		{
			working = finder.FindNextFileA();
			CString filename=finder.GetFileName();

			CTime LastAccessTime,LastWriteTime,CreationTime;
			//finder.GetLastAccessTime(LastAccessTime); ���ܶ�ȡ
			finder.GetLastWriteTime(LastWriteTime); //����޸�ʱ��
			//finder.GetCreationTime(CreationTime); ���ܶ�ȡ

			CString TimeStr = LastAccessTime.Format("%Y-%m-%d %H:%M:%S")+LastWriteTime.Format("\n%Y-%m-%d %H:%M:%S")+CreationTime.Format("\n%Y-%m-%d %H:%M:%S");
			//MessageBox(TimeStr);

			if(LastWriteTime > this->last_time)
			{
				SetProgramState("�ҵ��ļ� "+filename+", ��ʼ��������");

				if(pConnect->GetFile(filename,this->savepath+filename,FALSE))
				{
					SetProgramState("�����ļ� "+filename+ "�ɹ�!");
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

		//cout<<"���μ����� ����10���Ӻ����µ�¼Ftp�������鿴"<<endl;
	}
	catch (CInternetException* pEx)
	{
		char error[1025];
		pEx->GetErrorMessage(error, 1024);

		SetProgramState("���ִ���:"+CString(error));
		//cout<<"ERROR!"<<error<<endl;
		pEx->Delete();
		return false;
	}

	return isdownload ;
}

// ���ó���״̬��ˢ��
void CAutoGetAwsFileDlg::SetProgramState(CString state)
{
	ProgramState = state;
	UpdateData(FALSE);
}

// �������ļ���ȡ�ϴζ�ȡ�ļ�ʱ��
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
		//�˺����Զ������ļ����߽���
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

// ���ö�ȡʱ��
void CAutoGetAwsFileDlg::SetLastReadTime(CTime last_time)
{
	WritePrivateProfileString("lasttime","year",last_time.Format("%Y"),"./setup.ini");
	WritePrivateProfileString("lasttime","month",last_time.Format("%#m"),"./setup.ini");
	WritePrivateProfileString("lasttime","day",last_time.Format("%#d"),"./setup.ini");
	WritePrivateProfileString("lasttime","hour",last_time.Format("%#H"),"./setup.ini");
	WritePrivateProfileString("lasttime","minute",last_time.Format("%#M"),"./setup.ini");
	WritePrivateProfileString("lasttime","second",last_time.Format("%#S"),"./setup.ini");
}

// �����Զ�����
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

//���ص�վ������ [begin, end]
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

// ��172.18.172.6���������ļ�
bool CAutoGetAwsFileDlg::GetFilesFromWeb(void)
{
	using namespace std;

	//�ж�����
	if(!Fun_InternetGetConnectedState() )
	{
		MessageBox("���粻ͨ��������������","����");
		return false;
	}

	CTime begin = last_time,  cur_time = CTime::GetCurrentTime();
	
	if( (cur_time < last_time) || (cur_time.GetHour() == last_time.GetHour()) )
		return false;

	char * ss[]={"57065","57066","57070","57071","57074","57076","57077","57078","57162"};
	vector<string> stations(ss,ss+9);

	//��������վ������
	for(vector<string>::iterator it=stations.begin();
		it != stations.end(); it++)
	{
		SetProgramState(("downloading "+ *it + "files...").c_str());
		get_files_by_time(*it,begin,cur_time);
	}

	last_time = cur_time;

	return true;
}

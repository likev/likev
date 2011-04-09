// MessAtoBDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MessAtoB.h"
#include "MessAtoBDlg.h"
#include "SetWethDialog.h"
#include "comn.h"
#include "string-trans.h"
#include "setinfo.h"
#include "PYDlg.h"
#include "SelfForcast.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMessAtoBDlg �Ի���




CMessAtoBDlg::CMessAtoBDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMessAtoBDlg::IDD, pParent)
, all_weather_str(4,std::vector<std::string>(11,""))
, all_temph_value(4,std::vector<double>(11,101))
, is_czb_down_success(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	char * snames[]={"��������","����","�Ͻ�","��ʦ","����","����","�°�","����","����","����","�ﴨ"};  
	station_names.assign(snames,snames+11);
	
	forcast_type = GetForcastType();
	begin_head(fhead);
}

void CMessAtoBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_text);
}

BEGIN_MESSAGE_MAP(CMessAtoBDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_CHE, &CMessAtoBDlg::OnBnClickedChe)

	ON_BN_CLICKED(IDCANCEL, &CMessAtoBDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_WET, &CMessAtoBDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMessAtoBDlg::OnBnClickedButton1)

	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_GENERATE_PY, &CMessAtoBDlg::OnBnClickedGeneratePy)
	ON_BN_CLICKED(IDC_BUTTON_SelfForcast, &CMessAtoBDlg::OnBnClickedButtonSelfforcast)
END_MESSAGE_MAP()


// CMessAtoBDlg ��Ϣ�������

BOOL CMessAtoBDlg::OnInitDialog()
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

	CFont *cf = new CFont;
	cf->CreatePointFont(120,"����");
	m_text.SetFont(cf);

	if(forcast_type == AM12121)
	{
		SetWindowText("���12121Ԥ��  "+CTime::GetCurrentTime().Format("%Y��%m��%d��%Hʱ"));
		GetDlgItem(ID_CHE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SEND)->ShowWindow(SW_SHOW);

		fstr = generate121str();
		m_text.SetWindowTextA(fstr.c_str());

	}
	else
	{
		SetWindowText("����-->����Ԥ��  "+CTime::GetCurrentTime().Format("%Y��%m��%d��%Hʱ"));
	}


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMessAtoBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMessAtoBDlg::OnPaint()
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
HCURSOR CMessAtoBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//����ת��Ϊ����Ԥ��
void CMessAtoBDlg::OnBnClickedChe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	is_czb_down_success = FtpDownCzbFile();
	if(!is_czb_down_success)   //���س����ļ�ʧ��
	{
		MessageBox("���س����ļ�ʧ�ܣ�", "����", MB_ICONERROR);
		return;
	}

	if(!read_trans_data() )//��������
	{
		MessageBox("���������ļ�ʧ�ܣ�", "����", MB_ICONERROR);
		return;
	}

	fstr = fhead + generate_forcast_str();

	//��ʾ�ڱ༭��
	m_text.SetWindowTextA(fstr.c_str());

	GetDlgItem(ID_CHE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_WET)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SEND)->ShowWindow(SW_SHOW);

	//if(forcast_type == AFTERNOON)
	//	GetDlgItem(IDC_GENERATE_PY)->ShowWindow(SW_SHOW);
}



void CMessAtoBDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox("ȷ��Ҫ�˳���?","�����˳�",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		OnCancel();
	}

}

//����״���޸�
void CMessAtoBDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString sfile;
	m_text.GetWindowText(sfile);

	fstr = sfile.GetBuffer();
	size_t p = fstr.find("����");
	if(p != fstr.npos)
	{
		fhead = fstr.substr(0,p);
	}


	CSetWethDialog sd;

	sd.is_forcast48 = (forcast_type == AFTERNOON);

	sd.weather12 = all_weather_str[0][2].c_str();
	sd.weather24 = all_weather_str[1][2].c_str();
	sd.weather36 = all_weather_str[2][2].c_str();
	sd.weather48 = all_weather_str[3][2].c_str();

	if(sd.DoModal() == IDOK)
	{
		for(int j=0;j<11;j++)
		{
			if(sd.ischeck[0][j])
				all_weather_str[0][j] = sd.weather12.GetBuffer();
			if(sd.ischeck[1][j])
				all_weather_str[1][j] = sd.weather24.GetBuffer();
			if(sd.ischeck[2][j])
				all_weather_str[2][j] = sd.weather36.GetBuffer();
			if(sd.ischeck[3][j])
				all_weather_str[3][j] = sd.weather48.GetBuffer();
		}


		fstr = fhead + generate_forcast_str();

		//��ʾ�ڱ༭��
		m_text.SetWindowTextA(fstr.c_str());
	}
}

//������ť����
void CMessAtoBDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString sfile;
	m_text.GetWindowText(sfile);
	sfile.Replace("\r\n","\n");

	fstr = sfile.GetBuffer();

	if(!strtofile("f.txt",fstr))    //���ݱ���Ϊ�ļ�
	{
		MessageBox("�ļ�����ʧ�ܣ������ԣ�", "����", MB_ICONERROR);
		return ;
	}

	CTime cur_time=CTime::GetCurrentTime();//��ǰ����

	CString file_path = "//172.18.172.63/data_/xjdata/",
		file_name1 = cur_time.Format("YBFB/xqyb/%Y%m%d.%H"),
		file_name2 = cur_time.Format("FORECAST/dqyb/ly%Y%m%d%H.dq");

	//BOOL  is_success1 = CopyFile("f.txt", "f1.txt" , FALSE),
	//	is_success2 = CopyFile("f.txt","f2.txt" , FALSE);

	BOOL  is_success1 = CopyFile("f.txt", file_path+file_name1 , FALSE),	
	      is_success2 = CopyFile("f.txt", file_path+file_name2 , FALSE);

	if(forcast_type == AM12121)
	{
		if(is_success1)
			MessageBox("���� "+file_name1+" �ɹ���","�ɹ�",MB_ICONINFORMATION);
		else
			MessageBox("���� "+file_name1+" ʧ�ܣ�", "����", MB_ICONERROR);

		return;
	}



	if(is_success1&&is_success2)
	{
		MessageBox("���� "+file_name1+" �ɹ�!\n���� "+file_name2+" �ɹ���","�ɹ�",MB_ICONINFORMATION);
	}	
	else
	{
		if(is_success1)
			MessageBox("���� "+file_name1+" �ɹ���","�ɹ�",MB_ICONINFORMATION);
		else
			MessageBox("���� "+file_name1+" ʧ�ܣ�", "����", MB_ICONERROR);

		if(is_success2)
			MessageBox("���� "+file_name2+" �ɹ���","�ɹ�",MB_ICONINFORMATION);
		else
			MessageBox("���� "+file_name2+" ʧ�ܣ�", "����", MB_ICONERROR);
	}

}


//���ڴ�С�ı䴦��
void CMessAtoBDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rect;
	GetWindowRect(&rect);
	if(cx<600)
		rect.right = rect.left + 600;
	if(cy<300)
		rect.bottom = rect.top + 300;

	MoveWindow(&rect);

	if(m_text.m_hWnd)
		m_text.MoveWindow(15,70,rect.Width()-35,rect.Height()-120);
	// TODO: �ڴ˴������Ϣ����������
}

CMessAtoBDlg::ForcastType CMessAtoBDlg::GetForcastType()
{
	CTime ct1=CTime::GetCurrentTime();//��ǰ����
	int cth = ct1.GetHour();

	if(cth<5 || cth>19)
	{
		return SMALLHOURS;//04ʱԤ��
	}
	else if(cth<9)
	{
		return MORNING;//06���Ԥ��
	}
	else if(cth<14)
	{
		return AM12121;//12121Ԥ��
	}
	else
	{
		return AFTERNOON;//����Ԥ��
	}
}

//��¼ftp������  ��ָ��Ŀ¼ �������ļ�
//assumes server and file names have been initialized
bool CMessAtoBDlg::FtpDownCzbFile()
{

	try
	{
		//cout<<"���ڵ�½������......"<<endl;
		
		CInternetSession sess("My FTP Session");//"65.19.143.3","likev@xufanglu.cn","271828han",21,1
		
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.152.5","luoyang","luoyang");//��¼

		if(pConnect)
		{
			//AfxMessageBox("��¼�������ɹ� ���ڲ������ļ�......");
			//cout<<\n\n";
		}
		else
		{//�쳣����
		}

		
		CString ftp_filename = GetFtpFilename().c_str();
		
		
		pConnect->SetCurrentDirectory("/");
		CFtpFileFind finder(pConnect);
		
		
		// start looping
		//��ǰĿ¼����		
		if(!finder.FindFile(ftp_filename))
		{
			/*bWorking = finder.FindNextFile();*/
			pConnect->SetCurrentDirectory("/ok");

			if(!finder.FindFile(ftp_filename))//okĿ¼����
			{
				return false;
			}
		}

		CInternetFile *pIf = pConnect->OpenFile(ftp_filename);
		CFile local_file("b.txt",CFile::modeCreate|CFile::modeWrite);
		char pBuf[1000]; UINT rnum=0;
		while(rnum = pIf->Read(pBuf,1000))
		{
			local_file.Write(pBuf,rnum);
		}
		pIf->Close();
		local_file.Close();

		if (pConnect != NULL) 
		{
			pConnect->Close();
			delete pConnect;
		}

		return true;
	}
	catch (CInternetException* pEx)
	{
		char error[1025];
		pEx->GetErrorMessage(error, 1024);
		////cout<<"ERROR!"<<error<<endl;
		//AfxMessageBox("Error: "+CString(error));
		pEx->Delete();
		return false;
	}

	return true;
}

//�������ݲ�����
bool CMessAtoBDlg::read_trans_data()
{
	using namespace std;
	char * s[11]={"57073", "57073","57071","57076","57074",
		                "57078","57070","57065","57066","57162","57077"};

	station_forcasts.resize(11);
	string str;SetInfo c;


	filetostr("b.txt",str);
	if(str=="")  return false;

	string m[4];double t[4];
	for(int i=0;i<11;i++)
	{
		if(!station_forcasts[i].init(*(s+i),str))
		{
			return false;
		}

		//4��ʱ�ε�����״��
		m[0] = dtos(station_forcasts[i].f[0][19],1);
		m[1] = dtos(station_forcasts[i].f[1][19],1);
		m[2] = dtos(station_forcasts[i].f[2][19],1);
		m[3] = dtos(station_forcasts[i].f[3][19],1);

		//2���ڵ�������
		t[0] =  station_forcasts[i].f[1][11];
		t[1] =  station_forcasts[i].f[1][12];
		t[2] =  station_forcasts[i].f[3][11];
		t[3] =  station_forcasts[i].f[3][12];

		for(int j=0;j<4;j++)
		{
			all_weather_str[j][i] = c.weth[m[j] ];
			all_temph_value[j][i] = t[j];
		}
	}
	return true;
}

std::string CMessAtoBDlg::generate121str()
{
	std::stringstream stream;

	CTime cur_time=CTime::GetCurrentTime();//��ǰ����

	std::string file_path = "//172.18.172.63/data_/xjdata/",
			file_name = cur_time.Format("YBFB/xqyb/%Y%m%d.06");

	std::string lastfile_content;
	CString head_str;
	
	if(!filetostr(file_path+file_name,lastfile_content))
	{
		file_name = cur_time.Format("YBFB/xqyb/%Y%m%d.05");
		filetostr(file_path+file_name,lastfile_content);
	}
	
	size_t pos1 = lastfile_content.find("24Сʱ����"),
		   pos2 = lastfile_content.find("48Сʱ����");

	if(pos1 == std::string::npos || pos2 == std::string::npos)
	{
		return "";
	}
	head_str = lastfile_content.substr(pos1,pos2-pos1).c_str();
	head_str.Replace("\n","\r\n");

	stream<<"	                      ��   ��   Ԥ   ��\r\n"
		"                                     "<<cur_time.Format("%Y��%m��%d��%Hʱ����").GetBuffer()
	<<"\r\n-------------------------------------------------------------------\r\n  ";

	return stream.str()+(LPCSTR)head_str;
}

void CMessAtoBDlg::begin_head(std::string &fhead)
{

	using namespace std;
	stringstream stream;

	CTime ct1=CTime::GetCurrentTime();//��ǰ����

	stream<<"	                      ��   ��   Ԥ   ��\r\n"
		<<"                                     "<<ct1.Format("%Y��%m��%d��%Hʱ����").GetBuffer()
	<<"\r\n-------------------------------------------------------------------\r\n"
		"-------------------------------------------------------------------\r\n"
		"�������Ʒ���: \r\n"                                                      
		"-------------------------------------------------------------------\r\n"
		"  24Сʱ����: \r\n"                                                        
		"    �������: ƫ ��2-3��\r\n"                                                        
		"        �¶�: ����¶ȣ�       ����¶ȣ�\r\n"                                                        
		"-------------------------------------------------------------------\r\n"
		"  48Сʱ����:\r\n"                                                        
		"-------------------------------------------------------------------\r\n"
		"    ɭ�ֻ���: 2\r\n"                                                          
		"-------------------------------------------------------------------\r\n\r\n"

		" վ  ��       0-12Сʱ����   12-24Сʱ����    ����¶�      ����¶�\r\n"           
		"-------------------------------------------------------------------\r\n"
		"-------------------------------------------------------------------\r\n";

	fhead = stream.str();
}

//���24Сʱ����״�����������¶�
void CMessAtoBDlg::output_weather(std::stringstream & fout, int n)
{
	using namespace std;

	for(size_t i=0;i<11;i++)
	{
		fout<<left<<setw(14)<<station_names[i]<<setw(15)<<all_weather_str[0+n][i]<<" "<<setw(16)<<all_weather_str[1+n][i]
		<<" "<<setw(16)<<all_temph_value[0+n][i]<<setw(15)<<all_temph_value[1+n][i];
		fout<<"\r\n-------------------------------------------------------------------\r\n";
	}
}

//������д���ļ�
std::string CMessAtoBDlg::generate_forcast_str()
{

	using namespace std;
	stringstream stream;
	switch(forcast_type)
	{
	case SMALLHOURS:
		break;
	case MORNING:
		output_weather(stream);
		break;
	case AM12121:
		strtofile("f.txt",generate121str());
		break;

	case AFTERNOON:
		{
			output_weather(stream);//ǰ24Сʱ
			stream<<"\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"
				" վ  ��       24-36Сʱ����   36-48Сʱ����    ����¶�      ����¶�\r\n"           
				"-------------------------------------------------------------------\r\n"
				"-------------------------------------------------------------------\r\n";
			output_weather(stream,2);//��24Сʱ
			break;
		}
	default:break;
	}

	return stream.str();
}

//��ȡ��ҩ����
int CMessAtoBDlg::GetPYGrade(const Sglf &station_forcast)
{
	if(station_forcast.israin(12) && station_forcast.f[0][21]<1
	&& station_forcast.israin(24) && station_forcast.f[1][21]<1
	&& station_forcast.israin(36) && station_forcast.f[2][21]<1
	&& station_forcast.israin(48) && station_forcast.f[3][21]<1 )
	{
		return 1;
	}
	else if(station_forcast.f[0][21]>2 
	|| station_forcast.israin(24) || station_forcast.f[1][21]>2
	|| station_forcast.israin(36) || station_forcast.f[2][21]>2
	|| station_forcast.f[3][21]>2 || station_forcast.f[1][11]>35.0)
	{
		return 3;
	}
	else
	{
		return 2;
	}

}
void CMessAtoBDlg::OnBnClickedGeneratePy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPYDlg py_dlg;
	

	std::ostringstream sout;

	for(std::vector<Sglf>::iterator it= ++station_forcasts.begin();
		it != station_forcasts.end(); it++)
	{
		sout<<it->stn<<" "<<GetPYGrade(*it)<<"\r\n";
	}
	
	py_dlg.py_edit_content = sout.str().c_str();

	py_dlg.DoModal();
}

void CMessAtoBDlg::OnBnClickedButtonSelfforcast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!is_czb_down_success)
	{
		CWnd * pbutton = GetDlgItem(IDC_BUTTON_SelfForcast);
		pbutton->SetWindowText("���س����ļ�...");
		pbutton->EnableWindow(false);
	
		is_czb_down_success = FtpDownCzbFile();

		pbutton->SetWindowText("�ϴ�����Ԥ��");
		pbutton->EnableWindow(true);
	}

	if(!is_czb_down_success)
	{
		MessageBox("���س����ļ�ʧ�ܣ�", "����", MB_ICONERROR);
		return;
	}

	SelfForcast sf_dlg;
	sf_dlg.ftp_filename = GetFtpFilename();

	sf_dlg.DoModal();
}

// ��ȡ��ǰʱ�γ��򱨵��ļ���
std::string CMessAtoBDlg::GetFtpFilename(void)
{
	CTime ct1=CTime::GetCurrentTime();//��ǰ����
	CTime ct2=ct1 - CTimeSpan(1, 0, 0, 0);

	//��ñ���ʱ�䵱ǰ�����ַ���
	CString tdate=ct1.Format("%Y%m%d"),  ldate=ct2.Format("%Y%m%d");

	std::string ftp_filename;//Ҫ���ص��ļ���

	switch(forcast_type)
	{
	case SMALLHOURS:
		{
			//���04ʱԤ�� ��   			
			ftp_filename= "Z_SEVP_C_BFLB_"+ldate+"205000_P_RFFC-SPCC-"+tdate+"0000-07212.TXT";
			break;
		}
	case MORNING:
		{
			//�������Ԥ��20��6ʱ ��   			
			ftp_filename= "Z_SEVP_C_BFLB_"+ldate+"223500_P_RFFC-SPCC-"+tdate+"0000-16812.TXT";
			break;
		}
	case AM12121:
		{//12121Ԥ��19��10ʱ��   
			ftp_filename = "Z_SEVP_C_BFLB_"+tdate+"022000_P_RFFC-SPCC-"+tdate+"0000-16812.TXT";
			break;
		}
	case AFTERNOON:
		{
			//��������Ԥ��19��16ʱ ��   
			ftp_filename= "Z_SEVP_C_BFLB_"+tdate+"082000_P_RFFC-SPCC-"+tdate+"1200-16812.TXT";
			break;
		}
	default:break;
	}

	return ftp_filename;
}

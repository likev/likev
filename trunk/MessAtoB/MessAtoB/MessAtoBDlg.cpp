// MessAtoBDlg.cpp : 实现文件
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


// CMessAtoBDlg 对话框




CMessAtoBDlg::CMessAtoBDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMessAtoBDlg::IDD, pParent)
, all_weather_str(4,std::vector<std::string>(11,""))
, all_temph_value(4,std::vector<double>(11,101))
, is_czb_down_success(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	char * snames[]={"洛阳市区","吉利","孟津","偃师","伊川","汝阳","新安","宜阳","洛宁","嵩县","栾川"};  
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


// CMessAtoBDlg 消息处理程序

BOOL CMessAtoBDlg::OnInitDialog()
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

	CFont *cf = new CFont;
	cf->CreatePointFont(120,"宋体");
	m_text.SetFont(cf);

	if(forcast_type == AM12121)
	{
		SetWindowText("早间12121预报  "+CTime::GetCurrentTime().Format("%Y年%m月%d日%H时"));
		GetDlgItem(ID_CHE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SEND)->ShowWindow(SW_SHOW);

		fstr = generate121str();
		m_text.SetWindowTextA(fstr.c_str());

	}
	else
	{
		SetWindowText("城镇报-->县区预报  "+CTime::GetCurrentTime().Format("%Y年%m月%d日%H时"));
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMessAtoBDlg::OnPaint()
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
HCURSOR CMessAtoBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//城镇报转化为县区预报
void CMessAtoBDlg::OnBnClickedChe()
{
	// TODO: 在此添加控件通知处理程序代码

	is_czb_down_success = FtpDownCzbFile();
	if(!is_czb_down_success)   //下载城镇报文件失败
	{
		MessageBox("下载城镇报文件失败！", "错误", MB_ICONERROR);
		return;
	}

	if(!read_trans_data() )//处理数据
	{
		MessageBox("分析城镇报文件失败！", "错误", MB_ICONERROR);
		return;
	}

	fstr = fhead + generate_forcast_str();

	//显示在编辑区
	m_text.SetWindowTextA(fstr.c_str());

	GetDlgItem(ID_CHE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_WET)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_SEND)->ShowWindow(SW_SHOW);

	//if(forcast_type == AFTERNOON)
	//	GetDlgItem(IDC_GENERATE_PY)->ShowWindow(SW_SHOW);
}



void CMessAtoBDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(MessageBox("确定要退出吗?","程序退出",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		OnCancel();
	}

}

//天气状况修改
void CMessAtoBDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	CString sfile;
	m_text.GetWindowText(sfile);

	fstr = sfile.GetBuffer();
	size_t p = fstr.find("洛阳");
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

		//显示在编辑区
		m_text.SetWindowTextA(fstr.c_str());
	}
}

//送网按钮处理
void CMessAtoBDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString sfile;
	m_text.GetWindowText(sfile);
	sfile.Replace("\r\n","\n");

	fstr = sfile.GetBuffer();

	if(!strtofile("f.txt",fstr))    //数据保存为文件
	{
		MessageBox("文件保存失败，请重试！", "警告", MB_ICONERROR);
		return ;
	}

	CTime cur_time=CTime::GetCurrentTime();//当前日期

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
			MessageBox("送网 "+file_name1+" 成功！","成功",MB_ICONINFORMATION);
		else
			MessageBox("送网 "+file_name1+" 失败！", "警告", MB_ICONERROR);

		return;
	}



	if(is_success1&&is_success2)
	{
		MessageBox("送网 "+file_name1+" 成功!\n送网 "+file_name2+" 成功！","成功",MB_ICONINFORMATION);
	}	
	else
	{
		if(is_success1)
			MessageBox("送网 "+file_name1+" 成功！","成功",MB_ICONINFORMATION);
		else
			MessageBox("送网 "+file_name1+" 失败！", "警告", MB_ICONERROR);

		if(is_success2)
			MessageBox("送网 "+file_name2+" 成功！","成功",MB_ICONINFORMATION);
		else
			MessageBox("送网 "+file_name2+" 失败！", "警告", MB_ICONERROR);
	}

}


//窗口大小改变处理
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
	// TODO: 在此处添加消息处理程序代码
}

CMessAtoBDlg::ForcastType CMessAtoBDlg::GetForcastType()
{
	CTime ct1=CTime::GetCurrentTime();//当前日期
	int cth = ct1.GetHour();

	if(cth<5 || cth>19)
	{
		return SMALLHOURS;//04时预报
	}
	else if(cth<9)
	{
		return MORNING;//06早间预报
	}
	else if(cth<14)
	{
		return AM12121;//12121预报
	}
	else
	{
		return AFTERNOON;//下午预报
	}
}

//登录ftp服务器  打开指定目录 查找新文件
//assumes server and file names have been initialized
bool CMessAtoBDlg::FtpDownCzbFile()
{

	try
	{
		//cout<<"正在登陆服务器......"<<endl;
		
		CInternetSession sess("My FTP Session");//"65.19.143.3","likev@xufanglu.cn","271828han",21,1
		
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.152.5","luoyang","luoyang");//登录

		if(pConnect)
		{
			//AfxMessageBox("登录服务器成功 正在查找新文件......");
			//cout<<\n\n";
		}
		else
		{//异常处理
		}

		
		CString ftp_filename = GetFtpFilename().c_str();
		
		
		pConnect->SetCurrentDirectory("/");
		CFtpFileFind finder(pConnect);
		
		
		// start looping
		//当前目录查找		
		if(!finder.FindFile(ftp_filename))
		{
			/*bWorking = finder.FindNextFile();*/
			pConnect->SetCurrentDirectory("/ok");

			if(!finder.FindFile(ftp_filename))//ok目录查找
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

//处理数据并储存
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

		//4个时次的天气状况
		m[0] = dtos(station_forcasts[i].f[0][19],1);
		m[1] = dtos(station_forcasts[i].f[1][19],1);
		m[2] = dtos(station_forcasts[i].f[2][19],1);
		m[3] = dtos(station_forcasts[i].f[3][19],1);

		//2天内的最高最低
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

	CTime cur_time=CTime::GetCurrentTime();//当前日期

	std::string file_path = "//172.18.172.63/data_/xjdata/",
			file_name = cur_time.Format("YBFB/xqyb/%Y%m%d.06");

	std::string lastfile_content;
	CString head_str;
	
	if(!filetostr(file_path+file_name,lastfile_content))
	{
		file_name = cur_time.Format("YBFB/xqyb/%Y%m%d.05");
		filetostr(file_path+file_name,lastfile_content);
	}
	
	size_t pos1 = lastfile_content.find("24小时天气"),
		   pos2 = lastfile_content.find("48小时天气");

	if(pos1 == std::string::npos || pos2 == std::string::npos)
	{
		return "";
	}
	head_str = lastfile_content.substr(pos1,pos2-pos1).c_str();
	head_str.Replace("\n","\r\n");

	stream<<"	                      县   区   预   报\r\n"
		"                                     "<<cur_time.Format("%Y年%m月%d日%H时制作").GetBuffer()
	<<"\r\n-------------------------------------------------------------------\r\n  ";

	return stream.str()+(LPCSTR)head_str;
}

void CMessAtoBDlg::begin_head(std::string &fhead)
{

	using namespace std;
	stringstream stream;

	CTime ct1=CTime::GetCurrentTime();//当前日期

	stream<<"	                      县   区   预   报\r\n"
		<<"                                     "<<ct1.Format("%Y年%m月%d日%H时制作").GetBuffer()
	<<"\r\n-------------------------------------------------------------------\r\n"
		"-------------------------------------------------------------------\r\n"
		"天气形势分析: \r\n"                                                      
		"-------------------------------------------------------------------\r\n"
		"  24小时天气: \r\n"                                                        
		"    风向风速: 偏 风2-3级\r\n"                                                        
		"        温度: 最高温度：       最低温度：\r\n"                                                        
		"-------------------------------------------------------------------\r\n"
		"  48小时天气:\r\n"                                                        
		"-------------------------------------------------------------------\r\n"
		"    森林火险: 2\r\n"                                                          
		"-------------------------------------------------------------------\r\n\r\n"

		" 站  点       0-12小时天气   12-24小时天气    最高温度      最低温度\r\n"           
		"-------------------------------------------------------------------\r\n"
		"-------------------------------------------------------------------\r\n";

	fhead = stream.str();
}

//输出24小时天气状况，最高最低温度
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

//将数据写入文件
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
			output_weather(stream);//前24小时
			stream<<"\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"
				" 站  点       24-36小时天气   36-48小时天气    最高温度      最低温度\r\n"           
				"-------------------------------------------------------------------\r\n"
				"-------------------------------------------------------------------\r\n";
			output_weather(stream,2);//后24小时
			break;
		}
	default:break;
	}

	return stream.str();
}

//获取喷药级别
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	if(!is_czb_down_success)
	{
		CWnd * pbutton = GetDlgItem(IDC_BUTTON_SelfForcast);
		pbutton->SetWindowText("下载城镇报文件...");
		pbutton->EnableWindow(false);
	
		is_czb_down_success = FtpDownCzbFile();

		pbutton->SetWindowText("上传个人预报");
		pbutton->EnableWindow(true);
	}

	if(!is_czb_down_success)
	{
		MessageBox("下载城镇报文件失败！", "错误", MB_ICONERROR);
		return;
	}

	SelfForcast sf_dlg;
	sf_dlg.ftp_filename = GetFtpFilename();

	sf_dlg.DoModal();
}

// 获取当前时次城镇报的文件名
std::string CMessAtoBDlg::GetFtpFilename(void)
{
	CTime ct1=CTime::GetCurrentTime();//当前日期
	CTime ct2=ct1 - CTimeSpan(1, 0, 0, 0);

	//获得本地时间当前日期字符串
	CString tdate=ct1.Format("%Y%m%d"),  ldate=ct2.Format("%Y%m%d");

	std::string ftp_filename;//要下载的文件名

	switch(forcast_type)
	{
	case SMALLHOURS:
		{
			//早间04时预报 ：   			
			ftp_filename= "Z_SEVP_C_BFLB_"+ldate+"205000_P_RFFC-SPCC-"+tdate+"0000-07212.TXT";
			break;
		}
	case MORNING:
		{
			//早间县区预报20日6时 ：   			
			ftp_filename= "Z_SEVP_C_BFLB_"+ldate+"223500_P_RFFC-SPCC-"+tdate+"0000-16812.TXT";
			break;
		}
	case AM12121:
		{//12121预报19日10时：   
			ftp_filename = "Z_SEVP_C_BFLB_"+tdate+"022000_P_RFFC-SPCC-"+tdate+"0000-16812.TXT";
			break;
		}
	case AFTERNOON:
		{
			//下午县区预报19日16时 ：   
			ftp_filename= "Z_SEVP_C_BFLB_"+tdate+"082000_P_RFFC-SPCC-"+tdate+"1200-16812.TXT";
			break;
		}
	default:break;
	}

	return ftp_filename;
}

// MessAtoBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MessAtoB.h"
#include "MessAtoBDlg.h"
#include "SetWethDialog.h"

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
	: CDialog(CMessAtoBDlg::IDD, pParent),wht(whent())
	, weth(4,vector<string>(11,"")), teph(4,vector<double>(11,101))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	dealfhead(fhead);
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
//	ON_EN_CHANGE(IDC_EDIT1, &CMessAtoBDlg::OnEnChangeEdit1)
//ON_WM_CLOSE()
ON_BN_CLICKED(IDCANCEL, &CMessAtoBDlg::OnBnClickedCancel)
ON_BN_CLICKED(IDC_BUTTON2, &CMessAtoBDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON1, &CMessAtoBDlg::OnBnClickedButton1)
//ON_EN_CHANGE(IDC_EDIT1, &CMessAtoBDlg::OnEnChangeEdit1)
ON_WM_SIZE()
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


	

	if(wht == 2)
	{
		SetWindowText("早间12121预报  "+CTime::GetCurrentTime().Format("%Y年%m月%d日%H时"));
		GetDlgItem(ID_CHE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);

		fstr = dealf121();
		m_text.SetWindowTextA(fstr.c_str());

	}
	else
	{
		SetWindowText("城镇报-->县区预报  "+CTime::GetCurrentTime().Format("%Y年%m月%d日%H时"));
	}
	//m_text.ShowWindow(SW_SHOW);

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


void CMessAtoBDlg::OnBnClickedChe()
{
	// TODO: 在此添加控件通知处理程序代码
/**/	
	if(!FtpConnect(wht))   //下载城镇报文件失败
	{
		MessageBox("下载城镇报文件失败！", "错误", MB_ICONERROR);
		return;
	}

	if(!dealdata(weth,teph) )//处理数据
	{
		MessageBox("分析城镇报文件失败！", "错误", MB_ICONERROR);
		return;
	}

	fstr = fhead + dealfile(weth,teph,wht);
		
		//显示在编辑区
		m_text.SetWindowTextA(fstr.c_str());

	GetDlgItem(ID_CHE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);
}



void CMessAtoBDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(MessageBox("确定要退出吗?","程序退出",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		OnCancel();
	}
	
}

void CMessAtoBDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData();
	CString sfile;
	m_text.GetWindowText(sfile);
	
	fstr = sfile.GetBuffer();
	size_t p = fstr.find("洛阳");
	if(p != fstr.npos)
	{
		fhead = fstr.substr(0,p);
	}


	CSetWethDialog sd;

	sd.m_edit1 = weth[0][2].c_str();
	sd.m_edit2 = weth[1][2].c_str();
	sd.m_edit3 = weth[2][2].c_str();
	sd.m_edit4 = weth[3][2].c_str();

	if(sd.DoModal() == IDOK)
	{
		weth[0].assign(11,sd.m_edit1.GetBuffer());
		weth[1].assign(11,sd.m_edit2.GetBuffer());
		weth[2].assign(11,sd.m_edit3.GetBuffer());
		weth[3].assign(11,sd.m_edit4.GetBuffer());

		fstr = fhead + dealfile(weth,teph,wht);
		
		//显示在编辑区
		m_text.SetWindowTextA(fstr.c_str());
	}
}

void CMessAtoBDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString sfile;
	m_text.GetWindowText(sfile);
	sfile.Replace("\r\n","\n");

	fstr = sfile.GetBuffer();

	if(!strtofile("f.txt",fstr))    //数据保存为文件
	{
		MessageBox("文件保存失败，请重试！", "警告", MB_ICONERROR);
		return ;
	}



	CTime ct1=CTime::GetCurrentTime();//当前日期

	CString fpath = "//172.18.172.63/data_/xjdata/",
		      fname1 = ct1.Format("YBFB/xqyb/%Y%m%d.%H"),
			  fname2 = ct1.Format("FORECAST/dqyb/ly%Y%m%d%H.dq");
		
	//BOOL  s1 = CopyFile("f.txt", "f1.txt" , FALSE),
	//	    s2 = CopyFile("f.txt","f2.txt" , FALSE);
	
	BOOL  s1 = CopyFile("f.txt", fpath+fname1 , FALSE);

	if(wht == 2)
	{
		if(s1)
		MessageBox("送网 "+fname1+" 成功！","成功",MB_ICONINFORMATION);
		else
		MessageBox("送网 "+fname1+" 失败！", "警告", MB_ICONERROR);

		return;
	}

	BOOL s2 = CopyFile("f.txt", fpath+fname2 , FALSE);




	if(s1&&s2)
	{
		MessageBox("送网 "+fname1+" 成功!\n送网 "+fname2+" 成功！","成功",MB_ICONINFORMATION);
	}	
	else
	{
		if(s1)
		MessageBox("送网 "+fname1+" 成功！","成功",MB_ICONINFORMATION);
		else
		MessageBox("送网 "+fname1+" 失败！", "警告", MB_ICONERROR);

		if(s2)
		MessageBox("送网 "+fname2+" 成功！","成功",MB_ICONINFORMATION);
		else
		MessageBox("送网 "+fname2+" 失败！", "警告", MB_ICONERROR);
	}

}

//void CMessAtoBDlg::OnEnChangeEdit1()
//{
//
//}

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

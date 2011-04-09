// MessAtoBDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MessAtoB.h"
#include "MessAtoBDlg.h"
#include "SetWethDialog.h"

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


	

	if(wht == 2)
	{
		SetWindowText("���12121Ԥ��  "+CTime::GetCurrentTime().Format("%Y��%m��%d��%Hʱ"));
		GetDlgItem(ID_CHE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);

		fstr = dealf121();
		m_text.SetWindowTextA(fstr.c_str());

	}
	else
	{
		SetWindowText("����-->����Ԥ��  "+CTime::GetCurrentTime().Format("%Y��%m��%d��%Hʱ"));
	}
	//m_text.ShowWindow(SW_SHOW);

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


void CMessAtoBDlg::OnBnClickedChe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
/**/	
	if(!FtpConnect(wht))   //���س����ļ�ʧ��
	{
		MessageBox("���س����ļ�ʧ�ܣ�", "����", MB_ICONERROR);
		return;
	}

	if(!dealdata(weth,teph) )//��������
	{
		MessageBox("���������ļ�ʧ�ܣ�", "����", MB_ICONERROR);
		return;
	}

	fstr = fhead + dealfile(weth,teph,wht);
		
		//��ʾ�ڱ༭��
		m_text.SetWindowTextA(fstr.c_str());

	GetDlgItem(ID_CHE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);
}



void CMessAtoBDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox("ȷ��Ҫ�˳���?","�����˳�",MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		OnCancel();
	}
	
}

void CMessAtoBDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData();
	CString sfile;
	m_text.GetWindowText(sfile);
	
	fstr = sfile.GetBuffer();
	size_t p = fstr.find("����");
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
		
		//��ʾ�ڱ༭��
		m_text.SetWindowTextA(fstr.c_str());
	}
}

void CMessAtoBDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString sfile;
	m_text.GetWindowText(sfile);
	sfile.Replace("\r\n","\n");

	fstr = sfile.GetBuffer();

	if(!strtofile("f.txt",fstr))    //���ݱ���Ϊ�ļ�
	{
		MessageBox("�ļ�����ʧ�ܣ������ԣ�", "����", MB_ICONERROR);
		return ;
	}



	CTime ct1=CTime::GetCurrentTime();//��ǰ����

	CString fpath = "//172.18.172.63/data_/xjdata/",
		      fname1 = ct1.Format("YBFB/xqyb/%Y%m%d.%H"),
			  fname2 = ct1.Format("FORECAST/dqyb/ly%Y%m%d%H.dq");
		
	//BOOL  s1 = CopyFile("f.txt", "f1.txt" , FALSE),
	//	    s2 = CopyFile("f.txt","f2.txt" , FALSE);
	
	BOOL  s1 = CopyFile("f.txt", fpath+fname1 , FALSE);

	if(wht == 2)
	{
		if(s1)
		MessageBox("���� "+fname1+" �ɹ���","�ɹ�",MB_ICONINFORMATION);
		else
		MessageBox("���� "+fname1+" ʧ�ܣ�", "����", MB_ICONERROR);

		return;
	}

	BOOL s2 = CopyFile("f.txt", fpath+fname2 , FALSE);




	if(s1&&s2)
	{
		MessageBox("���� "+fname1+" �ɹ�!\n���� "+fname2+" �ɹ���","�ɹ�",MB_ICONINFORMATION);
	}	
	else
	{
		if(s1)
		MessageBox("���� "+fname1+" �ɹ���","�ɹ�",MB_ICONINFORMATION);
		else
		MessageBox("���� "+fname1+" ʧ�ܣ�", "����", MB_ICONERROR);

		if(s2)
		MessageBox("���� "+fname2+" �ɹ���","�ɹ�",MB_ICONINFORMATION);
		else
		MessageBox("���� "+fname2+" ʧ�ܣ�", "����", MB_ICONERROR);
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
	// TODO: �ڴ˴������Ϣ����������
}

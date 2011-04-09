// IntegrallerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Integraller.h"
#include "IntegrallerDlg.h"

#include "Integral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntegrallerDlg dialog

CIntegrallerDlg::CIntegrallerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIntegrallerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIntegrallerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIntegrallerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntegrallerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIntegrallerDlg, CDialog)
	//{{AFX_MSG_MAP(CIntegrallerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntegrallerDlg message handlers

BOOL CIntegrallerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIntegrallerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIntegrallerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIntegrallerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// 变步长梯形求积法
void CIntegrallerDlg::OnButton1() 
{
	// 建立CIntegral的子类，在其中重载函数Func
	class CInteg : public CIntegral
	{
		double Func(double x)
		{
			return exp(-x*x);
		}
	};

	// 求解
	CInteg Integ;
	double dblValue = Integ.GetValueTrapezia(0.0, 1.0);

	// 显示结果
	CString s;
	s.Format("积分值 = %f", dblValue);
	AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
}

// 变步长辛卜生求积法
void CIntegrallerDlg::OnButton2() 
{
	// 建立CIntegral的子类，在其中重载函数Func
	class CInteg : public CIntegral
	{
		double Func(double x)
		{
			return log(1.0+x)/(1.0+x*x);
		}
	};

	// 求解
	CInteg Integ;
	double dblValue = Integ.GetValueSimpson(0.0, 1.0);

	// 显示结果
	CString s;
	s.Format("积分值 = %f", dblValue);
	AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
}

// 自适应梯形求积法
void CIntegrallerDlg::OnButton3() 
{
	// 建立CIntegral的子类，在其中重载函数Func
	class CInteg : public CIntegral
	{
		double Func(double x)
		{
			return 1.0/(1.0+25.0*x*x);
		}
	};

	// 求解
	CInteg Integ;
	double dblValue = Integ.GetValueATrapezia(-1.0, 1.0, 0.0001);

	// 显示结果
	CString s;
	s.Format("积分值 = %f", dblValue);
	AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
}

// 龙贝格求积法
void CIntegrallerDlg::OnButton4() 
{
	// 建立CIntegral的子类，在其中重载函数Func
	class CInteg : public CIntegral
	{
		double Func(double x)
		{
			return x/(4.0+x*x);
		}
	};

	// 求解
	CInteg Integ;
	double dblValue = Integ.GetValueRomberg(0.0, 1.0);

	// 显示结果
	CString s;
	s.Format("积分值 = %f", dblValue);
	AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
}

// 计算一维积分的连分式法
void CIntegrallerDlg::OnButton5() 
{
	// 建立CIntegral的子类，在其中重载函数Func
	class CInteg : public CIntegral
	{
		double Func(double x)
		{
			return exp(-x*x);
		}
	};

	// 求解
	CInteg Integ;
	double dblValue = Integ.GetValuePq(0.0, 4.3);

	// 显示结果
	CString s;
	s.Format("积分值 = %f", dblValue);
	AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
}

// 高振荡函数求积法
void CIntegrallerDlg::OnButton6() 
{
    double s[2];
	double fa[4]={0.0,1.0,0.0,-3.0};
    double fb[4]={6.2831852,1.0,-6.2831852,-3.0};
    double a=0.0; 
	double b=6.2831852;
    int m=30; 
	int n=4;
	
	// 求解
	CIntegral Integ;
	double dblValue = Integ.GetValuePart(a, b, m, n, fa, fb, s);

	// 显示结果
	CString ss;
	ss.Format("s(0) = %e\ns(1) = %e", s[0], s[1]);
	AfxMessageBox(ss, MB_OK|MB_ICONINFORMATION);
}

// 勒让德－高斯求积法
void CIntegrallerDlg::OnButton7() 
{
	// 建立CIntegral的子类，在其中重载函数Func
	class CInteg : public CIntegral
	{
		double Func(double x)
		{
			return x*x+sin(x);
		}
	};

	// 求解
	CInteg Integ;
	double dblValue = Integ.GetValueLegdGauss(2.5, 8.4);

	// 显示结果
	CString s;
	s.Format("积分值 = %f", dblValue);
	AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
}

// 拉盖尔－高斯求积法
void CIntegrallerDlg::OnButton8() 
{
	// 建立CIntegral的子类，在其中重载函数Func
	class CInteg : public CIntegral
	{
		double Func(double x)
		{
			return x*exp(-x);
		}
	};

	// 求解
	CInteg Integ;
	double dblValue = Integ.GetValueLgreGauss();

	// 显示结果
	CString s;
	s.Format("积分值 = %f", dblValue);
	AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
}

// 埃尔米特－高斯求积法
void CIntegrallerDlg::OnButton9() 
{
	// 建立CIntegral的子类，在其中重载函数Func
	class CInteg : public CIntegral
	{
		double Func(double x)
		{
			return x*x*exp(-x*x);
		}
	};

	// 求解
	CInteg Integ;
	double dblValue = Integ.GetValueHermiteGauss();

	// 显示结果
	CString s;
	s.Format("积分值 = %f", dblValue);
	AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
}

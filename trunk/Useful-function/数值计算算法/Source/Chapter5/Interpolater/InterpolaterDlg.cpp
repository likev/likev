// InterpolaterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Interpolater.h"
#include "InterpolaterDlg.h"

#include "Interpolate.h"
#include "Spline3Dlg.h"

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
// CInterpolaterDlg dialog

CInterpolaterDlg::CInterpolaterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInterpolaterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterpolaterDlg)
	m_strXi = _T("");
	m_strYi = _T("");
	m_nNumNodes = 0;
	m_nNumTargetNodes = 1;
	m_strTargetXi = _T("");
	m_strStepOrBorderCondition = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInterpolaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterpolaterDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strXi);
	DDX_Text(pDX, IDC_EDIT2, m_strYi);
	DDX_Text(pDX, IDC_EDIT3, m_nNumNodes);
	DDX_Text(pDX, IDC_EDIT5, m_nNumTargetNodes);
	DDX_Text(pDX, IDC_EDIT6, m_strTargetXi);
	DDX_Text(pDX, IDC_EDIT4, m_strStepOrBorderCondition);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInterpolaterDlg, CDialog)
	//{{AFX_MSG_MAP(CInterpolaterDlg)
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
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_BUTTON16, OnButton16)
	ON_BN_CLICKED(IDC_BUTTON17, OnButton17)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterpolaterDlg message handlers

BOOL CInterpolaterDlg::OnInitDialog()
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

void CInterpolaterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CInterpolaterDlg::OnPaint() 
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
HCURSOR CInterpolaterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
10

0.10,0.15,0.25,0.40,0.50,0.57,0.70,0.85,0.93,1.00

0.904837,0.860708,0.778801,0.670320,0.606531,0.565525,0.496585,0.427415,0.394554,0.367879

1

0.63
*/
// 一元全区间不等距插值
void CInterpolaterDlg::OnButton1() 
{
	// 获取数据
	UpdateData();
	double *x = new double[m_nNumNodes];
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, m_nNumNodes, x, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	m_strTargetYi = "";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		double yt = CInterpolate::GetValueLagrange(m_nNumNodes, x, y, t[i]);
		CString s;
		s.Format("f(%f) = %f\r\n", t[i], yt);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] x;
	delete[] y;
}

/*
10

0.1

0.1;

0.904837,0.818731,0.740818,0.670320,0.606531,0.548812,0.496585,0.449329,0.406570,0.367879

3

0.25,0.63,0.95
*/
// 一元全区间等距插值
void CInterpolaterDlg::OnButton2() 
{
	// 获取数据
	UpdateData();
	double x0;
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, 1, &x0, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	double dblStep = atof(m_strStepOrBorderCondition);
	m_strTargetYi = "";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		double yt = CInterpolate::GetValueLagrange(m_nNumNodes, x0, dblStep, y, t[i]);
		CString s;
		s.Format("f(%f) = %f\r\n", t[i], yt);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] y;
}

/*
5

1.615,1.634,1.702,1.828,1.921

2.41450,2.46459,2.65271,3.03035,3.34066

2

1.682,1.813
*/
// 一元三点不等距插值
void CInterpolaterDlg::OnButton3() 
{
	// 获取数据
	UpdateData();
	double *x = new double[m_nNumNodes];
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, m_nNumNodes, x, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	m_strTargetYi = "";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		double yt = CInterpolate::GetValueLagrange3(m_nNumNodes, x, y, t[i]);
		CString s;
		s.Format("f(%f) = %f\r\n", t[i], yt);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] x;
	delete[] y;
}

/*
10

0.1

0.1

0.904837,0.818731,0.740818,0.670320,0.606531,0.548812,0.496585,0.449329,0.406570,0.367879

3

0.23,0.63,0.95
*/
// 一元三点等距插值
void CInterpolaterDlg::OnButton4() 
{
	// 获取数据
	UpdateData();
	double x0;
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, 1, &x0, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	double dblStep = atof(m_strStepOrBorderCondition);
	m_strTargetYi = "";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		double yt = CInterpolate::GetValueLagrange3(m_nNumNodes, x0, dblStep, y, t[i]);
		CString s;
		s.Format("f(%f) = %f\r\n", t[i], yt);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] y;
}

/*
10

-1.0,-0.8,-0.65,-0.4,-0.3,0.0,0.2,0.45,0.8,1.0

0.0384615,0.0588236,0.0864865,0.2,0.307692,1.0,0.5,0.164948,0.0588236,0.0384615

2

0.85,0.25
*/
// 连分式不等距插值
void CInterpolaterDlg::OnButton5() 
{
	// 获取数据
	UpdateData();
	double *x = new double[m_nNumNodes];
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, m_nNumNodes, x, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	m_strTargetYi = "";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		double yt = CInterpolate::GetValuePqs(m_nNumNodes, x, y, t[i]);
		CString s;
		s.Format("f(%f) = %f\r\n", t[i], yt);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] x;
	delete[] y;
}

/*
11

0.2

-1.0

0.0384615,0.0588236,0.1,0.2,0.5,1.0,0.5,0.2,0.1,0.0588236,0.0384615

2

-0.75, -0.05
*/
// 连分式等距插值
void CInterpolaterDlg::OnButton6() 
{
	// 获取数据
	UpdateData();
	double x0;
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, 1, &x0, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	double dblStep = atof(m_strStepOrBorderCondition);
	m_strTargetYi = "";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		double yt = CInterpolate::GetValuePqs(m_nNumNodes, x0, dblStep, y, t[i]);
		CString s;
		s.Format("f(%f) = %f\r\n", t[i], yt);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] y;
}

/*
10

0.1,0.15,0.3,0.45,0.55,0.6,0.7,0.85,0.9,1.0

0.904837,0.860708,0.740818,0.637628,0.576950,0.548812,0.496585,0.427415,0.406570,0.367879

1

0.356
*/
// 埃尔米特不等距插值
void CInterpolaterDlg::OnButton7() 
{
	// 获取数据
	UpdateData();
	double *x = new double[m_nNumNodes];
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, m_nNumNodes, x, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	double *dy = new double[m_nNumNodes];
	for (int i=0; i<m_nNumNodes; ++i)
		dy[i]=-y[i];

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	m_strTargetYi = "";
	for (i=0; i<m_nNumTargetNodes; ++i)
	{
		double yt = CInterpolate::GetValueHermite(m_nNumNodes, x, y, dy, t[i]);
		CString s;
		s.Format("f(%f) = %f\r\n", t[i], yt);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] dy;
	delete[] t;
	delete[] x;
	delete[] y;
}

/*
10

0.1

0.1

0.904837,0.818731,0.740818,0.670320,0.606531,0.548812,0.496585,0.449329,0.406570,0.367879

1

0.752
*/
// 埃尔米特等距插值
void CInterpolaterDlg::OnButton8() 
{
	// 获取数据
	UpdateData();
	double x0;
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, 1, &x0, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	double *dy = new double[m_nNumNodes];
	for (int i=0; i<m_nNumNodes; ++i)
		dy[i]=-y[i];

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	double dblStep = atof(m_strStepOrBorderCondition);
	m_strTargetYi = "";
	for (i=0; i<m_nNumTargetNodes; ++i)
	{
		double yt = CInterpolate::GetValueHermite(m_nNumNodes, x0, dblStep, y, dy, t[i]);
		CString s;
		s.Format("f(%f) = %f\r\n", t[i], yt);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] dy;
	delete[] t;
	delete[] y;
}

/*
10

-1.0,-0.8,-0.65,-0.4,-0.3,0.0,0.2,0.4,0.6,0.8,1.0

0.0384615,0.0588236,0.0864865,0.2,0.307692,1.0,0.5,0.2,0.1,0.0588236,0.0384615

2

-0.75,0.05
*/
// 埃特金不等距逐步插值
void CInterpolaterDlg::OnButton9() 
{
	// 获取数据
	UpdateData();
	double *x = new double[m_nNumNodes];
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, m_nNumNodes, x, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	m_strTargetYi = "";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		double yt = CInterpolate::GetValueAitken(m_nNumNodes, x, y, t[i]);
		CString s;
		s.Format("f(%f) = %f\r\n", t[i], yt);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] x;
	delete[] y;
}

/*
10

0.1

0.1

0.904837,0.818731,0.740818,0.670320,0.606531,0.548812,0.496585,0.449329,0.406570,0.367879

2

0.15,0.55
*/
// 埃特金等距逐步插值
void CInterpolaterDlg::OnButton10() 
{
	// 获取数据
	UpdateData();
	double x0;
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, 1, &x0, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	double dblStep = atof(m_strStepOrBorderCondition);
	m_strTargetYi = "";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		double yt = CInterpolate::GetValueAitken(m_nNumNodes, x0, dblStep, y, t[i]);
		CString s;
		s.Format("f(%f) = %f\r\n", t[i], yt);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] y;
}

/*
11

-1.0,-0.95,-0.75,-0.55,-0.3,0.0,0.2,0.45,0.6,0.8,1.0

0.0384615,0.0424403,0.06639,0.116788,0.307692,1.0,0.5,0.164948,0.1,0.0588236,0.0384615

2

-0.85,0.15
*/
// 光滑不等距插值
void CInterpolaterDlg::OnButton11() 
{
	// 获取数据
	UpdateData();
	double *x = new double[m_nNumNodes];
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, m_nNumNodes, x, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	m_strTargetYi = "";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		double dblCoef[5];
		double yt = CInterpolate::GetValueAkima(m_nNumNodes, x, y, t[i], dblCoef);
		CString s;
		s.Format("f(%f) = %f\r\ns0 = %f  s1 = %f  s2 = %f  s3 = %f\r\n\r\n", 
					t[i], yt, dblCoef[0], dblCoef[1], dblCoef[2], dblCoef[3]);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] x;
	delete[] y;
}

/*
11

0.2

-1.0

0.0384615,0.0588236,0.1,0.2,0.5,1.0,0.5,0.2,0.1,0.0588236,0.0384615

2

-0.65,0.25
*/
// 光滑等距插值
void CInterpolaterDlg::OnButton12() 
{
	// 获取数据
	UpdateData();
	double x0;
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, 1, &x0, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	// 显示结果
	double dblStep = atof(m_strStepOrBorderCondition);
	m_strTargetYi = "";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		double dblCoef[5];
		double yt = CInterpolate::GetValueAkima(m_nNumNodes, x0, dblStep, y, t[i], dblCoef);
		CString s;
		s.Format("f(%f) = %f\r\ns0 = %f  s1 = %f  s2 = %f  s3 = %f\r\n\r\n", 
					t[i], yt, dblCoef[0], dblCoef[1], dblCoef[2], dblCoef[3]);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] y;
}

/*
12

1.86548,-0.046115

0.52,8.0,17.95,28.65,50.65,104.6,156.6,260.7,364.4,468.0,507.0,520.0

5.28794,13.84,20.2,24.9,31.1,36.5,36.6,31.0,20.9,7.8,1.5,0.2

8

4.0,14.0,30.0,60.0,130.0,230.0,450.0,515.0
*/
// 第一种边界条件的三次样条函数插值、微商与积分
void CInterpolaterDlg::OnButton13() 
{
	// 获取数据
	UpdateData();
	double *x = new double[m_nNumNodes];
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, m_nNumNodes, x, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	double *dy = new double[m_nNumNodes];
	double *ddy = new double[m_nNumNodes];

	double dblTmp[2];
	CInterpolate::GetNodesFromString(m_strStepOrBorderCondition, 2, dblTmp, ",");
	dy[0] = dblTmp[0];
	dy[m_nNumNodes-1] = dblTmp[1];

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	double *z = new double[m_nNumTargetNodes];
	double *dz = new double[m_nNumTargetNodes];
	double *ddz = new double[m_nNumTargetNodes];
	
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	double yt = CInterpolate::GetValueSpline1(m_nNumNodes, x, y, dy, ddy, m_nNumTargetNodes, t, z, dz, ddz);

	// 显示结果
	m_strTargetYi.Format("积分值 ＝ %f\r\n\r\n", yt);
	m_strTargetYi += "    t[i]\t    z[i]\t    dz[i]\t    ddz[i]\r\n";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		CString s;
		s.Format("%f  %f  %f  %f\r\n", t[i], z[i], dz[i], ddz[i]);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] x;
	delete[] y;
	delete[] dy;
	delete[] ddy;
	delete[] z;
	delete[] dz;
	delete[] ddz;
}

/*
12

-0.279319,0.011156

0.52,8.0,17.95,28.65,50.65,104.6,156.6,260.7,364.4,468.0,507.0,520.0

5.28794,13.84,20.2,24.9,31.1,36.5,36.6,31.0,20.9,7.8,1.5,0.2

8

4.0,14.0,30.0,60.0,130.0,230.0,450.0,515.0
*/
// 第二种边界条件的三次样条函数插值、微商与积分
void CInterpolaterDlg::OnButton14() 
{
	// 获取数据
	UpdateData();
	double *x = new double[m_nNumNodes];
	double *y = new double[m_nNumNodes];
	CInterpolate::GetNodesFromString(m_strXi, m_nNumNodes, x, ",");
	CInterpolate::GetNodesFromString(m_strYi, m_nNumNodes, y, ",");

	double *dy = new double[m_nNumNodes];
	double *ddy = new double[m_nNumNodes];

	double dblTmp[2];
	CInterpolate::GetNodesFromString(m_strStepOrBorderCondition, 2, dblTmp, ",");
	ddy[0] = dblTmp[0];
	ddy[m_nNumNodes-1] = dblTmp[1];

	// 插值运算
	double *t = new double[m_nNumTargetNodes];
	double *z = new double[m_nNumTargetNodes];
	double *dz = new double[m_nNumTargetNodes];
	double *ddz = new double[m_nNumTargetNodes];
	
	CInterpolate::GetNodesFromString(m_strTargetXi, m_nNumTargetNodes, t, ",");

	double yt = CInterpolate::GetValueSpline2(m_nNumNodes, x, y, dy, ddy, m_nNumTargetNodes, t, z, dz, ddz);

	// 显示结果
	m_strTargetYi.Format("积分值 ＝ %f\r\n\r\n", yt);
	m_strTargetYi += "    t[i]\t    z[i]\t    dz[i]\t    ddz[i]\r\n";
	for (int i=0; i<m_nNumTargetNodes; ++i)
	{
		CString s;
		s.Format("%f  %f  %f  %f\r\n", t[i], z[i], dz[i], ddz[i]);
		m_strTargetYi += s;
	}
	AfxMessageBox(m_strTargetYi, MB_OK|MB_ICONINFORMATION);

	// 释放内存
	delete[] t;
	delete[] x;
	delete[] y;
	delete[] dy;
	delete[] ddy;
	delete[] z;
	delete[] dz;
	delete[] ddz;
}

/*
37

36
*/
// 第三种边界条件的三次样条函数插值、微商与积分
void CInterpolaterDlg::OnButton15() 
{
	// 获取数据
	UpdateData();

	double x[37], y[37], dy[37], ddy[37];
	double t[36], z[36], dz[36], ddz[36];

	for (int i=0; i<37; ++i)
	{
		x[i]=i*6.2831852/36.0;
        y[i]=sin(x[i]);
	}
	
	// 插值运算
	for (i=0; i<36; ++i)
	{
        t[i]=(0.5+i)*6.2831852/36.0;
	}

	double yt = CInterpolate::GetValueSpline3(37, x, y, dy, ddy, 36, t, z, dz, ddz);

	// 显示结果
	CString s, ss;
	s.Format("积分值 ＝ %f\r\n\r\n", yt);
    ss.Format(" x(i) y(i)=sin(x) dy(i)=cos(x) ddy(i)=-sin(x)\r\n\r\n");
	s += ss;
    ss.Format("%6.1f%10.6f%11.6f%12.6f\r\n",x[0],y[0],dy[0],ddy[0]);
	s += ss;
    for (i=0; i<36; i++)
    { 
		double u=t[i]*36.0/0.62831852;
        ss.Format("%6.1f%10.6f%11.6f%12.6f\r\n",u,z[i],dz[i],ddz[i]);
		s += ss;

        u=x[i+1]*36.0/0.62831852;
        int j=i+1;
        ss.Format("%6.1f%10.6f%11.6f%12.6f\r\n",u,y[j],dy[j],ddy[j]);
		s += ss;
    }

	CSpline3Dlg dlg;

	dlg.m_strResult = s;
	dlg.DoModal();

}

// 二元三点插值
void CInterpolaterDlg::OnButton16() 
{
	int i,j;
    double u,v,w;
    double x[6],y[5],z[30];

    for (i=0;i<=5;i++) 
		x[i]=0.2*i;
    for (j=0;j<=4;j++) 
		y[j]=0.25*j;
    for (i=0;i<=5;i++)
    {
		for (j=0;j<=4;j++)
			z[i*5+j]=exp(-(x[i]-y[j]));
	}

	// 插值运算
	CString s, ss;

    u = 0.9; 
	v = 0.8;
    w = CInterpolate::GetValueTqip(6, x, 5, y, z, u, v);
    s.Format("z(%f, %f) = %f\n",u,v,w);

    u = 0.3; 
	v = 0.9;
    w = CInterpolate::GetValueTqip(6, x, 5, y, z, u, v);
    ss.Format("z(%f, %f) = %f\n",u,v,w);

	s += ss;

	// 显示结果
	AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
}

// 二元全区间插值
void CInterpolaterDlg::OnButton17() 
{
	int i,j;
    double u,v,w;
    double x[11],y[11],z[121];

    for (i=0;i<=10;i++)
    { 
		x[i]=0.1*i; 
		y[i]=x[i];
	}
    
	for (i=0;i<=10;i++)
    {
		for (j=0;j<=10;j++)
			z[i*11+j]=exp(-(x[i]-y[j]));
	}

	// 插值运算
	CString s, ss;

    u=0.35; 
	v=0.65;
    w = CInterpolate::GetValueLagrange2(11, x, 11, y, z, u, v);
    s.Format("z(%f, %f) = %f\n",u,v,w);

    u=0.45; 
	v=0.55;
    w = CInterpolate::GetValueLagrange2(11, x, 11, y, z, u, v);
    ss.Format("z(%f, %f) = %f\n",u,v,w);

	s += ss;

	// 显示结果
	AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
}

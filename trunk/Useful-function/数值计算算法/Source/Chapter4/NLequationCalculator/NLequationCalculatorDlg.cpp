// NLequationCalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NLequationCalculator.h"
#include "NLequationCalculatorDlg.h"
#include "NLequation.h"

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
// CNLequationCalculatorDlg dialog

CNLequationCalculatorDlg::CNLequationCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNLequationCalculatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNLequationCalculatorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNLequationCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNLequationCalculatorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNLequationCalculatorDlg, CDialog)
	//{{AFX_MSG_MAP(CNLequationCalculatorDlg)
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNLequationCalculatorDlg message handlers

BOOL CNLequationCalculatorDlg::OnInitDialog()
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

void CNLequationCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNLequationCalculatorDlg::OnPaint() 
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
HCURSOR CNLequationCalculatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// 求非线性方程实根的对分法
void CNLequationCalculatorDlg::OnButton1() 
{
	// 建立CNLequation的子类，在其中重载函数Func
	class CNLeq : public CNLequation
	{
		double Func(double x)
		{
			double z = (((((x-5.0)*x+3.0)*x+1.0)*x-7.0)*x+7.0)*x-20.0;
			return z;
		}
	};

	// 求解
	CNLeq nleq;
	double x[6];
	int n = nleq.GetRootBisect(6, x, -2, 5, 0.2);

	// 显示结果
	CString sMsg;
	sMsg.Format("求得如下 %d 个根：\n\n", n);
	CString ss;
    for (int i=0; i<=n-1; i++)
	{
		ss.Format("x(%d) = %f\n",i,x[i]);
		sMsg += ss;
	}

    AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求非线性方程一个实根的牛顿法
void CNLequationCalculatorDlg::OnButton2() 
{
	// 建立CNLequation的子类，在其中重载函数Func
	class CNLeq : public CNLequation
	{
		void Func(double x, double y[])
		{
			y[0]=x*x*(x-1.0)-1.0;
			y[1]=3.0*x*x-2.0*x;
		}
	};

	// 求解
	CNLeq nleq;
	double x = 1.5;
	int bRet = nleq.GetRootNewton(&x);

	// 显示结果
	CString sMsg;
	if (bRet)
		sMsg.Format("求得的一个实根为：\n\nx = %f\n", x);
	else
		sMsg = "求解失败";
		
	AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求非线性方程一个实根的埃特金迭代法
void CNLequationCalculatorDlg::OnButton3() 
{
	// 建立CNLequation的子类，在其中重载函数Func
	class CNLeq : public CNLequation
	{
		double Func(double x)
		{
		    double y = 6.0-x*x;

			return y;
		}
	};

	// 求解
	CNLeq nleq;
	double x = 0.0;
	int bRet = nleq.GetRootAitken(&x);

	// 显示结果
	CString sMsg;
	if (bRet)
		sMsg.Format("求得的一个实根为：\n\nx = %f\n", x);
	else
		sMsg = "求解失败";
		
	AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求非线性方程一个实根的连分式解法
void CNLequationCalculatorDlg::OnButton4() 
{
	// 建立CNLequation的子类，在其中重载函数Func
	class CNLeq : public CNLequation
	{
		double Func(double x)
		{
		    double y = x*x*(x-1.0)-1.0;

			return y;
		}
	};

	// 求解
	CNLeq nleq;
	double x = 1.0;
	int bRet = nleq.GetRootPq(&x);

	// 显示结果
	CString sMsg;
	if (bRet)
		sMsg.Format("求得的一个实根为：\n\nx = %f\n", x);
	else
		sMsg = "求解失败";
		
	AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求实系数代数方程全部根的QR方法
void CNLequationCalculatorDlg::OnButton5() 
{
	// 求解
	CNLequation nleq;
	double xr[6], xi[6];
	double a[7] = {-30.0,10.5,-10.5,1.5,4.5,-7.5,1.5};
	int n = 6;
	int bRet = nleq.GetRootQr(n, a, xr, xi);

	// 显示结果
	CString sMsg;
	if (bRet)
	{
		sMsg.Format("求得的 %d 个根为：\n\n", n);
		for (int i=0; i<n; ++i)
		{
			CComplex root;
			root.SetReal(xr[i]);
			root.SetImag(xi[i]);

			CString ss;
			ss.Format("x(%d) = %s\n", i, root.ToString());

			sMsg += ss;
		}
	}
	else
		sMsg = "求解失败";
		
	AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求实系数代数方程全部根的牛顿下山法
void CNLequationCalculatorDlg::OnButton6() 
{
	// 求解
	CNLequation nleq;
	double xr[6], xi[6];
	double a[7] = {-20.0,7.0,-7.0,1.0,3.0,-5.0,1.0};
	int n = 6;
	int bRet = nleq.GetRootNewtonDownHill(n, a, xr, xi);

	// 显示结果
	CString sMsg;
	if (bRet)
	{
		sMsg.Format("求得的 %d 个根为：\n\n", n);
		for (int i=0; i<n; ++i)
		{
			CComplex root;
			root.SetReal(xr[i]);
			root.SetImag(xi[i]);

			CString ss;
			ss.Format("x(%d) = %s\n", i, root.ToString());

			sMsg += ss;
		}
	}
	else
		sMsg = "求解失败";
		
	AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求复系数代数方程全部根的牛顿下山法
void CNLequationCalculatorDlg::OnButton7() 
{
	// 求解
	CNLequation nleq;
	double xr[5], xi[5];
    double ar[6]={0.1,21.33,4.9,0.0,3.0,1.0};
    double ai[6]={-100.0,0.0,-19.0,-0.01,2.0,0.0};
	int n = 5;
	int bRet = nleq.GetRootNewtonDownHill(n, ar, ai, xr, xi);

	// 显示结果
	CString sMsg;
	if (bRet)
	{
		sMsg.Format("求得的 %d 个根为：\n\n", n);
		for (int i=0; i<n; ++i)
		{
			CComplex root;
			root.SetReal(xr[i]);
			root.SetImag(xi[i]);

			CString ss;
			ss.Format("x(%d) = %s\n", i, root.ToString());

			sMsg += ss;
		}
	}
	else
		sMsg = "求解失败";
		
	AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求非线性方程一个实根的蒙特卡洛法
void CNLequationCalculatorDlg::OnButton8() 
{
	// 建立CNLequation的子类，在其中重载函数Func
	class CNLeq : public CNLequation
	{
		double Func(double x)
		{
			double z = exp(-x*x*x)-sin(x)/cos(x)+800.0;
			return z;
		}
	};

	// 求解
	CNLeq nleq;
    double x=0.5; 
	double b=1.0; 
	int m=10;
	nleq.GetRootMonteCarlo(&x, b, m);

	// 显示结果
	CString sMsg;
	sMsg.Format("求得的一个根为：\n\nx = %f", x);

    AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求实函数或复函数方程一个复根的蒙特卡洛法
void CNLequationCalculatorDlg::OnButton9() 
{
	// 建立CNLequation的子类，在其中重载函数Func
	class CNLeq : public CNLequation
	{
		double Func(double x, double y)
		{
			double u=x*x-y*y-6.0*x+13.0;
			double v=2.0*x*y-6.0*y;
			double z=sqrt(u*u+v*v);
			return z;
		}
	};

	// 求解
	CNLeq nleq;
    double x=0.5; 
	double y=0.5; 
	double b=1.0; 
	int m=10;
	nleq.GetRootMonteCarlo(&x, &y, b, m);

	// 构造复数
	CComplex root(x, y);

	// 显示结果
	CString sMsg;
	sMsg.Format("求得的一个根为：\n\nx = %s", root.ToString());

    AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求非线性方程组一组实根的梯度法
void CNLequationCalculatorDlg::OnButton10() 
{
	// 建立CNLequation的子类，在其中重载函数Func
	class CNLeq : public CNLequation
	{
		double Func(double x[], double y[])
		{
			double z,f1,f2,f3,df1,df2,df3;

			f1=x[0]-5.0*x[1]*x[1]+7.0*x[2]*x[2]+12.0;
			f2=3.0*x[0]*x[1]+x[0]*x[2]-11.0*x[0];
			f3=2.0*x[1]*x[2]+40.0*x[0];
			z=f1*f1+f2*f2+f3*f3;
			
			df1=1.0; 
			df2=3.0*x[1]+x[2]-11.0; 
			df3=40.0;
			
			y[0]=2.0*(f1*df1+f2*df2+f3*df3);
			df1=10.0*x[1]; 
			df2=3.0*x[0]; 
			df3=2.0*x[2];
			
			y[1]=2.0*(f1*df1+f2*df2+f3*df3);
			df1=14.0*x[2]; 
			df2=x[0]; 
			df3=2.0*x[1];
			y[2]=2.0*(f1*df1+f2*df2+f3*df3);
			
			return(z);
		}
	};

	// 求解
	CNLeq nleq;
    double x[3]={1.5,6.5,-5.0};
	int n = 3;
    int nMaxIt = 600;
	BOOL bRet = nleq.GetRootsetGrad(n, x, nMaxIt);

	// 显示结果
	CString sMsg;
	if (bRet)
	{
		sMsg.Format("求得的 %d 个根为：\n\n", n);
		for (int i=0; i<n; ++i)
		{
			CString ss;
			ss.Format("x(%d) = %f\n", i, x[i]);

			sMsg += ss;
		}
	}
	else
		sMsg = "求解失败";
		
	AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求非线性方程组一组实根的拟牛顿法
void CNLequationCalculatorDlg::OnButton11() 
{
	// 建立CNLequation的子类，在其中重载函数Func
	class CNLeq : public CNLequation
	{
		double Func(double x[], double y[])
		{
			y[0]=x[0]*x[0]+x[1]*x[1]+x[2]*x[2]-1.0;
			y[1]=2.0*x[0]*x[0]+x[1]*x[1]-4.0*x[2];
			y[2]=3.0*x[0]*x[0]-4.0*x[1]+x[2]*x[2];

			return 0.0;
		}
	};

	// 求解
	CNLeq nleq;
    double x[3]={1.0,1.0,1.0};
    double t=0.1; 
	double h=0.1;
	int n = 3;
    int nMaxIt = 100;
	BOOL bRet = nleq.GetRootsetNewton(n, x, t, h, nMaxIt);

	// 显示结果
	CString sMsg;
	if (bRet)
	{
		sMsg.Format("求得的 %d 个根为：\n\n", n);
		for (int i=0; i<n; ++i)
		{
			CString ss;
			ss.Format("x(%d) = %f\n", i, x[i]);

			sMsg += ss;
		}
	}
	else
		sMsg = "求解失败";
		
	AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求非线性方程组最小二乘解的广义逆法
void CNLequationCalculatorDlg::OnButton12() 
{
	// 建立CNLequation的子类，在其中重载函数Func
	class CNLeq : public CNLequation
	{
		double Func(double x[], double y[])
		{
			y[0]=x[0]*x[0]+7.0*x[0]*x[1]+3.0*x[1]*x[1]+0.5;
			y[1]=x[0]*x[0]-2.0*x[0]*x[1]+x[1]*x[1]-1.0;
			y[2]=x[0]+x[1]+1.0;

			return 0.0;
		}
		void FuncMJ(int n, double x[], double p[])
		{
			p[0*n+0]=2.0*x[0]+7.0*x[1];
			p[0*n+1]=7.0*x[0]+6.0*x[1];
			p[1*n+0]=2.0*x[0]-2.0*x[1];
			p[1*n+1]=-2.0*x[0]+2.0*x[1];
			p[2*n+0]=1.0;
			p[2*n+1]=1.0;
		}
	};

	// 求解
	CNLeq nleq;
    double eps1 = 0.000001;
	double eps2 = 0.000001;
    double x[2]={1.0,-1.0};
    int m=3; 
	int n=2;
	BOOL bRet = nleq.GetRootsetGinv(m, n, x, eps1, eps2);

	// 显示结果
	CString sMsg;
	if (bRet)
	{
		sMsg.Format("求得的 %d 个根为：\n\n", n);
		for (int i=0; i<n; ++i)
		{
			CString ss;
			ss.Format("x(%d) = %f\n", i, x[i]);

			sMsg += ss;
		}
	}
	else
		sMsg = "求解失败";
		
	AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

// 求非线性方程组一组实根的蒙特卡洛法
void CNLequationCalculatorDlg::OnButton13() 
{
	// 建立CNLequation的子类，在其中重载函数Func
	class CNLeq : public CNLequation
	{
		double Func(int n, double x[])
		{ 
			double f,f1,f2,f3;
			n=n;
			f1=3.0*x[0]+x[1]+2.0*x[2]*x[2]-3.0;
			f2=-3.0*x[0]+5.0*x[1]*x[1]+2.0*x[0]*x[2]-1.0;
			f3=25.0*x[0]*x[1]+20.0*x[2]+12.0;
			f=sqrt(f1*f1+f2*f2+f3*f3);
			return(f);
		}
	};

	// 求解
	CNLeq nleq;
    double x[3]={0.0,0.0,0.0};
    double b=2.0; 
	int m=10; 
	int n=3; 
	double eps=0.000001;
	nleq.GetRootsetMonteCarlo(n, x, b, m, eps);

	// 显示结果
	CString sMsg;
	sMsg.Format("求得的 %d 个根为：\n\n", n);
	for (int i=0; i<n; ++i)
	{
		CString ss;
		ss.Format("x(%d) = %f\n", i, x[i]);

		sMsg += ss;
	}
		
	AfxMessageBox(sMsg, MB_OK|MB_ICONINFORMATION);
}

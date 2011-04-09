// ComplexCalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComplexCalculator.h"
#include "ComplexCalculatorDlg.h"

#include "Complex.h"

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
// CComplexCalculatorDlg dialog

CComplexCalculatorDlg::CComplexCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComplexCalculatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComplexCalculatorDlg)
	m_dblA = 0.0;
	m_dblB = 0.0;
	m_dblC = 0.0;
	m_dblD = 0.0;
	m_strResult = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComplexCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComplexCalculatorDlg)
	DDX_Text(pDX, IDC_EDIT1, m_dblA);
	DDX_Text(pDX, IDC_EDIT2, m_dblB);
	DDX_Text(pDX, IDC_EDIT3, m_dblC);
	DDX_Text(pDX, IDC_EDIT4, m_dblD);
	DDX_Text(pDX, IDC_EDIT5, m_strResult);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CComplexCalculatorDlg, CDialog)
	//{{AFX_MSG_MAP(CComplexCalculatorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComplexCalculatorDlg message handlers

BOOL CComplexCalculatorDlg::OnInitDialog()
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

void CComplexCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CComplexCalculatorDlg::OnPaint() 
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
HCURSOR CComplexCalculatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// 乘法
void CComplexCalculatorDlg::OnButton1() 
{
	// 获取数据
	UpdateData();

	// 构造复数
	CComplex cpxA(m_dblA, m_dblB);
	CComplex cpxB(m_dblC, m_dblD);
	
	// 计算复数乘法
	CComplex cpxC = cpxA*cpxB;

	// 将结果转化为字符串
	m_strResult = cpxC.ToString();
	// 显示结果
	UpdateData(FALSE);
}

// 除法
void CComplexCalculatorDlg::OnButton2() 
{
	// 获取数据
	UpdateData();

	// 构造复数
	CComplex cpxA(m_dblA, m_dblB);
	CComplex cpxB(m_dblC, m_dblD);

	// 计算复数除法
	CComplex cpxC = cpxA/cpxB;

	// 将结果转化为字符串
	m_strResult = cpxC.ToString();

	// 显示结果
	UpdateData(FALSE);
}

// 根
void CComplexCalculatorDlg::OnButton3() 
{
	// 获取数据
	UpdateData();

	// 构造复数
	CComplex cpxA(m_dblA, m_dblB);
	// 根次
	int n = (int)m_dblC;
	// 构造存储根的复数组
	CComplex* pcpxR = new CComplex[n];

	// 计算复数的根
	cpxA.Root(n, pcpxR);

	// 将结果转化为字符串
	m_strResult = "";
	for (int i=0; i<n; ++i)
	{
		m_strResult += pcpxR[i].ToString();
		if (i != n-1)
			m_strResult += ", ";
	}

	// 显示结果
	UpdateData(FALSE);
}

// 模
void CComplexCalculatorDlg::OnButton4() 
{
	// 获取数据
	UpdateData();

	// 构造复数
	CComplex cpxA(m_dblA, m_dblB);

	// 计算复数模，并将结果转化为字符串
	m_strResult.Format("%f", cpxA.Abs());

	// 显示结果
	UpdateData(FALSE);
}

// 自然对数
void CComplexCalculatorDlg::OnButton6() 
{
	// 获取数据
	UpdateData();

	// 构造复数
	CComplex cpxA(m_dblA, m_dblB);

	// 计算复数自然对数，并将结果转化为字符串
	m_strResult = cpxA.Log().ToString();

	// 显示结果
	UpdateData(FALSE);
}

// 实幂
void CComplexCalculatorDlg::OnButton5() 
{
	// 获取数据
	UpdateData();

	// 构造复数
	CComplex cpxA(m_dblA, m_dblB);

	// 计算复数的实数幂
	CComplex cpxC = cpxA.Pow(m_dblC);

	// 将结果转化为字符串
	m_strResult = cpxC.ToString();

	// 显示结果
	UpdateData(FALSE);
}

// 复幂
void CComplexCalculatorDlg::OnButton10() 
{
	// 获取数据
	UpdateData();

	// 构造复数
	CComplex cpxA(m_dblA, m_dblB);
	CComplex cpxB(m_dblC, m_dblD);

	// 计算复数的复数幂
	CComplex cpxC = cpxA.Pow(cpxB, 0);

	// 将结果转化为字符串
	m_strResult = cpxC.ToString();
	// 显示结果
	UpdateData(FALSE);
}

// 正弦
void CComplexCalculatorDlg::OnButton7() 
{
	// 获取数据
	UpdateData();

	// 构造复数
	CComplex cpxA(m_dblA, m_dblB);

	// 计算复数的正弦，并将结果转化为字符串
	m_strResult = cpxA.Sin().ToString();

	// 显示结果
	UpdateData(FALSE);
}

// 余弦
void CComplexCalculatorDlg::OnButton8() 
{
	// 获取数据
	UpdateData();

	// 构造复数
	CComplex cpxA(m_dblA, m_dblB);

	// 计算复数的余弦，并将结果转化为字符串
	m_strResult = cpxA.Cos().ToString();

	// 显示结果
	UpdateData(FALSE);
}

// 正切
void CComplexCalculatorDlg::OnButton9() 
{
	// 获取数据
	UpdateData();

	// 构造复数
	CComplex cpxA(m_dblA, m_dblB);

	// 计算复数的正切，并将结果转化为字符串
	m_strResult = cpxA.Tan().ToString();

	// 显示结果
	UpdateData(FALSE);
}

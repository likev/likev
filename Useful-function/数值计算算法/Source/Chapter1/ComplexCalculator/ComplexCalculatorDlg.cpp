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

// �˷�
void CComplexCalculatorDlg::OnButton1() 
{
	// ��ȡ����
	UpdateData();

	// ���츴��
	CComplex cpxA(m_dblA, m_dblB);
	CComplex cpxB(m_dblC, m_dblD);
	
	// ���㸴���˷�
	CComplex cpxC = cpxA*cpxB;

	// �����ת��Ϊ�ַ���
	m_strResult = cpxC.ToString();
	// ��ʾ���
	UpdateData(FALSE);
}

// ����
void CComplexCalculatorDlg::OnButton2() 
{
	// ��ȡ����
	UpdateData();

	// ���츴��
	CComplex cpxA(m_dblA, m_dblB);
	CComplex cpxB(m_dblC, m_dblD);

	// ���㸴������
	CComplex cpxC = cpxA/cpxB;

	// �����ת��Ϊ�ַ���
	m_strResult = cpxC.ToString();

	// ��ʾ���
	UpdateData(FALSE);
}

// ��
void CComplexCalculatorDlg::OnButton3() 
{
	// ��ȡ����
	UpdateData();

	// ���츴��
	CComplex cpxA(m_dblA, m_dblB);
	// ����
	int n = (int)m_dblC;
	// ����洢���ĸ�����
	CComplex* pcpxR = new CComplex[n];

	// ���㸴���ĸ�
	cpxA.Root(n, pcpxR);

	// �����ת��Ϊ�ַ���
	m_strResult = "";
	for (int i=0; i<n; ++i)
	{
		m_strResult += pcpxR[i].ToString();
		if (i != n-1)
			m_strResult += ", ";
	}

	// ��ʾ���
	UpdateData(FALSE);
}

// ģ
void CComplexCalculatorDlg::OnButton4() 
{
	// ��ȡ����
	UpdateData();

	// ���츴��
	CComplex cpxA(m_dblA, m_dblB);

	// ���㸴��ģ���������ת��Ϊ�ַ���
	m_strResult.Format("%f", cpxA.Abs());

	// ��ʾ���
	UpdateData(FALSE);
}

// ��Ȼ����
void CComplexCalculatorDlg::OnButton6() 
{
	// ��ȡ����
	UpdateData();

	// ���츴��
	CComplex cpxA(m_dblA, m_dblB);

	// ���㸴����Ȼ�������������ת��Ϊ�ַ���
	m_strResult = cpxA.Log().ToString();

	// ��ʾ���
	UpdateData(FALSE);
}

// ʵ��
void CComplexCalculatorDlg::OnButton5() 
{
	// ��ȡ����
	UpdateData();

	// ���츴��
	CComplex cpxA(m_dblA, m_dblB);

	// ���㸴����ʵ����
	CComplex cpxC = cpxA.Pow(m_dblC);

	// �����ת��Ϊ�ַ���
	m_strResult = cpxC.ToString();

	// ��ʾ���
	UpdateData(FALSE);
}

// ����
void CComplexCalculatorDlg::OnButton10() 
{
	// ��ȡ����
	UpdateData();

	// ���츴��
	CComplex cpxA(m_dblA, m_dblB);
	CComplex cpxB(m_dblC, m_dblD);

	// ���㸴���ĸ�����
	CComplex cpxC = cpxA.Pow(cpxB, 0);

	// �����ת��Ϊ�ַ���
	m_strResult = cpxC.ToString();
	// ��ʾ���
	UpdateData(FALSE);
}

// ����
void CComplexCalculatorDlg::OnButton7() 
{
	// ��ȡ����
	UpdateData();

	// ���츴��
	CComplex cpxA(m_dblA, m_dblB);

	// ���㸴�������ң��������ת��Ϊ�ַ���
	m_strResult = cpxA.Sin().ToString();

	// ��ʾ���
	UpdateData(FALSE);
}

// ����
void CComplexCalculatorDlg::OnButton8() 
{
	// ��ȡ����
	UpdateData();

	// ���츴��
	CComplex cpxA(m_dblA, m_dblB);

	// ���㸴�������ң��������ת��Ϊ�ַ���
	m_strResult = cpxA.Cos().ToString();

	// ��ʾ���
	UpdateData(FALSE);
}

// ����
void CComplexCalculatorDlg::OnButton9() 
{
	// ��ȡ����
	UpdateData();

	// ���츴��
	CComplex cpxA(m_dblA, m_dblB);

	// ���㸴�������У��������ת��Ϊ�ַ���
	m_strResult = cpxA.Tan().ToString();

	// ��ʾ���
	UpdateData(FALSE);
}

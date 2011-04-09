// LECalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LECalculator.h"
#include "LECalculatorDlg.h"
#include "LEquations.h"
#include "ImagDataDlg.h"
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
// CLECalculatorDlg dialog

CLECalculatorDlg::CLECalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLECalculatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLECalculatorDlg)
	m_strCoefficient = _T("");
	m_strConstant = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLECalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLECalculatorDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strCoefficient);
	DDX_Text(pDX, IDC_EDIT2, m_strConstant);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLECalculatorDlg, CDialog)
	//{{AFX_MSG_MAP(CLECalculatorDlg)
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLECalculatorDlg message handlers

BOOL CLECalculatorDlg::OnInitDialog()
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

void CLECalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLECalculatorDlg::OnPaint() 
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
HCURSOR CLECalculatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
0.2368,0.2471,0.2568,1.2671
0.1968,0.2071,1.2168,0.2271
0.1581,1.1675,0.1768,0.1871
1.1161,0.1254,0.1397,0.1490

1.8471
1.7471
1.6471
1.5471
*/
// ȫѡ��Ԫ��˹��ȥ��
void CLECalculatorDlg::OnButton1() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ȫѡ��Ԫ��˹��ȥ��
	if (leqs.GetRootsetGauss(mtxC))
		m_strResult = mtxC.ToString(" ");
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,3.0,2.0,13.0
7.0,2.0,1.0,-2.0
9.0,15.0,3.0,-2.0
-2.0,-2.0,11.0,5.0

9.0,0.0
6.0,4.0
11.0,7.0
-2.0,-1.0
*/
// ȫѡ��Ԫ��˹��Լ����ȥ��
void CLECalculatorDlg::OnButton2() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ȫѡ��Ԫ��˹��Լ����ȥ��
	if (leqs.GetRootsetGaussJordan(mtxC))
		m_strResult = mtxC.ToString(" ");
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,3.0,2.0,13.0
7.0,2.0,1.0,-2.0
9.0,15.0,3.0,-2.0
-2.0,-2.0,11.0,5.0

3.0,-2.0,1.0,6.0
-2.0,7.0,5.0,8.0
9.0,-3.0,15.0,1.0
-2.0,-2.0,7.0,6.0

2.0
7.0
3.0
9.0

1.0
2.0
-2.0
3.0
*/
// ��ϵ���������ȫѡ��Ԫ��˹��ȥ��
void CLECalculatorDlg::OnButton3() 
{
	// ��ȡϵ���ͳ���������鲿��������
	CImagDataDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxAI, mtxBI, mtxC, mtxCI;

	// ��ʼ��ϵ������ʵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ��ϵ������ʵ������
	mtxB.FromString(m_strConstant, ",");

	// ��ʼ��ϵ�������鲿����
	mtxAI.FromString(dlg.m_strCoefficient, ",");
	// ��ʼ��ϵ�������鲿����
	mtxBI.FromString(dlg.m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ��ϵ���������ȫѡ��Ԫ��˹��ȥ��
	if (leqs.GetRootsetGauss(mtxAI, mtxBI, mtxC, mtxCI))
	{
		for (int i=0; i<mtxA.GetNumColumns(); ++i)
		{
			CComplex cpxS(mtxC.GetElement(i, 0), mtxCI.GetElement(i, 0));
			m_strResult += cpxS.ToString() + "\r\n";
		}
	}
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,3.0,2.0,13.0
7.0,2.0,1.0,-2.0
9.0,15.0,3.0,-2.0
-2.0,-2.0,11.0,5.0

3.0,-2.0,1.0,6.0
-2.0,7.0,5.0,8.0
9.0,-3.0,15.0,1.0
-2.0,-2.0,7.0,6.0

2.0,-2.0
7.0,3.0
3.0,2.0
9.0,1.0

1.0,3.0
2.0,7.0
-2.0,9.0
3.0,2.0
*/
// ��ϵ���������ȫѡ��Ԫ��˹��Լ����ȥ��
void CLECalculatorDlg::OnButton4() 
{
	// ��ȡϵ���ͳ���������鲿��������
	CImagDataDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxAI, mtxBI, mtxC, mtxCI;

	// ��ʼ��ϵ������ʵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ��ϵ������ʵ������
	mtxB.FromString(m_strConstant, ",");

	// ��ʼ��ϵ�������鲿����
	mtxAI.FromString(dlg.m_strCoefficient, ",");
	// ��ʼ��ϵ�������鲿����
	mtxBI.FromString(dlg.m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ��ϵ���������ȫѡ��Ԫ��˹��Լ����ȥ��
	if (leqs.GetRootsetGaussJordan(mtxAI, mtxBI, mtxC, mtxCI))
	{
		for (int i=0; i<mtxA.GetNumColumns(); ++i)
		{
			CComplex cpxS1(mtxC.GetElement(i, 0), mtxCI.GetElement(i, 0));
			CComplex cpxS2(mtxC.GetElement(i, 1), mtxCI.GetElement(i, 1));
			m_strResult += cpxS1.ToString() + " , " + cpxS2.ToString() + "\r\n";
		}
	}
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
13,12,0,0,0
11,10,9,0,0
 0, 8,7,6,0
 0, 0,5,4,3
 0, 0,0,2,1

3.0
0.0
-2.0
6.0
8.0
*/
// ������Խ��߷������׷�Ϸ�
void CLECalculatorDlg::OnButton5() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ������Խ��߷������׷�Ϸ�
	if (leqs.GetRootsetTriDiagonal(mtxC))
		m_strResult = mtxC.ToString(" ");
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
3.0,-4.0,1.0,0.0,0.0,0,0,0
-2.0,-5.0,6.0,1.0,0.0,0,0,0
1.0,3.0,-1.0,2.0,-3.0,0,0,0
0,2.0,5.0,-5.0,6.0,-1.0,0,0
0,0,-3.0,1.0,-1.0,2.0,-5.0,0
0,0,0,6.0,1.0,-3.0,2.0,-9.0
0,0,0,0,-4.0,1.0,-1.0,2.0
0,0,0,0,0,5.0,1.0,-7.0

13.0,29.0,-13.0
-6.0,17.0,-21.0
-31.0,-6.0,4.0
64.0,3.0,16.0
-20.0,1.0,-5.0
-22.0,-41.0,56.0
-29.0,10.0,-21.0
7.0,-24.0,20.0
*/
// һ����ͷ���������
void CLECalculatorDlg::OnButton6() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// һ����ͷ���������
	if (leqs.GetRootsetBand(5, mtxC))
		m_strResult = mtxC.ToString(" ");
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
5.0,7.0,6.0,5.0,1.0
7.0,10.0,8.0,7.0,2.0
6.0,8.0,10.0,9.0,3.0
5.0,7.0,9.0,10.0,4.0
1.0,2.0,3.0,4.0,5.0

24.0,96.0
34.0,136.0
36.0,144.0
35.0,140.0
15.0,60.0
*/
// ���ԳƷ�����ķֽⷨ
void CLECalculatorDlg::OnButton7() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ���ԳƷ�����ķֽⷨ
	if (leqs.GetRootsetDjn(mtxC))
		m_strResult = mtxC.ToString(" ");
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
5.0,7.0,6.0,5.0
7.0,10.0,8.0,7.0
6.0,8.0,10.0,9.0
5.0,7.0,9.0,10.0

23.0,92.0
32.0,128.0
33.0,132.0
31.0,124.0
*/
// ���Գ������������ƽ������
void CLECalculatorDlg::OnButton8() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ���Գ������������ƽ������
	if (leqs.GetRootsetCholesky(mtxC))
		m_strResult = mtxC.ToString(" ");
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
0.0,0.0,-1.0,0.0,0.0,0.0,2.0,0.0
0.0,6.0,0.0,0.0,0.0,-6.0,0.0,0.0
0.0,0.0,0.0,2.0,0.0,0.0,0.0,-4.0
3.0,0.0,0.0,0.0,-2.0,0.0,1.0,0.0
0.0,0.0,6.0,0.0,0.0,0.0,5.0,0.0
1.0,0.0,0.0,0.0,-3.0,0.0,0.0,2.0
0.0,4.0,0.0,-1.0,0.0,0.0,0.0,0.0
0.0,0.0,1.0,0.0,-1.0,0.0,0.0,-2.0

4.0
6.0
-8.0
-2.0
27.0
-9.0
2.0
-4.0
*/
// ������ϡ�跽�����ȫѡ��Ԫ��˹��Լȥ��ȥ��
void CLECalculatorDlg::OnButton9() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ������ϡ�跽�����ȫѡ��Ԫ��˹��Լȥ��ȥ��
	if (leqs.GetRootsetGgje(mtxC))
		m_strResult = mtxC.ToString(" ");
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
6.0,5.0,4.0,3.0,2.0,1.0
5.0,6.0,5.0,4.0,3.0,2.0
4.0,5.0,6.0,5.0,4.0,3.0
3.0,4.0,5.0,6.0,5.0,4.0
2.0,3.0,4.0,5.0,6.0,5.0
1.0,2.0,3.0,4.0,5.0,6.0

11.0
9.0
9.0
9.0
13.0
17.0
*/
// ����в����ȷ����������ѷ����
void CLECalculatorDlg::OnButton10() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ����в����ȷ����������ѷ����
	if (leqs.GetRootsetTlvs(mtxC))
		m_strResult = mtxC.ToString(" ");
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
7.0,2.0,1.0,-2.0
9.0,15.0,3.0,-2.0
-2.0,-2.0,11.0,5.0
1.0,3.0,2.0,13.0

4.0
7.0
-1.0
0.0
*/
// ��˹�����¶�������
void CLECalculatorDlg::OnButton11() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ��˹�����¶�������
	if (leqs.GetRootsetGaussSeidel(mtxC))
		m_strResult = mtxC.ToString(" ");
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
5.0,7.0,6.0,5.0
7.0,10.0,8.0,7.0
6.0,8.0,10.0,9.0
5.0,7.0,9.0,10.0

23.0
32.0
33.0
31.0
*/
// ���Գ�����������Ĺ����ݶȷ�
void CLECalculatorDlg::OnButton12() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ���Գ�����������Ĺ����ݶȷ�
	leqs.GetRootsetGrad(mtxC);
	m_strResult = mtxC.ToString(" ");

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,1.0,-1.0
2.0,1.0,0.0
1.0,-1.0,0.0
-1.0,2.0,1.0

2.0
-3.0
1.0
4.0
*/
// ���������С��������ĺ�˹�ɶ��±任��
void CLECalculatorDlg::OnButton13() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC, mtxQ, mtxR;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ���������С��������ĺ�˹�ɶ��±任��
	if (leqs.GetRootsetMqr(mtxC, mtxQ, mtxR))
	{
		m_strResult = "�����Ϊ��\r\n";
		m_strResult += mtxC.ToString(" ");
		m_strResult += "\r\n\r\nQ�����Ϊ��\r\n";
		m_strResult += mtxQ.ToString(" ");
		m_strResult += "\r\n\r\nR�����Ϊ��\r\n";
		m_strResult += mtxR.ToString(" ");
	}
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,1.0,-1.0
2.0,1.0,0.0
1.0,-1.0,0.0
-1.0,2.0,1.0

2.0
-3.0
1.0
4.0
*/
// ���������С��������Ĺ����淨
void CLECalculatorDlg::OnButton14() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC, mtxAP, mtxU, mtxV;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ���������С��������Ĺ����淨
	if (leqs.GetRootsetGinv(mtxC, mtxAP, mtxU, mtxV))
	{
		m_strResult = "�����Ϊ��\r\n";
		m_strResult += mtxC.ToString(" ");
		m_strResult += "\r\n\r\n����������Ϊ��\r\n";
		m_strResult += mtxAP.ToString(" ");
	}
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

/*
3.4336,-0.5238,0.67105,-0.15272
-0.5238,3.28326,-0.73051,-0.2689
0.67105,-0.73051,4.02612,0.01835
-0.15272,-0.2689,0.01835,2.75702

-1.0
1.5
2.5
-2.0
*/
// ��̬����������
void CLECalculatorDlg::OnButton15() 
{
	// ��ȡ����
	UpdateData();

	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ʼ��ϵ������
	mtxA.FromString(m_strCoefficient, ",");
	// ��ʼ������������
	mtxB.FromString(m_strConstant, ",");

	// �������Է�����
	CLEquations leqs(mtxA, mtxB);

	// ��̬����������
	if (leqs.GetRootsetMorbid(mtxC))
		m_strResult = mtxC.ToString(" ");
	else
		m_strResult = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strResult, MB_OK|MB_ICONINFORMATION);
}

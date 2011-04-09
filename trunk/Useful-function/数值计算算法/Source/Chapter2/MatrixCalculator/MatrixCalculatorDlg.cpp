// MatrixCalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MatrixCalculator.h"
#include "MatrixCalculatorDlg.h"
#include "Matrix.h"
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
// CMatrixCalculatorDlg dialog

CMatrixCalculatorDlg::CMatrixCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMatrixCalculatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatrixCalculatorDlg)
	m_strMatrix1 = _T("");
	m_strMatrix2 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMatrixCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatrixCalculatorDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strMatrix1);
	DDX_Text(pDX, IDC_EDIT2, m_strMatrix2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMatrixCalculatorDlg, CDialog)
	//{{AFX_MSG_MAP(CMatrixCalculatorDlg)
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
	ON_BN_CLICKED(IDC_BUTTON18, OnButton18)
	ON_BN_CLICKED(IDC_BUTTON19, OnButton19)
	ON_BN_CLICKED(IDC_BUTTON20, OnButton20)
	ON_BN_CLICKED(IDC_BUTTON21, OnButton21)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatrixCalculatorDlg message handlers

BOOL CMatrixCalculatorDlg::OnInitDialog()
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

void CMatrixCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMatrixCalculatorDlg::OnPaint() 
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
HCURSOR CMatrixCalculatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// �ӷ�
void CMatrixCalculatorDlg::OnButton1() 
{
	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1);
	mtxB.FromString(m_strMatrix2);

	// ����ӷ�
	mtxC = mtxA + mtxB;

	// ��ʾ����
	m_strMatrix3 = mtxC.ToString(" ");
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

// ����
void CMatrixCalculatorDlg::OnButton2() 
{
	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1);
	mtxB.FromString(m_strMatrix2);

	// �������
	mtxC = mtxA - mtxB;

	// ��ʾ����
	m_strMatrix3 = mtxC.ToString(" ");
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

// ת��
void CMatrixCalculatorDlg::OnButton3() 
{
	// �������
	CMatrix mtxA, mtxC;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1);

	// ����ת��
	mtxC = mtxA.Transpose();

	// ��ʾ����
	m_strMatrix3 = mtxC.ToString(" ");
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
 1  3 -2  0  4
-2 -1  5 -7  2
 0  8  4  1 -5
 3 -3  2 -4  1

4  5 -1
2 -2  6
7  8  1
0  3 -5
9  8 -6
*/
// �˷�
void CMatrixCalculatorDlg::OnButton4() 
{
	// �������
	CMatrix mtxA, mtxB, mtxC;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1);
	mtxB.FromString(m_strMatrix2);

	// ����˷�
	mtxC = mtxA * mtxB;

	// ��ʾ����
	m_strMatrix3 = mtxC.ToString(" ");
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
0.2368,0.2471,0.2568,1.2671
1.1161,0.1254,0.1397,0.1490
0.1582,1.1675,0.1768,0.1871
0.1968,0.2071,1.2168,0.2271
*/
// ʵ���������ȫѡ��Ԫ��˹��Լ����
void CMatrixCalculatorDlg::OnButton5() 
{
	// �������
	CMatrix mtxA;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// ʵ���������ȫѡ��Ԫ��˹��Լ����
	if (mtxA.InvertGaussJordan())
		m_strMatrix3 = mtxA.ToString(" ");
	else
		m_strMatrix3 = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
0.2368,0.2471,0.2568,1.2671
1.1161,0.1254,0.1397,0.1490
0.1582,1.1675,0.1768,0.1871
0.1968,0.2071,1.2168,0.2271

0.1345,0.1678,0.1875,1.1161
1.2671,0.2017,0.7024,0.2721
-0.2836,-1.1967,0.3558,-0.2078
0.3576,-1.2345,2.1185,0.4773
*/
// �����������ȫѡ��Ԫ��˹��Լ����
void CMatrixCalculatorDlg::OnButton6() 
{
	// �������
	CMatrix mtxA, mtxB;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");
	mtxB.FromString(m_strMatrix2, ",");

	// �����������ȫѡ��Ԫ��˹��Լ����
	if (mtxA.InvertGaussJordan(mtxB))
	{
		m_strMatrix3  = "ʵ������������Ϊ��\n" + mtxA.ToString(" ");
		m_strMatrix3 += "\n\n�鲿����������Ϊ��\n"+mtxB.ToString(" ");
	}
	else
		m_strMatrix3 = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
5.0,7.0,6.0,5.0
7.0,10.0,8.0,7.0
6.0,8.0,10.0,9.0
5.0,7.0,9.0,10.0
*/
// �Գ��������������
void CMatrixCalculatorDlg::OnButton7() 
{
	// �������
	CMatrix mtxA;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// �Գ��������������
	if (mtxA.InvertSsgj())
		m_strMatrix3 = mtxA.ToString(" ");
	else
		m_strMatrix3 = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
10, 5, 4, 3, 2, 1
-1,10, 5, 4, 3, 2
-2,-1,10, 5, 4, 3
-3,-2,-1,10, 5, 4
-4,-3,-2,-1,10, 5
-5,-4,-3,-2,-1,10
*/
// �в����Ⱦ�������İ����ط���
void CMatrixCalculatorDlg::OnButton8() 
{
	// �������
	CMatrix mtxA;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// �в����Ⱦ�������İ����ط���
	if (mtxA.InvertTrench())
		m_strMatrix3 = mtxA.ToString(" ");
	else
		m_strMatrix3 = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,2.0,3.0,4.0
5.0,6.0,7.0,8.0
9.0,10.0,11.0,12.0
13.0,14.0,15.0,16.0

3.0,-3.0,-2.0,4.0
5.0,-5.0,1.0,8.0
11.0,8.0,5.0,-7.0
5.0,-1.0,-3.0,-1.0
*/
// ������ʽֵ��ȫѡ��Ԫ��˹��ȥ��
void CMatrixCalculatorDlg::OnButton9() 
{
	// �������
	CMatrix mtxA;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// ������ʽֵ��ȫѡ��Ԫ��˹��ȥ��
	double dblValue = mtxA.DetGauss();
	m_strMatrix3.Format("%f", dblValue);

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,2.0,3.0,4.0
5.0,6.0,7.0,8.0
9.0,10.0,11.0,12.0
13.0,14.0,15.0,16.0
17.0,18.0,19.0,20.0
*/
// ������ȵ�ȫѡ��Ԫ��˹��ȥ��
void CMatrixCalculatorDlg::OnButton10() 
{
	// �������
	CMatrix mtxA;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// ������ȵ�ȫѡ��Ԫ��˹��ȥ��
	int nValue = mtxA.RankGauss();
	m_strMatrix3.Format("%d", nValue);

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
5.0,7.0,6.0,5.0
7.0,10.0,8.0,7.0
6.0,8.0,10.0,9.0
5.0,7.0,9.0,10.0
*/
// �Գ��������������˹���ֽ�������ʽ����ֵ
void CMatrixCalculatorDlg::OnButton11() 
{
	// �������
	CMatrix mtxA;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// �Գ��������������˹���ֽ�������ʽ����ֵ
	double dblValue;
	if (mtxA.DetCholesky(&dblValue))
	{
		m_strMatrix3.Format("����ʽֵ = %f\r\n\r\n�ֽ��������Ǿ���Ϊ\r\n", dblValue);
		m_strMatrix3 += mtxA.ToString(" ");
	}
	else
		m_strMatrix3 = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
2.0,4.0,4.0,2.0
3.0,3.0,12.0,6.0
2.0,4.0,-1.0,2.0
4.0,2.0,1.0,1.0
*/
// ��������Ƿֽ�
void CMatrixCalculatorDlg::OnButton12() 
{
	// �������
	CMatrix mtxA, mtxL, mtxU;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// ��������Ƿֽ�
	if (mtxA.SplitLU(mtxL, mtxU))
	{
		m_strMatrix3.Format("�ֽ���L����Ϊ\r\n%s\r\n\r\n�ֽ���U����Ϊ\r\n%s", 
			mtxL.ToString(), mtxU.ToString());
	}
	else
		m_strMatrix3 = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,1.0,-1.0
2.0,1.0,0.0
1.0,-1.0,0.0
-1.0,2.0,1.0
*/
// һ��ʵ�����QR�ֽ�
void CMatrixCalculatorDlg::OnButton13() 
{
	// �������
	CMatrix mtxA, mtxQ;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// һ��ʵ�����QR�ֽ�
	if (mtxA.SplitQR(mtxQ))
	{
		m_strMatrix3.Format("�ֽ���Q����Ϊ\r\n%s\r\n\r\n�ֽ���R����Ϊ\r\n%s", 
			mtxQ.ToString(), mtxA.ToString());
	}
	else
		m_strMatrix3 = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,1.0,-1.0
2.0,1.0,0.0
1.0,-1.0,0.0
-1.0,2.0,1.0

1.0,1.0,-1.0,-1.0
2.0,1.0,0.0,2.0
1.0,-1.0,0.0,1.0
*/
// һ��ʵ���������ֵ�ֽ�
void CMatrixCalculatorDlg::OnButton14() 
{
	// �������
	CMatrix mtxA, mtxU, mtxV;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// һ��ʵ���������ֵ�ֽ�
	if (mtxA.SplitUV(mtxU, mtxV))
	{
		m_strMatrix3 = "�ֽ���U����Ϊ\n" + mtxU.ToString();
		m_strMatrix3 += "\n\n�ֽ���V����Ϊ\n" + mtxV.ToString();
		m_strMatrix3 += "\n\n�ֽ���A����Ϊ\n" + mtxA.ToString();
	}
	else
		m_strMatrix3 = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,2.0,3.0,4.0
6.0,7.0,8.0,9.0
1.0,2.0,13.0,0.0
16.0,17.0,8.0,9.0
2.0,4.0,3.0,4.0
*/
// ������������ֵ�ֽⷨ
void CMatrixCalculatorDlg::OnButton15() 
{
	// �������
	CMatrix mtxA, mtxU, mtxV, mtxAP;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// ������������ֵ�ֽⷨ
	if (mtxA.GInvertUV(mtxAP, mtxU, mtxV))
	{
		m_strMatrix3 = mtxAP.ToString();
	}
	else
		m_strMatrix3 = "���ʧ��";

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
10.0,1.0,2.0,3.0,4.0
1.0,9.0,-1.0,2.0,-3.0
2.0,-1.0,7.0,3.0,-5.0
3.0,2.0,3.0,12.0,-1.0
4.0,-3.0,-5.0,-1.0,15.0
*/
// Լ���Գƾ���Ϊ�Գ����Խ���ĺ�˹�ɶ��±任��
void CMatrixCalculatorDlg::OnButton16() 
{
	// �������
	CMatrix mtxA, mtxQ, mtxT;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// �����ڴ�
	double *dblB = NULL, *dblC = NULL;
	dblB = new double[mtxA.GetNumColumns()];
	dblC = new double[mtxA.GetNumColumns()];

	// Լ���Գƾ���Ϊ�Գ����Խ���ĺ�˹�ɶ��±任��
	if (mtxA.MakeSymTri(mtxQ, mtxT, dblB, dblC))
	{
		m_strMatrix3.Format("�˻�����QΪ\r\n%s\r\n\r\n���Խ���Ϊ\r\n%s", 
			mtxQ.ToString(), mtxT.ToString());
	}
	else
		m_strMatrix3 = "���ʧ��";

	// �����ڴ�
	delete[] dblB;
	delete[] dblC;

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
10.0,1.0,2.0,3.0,4.0
1.0,9.0,-1.0,2.0,-3.0
2.0,-1.0,7.0,3.0,-5.0
3.0,2.0,3.0,12.0,-1.0
4.0,-3.0,-5.0,-1.0,15.0
*/
// ʵ�Գ����Խ����ȫ������ֵ�����������ļ���
void CMatrixCalculatorDlg::OnButton17() 
{
	// �������
	CMatrix mtxA, mtxQ, mtxT;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// �����ڴ�
	double *dblB = NULL, *dblC = NULL;
	dblB = new double[mtxA.GetNumColumns()];
	dblC = new double[mtxA.GetNumColumns()];

	// ʵ�Գ����Խ����ȫ������ֵ�����������ļ���
	if (mtxA.MakeSymTri(mtxQ, mtxT, dblB, dblC))
	{
		if (mtxA.SymTriEigenv(dblB, dblC, mtxQ))
		{
			int n = mtxQ.GetNumColumns();

			m_strMatrix3.Format("����ֵΪ\r\n");
			CString s;
			for (int i=0; i<n; ++i)
			{
				s.Format("%d: %f\r\n", i+1, dblB[i]);
				m_strMatrix3 += s;
			}

			m_strMatrix3 += "\r\n��Ӧ����������Ϊ\r\n";
			for (i=0; i<n; ++i)
			{
				s.Format("%d: %s\r\n", i+1, mtxQ.ColToString(i));
				m_strMatrix3 += s;
			}
		}
		else
			m_strMatrix3 = "���ʧ��";
	}
	else
		m_strMatrix3 = "���ʧ��";

	// �����ڴ�
	delete[] dblB;
	delete[] dblC;

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,6.0,-3.0,-1.0,7.0
8.0,-15.0,18.0,5.0,4.0
-2.0,11.0,9.0,15.0,20.0
-13.0,2.0,21.0,30.0,-6.0
17.0,22.0,-5.0,3.0,6.0
*/
// Լ��һ��ʵ����Ϊ���겮�����ĳ������Ʊ任��
void CMatrixCalculatorDlg::OnButton18() 
{
	// �������
	CMatrix mtxA;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// Լ��һ��ʵ����Ϊ���겮�����ĳ������Ʊ任��
	mtxA.MakeHberg();
	m_strMatrix3 = mtxA.ToString();

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,6.0,-3.0,-1.0,7.0
8.0,-15.0,18.0,5.0,4.0
-2.0,11.0,9.0,15.0,20.0
-13.0,2.0,21.0,30.0,-6.0
17.0,22.0,-5.0,3.0,6.0
*/
// ����겮�����ȫ������ֵ��QR����
void CMatrixCalculatorDlg::OnButton19() 
{
	// �������
	CMatrix mtxA, mtxQ, mtxT;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// �������겮�����
	mtxA.MakeHberg();
	m_strMatrix3.Format("Լ���õ��ĺ��겮�����Ϊ\r\n%s", mtxA.ToString());

	// �����ڴ�
	double *dblU = NULL, *dblV = NULL;
	dblU = new double[mtxA.GetNumColumns()];
	dblV = new double[mtxA.GetNumColumns()];

	// ����겮�����ȫ������ֵ��QR����
	if (mtxA.HBergEigenv(dblU, dblV))
	{
		m_strMatrix3 += "\r\n\r\n����ֵΪ\r\n";
		for (int i=0; i<mtxA.GetNumColumns(); ++i)
		{
			CComplex x(dblU[i], dblV[i]);
			m_strMatrix3 += x.ToString() + "\r\n";
		}
	}
	else
		m_strMatrix3 = "���ʧ��";

	// �����ڴ�
	delete[] dblU;
	delete[] dblV;

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
2.0,-1.0,0.0
-1.0,2.0,-1.0
0.0,-1.0,2.0
*/
// ��ʵ�Գƾ�������ֵ�������������ſɱȷ�
void CMatrixCalculatorDlg::OnButton20() 
{
	// �������
	CMatrix mtxA, mtxV;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// �����ڴ�
	double* dblV = new double[mtxA.GetNumColumns()];

	// ��ʵ�Գƾ�������ֵ�������������ſɱȷ�
	if (mtxA.JacobiEigenv(dblV, mtxV, 100))
	{
		m_strMatrix3.Format("����ֵΪ\r\n");
		CString s;
		for (int i=0; i<mtxA.GetNumColumns(); ++i)
		{
			s.Format("%d: %f\r\n", i+1, dblV[i]);
			m_strMatrix3 += s;
		}

		m_strMatrix3 += "\r\n��Ӧ����������Ϊ\r\n";
		for (i=0; i<mtxA.GetNumColumns(); ++i)
		{
			s.Format("%d: %s\r\n", i+1, mtxV.ColToString(i));
			m_strMatrix3 += s;
		}
	}
	else
		m_strMatrix3 = "���ʧ��";

	// �����ڴ�
	delete[] dblV;

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
10.0,1.0,2.0,3.0,4.0
1.0,9.0,-1.0,2.0,-3.0
2.0,-1.0,7.0,3.0,-5.0
3.0,2.0,3.0,12.0,-1.0
4.0,-3.0,-5.0,-1.0,15.0
*/
// ��ʵ�Գƾ�������ֵ�������������ſɱȹ��ط�
void CMatrixCalculatorDlg::OnButton21() 
{
	// �������
	CMatrix mtxA, mtxV;

	// ��ȡ����
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// �����ڴ�
	double* dblV = new double[mtxA.GetNumColumns()];

	// ��ʵ�Գƾ�������ֵ�������������ſɱȹ��ط�
	if (mtxA.JacobiEigenv2(dblV, mtxV))
	{
		m_strMatrix3.Format("����ֵΪ\r\n");
		CString s;
		for (int i=0; i<mtxA.GetNumColumns(); ++i)
		{
			s.Format("%d: %f\r\n", i+1, dblV[i]);
			m_strMatrix3 += s;
		}

		m_strMatrix3 += "\r\n��Ӧ����������Ϊ\r\n";
		for (i=0; i<mtxA.GetNumColumns(); ++i)
		{
			s.Format("%d: %s\r\n", i+1, mtxV.ColToString(i));
			m_strMatrix3 += s;
		}
	}
	else
		m_strMatrix3 = "���ʧ��";

	// �����ڴ�
	delete[] dblV;

	// ��ʾ����
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

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

// 加法
void CMatrixCalculatorDlg::OnButton1() 
{
	// 构造矩阵
	CMatrix mtxA, mtxB, mtxC;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1);
	mtxB.FromString(m_strMatrix2);

	// 矩阵加法
	mtxC = mtxA + mtxB;

	// 显示数据
	m_strMatrix3 = mtxC.ToString(" ");
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

// 减法
void CMatrixCalculatorDlg::OnButton2() 
{
	// 构造矩阵
	CMatrix mtxA, mtxB, mtxC;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1);
	mtxB.FromString(m_strMatrix2);

	// 矩阵减法
	mtxC = mtxA - mtxB;

	// 显示数据
	m_strMatrix3 = mtxC.ToString(" ");
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

// 转置
void CMatrixCalculatorDlg::OnButton3() 
{
	// 构造矩阵
	CMatrix mtxA, mtxC;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1);

	// 矩阵转置
	mtxC = mtxA.Transpose();

	// 显示数据
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
// 乘法
void CMatrixCalculatorDlg::OnButton4() 
{
	// 构造矩阵
	CMatrix mtxA, mtxB, mtxC;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1);
	mtxB.FromString(m_strMatrix2);

	// 矩阵乘法
	mtxC = mtxA * mtxB;

	// 显示数据
	m_strMatrix3 = mtxC.ToString(" ");
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
0.2368,0.2471,0.2568,1.2671
1.1161,0.1254,0.1397,0.1490
0.1582,1.1675,0.1768,0.1871
0.1968,0.2071,1.2168,0.2271
*/
// 实矩阵求逆的全选主元高斯－约当法
void CMatrixCalculatorDlg::OnButton5() 
{
	// 构造矩阵
	CMatrix mtxA;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 实矩阵求逆的全选主元高斯－约当法
	if (mtxA.InvertGaussJordan())
		m_strMatrix3 = mtxA.ToString(" ");
	else
		m_strMatrix3 = "求解失败";

	// 显示数据
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
// 复矩阵求逆的全选主元高斯－约当法
void CMatrixCalculatorDlg::OnButton6() 
{
	// 构造矩阵
	CMatrix mtxA, mtxB;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");
	mtxB.FromString(m_strMatrix2, ",");

	// 复矩阵求逆的全选主元高斯－约当法
	if (mtxA.InvertGaussJordan(mtxB))
	{
		m_strMatrix3  = "实部矩阵的逆矩阵为：\n" + mtxA.ToString(" ");
		m_strMatrix3 += "\n\n虚部矩阵的逆矩阵为：\n"+mtxB.ToString(" ");
	}
	else
		m_strMatrix3 = "求解失败";

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
5.0,7.0,6.0,5.0
7.0,10.0,8.0,7.0
6.0,8.0,10.0,9.0
5.0,7.0,9.0,10.0
*/
// 对称正定矩阵的求逆
void CMatrixCalculatorDlg::OnButton7() 
{
	// 构造矩阵
	CMatrix mtxA;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 对称正定矩阵的求逆
	if (mtxA.InvertSsgj())
		m_strMatrix3 = mtxA.ToString(" ");
	else
		m_strMatrix3 = "求解失败";

	// 显示数据
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
// 托伯利兹矩阵求逆的埃兰特方法
void CMatrixCalculatorDlg::OnButton8() 
{
	// 构造矩阵
	CMatrix mtxA;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 托伯利兹矩阵求逆的埃兰特方法
	if (mtxA.InvertTrench())
		m_strMatrix3 = mtxA.ToString(" ");
	else
		m_strMatrix3 = "求解失败";

	// 显示数据
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
// 求行列式值的全选主元高斯消去法
void CMatrixCalculatorDlg::OnButton9() 
{
	// 构造矩阵
	CMatrix mtxA;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 求行列式值的全选主元高斯消去法
	double dblValue = mtxA.DetGauss();
	m_strMatrix3.Format("%f", dblValue);

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,2.0,3.0,4.0
5.0,6.0,7.0,8.0
9.0,10.0,11.0,12.0
13.0,14.0,15.0,16.0
17.0,18.0,19.0,20.0
*/
// 求矩阵秩的全选主元高斯消去法
void CMatrixCalculatorDlg::OnButton10() 
{
	// 构造矩阵
	CMatrix mtxA;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 求矩阵秩的全选主元高斯消去法
	int nValue = mtxA.RankGauss();
	m_strMatrix3.Format("%d", nValue);

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
5.0,7.0,6.0,5.0
7.0,10.0,8.0,7.0
6.0,8.0,10.0,9.0
5.0,7.0,9.0,10.0
*/
// 对称正定矩阵的乔里斯基分解与行列式的求值
void CMatrixCalculatorDlg::OnButton11() 
{
	// 构造矩阵
	CMatrix mtxA;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 对称正定矩阵的乔里斯基分解与行列式的求值
	double dblValue;
	if (mtxA.DetCholesky(&dblValue))
	{
		m_strMatrix3.Format("行列式值 = %f\r\n\r\n分解后的下三角矩阵为\r\n", dblValue);
		m_strMatrix3 += mtxA.ToString(" ");
	}
	else
		m_strMatrix3 = "求解失败";

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
2.0,4.0,4.0,2.0
3.0,3.0,12.0,6.0
2.0,4.0,-1.0,2.0
4.0,2.0,1.0,1.0
*/
// 矩阵的三角分解
void CMatrixCalculatorDlg::OnButton12() 
{
	// 构造矩阵
	CMatrix mtxA, mtxL, mtxU;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 矩阵的三角分解
	if (mtxA.SplitLU(mtxL, mtxU))
	{
		m_strMatrix3.Format("分解后的L矩阵为\r\n%s\r\n\r\n分解后的U矩阵为\r\n%s", 
			mtxL.ToString(), mtxU.ToString());
	}
	else
		m_strMatrix3 = "求解失败";

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,1.0,-1.0
2.0,1.0,0.0
1.0,-1.0,0.0
-1.0,2.0,1.0
*/
// 一般实矩阵的QR分解
void CMatrixCalculatorDlg::OnButton13() 
{
	// 构造矩阵
	CMatrix mtxA, mtxQ;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 一般实矩阵的QR分解
	if (mtxA.SplitQR(mtxQ))
	{
		m_strMatrix3.Format("分解后的Q矩阵为\r\n%s\r\n\r\n分解后的R矩阵为\r\n%s", 
			mtxQ.ToString(), mtxA.ToString());
	}
	else
		m_strMatrix3 = "求解失败";

	// 显示数据
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
// 一般实矩阵的奇异值分解
void CMatrixCalculatorDlg::OnButton14() 
{
	// 构造矩阵
	CMatrix mtxA, mtxU, mtxV;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 一般实矩阵的奇异值分解
	if (mtxA.SplitUV(mtxU, mtxV))
	{
		m_strMatrix3 = "分解后的U矩阵为\n" + mtxU.ToString();
		m_strMatrix3 += "\n\n分解后的V矩阵为\n" + mtxV.ToString();
		m_strMatrix3 += "\n\n分解后的A矩阵为\n" + mtxA.ToString();
	}
	else
		m_strMatrix3 = "求解失败";

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,2.0,3.0,4.0
6.0,7.0,8.0,9.0
1.0,2.0,13.0,0.0
16.0,17.0,8.0,9.0
2.0,4.0,3.0,4.0
*/
// 求广义逆的奇异值分解法
void CMatrixCalculatorDlg::OnButton15() 
{
	// 构造矩阵
	CMatrix mtxA, mtxU, mtxV, mtxAP;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 求广义逆的奇异值分解法
	if (mtxA.GInvertUV(mtxAP, mtxU, mtxV))
	{
		m_strMatrix3 = mtxAP.ToString();
	}
	else
		m_strMatrix3 = "求解失败";

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
10.0,1.0,2.0,3.0,4.0
1.0,9.0,-1.0,2.0,-3.0
2.0,-1.0,7.0,3.0,-5.0
3.0,2.0,3.0,12.0,-1.0
4.0,-3.0,-5.0,-1.0,15.0
*/
// 约化对称矩阵为对称三对角阵的豪斯荷尔德变换法
void CMatrixCalculatorDlg::OnButton16() 
{
	// 构造矩阵
	CMatrix mtxA, mtxQ, mtxT;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 分配内存
	double *dblB = NULL, *dblC = NULL;
	dblB = new double[mtxA.GetNumColumns()];
	dblC = new double[mtxA.GetNumColumns()];

	// 约化对称矩阵为对称三对角阵的豪斯荷尔德变换法
	if (mtxA.MakeSymTri(mtxQ, mtxT, dblB, dblC))
	{
		m_strMatrix3.Format("乘积矩阵Q为\r\n%s\r\n\r\n三对角阵为\r\n%s", 
			mtxQ.ToString(), mtxT.ToString());
	}
	else
		m_strMatrix3 = "求解失败";

	// 清理内存
	delete[] dblB;
	delete[] dblC;

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
10.0,1.0,2.0,3.0,4.0
1.0,9.0,-1.0,2.0,-3.0
2.0,-1.0,7.0,3.0,-5.0
3.0,2.0,3.0,12.0,-1.0
4.0,-3.0,-5.0,-1.0,15.0
*/
// 实对称三对角阵的全部特征值与特征向量的计算
void CMatrixCalculatorDlg::OnButton17() 
{
	// 构造矩阵
	CMatrix mtxA, mtxQ, mtxT;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 分配内存
	double *dblB = NULL, *dblC = NULL;
	dblB = new double[mtxA.GetNumColumns()];
	dblC = new double[mtxA.GetNumColumns()];

	// 实对称三对角阵的全部特征值与特征向量的计算
	if (mtxA.MakeSymTri(mtxQ, mtxT, dblB, dblC))
	{
		if (mtxA.SymTriEigenv(dblB, dblC, mtxQ))
		{
			int n = mtxQ.GetNumColumns();

			m_strMatrix3.Format("特征值为\r\n");
			CString s;
			for (int i=0; i<n; ++i)
			{
				s.Format("%d: %f\r\n", i+1, dblB[i]);
				m_strMatrix3 += s;
			}

			m_strMatrix3 += "\r\n对应的特征向量为\r\n";
			for (i=0; i<n; ++i)
			{
				s.Format("%d: %s\r\n", i+1, mtxQ.ColToString(i));
				m_strMatrix3 += s;
			}
		}
		else
			m_strMatrix3 = "求解失败";
	}
	else
		m_strMatrix3 = "求解失败";

	// 清理内存
	delete[] dblB;
	delete[] dblC;

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,6.0,-3.0,-1.0,7.0
8.0,-15.0,18.0,5.0,4.0
-2.0,11.0,9.0,15.0,20.0
-13.0,2.0,21.0,30.0,-6.0
17.0,22.0,-5.0,3.0,6.0
*/
// 约化一般实矩阵为赫申伯格矩阵的初等相似变换法
void CMatrixCalculatorDlg::OnButton18() 
{
	// 构造矩阵
	CMatrix mtxA;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 约化一般实矩阵为赫申伯格矩阵的初等相似变换法
	mtxA.MakeHberg();
	m_strMatrix3 = mtxA.ToString();

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
1.0,6.0,-3.0,-1.0,7.0
8.0,-15.0,18.0,5.0,4.0
-2.0,11.0,9.0,15.0,20.0
-13.0,2.0,21.0,30.0,-6.0
17.0,22.0,-5.0,3.0,6.0
*/
// 求赫申伯格矩阵全部特征值的QR方法
void CMatrixCalculatorDlg::OnButton19() 
{
	// 构造矩阵
	CMatrix mtxA, mtxQ, mtxT;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 建立赫申伯格矩阵
	mtxA.MakeHberg();
	m_strMatrix3.Format("约化得到的赫申伯格矩阵为\r\n%s", mtxA.ToString());

	// 分配内存
	double *dblU = NULL, *dblV = NULL;
	dblU = new double[mtxA.GetNumColumns()];
	dblV = new double[mtxA.GetNumColumns()];

	// 求赫申伯格矩阵全部特征值的QR方法
	if (mtxA.HBergEigenv(dblU, dblV))
	{
		m_strMatrix3 += "\r\n\r\n特征值为\r\n";
		for (int i=0; i<mtxA.GetNumColumns(); ++i)
		{
			CComplex x(dblU[i], dblV[i]);
			m_strMatrix3 += x.ToString() + "\r\n";
		}
	}
	else
		m_strMatrix3 = "求解失败";

	// 清理内存
	delete[] dblU;
	delete[] dblV;

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
2.0,-1.0,0.0
-1.0,2.0,-1.0
0.0,-1.0,2.0
*/
// 求实对称矩阵特征值与特征向量的雅可比法
void CMatrixCalculatorDlg::OnButton20() 
{
	// 构造矩阵
	CMatrix mtxA, mtxV;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 分配内存
	double* dblV = new double[mtxA.GetNumColumns()];

	// 求实对称矩阵特征值与特征向量的雅可比法
	if (mtxA.JacobiEigenv(dblV, mtxV, 100))
	{
		m_strMatrix3.Format("特征值为\r\n");
		CString s;
		for (int i=0; i<mtxA.GetNumColumns(); ++i)
		{
			s.Format("%d: %f\r\n", i+1, dblV[i]);
			m_strMatrix3 += s;
		}

		m_strMatrix3 += "\r\n对应的特征向量为\r\n";
		for (i=0; i<mtxA.GetNumColumns(); ++i)
		{
			s.Format("%d: %s\r\n", i+1, mtxV.ColToString(i));
			m_strMatrix3 += s;
		}
	}
	else
		m_strMatrix3 = "求解失败";

	// 清理内存
	delete[] dblV;

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

/*
10.0,1.0,2.0,3.0,4.0
1.0,9.0,-1.0,2.0,-3.0
2.0,-1.0,7.0,3.0,-5.0
3.0,2.0,3.0,12.0,-1.0
4.0,-3.0,-5.0,-1.0,15.0
*/
// 求实对称矩阵特征值与特征向量的雅可比过关法
void CMatrixCalculatorDlg::OnButton21() 
{
	// 构造矩阵
	CMatrix mtxA, mtxV;

	// 获取数据
	UpdateData();
	mtxA.FromString(m_strMatrix1, ",");

	// 分配内存
	double* dblV = new double[mtxA.GetNumColumns()];

	// 求实对称矩阵特征值与特征向量的雅可比过关法
	if (mtxA.JacobiEigenv2(dblV, mtxV))
	{
		m_strMatrix3.Format("特征值为\r\n");
		CString s;
		for (int i=0; i<mtxA.GetNumColumns(); ++i)
		{
			s.Format("%d: %f\r\n", i+1, dblV[i]);
			m_strMatrix3 += s;
		}

		m_strMatrix3 += "\r\n对应的特征向量为\r\n";
		for (i=0; i<mtxA.GetNumColumns(); ++i)
		{
			s.Format("%d: %s\r\n", i+1, mtxV.ColToString(i));
			m_strMatrix3 += s;
		}
	}
	else
		m_strMatrix3 = "求解失败";

	// 清理内存
	delete[] dblV;

	// 显示数据
	AfxMessageBox(m_strMatrix3, MB_OK|MB_ICONINFORMATION);
}

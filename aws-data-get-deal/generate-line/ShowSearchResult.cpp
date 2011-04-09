// ShowSearchResult.cpp : 实现文件
//

#include "stdafx.h"
#include "generate-line.h"
#include "ShowSearchResult.h"
#include <string-trans.h>

// ShowSearchResult 对话框

IMPLEMENT_DYNAMIC(ShowSearchResult, CDialog)

ShowSearchResult::ShowSearchResult(CWnd* pParent /*=NULL*/)
	: CDialog(ShowSearchResult::IDD, pParent)
{
	have_init = false;
	column_width = 70;
}

ShowSearchResult::~ShowSearchResult()
{
}

void ShowSearchResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, show_list);
}


BEGIN_MESSAGE_MAP(ShowSearchResult, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SAVEASTEXT, &ShowSearchResult::OnBnClickedSaveastext)
END_MESSAGE_MAP()


// ShowSearchResult 消息处理程序

BOOL ShowSearchResult::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(title);

	show_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	//设置行高为30px
	CImageList imagelist;
	imagelist.Create(5,30,0,0,0);
	show_list.SetImageList(&imagelist,LVSIL_SMALL);

	for(size_t i=0;i<headtitles.size();i++)
	{
		show_list.InsertColumn(i,headtitles[i].c_str(),LVCFMT_LEFT,60,i);
	}

	for(int row=0;contents.size() && row<contents.front().size();row++)
	{
		show_list.InsertItem(row,"");
		for(int col=0;col<contents.size();col++)
		{
			if(contents.at(col).size() > row)
			{//防止溢出
				show_list.SetItemText(row,col,contents.at(col).at(row).c_str());
			}
		}
	}


	have_init = true;
	CRect rect;
	GetWindowRect(&rect);
	MoveWindow(rect.left,rect.top,headtitles.size()*column_width+165,rect.Height());

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ShowSearchResult::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//初始化之前不应执行下面的操作
	if(!have_init) return;

	CRect rect(10,10,100,100);
	GetWindowRect(&rect);

	if(cx<300 || cy<400)
	{
		MoveWindow(rect.left,rect.top,310,420);
		cx = 300,cy=400;
	}

	show_list.MoveWindow(25,25,cx-165,cy-40);
	int cols = show_list.GetHeaderCtrl()->GetItemCount();

	for(int i=0;i<cols;i++)
	{
		show_list.SetColumnWidth(i,(cx-170)/cols);
	}


	GetDlgItem(IDC_SAVEASTEXT)->MoveWindow(cx-125,25,100,30);
	GetDlgItem(IDC_PRINTRESULT)->MoveWindow(cx-125,80,100,30);


	// TODO: 在此处添加消息处理程序代码
}

void ShowSearchResult::OnBnClickedSaveastext()
{
	// TODO: 在此添加控件通知处理程序代码

	CString filter = "文本文件(*.txt)|*.txt|任意类型(*.*)|*.*||";
	CFileDialog fdlg(FALSE,"txt",this->title,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);
	if(fdlg.DoModal() != IDOK)
		return;

	std::string filecontent;

	for(size_t i=0;i<headtitles.size();i++)
	{
		filecontent += headtitles[i]+"    ";
	}
	filecontent += "\n------------------------------------------------\n";

	for(int row=0;row<contents.front().size();row++)
	{

		for(int col=0;col<contents.size();col++)
		{
			filecontent += contents.at(col).at(row)+"    ";
		}
		filecontent += "\n";
	}

	std::string filepath = fdlg.GetPathName();

	strtofile(filepath,filecontent);

}

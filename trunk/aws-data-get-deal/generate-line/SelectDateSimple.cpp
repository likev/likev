// SelectDateSimple.cpp : 实现文件
//

#include "stdafx.h"
#include "generate-line.h"
#include "SelectDateSimple.h"


// SelectDateSimple 对话框

IMPLEMENT_DYNAMIC(SelectDateSimple, CDialog)

SelectDateSimple::SelectDateSimple(CWnd* pParent /*=NULL*/)
	: CDialog(SelectDateSimple::IDD, pParent)
{
	date = CTime::GetCurrentTime();
}

SelectDateSimple::~SelectDateSimple()
{
}

void SelectDateSimple::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, date);
}


BEGIN_MESSAGE_MAP(SelectDateSimple, CDialog)
END_MESSAGE_MAP()


// SelectDateSimple 消息处理程序


#include "search-condition.h"
#include "wx/valgen.h"
#include "wx/valtext.h"

BEGIN_EVENT_TABLE(DisasterSearchDlg, wxDialog)
	EVT_BUTTON(wxID_OK,  DisasterSearchDlg::OnOk)
END_EVENT_TABLE()

DisasterSearchDlg::DisasterSearchDlg(const wxString& title)
:wxDialog(NULL,-1,title,wxDefaultPosition, wxSize(400,340))
{
	new wxCheckBox(this,-1,wxT("类型"),wxPoint(30,30),wxSize(60,30),0,wxGenericValidator(&condition.istype));
	
	comboInstanceType = new wxComboBox(this, -1, wxT("未知"),wxPoint(110,30),wxSize(100,30), 0, NULL, wxCB_READONLY|wxCB_DROPDOWN,wxGenericValidator(&typeName));
	
	for(size_t index=0;index<DisasterInstance::disasterKind; index ++)
	{
		comboInstanceType->Append(DisasterInstance::DisasterNames[index] );
	}
	
	new wxCheckBox(this,-1,wxT("年份"),wxPoint(30,80),wxSize(60,30),0,wxGenericValidator(&condition.isyear));
	new wxStaticText(this, -1, wxT("起始"),wxPoint(110,85),wxSize(30,30));
	new wxTextCtrl(this, -1, wxT("2010"),wxPoint(150,80),wxSize(60,30), 0, wxTextValidator(wxFILTER_NUMERIC,&condition.beginYear) );
	new wxStaticText(this, -1, wxT("结束"),wxPoint(260,85),wxSize(30,30));
	new wxTextCtrl(this, -1, wxT("2010"),wxPoint(300,80),wxSize(60,30), 0, wxTextValidator(wxFILTER_NUMERIC,&condition.endYear) );
	
	new wxCheckBox(this,-1,wxT("月份"),wxPoint(30,130),wxSize(60,30),0,wxGenericValidator(&condition.ismonth));
	new wxStaticText(this, -1, wxT("起始"),wxPoint(110,135),wxSize(30,30));
	new wxTextCtrl(this, -1, wxT("1"),wxPoint(150,130),wxSize(60,30), 0, wxTextValidator(wxFILTER_NUMERIC,&condition.beginMonth) );
	new wxStaticText(this, -1, wxT("结束"),wxPoint(260,135),wxSize(30,30));
	new wxTextCtrl(this, -1, wxT("12"),wxPoint(300,130),wxSize(60,30), 0, wxTextValidator(wxFILTER_NUMERIC,&condition.endMonth) );
	
	new wxCheckBox(this,-1,wxT("关键词"),wxPoint(30,180),wxSize(70,30),0,wxGenericValidator(&condition.isword));
	new wxTextCtrl(this, -1, wxT("输入关键词"),wxPoint(110,180),wxSize(250,30),0,wxGenericValidator(&condition.searchWord));
	
	new wxButton(this, wxID_CANCEL, wxT("取消"),wxPoint(30,250),wxSize(100,30));
	new wxButton(this, wxID_OK, wxT("搜索"),wxPoint(260,250),wxSize(100,30));
}

void DisasterSearchDlg::OnOk(wxCommandEvent& WXUNUSED(event) )
{
	
	if ( Validate() && TransferDataFromWindow() )
	{	
		condition.dstType = DisasterInstance::GetDisasterType(typeName);
		EndModal(wxID_OK);
	}
}

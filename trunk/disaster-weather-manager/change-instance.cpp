
#include "change-instance.h"
#include "wx/mimetype.h"
#include "wx/tokenzr.h"
#include "wx/config.h"

enum{
	wxID_RELATE_FILES,
	wxID_VIEW_FILE,
	wxID_DELETE_FILE
};

BEGIN_EVENT_TABLE(ChangeInstanceDlg, wxDialog)
	EVT_BUTTON(wxID_OK,  ChangeInstanceDlg::OnOk)
	EVT_BUTTON(wxID_VIEW_FILE,  ChangeInstanceDlg::OnClickViewFileButton)
	EVT_BUTTON(wxID_DELETE_FILE,  ChangeInstanceDlg::DeleteSelectFile)
	EVT_WINDOW_CREATE(ChangeInstanceDlg::AfterDialogCreation)
	EVT_LISTBOX_DCLICK(wxID_RELATE_FILES, ChangeInstanceDlg::OnDoubleClickListItem)
END_EVENT_TABLE()

ChangeInstanceDlg::ChangeInstanceDlg(const wxString& title, CHANGE_INSTANCE_TYPE type)
:wxDialog(NULL,-1,title,wxDefaultPosition, wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX)
,changeType(type)
{
	//wxMessageBox(wxT("will get config"));
	wxConfigBase *pConfig = wxConfigBase::Get();

  	pConfig->Read(wxT("/Path/dstDb"), &dstDbPath);
	//wxMessageBox(wxT("get config success"));

	//wxMessageBox(wxT("will creat combobox"));
	
	conboInstanceType = new wxComboBox(this, -1, wxEmptyString,wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY|wxCB_DROPDOWN);
	//wxMessageBox(wxT("creat combobox success"));

	if( ADD == changeType )
	{
		for(size_t index=0;index<DisasterInstance::disasterKind; index ++)
		{
			conboInstanceType->Append(DisasterInstance::DisasterNames[index] );
		}
	}
	
	wxFlexGridSizer *gs = new wxFlexGridSizer(7, 2, 5, 5);
	
	//wxMessageBox(wxT(" will creat text ctrls"));
	CreatTextCtrls();
	//wxMessageBox(wxT("creat text ctrls success"));
	
	gs->Add(new wxStaticText(this, -1, wxT("灾害类型")), 0, wxEXPAND);
	gs->Add(conboInstanceType, 0);
	gs->Add(new wxStaticText(this, -1, wxT("起始日期")), 0, wxEXPAND);
	
	wxSizer *sizerDate = new wxBoxSizer(wxHORIZONTAL);
	sizerDate->Add(textBeginDate);
	sizerDate->Add(50,0,0);
	sizerDate->Add(new wxStaticText(this, -1, wxT("结束日期") ) );
	sizerDate->Add(textEndDate);
	gs->Add(sizerDate,1, wxEXPAND);
	
	gs->Add(new wxStaticText(this, -1, wxT("简介")), 0, wxEXPAND);
	gs->Add(textSimpleDescribe , 1, wxEXPAND);
	gs->Add(new wxStaticText(this, -1, wxT("天气背景")), 0, wxEXPAND);
	gs->Add(textWeatherBackground , 2, wxEXPAND);
	gs->Add(new wxStaticText(this, -1, wxT("影响系统")), 0, wxEXPAND);
	gs->Add(textImportantSystem , 2, wxEXPAND);
	
	gs->Add(new wxStaticText(this, -1, wxT("移动路径")), 0, wxEXPAND);
	gs->Add(textPath , 1, wxEXPAND);
	
	gs->Add(new wxStaticText(this, -1, wxT("量值")), 0, wxEXPAND);
	gs->Add(textSignValue , 1, wxEXPAND);
	
	gs->Add(new wxStaticText(this, -1, wxT("详细描述")), 0, wxEXPAND);
	gs->Add(textDetailDescribe , 5, wxEXPAND);
	
	//wxMessageBox(wxT("will creat files list"));
	CreatFilesListSizer();
	gs->Add(new wxStaticText(this, -1, wxT("相关文件")), 0, wxEXPAND);
	gs->Add(sizerFilesList, 0, wxEXPAND);
	
	gs->AddGrowableRow(3, 2);
	gs->AddGrowableRow(4, 2);
	gs->AddGrowableRow(7, 5);
  	gs->AddGrowableCol(1, 1);

	//InitControlValue();
	
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(gs,1,wxEXPAND|wxALL,20);
	
	if( VIEWONLY != changeType )
	{
		wxSizer *sizerButton = new wxBoxSizer(wxHORIZONTAL);
		sizerButton->Add(new wxButton(this, wxID_CANCEL, wxT("取消"),wxDefaultPosition,wxSize(-1,30) ), 1, wxEXPAND);
		sizerButton->Add(50,0,0);
		sizerButton->Add(new wxButton(this, wxID_OK, wxT("保存")), 1, wxEXPAND);
		
		sizer->Add(sizerButton,0,wxEXPAND|wxALL,20);
	}
	
	SetSizer(sizer);
  	SetMinSize(wxSize(700, 600));

  	CentreOnScreen();

}

void ChangeInstanceDlg::CreatFilesListSizer()
{
	sizerFilesList = new wxBoxSizer(wxHORIZONTAL);
	
	filenamesList = new wxListBox (this,wxID_RELATE_FILES, wxPoint(-1,-1),wxSize(-1,60));
	

	
	wxBoxSizer *listManagerSizer = new wxBoxSizer(wxVERTICAL);
	listManagerSizer-> Add(new wxButton(this, wxID_VIEW_FILE, wxT("查看"), wxPoint(-1,-1),wxSize(-1,25)), 0, wxEXPAND);

	if( VIEWONLY != changeType )
	{
		filenamesList->SetDropTarget ( new DnDFile ( filenamesList ));
		listManagerSizer-> AddSpacer(5);
		listManagerSizer-> Add(new wxButton(this, wxID_DELETE_FILE, wxT("删除"), wxPoint(-1,-1),wxSize(-1,25)), 0, wxEXPAND);
	}	

	sizerFilesList->Add(filenamesList,1,wxEXPAND);
	sizerFilesList-> AddSpacer(15);
	sizerFilesList->Add(listManagerSizer,0,wxEXPAND);
}

void ChangeInstanceDlg::CreatTextCtrls()
{
	long style = 0;
	if( VIEWONLY == changeType )
	{
		style = wxTE_READONLY;
	}
	
	textBeginDate = new wxTextCtrl(this, -1, wxT("20100101"),wxDefaultPosition,wxSize(150,-1), style, wxTextValidator(wxFILTER_NUMERIC) );

	textEndDate = new wxTextCtrl(this, -1, wxT("20100101"),wxDefaultPosition,wxSize(150,-1), style, wxTextValidator(wxFILTER_NUMERIC) );

	textSimpleDescribe = new wxTextCtrl(this, -1, wxT("简介"), wxPoint(-1, -1), wxSize(-1, -1), style );

	textWeatherBackground = new wxTextCtrl(this, -1, wxT("天气背景介绍"), wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE|style );

	textImportantSystem = new wxTextCtrl(this, -1, wxT("影响系统介绍"), wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE|style );
	
	textPath = new wxTextCtrl(this, -1, wxT("在这里填写路径"), wxPoint(-1, -1), wxSize(-1, -1),style );
	
	textSignValue = new wxTextCtrl(this, -1, wxT("量值"), wxPoint(-1, -1), wxSize(-1, -1), style );

	textDetailDescribe = new wxTextCtrl(this, -1, wxT("详细情况介绍"), wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE|style );
}

void ChangeInstanceDlg::InitControlValue()
{
	
	//wxMessageBox(wxT("will initial textctrl"));
	switch(changeType)
	{
	case VIEWONLY:
	case EDIT:
			conboInstanceType->Clear();
			conboInstanceType->Append( instance.GetTypeName() );
			conboInstanceType->SetStringSelection(instance.GetTypeName());
		
			textBeginDate->SetValue(instance.GetBeginDate() );
			textEndDate->SetValue( instance.GetEndDate() );
	
			textWeatherBackground->SetValue( instance.GetBackground() );
			textSimpleDescribe->SetValue(instance.GetSimple() );
			textSignValue->SetValue(instance.GetValue() );
			textPath->SetValue(instance.GetPath() );
			textImportantSystem->SetValue( instance.GetSystem() );
			textDetailDescribe->SetValue( instance.GetDetail() );
			
			InitRelateFilesList();

			break;
	
		default:break;
	}
	//wxMessageBox(wxT("after initial textctrl"));
	
	
	Refresh();
}

void ChangeInstanceDlg::SetInstance(const DisasterInstance &disInstance)
{
	instance = disInstance;
	InitControlValue();
}

void ChangeInstanceDlg::InitRelateFilesList()
{
	filenamesList->Clear();

	wxStringTokenizer tkz(instance.GetRelateFiles(), wxT("\n"));
	
	while ( tkz.HasMoreTokens() )
	{
		wxString token = tkz.GetNextToken();

		// process token here
		filenamesList->Append(token);
	}

}

void ChangeInstanceDlg::AfterDialogCreation(wxWindowCreateEvent & event)
{
	
}

bool LaunchFile(wxString filename)
{

	bool isok = false ;
	wxFileType * ft = wxTheMimeTypesManager->GetFileTypeFromExtension( filename.AfterLast(wxT('.') ) );
	if ( ft )
	{
		wxString cmd = ft->GetOpenCommand(filename);
		if( cmd.Find(wxT("\"")) == wxNOT_FOUND 
		 && cmd.Find(wxT("\'")) == wxNOT_FOUND )
		 {
		 	filename = wxT("\'") + filename + wxT("\'");
		 }
		 
		 
		//wxMessageBox(ft->GetOpenCommand(filename));
		isok = wxExecute(ft->GetOpenCommand(filename));
		
		delete ft ;
		
		return isok;
	}

	return false;
}

void ChangeInstanceDlg::OnDoubleClickListItem(wxCommandEvent &event)
{
	wxString fullName = event.GetString();
	
	ViewSelectFile(fullName);
}

void ChangeInstanceDlg::ViewSelectFile(wxString &fullName )
{
	if(!fullName.empty())
	{
		if(fullName.Find(wxFILE_SEP_PATH) == wxNOT_FOUND )
		{
			fullName = dstDbPath + wxT("relate-files")+wxFILE_SEP_PATH+fullName;	
		}
		LaunchFile(fullName);
		
	}
}

void ChangeInstanceDlg::OnClickViewFileButton(wxCommandEvent& WXUNUSED(event) )
{
	wxString fullName = filenamesList->GetStringSelection();
	
	ViewSelectFile(fullName);
}

void ChangeInstanceDlg::DeleteSelectFile(wxCommandEvent& WXUNUSED(event) )
{
	int index = filenamesList->GetSelection();
	
	if(index != wxNOT_FOUND)
	{
		filenamesList->Delete(index);
	}
}

void ChangeInstanceDlg::SaveRelateFiles()
{
	for(size_t index=0;index != filenamesList->GetCount(); index++)
	{
		wxString fullName = filenamesList->GetString(index),
				 name = fullName.AfterLast(wxFILE_SEP_PATH);
		
		if(fullName.Find(wxFILE_SEP_PATH) != wxNOT_FOUND )
		{
			wxCopyFile(fullName, dstDbPath+wxT("relate-files")+wxFILE_SEP_PATH+name);
			filenamesList->SetString(index, name );
		}
		
		relateFilesStr += name+wxT("\n");	
	}
}

void ChangeInstanceDlg::OnOk(wxCommandEvent& WXUNUSED(event) )
{
	//void Assign(wxString name,wxString date,wxString simpDescribe,wxString value,
	//			wxString background,wxString system,wxString path,wxString detail)
	
	SaveRelateFiles();
	
	wxString dateStr = textBeginDate->GetValue() + wxT('-') + textEndDate->GetValue();
	
	instance.Assign(conboInstanceType-> GetValue(), dateStr, 
					textSimpleDescribe -> GetValue(),
					textSignValue -> GetValue(),
					textWeatherBackground -> GetValue(),
					textImportantSystem -> GetValue(),
					textPath -> GetValue(),
					textDetailDescribe -> GetValue(),
					relateFilesStr);
					
	
	
	//wxMessageBox(wxT("will exit") );
	EndModal(wxID_OK);
}

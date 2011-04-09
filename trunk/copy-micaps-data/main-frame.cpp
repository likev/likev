
#include "main-frame.h"
#include "copy-all-file.h"

enum
{
	ID_BeginCopy
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_BUTTON(ID_BeginCopy,  MyFrame::BeginCopy)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame( NULL, -1, title, pos, size )
{	
	wxConfigBase *pConfig = wxConfigBase::Get();

  	wxString micaps_dir,copy_dir;
  	pConfig->Read(wxT("/Position/micaps-dir"), &micaps_dir, wxGetHomeDir());
  	pConfig->Read(wxT("/Position/copy-dir"), &copy_dir, wxGetHomeDir());
  	
	//pane all
	wxPanel *base_panel = new wxPanel(this);
    wxSizer *sizerall = new wxBoxSizer(wxVERTICAL);
  	// 1 pane
    wxStaticBox *box1 = new wxStaticBox(base_panel, wxID_ANY, _T("选择目录"));

    wxSizer *sizer1 = new wxStaticBoxSizer(box1, wxHORIZONTAL);
    dir_pick_from = new wxDirPickerCtrl(base_panel, -1,micaps_dir, wxT("选择Micaps资料所在目录"),
                                        wxDefaultPosition, wxSize(180,50),wxDIRP_USE_TEXTCTRL|wxDIRP_DIR_MUST_EXIST);
    dir_pick_to = new wxDirPickerCtrl(base_panel, -1,copy_dir, wxT("资料复制到"),
                                        wxDefaultPosition, wxSize(180,50),wxDIRP_USE_TEXTCTRL|wxDIRP_DIR_MUST_EXIST);
                                        
    sizer1 -> Add(dir_pick_from,1,wxEXPAND|wxALL,10);
    sizer1 -> Add(dir_pick_to,1,  wxEXPAND|wxALL,10);
    
    //2 pane
	wxSizer *sizer2 = new wxStaticBoxSizer(wxHORIZONTAL,base_panel,wxT("选择需要复制的内容"));
    
    check1 = new wxCheckBox(base_panel,-1,wxT("云图"));
    check2 = new wxCheckBox(base_panel,-1,wxT("高空")); 
    check3 = new wxCheckBox(base_panel,-1,wxT("地面"));
    
    check4 = new wxCheckBox(base_panel,-1,wxT("EC"));
    check5 = new wxCheckBox(base_panel,-1,wxT("T213"));
    check6 = new wxCheckBox(base_panel,-1,wxT("physic"));
    
   	sizer2 -> Add(check1,1,wxALL,10);
   	sizer2 -> Add(check2,1,wxALL,10);
   	sizer2 -> Add(check3,1,wxALL,10);
   	sizer2 -> Add(check4,1,wxALL,10);
   	sizer2 -> Add(check5,1,wxALL,10);
   	sizer2 -> Add(check6,1,wxALL,10);
   	
   	//3 pane
   	wxStaticBox *box3 = new wxStaticBox(base_panel, wxID_ANY, _T("选择时间范围"));

    wxSizer *sizer3 = new wxStaticBoxSizer(box3, wxHORIZONTAL);
    
    pick_begin = new wxDatePickerCtrl(base_panel,-1,wxDefaultDateTime,wxPoint(-1,-1),wxSize(180,30),wxDP_DROPDOWN);
    pick_end   = new wxDatePickerCtrl(base_panel,-1,wxDefaultDateTime,wxPoint(-1,-1),wxSize(180,30),wxDP_DROPDOWN);
    				 
    sizer3 -> Add(pick_begin,1,wxALL,10);
    sizer3 -> Add(pick_end,1,wxEXPAND|wxALL,10);
    
    //4 pane
    wxSizer *sizer4 = new wxBoxSizer(wxHORIZONTAL);
    begin_copy = new wxButton(base_panel, ID_BeginCopy, wxT("开始复制"),wxPoint(-1,-1),wxSize(100,50));
    sizer4 -> Add(begin_copy,1);
    
    base_panel->SetSizer(sizerall);
    
    sizerall -> Add(sizer1,0,wxEXPAND|wxALL,10);
    sizerall -> Add(sizer2,0,wxEXPAND|wxALL,10);
    sizerall -> Add(sizer3,0,wxEXPAND|wxALL,10);
    sizerall -> Add(sizer4,0,wxEXPAND|wxALL,10);
    
    Center();
}

void MyFrame::BeginCopy(wxCommandEvent& event)
{
	begin_copy -> SetLabel(wxT("正在复制文件...") );
	begin_copy -> Disable();

	if(check1->IsChecked())
	{ 
		CopyALLFile(wxT("fy2"));
		CopyALLFile(wxT("cloud"));
	}
	if(check2->IsChecked()) CopyALLFile(wxT("high"));
	if(check3->IsChecked()) CopyALLFile(wxT("surface"));
	if(check4->IsChecked()) CopyALLFile(wxT("ecmwf"));
	if(check5->IsChecked()) CopyALLFile(wxT("T213"));
	if(check6->IsChecked()) CopyALLFile(wxT("physic"));

	begin_copy -> SetLabel(wxT("复制文件完成！") );
	wxMessageBox(wxT("复制文件完成！"), wxT("完成！"), wxOK|wxICON_INFORMATION);
	
	begin_copy -> Enable();
	begin_copy -> SetLabel(wxT("开始复制") );
}

bool MyFrame::CopyALLFile(const wxString &content)
{
	wxString oridir = dir_pick_from->GetPath()+wxT("\\")+content,
			 desdir = dir_pick_to->GetPath() + wxT("\\")+content;
	
	//wxMessageBox(oridir,wxT("oridir"));
	//wxMessageBox(desdir,wxT("desdir"));
	
	if(!::wxDirExists(oridir) ) return false;
	
	if(!::wxDirExists(desdir) )
	{
		::wxMkdir(desdir);
	}
	
	wxDir dir(oridir);
	MyDirTrav trvs(oridir,desdir);
	
	dir.Traverse(trvs,wxEmptyString,wxDIR_DIRS); //创建目录
	
	for(wxDateTime day=pick_begin->GetValue(); day <= pick_end->GetValue(); day += wxTimeSpan::Day() )
	{
		wxString filespec = day.Format(wxT("%y%m%d*.*"));

		dir.Traverse(trvs,filespec); //复制文件
	}
	
	return true;
}

MyFrame::~MyFrame()
{
  wxConfigBase *pConfig = wxConfigBase::Get();
  if ( pConfig == NULL )
    return;

  // save the control's values to the config
  pConfig->Write(wxT("/Position/micaps-dir"), dir_pick_from->GetPath());
  pConfig->Write(wxT("/Position/copy-dir"), dir_pick_to->GetPath());
}

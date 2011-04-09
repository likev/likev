
#include "main-frame.h"
#include "plot-panel.h"

enum
{
    ID_Quit = 1,
    ID_About,
    ID_PrevTime,
    ID_NextTime,
    ID_SelectTime,
    ID_SetLonLat
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Quit, MyFrame::OnQuit)
    EVT_MENU(ID_About, MyFrame::OnAbout)
    
    EVT_BUTTON(ID_PrevTime,  MyFrame::PrevTime)
    EVT_BUTTON(ID_NextTime,  MyFrame::NextTime)
    EVT_DATE_CHANGED(ID_SelectTime, MyFrame::SelectTime)
    EVT_BUTTON(ID_SetLonLat,  MyFrame::SetLonLat)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame( NULL, -1, title, pos, size )
{	
	wxConfigBase *pConfig = wxConfigBase::Get();

  	//pConfig->SetPath(wxT("/Position"));
  	
  	pConfig->Read(wxT("/Position/lon"), &lon, 112.5);
  	pConfig->Read(wxT("/Position/lat"), &lat, 35.0);
  	pConfig->Read(wxT("/Period/ftimes"), &ftimes, 7);
  	pConfig->Read(wxT("/Path/file_path"), &data_path, wxT("/home/atqixiangju/data/ecmwf/") );
  	
	
	forcast_begin = GetLastestForcastTime();
	InitPointValue();
    
    //3.
    wxPanel *panel = new wxPanel(this, -1);
  	//panel->SetBackgroundColour(col1);
  	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  	panel->SetSizer(vbox);
  	
  	wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
  	
  	wxButton *prev_time = new wxButton(panel, ID_PrevTime, wxT("<--"),wxPoint(-1,-1),wxSize(100,30) );
  	select_time = new wxDatePickerCtrl(panel,ID_SelectTime,forcast_begin,wxPoint(-1,-1),wxSize(140,30),
										wxDP_DROPDOWN);
	
  	wxButton *next_time = new wxButton(panel, ID_NextTime, wxT("-->"),wxPoint(-1,-1),wxSize(100,30) );
  	
  	wxStaticText *lon_text = new wxStaticText(panel,-1,wxT("lon")),
  				 *lat_text = new wxStaticText(panel,-1,wxT("lat"));
  				 
  	lon_edit = new wxTextCtrl(panel,-1,wxString::Format(wxT("%4.1f"),lon),wxPoint(-1, -1), wxSize(70, 30), 
  							  wxTE_RIGHT, wxTextValidator(wxFILTER_NUMERIC) ),
  	lat_edit = new wxTextCtrl(panel,-1,wxString::Format(wxT("%3.1f"),lat),wxPoint(-1, -1), wxSize(70, 30), 
  							  wxTE_RIGHT, wxTextValidator(wxFILTER_NUMERIC) );
  				 
  	wxButton *set_lonlat = new wxButton(panel, ID_SetLonLat, wxT("设置"),wxPoint(-1,-1),wxSize(100,30) );
  	
  	sizer1->Add(prev_time,0,wxLEFT,10);
  	sizer1->Add(select_time,0,wxLEFT|wxRIGHT,10);
  	sizer1->Add(next_time,0);
  	sizer1->Add(250,-1);
  	sizer1->Add(lon_text,0,wxTOP,5);
  	sizer1->Add(lon_edit,0,wxRIGHT,10);
  	
  	sizer1->Add(lat_text,0,wxTOP,5);
  	sizer1->Add(lat_edit,0);
  	sizer1->Add(set_lonlat,0,wxLEFT,10);
  	

	wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
	
  	drawPane = new PlotPanel(panel);
    sizer2->Add(drawPane,0,wxBOTTOM,10);
	
	vbox->Add(-1,10);
	vbox->Add(sizer1,0, wxALL,10);
	vbox->Add(sizer2,1, wxALL,10);
  	
  	Centre();
  	
  	ChangeView();
}

void MyFrame::AddMenuStatusBar()
{
		//1. MenuBar
    wxMenu *menuFile = new wxMenu;

    menuFile->Append( ID_About, _("&About...") );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, _("E&xit") );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, _("&File") );
    
    wxMenu *menuFile2 = new wxMenu;

    menuFile2->Append( ID_About, _("&About2...") );
    menuFile2->AppendSeparator();
    menuFile2->Append( ID_Quit, _("E&xit2") );
    
    menuBar->Append( menuFile2, _("&File2") );
    
    SetMenuBar( menuBar );

	//2. StatusBar
    CreateStatusBar();
    SetStatusText( wxString::Format(wxT("%d"),ftimes) );
}

bool MyFrame::GetFiles()
{	
	std::string file_name(forcast_begin.Format(wxT("%y%m%d%H")).mb_str() );

	//clear
	wind500_f.clear();
	wind700_f.clear();
	wind850_f.clear();
	rh700_f.clear();
	rh850_f.clear();
	temper850_f.clear();
	press999_f.clear();
	//add
	
	for(int i=1;i<ftimes+1;i++)
	{
		std::string file_path(data_path.mb_str() );
		std::string ext(wxString::Format(wxT(".%03d"),i*24).mb_str() );
		
		//wxMessageBox( wxString((file_path+"wind/500/"+file_name+ext).c_str(), wxConvUTF8) );
		
		wind500_f.push_back(Diamond2(file_path+"wind/500/"+file_name+ext) );
		wind700_f.push_back(Diamond2(file_path+"wind/700/"+file_name+ext) );
		wind850_f.push_back(Diamond2(file_path+"wind/850/"+file_name+ext) );
		
		rh700_f.push_back(Diamond3(file_path+"rh-p/700/"+file_name+ext) );
		rh850_f.push_back(Diamond3(file_path+"rh-p/850/"+file_name+ext) );
		temper850_f.push_back(Diamond3(file_path+"temper-p/850/"+file_name+ext) );
		press999_f.push_back(Diamond3(file_path+"pres-p/999/"+file_name+ext) );
		
		wind500_f[i-1].GetValue(lon,lat,wind500_p[i-1]);
		wind700_f[i-1].GetValue(lon,lat,wind700_p[i-1]);
		wind850_f[i-1].GetValue(lon,lat,wind850_p[i-1]);
		
		rh700_f[i-1].GetValue(lon,lat,rh700_p[i-1]);
		rh850_f[i-1].GetValue(lon,lat,rh850_p[i-1]);
		temper850_f[i-1].GetValue(lon,lat,temper850_p[i-1]);
		press999_f[i-1].GetValue(lon,lat,press999_p[i-1]);
		
	}
	
	return true;
}
void MyFrame::InitPointValue()
{
	wind500_p.assign(ftimes,WindVector() );
	wind700_p.assign(ftimes,WindVector() );
	wind850_p.assign(ftimes,WindVector() );
	rh700_p.assign(ftimes,0);
	rh850_p.assign(ftimes,0);
	temper850_p.assign(ftimes,0);
	press999_p.assign(ftimes,0);	
}
bool MyFrame::GetPointValue()
{
	for(int i=0;i<ftimes;i++)
	{	
		wind500_f[i].GetValue(lon,lat,wind500_p[i]);
		wind700_f[i].GetValue(lon,lat,wind700_p[i]);
		wind850_f[i].GetValue(lon,lat,wind850_p[i]);
		
		rh700_f[i].GetValue(lon,lat,rh700_p[i]);
		rh850_f[i].GetValue(lon,lat,rh850_p[i]);
		temper850_f[i].GetValue(lon,lat,temper850_p[i]);
		press999_f[i].GetValue(lon,lat,press999_p[i]);
	}
	return true;
}

//when click quit
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

//when click about
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox( _("This is a wxWidgets Hello world sample"),
                  _("About Hello World"),
                  wxOK | wxICON_INFORMATION, this);
}

void MyFrame::PrevTime(wxCommandEvent& event)
{
	forcast_begin -= wxTimeSpan::Hours(12);
	select_time->SetValue(forcast_begin);
	ChangeView();
}
void MyFrame::NextTime(wxCommandEvent& event)
{
	forcast_begin += wxTimeSpan::Hours(12);
	if(forcast_begin > GetLastestForcastTime())
	{
		forcast_begin -= wxTimeSpan::Hours(12);
		return;
	}
	
	select_time->SetValue(forcast_begin);
	ChangeView();
}

void MyFrame::SetLonLat(wxCommandEvent& event)
{
	if(Validate() )
	{
		if( lon_edit->GetValue().ToDouble(&lon) &&
			lat_edit->GetValue().ToDouble(&lat) )
		{
			InitPointValue();
			GetPointValue();
			drawPane->Refresh();
		}
	}
}
void MyFrame::SelectTime(wxDateEvent& event)
{
	if(event.GetDate() > GetLastestForcastTime() || 
		event.GetDate().GetDateOnly() == forcast_begin.GetDateOnly() )
	{
		select_time->SetValue(forcast_begin);
		return;
	}
	
	forcast_begin = event.GetDate().GetDateOnly()+wxTimeSpan::Hours(forcast_begin.GetHour());
	ChangeView();
	
}

void MyFrame::ChangeView()
{
	GetFiles();
	InitPointValue();
	GetPointValue();
	drawPane->Refresh();
	SetTitle(wxString::Format(wxT("EC预报格点值查看--起始场:%d年%d月%d日 %d时"),
		forcast_begin.GetYear(),forcast_begin.GetMonth()+1,forcast_begin.GetDay(),forcast_begin.GetHour()) );
	//SetTitle(forcast_begin.Format(_("EC预报格点值查看--起始场:%Y年%m月%d日 %H时")) );
}

wxDateTime MyFrame::GetLastestForcastTime()
{
	wxDateTime lastest = wxDateTime::Today() - wxTimeSpan::Day();
	
	int cur_hour = wxDateTime::Now().GetHour();
	
	if(cur_hour<6)
	{
		lastest += wxTimeSpan::Hours(8);	
	}
	else if(cur_hour<16)
	{
		lastest += wxTimeSpan::Hours(20);
	}
	else
	{//today hour 8
		lastest += wxTimeSpan::Day() + wxTimeSpan::Hours(8);
	}
	
	return lastest;
}

MyFrame::~MyFrame()
{
  wxConfigBase *pConfig = wxConfigBase::Get();
  if ( pConfig == NULL )
    return;

  // save the control's values to the config
  pConfig->Write(wxT("/Position/lon"), lon);
  pConfig->Write(wxT("/Position/lat"), lat);
}

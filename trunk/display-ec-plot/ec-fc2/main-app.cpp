#include "main-app.h"
#include "main-frame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxFileConfig *pConfig1 = new wxFileConfig(wxT("ec-fc"),wxT("lyqx"),
                               wxT("ec-fc.ini"),wxT("ec-fc.ini"),
                               wxCONFIG_USE_GLOBAL_FILE|wxCONFIG_USE_RELATIVE_PATH);
                               
  	wxConfigBase::Set(pConfig1);
  	wxConfigBase::Get() -> SetRecordDefaults();
    
    MyFrame *frame = new MyFrame(wxT("Hello wxDC"), wxPoint(50,50), wxSize(940,680));
	
    
    //frame->SetAutoLayout(true);
	
    frame->Show(true);
	SetTopWindow(frame);
    return true;
}

int MyApp::OnExit()
{
  delete wxConfigBase::Set((wxConfigBase *) NULL);

  return 0;
}

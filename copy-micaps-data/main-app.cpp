#include "main-app.h"
#include "main-frame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxFileConfig *pConfig1 = new wxFileConfig(wxT("copy-micpas"),wxT("lyqx"),
                               wxT("copy-micpas.ini"),wxT("copy-micpas.ini"),
                               wxCONFIG_USE_GLOBAL_FILE|wxCONFIG_USE_RELATIVE_PATH);
                               
  	wxConfigBase::Set(pConfig1);
  	wxConfigBase::Get() -> SetRecordDefaults();
    
    MyFrame *frame = new MyFrame(wxT("Micaps资料复制"), wxPoint(-1,-1), wxSize(940,400));
	
    
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

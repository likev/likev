#include "main-app.h"
#include "main-frame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxFileConfig *pConfig1 = new wxFileConfig(wxT("disaster-manage"),wxT("lyqx"),
                               wxT("disaster-manage.ini"),wxT("disaster-manage.ini"),
                               wxCONFIG_USE_GLOBAL_FILE|wxCONFIG_USE_RELATIVE_PATH|wxCONFIG_USE_NO_ESCAPE_CHARACTERS);
                               
  	wxConfigBase::Set(pConfig1);
  	wxConfigBase::Get() -> SetRecordDefaults();
    
    MyFrame *frame = new MyFrame(wxT("洛阳市灾害性天气查询系统"), wxPoint(-1,-1), wxSize(960,560));
	
    
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

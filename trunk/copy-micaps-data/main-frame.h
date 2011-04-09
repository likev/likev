/*
    main frame
    last modify:2010 10 9
*/

#ifndef _MAIN_FRAME_
#define _MAIN_FRAME_


#include "wx/wx.h"
#include "wx/dateevt.h"
#include "wx/datectrl.h"
#include "wx/filepicker.h"
#include "wx/fileconf.h"
#include "wx/checkbox.h"
#include <vector>


class MyFrame: public wxFrame
{
public:

	//window 
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MyFrame();


    DECLARE_EVENT_TABLE()
    
public:

	
private:
	wxDirPickerCtrl *dir_pick_from, *dir_pick_to;
	wxCheckBox *check1, *check2, *check3, *check4, *check5, *check6;
	wxDatePickerCtrl *pick_begin, *pick_end;
	wxButton *begin_copy;
	
private:
	void BeginCopy(wxCommandEvent& event);
	bool CopyALLFile(const wxString &content);
};


#endif //_MAIN_FRAME_

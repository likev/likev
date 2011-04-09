/*
    main frame
    last modify:2010 12 24
*/

#ifndef _MAIN_FRAME_
#define _MAIN_FRAME_

#include <vector>

#include "wx/wx.h"
#include "wx/string.h"
#include "wx/fileconf.h"
#include "wx/checkbox.h"
#include "wx/listctrl.h"
#include "wx/richtext/richtextctrl.h"
#include "wx/tglbtn.h"

#include "disaster-instance.h"
#include "search-condition.h"

class MyFrame: public wxFrame
{
public:

	//window 
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MyFrame();


    DECLARE_EVENT_TABLE()
    
public:

	
private:
	enum SORTSTYLE{ BYTYPE, BYYEAR, BYMONTH, BYSEARCH};

	wxListBox *sortList;
	wxListCtrl  *instanceList;
	wxToggleButton * sortByType, * sortByYear, * sortByMonth, *searchResult;
	wxRichTextCtrl *detailPanel;
	std::vector<DisasterInstance> allInstances;
	
	SORTSTYLE sortStyle;
	wxString sortSelectItem;
	wxString dstDbPath, micapsPath;
	int micapsVersion;
	
	bool ReadFromXmlFile();
	bool WriteToXmlFile();
	void ReadDataAgain();
	bool InstanceShoudeBeShow(const DisasterInstance &dstInstance)const;
	bool InstanceAgreeSearch(const DisasterInstance &dstInstance) const;
	void RefreshInstanceList();
	void UpdateSortList();
	
	long SeleteInstanceId;
	std::vector<DisasterInstance>::iterator GetSeleteInstance();
private:
	
	wxSizer * CreatPanelLeft(wxWindow * parent);
	wxSizer * CreatPanelMiddle(wxWindow * parent);
	wxSizer * CreatPanelRight(wxWindow * parent);
	
	wxToolBar *toolbar;
	void InitToolBar(wxWindow * parent);
	
	void UpdateToggleButton();
	
	void InitAllCtrl();
	void OnQuit(wxCommandEvent& WXUNUSED(event));
	void AddInstance(wxCommandEvent& event);
	
	void ViewInstance(wxCommandEvent& event);
	void EditInstance(wxCommandEvent& event);
	void DeleteInstance(wxCommandEvent& event);
	
	SearchCondition condition;
	void SearchInstance(wxCommandEvent& event);
	void MicapsInstance(wxCommandEvent& event);
	void RadarInstance(wxCommandEvent& event);
	
	void OnToggleSortStyle(wxCommandEvent& event);

	void OnClickSortItem(wxCommandEvent& event);
	void OnClickListItem(wxListEvent &event);
	
	
};


#endif //_MAIN_FRAME_

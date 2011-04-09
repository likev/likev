/*
    main frame
    last modify:2010 10 14
*/

#ifndef _MAIN_FRAME_
#define _MAIN_FRAME_


#include "wx/wx.h"
#include "wx/dateevt.h"
#include "wx/datectrl.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "micaps-data.h"
#include <vector>


class PlotPanel;

class MyFrame: public wxFrame
{
public:

	//window 
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MyFrame();

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void PrevTime(wxCommandEvent& event);
	void NextTime(wxCommandEvent& event);
	void SelectTime(wxDateEvent& event);
	void SetLonLat(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
    
public:
	wxDateTime forcast_begin;
	double lon,lat;
	int ftimes;
	
	wxString data_path;
	//std::string file_path;
	//forcast files
	std::vector<Diamond2> wind500_f, wind700_f, wind850_f;
	std::vector<Diamond3> rh700_f, rh850_f, temper850_f, press999_f;
	
	//need point value
	std::vector<WindVector> wind500_p, wind700_p, wind850_p;
	std::vector<double> rh700_p, rh850_p, temper850_p, press999_p;
	
	//get files
	bool GetFiles();
	void InitPointValue();
	bool GetPointValue();
	
private:
	void AddMenuStatusBar();
	wxDatePickerCtrl *select_time;
	wxTextCtrl   *lon_edit , *lat_edit;
	PlotPanel *drawPane;
	wxDateTime GetLastestForcastTime();
	void ChangeView();
};


#endif //_MAIN_FRAME_

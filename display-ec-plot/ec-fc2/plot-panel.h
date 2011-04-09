/*
    plot lines and wind
    last modify:2010 10 14
*/

#ifndef _PLOT_PANEL_
#define _PLOT_PANEL_

#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/listctrl.h"
#include "main-frame.h"

class PlotPanel : public wxPanel
{
	wxListCtrl * list1;
	
	wxButton * button1;
	
	MyFrame * pant;
    
public:
    PlotPanel(wxPanel* parent);
    
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    
    void UpdateListTitle();
    
    void DrawWind(wxDC&  dc, double posX, double posY, double value, double direction);
    
    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */
     void mouseDown(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     
     void SetWind(wxCommandEvent& event);
    
    DECLARE_EVENT_TABLE()
};

#endif //_PLOT_PANEL_

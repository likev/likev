#include "plot-panel.h"
#include "cmath-ex.h"
#include <vector> 
#include <algorithm>

enum {
wxID_DRAW = 1
};
 
BEGIN_EVENT_TABLE(PlotPanel, wxPanel)
// some useful events
/*
 EVT_MOTION(PlotPanel::mouseMoved)
 
 EVT_LEFT_UP(PlotPanel::mouseReleased)

 EVT_LEAVE_WINDOW(PlotPanel::mouseLeftWindow)
 EVT_KEY_DOWN(PlotPanel::keyPressed)
 EVT_KEY_UP(PlotPanel::keyReleased)
 EVT_MOUSEWHEEL(PlotPanel::mouseWheelMoved)
 */
 
// catch paint events
EVT_PAINT(PlotPanel::paintEvent)
//EVT_LEFT_DOWN(PlotPanel::mouseDown)
//EVT_RIGHT_DOWN(PlotPanel::rightClick)
 
END_EVENT_TABLE()
 
 
// some useful events
/*
 void PlotPanel::mouseMoved(wxMouseEvent& event) {}

 void PlotPanel::mouseWheelMoved(wxMouseEvent& event) {}
 void PlotPanel::mouseReleased(wxMouseEvent& event) {}

 void PlotPanel::mouseLeftWindow(wxMouseEvent& event) {}
 void PlotPanel::keyPressed(wxKeyEvent& event) {}
 void PlotPanel::keyReleased(wxKeyEvent& event) {}
 */
 
void PlotPanel::mouseDown(wxMouseEvent& event) 
{
	wxClientDC dc(this);
    //wxScreenDC dc;
    dc.SetBackground(*wxTRANSPARENT_BRUSH);
    dc.Clear();
}
 
void PlotPanel::rightClick(wxMouseEvent& event) 
{
	paintNow();
}
 
PlotPanel::PlotPanel(wxPanel* parent) 
	:wxPanel(parent)
{
	pant = (MyFrame *)(GetGrandParent());
	//text1 = new wxTextCtrl(this, -1, wxT("value"), wxPoint(20,20));
	//text2 = new wxTextCtrl(this, -1, wxT("direction"), wxPoint(100,20));
	
	list1 = new wxListCtrl(this, -1, wxPoint(10,380),wxSize(900,180), wxLC_REPORT);
	list1->SetFont(wxFont(11,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL) );

	 // note that under MSW for SetColumnWidth() to work we need to create the
    // items with images initially even if we specify dummy image id
	wxListItem itemCol;
   
    itemCol.SetText(_T(""));
    itemCol.SetImage(-1);
    list1->InsertColumn(0, itemCol);
    list1->SetColumnWidth(0, 100 );
    
    for(int i=1;i<8;i++)
    {
    	itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    	itemCol.SetText(wxT(""));
    	list1->InsertColumn(i, itemCol);
    	list1->SetColumnWidth(i, 100 );
    }
    
    wxString itemNames[] = {wxT("wind 500hPa"),wxT("wind 700hPa"),wxT("wind 850hPa"), 
    						wxT("t 850hPa"), wxT("rh 700hPa"), wxT("rh 850hPa"), wxT("press sea")};
    
    for(int i=0;i<7;i++)
    {
    	list1->InsertItem(i, itemNames[i]);
    }
    
    list1->SetSingleStyle(wxLC_HRULES | wxLC_VRULES, true);
}

void PlotPanel::UpdateListTitle()
{
	wxListItem itemCol;
    for(int i=1;i<8;i++)
    {
    	itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    	//itemCol.SetText((pant->forcast_begin+wxTimeSpan::Days(i) ).Format(wxT("%d日")));
		itemCol.SetText((pant->forcast_begin+wxTimeSpan::Days(i) ).Format(wxT("%d/%m")));
    	list1->SetColumn(i, itemCol);
    	list1->SetColumnWidth(i, 100 );
    }
}

void PlotPanel::SetWind(wxCommandEvent& event)
{
	//(text1 -> GetValue()).Trim().ToDouble(&value);
	//(text2 -> GetValue()).Trim().ToDouble(&direction);
	
	//wxMessageDialog(this,wxString::Format(wxT("value: %f\ndirection: %f"), value,direction ) ).ShowModal();
	Refresh();
}
 
/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */
 
int rand_range(int min,int max)
{
	int value = 0;
	
	do{
		value = rand()%(max+1);
	}while(value < min);
	
	return value;
}
 
void PlotPanel::paintEvent(wxPaintEvent & evt)
{
	UpdateListTitle();

    wxPaintDC dc(this);
    
    dc.SetDeviceOrigin(50,370);
    dc.SetAxisOrientation(true,true);
	dc.SetFont(wxFont(11,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL) );
    
    dc.DrawRectangle( -40, 0, 900, 350 );
    
    dc.SetPen(wxPen( wxColor(200,200,200), 1 ,wxDOT));
    for(int i=1;i<8;i++)
    {
    	dc.DrawLine(i*100,0,i*100,350);
    }
 
    std::vector<wxPoint> points;   
    //850 temph

    int min_t = int(*std::min_element(pant->temper850_p.begin(), pant->temper850_p.end() ) ) ,
    	max_t = int(*std::max_element(pant->temper850_p.begin(), pant->temper850_p.end() ) ) ;
    	
    double yscale = 300/(max_t - min_t +1e-10);
    for(int i=1;i<8;i++)
    {
    	double temph = pant->temper850_p[i-1] ;
    	points.push_back(wxPoint(i*100,temph*yscale) );
    	
    	list1->SetItem(3, i, wxString::Format(wxT("%3.1f"),temph));
    }
    
    dc.SetPen(wxPen( wxColor(255,175,175) ,3));
    
    //yzixs
    dc.DrawLine(20,0,20,340);
    dc.DrawText(wxT("t-850/度"),20,15);
    
    dc.SetAxisOrientation(true,false);
    dc.SetLogicalOrigin(0,min_t*yscale);
    dc.SetAxisOrientation(true,true);
    
    for(int t=min_t+1;t<=max_t;t++)
    {
    	double h = t*yscale;
    	dc.DrawLine(20,h,30,h);
    	dc.DrawText(wxString::Format(wxT("%d"),t),10,h+5);
    }

    dc.DrawLines(points.size(), &points[0]);
    
    //
    dc.SetAxisOrientation(true,false);
    dc.SetLogicalOrigin(0,0);
    dc.SetAxisOrientation(true,true);
    //700 rp
    points.clear();
    for(int i=1;i<8;i++)
    {
    	double rp700 = pant->rh700_p[i-1] ;
    	points.push_back(wxPoint(i*100,rp700) );
    	
    	list1->SetItem(4, i, wxString::Format(wxT("%4.1f"),rp700));
    }
    
    dc.SetPen(wxPen( wxColor(175,255,175), 1 ));
    dc.SetUserScale(1,3.5);
    dc.DrawLines(points.size(), &points[0]);
    
    dc.DrawLine(780,0,780,100);
    
    //850 rp
    points.clear();
    for(int i=1;i<8;i++)
    {
    	
    	double rp850 = pant->rh850_p[i-1] ;
    	points.push_back(wxPoint(i*100,rp850) );
    	
    	list1->SetItem(5, i, wxString::Format(wxT("%4.1f"),rp850));
    }
    
    dc.SetPen(wxPen( wxColor(175,105,195), 1 ));
    dc.DrawLines(points.size(), &points[0]);
    
    dc.DrawLine(830,0,830,100);
    
    dc.SetUserScale(1,1);
    
    dc.DrawText(wxT("rp-700/850"),780,15);
        
    for(int t=10;t<100;t+=10)
    {
    	dc.DrawLine(770,t*3.5,780,t*3.5);
    	dc.DrawText(wxString::Format(wxT("%d%%"),t),780,t*3.5+5);
    }
    
    //1000 presure
    int min_p = int(*std::min_element(pant->press999_p.begin(), pant->press999_p.end() ) ),
    	max_p = int(*std::max_element(pant->press999_p.begin(), pant->press999_p.end() ) );
    	
    double pscale = 300.0/(max_p - min_p +1e-10);
    
    points.clear();
    for(int i=1;i<8;i++)
    {
    	double press1000 = pant->press999_p[i-1];
    	points.push_back(wxPoint(i*100, (press1000)*pscale) );
    	list1->SetItem(6, i, wxString::Format(wxT("%5.1f"),press1000) );
    }
    dc.SetUserScale(1,1);
    dc.SetPen(wxPen( wxColor(120,120,120), 3 ));
    
     //yzixs
    dc.DrawLine(-40,0,-40,340);
    dc.DrawText(wxT("hPa"),-30,15);
    
    dc.SetAxisOrientation(true,false);
    dc.SetLogicalOrigin(0,min_p*pscale);
    dc.SetAxisOrientation(true,true);

    dc.DrawLines(points.size(), &points[0]);
   
    for(int p=min_p+2;p<=max_p;p++)
    {
    	double h = p*pscale;
    	dc.DrawLine(-40,h,-30,h);
    	dc.DrawText(wxString::Format(wxT("%d"),p),-40,h+5);
    }
    
    //wind
    dc.SetAxisOrientation(true,false);
    dc.SetLogicalOrigin(0,0);
    dc.SetAxisOrientation(true,true);
    dc.SetUserScale(1,1);
    dc.SetPen(wxPen( wxColor(100,100,100), 1 ,wxSOLID));
    
    //pant->SetStatusText( wxString::Format(wxT("hello%d"),pant->ftimes) );
    for(int i=1; i <= pant->ftimes; i++)
    {
    	double value500= pant->wind500_p[i-1].val,  direction500 = pant->wind500_p[i-1].dirct,
    		   value700= pant->wind700_p[i-1].val,  direction700 = pant->wind700_p[i-1].dirct,
    		   value850= pant->wind850_p[i-1].val,  direction850 = pant->wind850_p[i-1].dirct;
    		   
    	DrawWind(dc,i*100,300, value500, direction500);
    	DrawWind(dc,i*100,200, value700, direction700);
    	DrawWind(dc,i*100,100, value850, direction850);
    	
    	list1->SetItem(0, i, wxString::Format(wxT("%3.1f  %4.1f"),value500, direction500)); 
    	list1->SetItem(1, i, wxString::Format(wxT("%3.1f  %4.1f"),value700, direction700));
    	list1->SetItem(2, i, wxString::Format(wxT("%3.1f  %4.1f"),value850, direction850));
    }
}
 
/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void PlotPanel::paintNow()
{
    wxClientDC dc(this);
    //wxScreenDC dc;
    
}
 
/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */

void PlotPanel::DrawWind(wxDC&  dc, double posX, double posY, double value, double direction)
{
	if(value > 1000 ) return;

    dc.SetAxisOrientation(true,true);
    
    double l=50, s=12, w=24;
    double ax = posX+l*sind(direction),
    	   ay = posY+l*cosd(direction);
    
    dc.SetPen( wxPen( wxColor(0,0,0), 2 ) );
    dc.DrawLine(posX,posY,ax, ay);
    
    double rest = value+1;
    int n20=rest/20;
    
    for(int i=0;i<n20;i++)
    {
    	double bx = ax - i*s*sind(direction),
    		   by = ay - i*s*cosd(direction),
    		   
    		   cx = bx + w*cosd(direction),
    		   cy = by - w*sind(direction),
    		   
    		   dx = bx - s*sind(direction),
    		   dy = by - s*cosd(direction);
    		   
    	dc.DrawLine(bx,by,cx,cy);
    	dc.DrawLine(cx,cy,dx,dy);	
    }
    
    ax -= n20*s*sind(direction);
    ay -= n20*s*cosd(direction);
    
    s = 8;
    rest -= n20*20;
    int n4 = rest/4;
    for(int i=0;i<n4;i++)
    {
    	double bx = ax - i*s*sind(direction),
    		   by = ay - i*s*cosd(direction),
    		   
    		   cx = bx + w*cosd(direction),
    		   cy = by - w*sind(direction);
    		   
    	dc.DrawLine(bx,by,cx,cy);	
    }
    
    rest -= n4*4;
    
    if(rest > 2 || dbeql(rest,2,6) )
    {
    	double bx = ax - n4*s*sind(direction),
    		   by = ay - n4*s*cosd(direction),
    		   
    		   cx = bx + w*cosd(direction)/2,
    		   cy = by - w*sind(direction)/2;
    		   
    	dc.DrawLine(bx,by,cx,cy);
    }
    
    // Look at the wxDC docs to learn how to draw other stuff
}

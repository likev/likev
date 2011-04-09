
#include <windows.h>
#include <fstream>
#include "main-frame.h"
#include "change-instance.h"


enum
{
	ID_BeginCopy,
	wxID_VIEW_ITEM,
	wxID_EDIT_ITEM, 
	wxID_ADD_ITEM,
	wxID_DELETE_ITEM,
	wxID_MICAPS,
	wxID_RADAR,
	wxID_SEARCH,
	wxID_SORT_LIST,
	wxID_DETAIL_LIST,
	wxID_DETAIL_TEXT,
	wxID_TOGGLE_TYPE,
	wxID_TOGGLE_YEAR,
	wxID_TOGGLE_MONTH,
	wxID_TOGGLE_SEARCH
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	//EVT_BUTTON(ID_BeginCopy,  MyFrame::BeginCopy)
	EVT_MENU(wxID_ADD_ITEM, MyFrame::AddInstance)
	EVT_MENU(wxID_VIEW_ITEM, MyFrame::ViewInstance)
	EVT_MENU(wxID_EDIT_ITEM, MyFrame::EditInstance)
	EVT_MENU(wxID_DELETE_ITEM, MyFrame::DeleteInstance)
	EVT_MENU(wxID_SEARCH, MyFrame::SearchInstance)
	EVT_MENU(wxID_MICAPS, MyFrame::MicapsInstance)
	EVT_MENU(wxID_RADAR, MyFrame::RadarInstance)
	
	EVT_TOGGLEBUTTON(wxID_TOGGLE_TYPE, MyFrame::OnToggleSortStyle)
	EVT_TOGGLEBUTTON(wxID_TOGGLE_YEAR, MyFrame::OnToggleSortStyle)
	EVT_TOGGLEBUTTON(wxID_TOGGLE_MONTH, MyFrame::OnToggleSortStyle)
	EVT_TOGGLEBUTTON(wxID_TOGGLE_SEARCH, MyFrame::OnToggleSortStyle)
	
	EVT_LISTBOX(wxID_SORT_LIST, MyFrame::OnClickSortItem) //wxEVT_COMMAND_LISTBOX_SELECTED
	EVT_LIST_ITEM_SELECTED(wxID_DETAIL_LIST,MyFrame::OnClickListItem)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame( NULL, -1, title, pos, size )
, sortStyle(BYTYPE), SeleteInstanceId(0), sortSelectItem(wxT("ȫ��"))
{	
	wxConfigBase *pConfig = wxConfigBase::Get();

  	pConfig->Read(wxT("/Path/dstDb"), &dstDbPath);
	pConfig->Read(wxT("/Path/micaps"), &micapsPath,wxT("D:\\MICAPS\\micaps3\\"));
	pConfig->Read(wxT("/Version/micaps"),&micapsVersion, 3);
    
	SetIcon(wxIcon(wxT("IDI_ICON_MAIN")) );
	SetFont(wxFont(11,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL) );
	
	//pane all 
	wxPanel * panelAll = new wxPanel(this);
    
	InitToolBar(panelAll);
	wxSizer *panelLeft = CreatPanelLeft(panelAll),
	      *panelCenter = CreatPanelMiddle(panelAll),
	       *panelRight = CreatPanelRight(panelAll);
  
    wxSizer *sizerClient = new wxBoxSizer(wxHORIZONTAL);
   
    sizerClient -> Add(panelLeft,0,wxEXPAND|wxLEFT|wxTOP|wxBOTTOM,15);
    sizerClient -> Add(panelCenter,0,wxLEFT|wxRIGHT,10);
    sizerClient -> Add(panelRight,1,wxEXPAND|wxRIGHT|wxTOP|wxBOTTOM,15);
    
	wxSizer *sizerAll = new wxBoxSizer(wxVERTICAL);
	sizerAll->Add(toolbar,0,wxEXPAND|wxLEFT|wxRIGHT,15);
	sizerAll->Add(sizerClient,1,wxEXPAND);

	panelAll->SetSizer(sizerAll);
    
    InitAllCtrl();
    
   // ReadFromXmlFile();
    
    
    
    Center();
}

wxSizer * MyFrame::CreatPanelLeft(wxWindow * parent)
{
	wxSizer *panelLeft = new wxBoxSizer(wxVERTICAL);
	
	sortList = new wxListBox(parent,wxID_SORT_LIST,wxPoint(-1,-1),wxSize(150,-1));
	
	sortByType = new wxToggleButton(parent,wxID_TOGGLE_TYPE,wxT("�����") );
	sortByYear = new wxToggleButton(parent,wxID_TOGGLE_YEAR,wxT("�����") );
	sortByMonth = new wxToggleButton(parent,wxID_TOGGLE_MONTH,wxT("���·�") );
	searchResult = new wxToggleButton(parent,wxID_TOGGLE_SEARCH,wxT("�������") );
	
	panelLeft -> Add(sortList,1);
	
	panelLeft -> Add(sortByType,0,wxEXPAND|wxTOP,10);
	panelLeft -> Add(sortByYear,0,wxEXPAND|wxTOP,10);
	panelLeft -> Add(sortByMonth,0,wxEXPAND|wxTOP,10);
	panelLeft -> Add(searchResult,0,wxEXPAND|wxTOP,10);
	
	return panelLeft;
}
wxSizer * MyFrame::CreatPanelMiddle(wxWindow * parent)
{
	wxSizer *panelCenter = new wxBoxSizer(wxVERTICAL);
	
	return panelCenter;
}
wxSizer * MyFrame::CreatPanelRight(wxWindow * parent)
{
	wxSizer *sizerTop = new wxBoxSizer(wxHORIZONTAL);
	
	instanceList = new wxListCtrl(parent, wxID_DETAIL_LIST, wxPoint(-1,-1),wxSize(-1,-1), wxLC_REPORT);

    instanceList->SetSingleStyle(wxLC_HRULES | wxLC_VRULES, true);
    
    sizerTop -> Add(instanceList,1,wxEXPAND);
    
    wxSizer *sizerMiddle = new wxBoxSizer(wxHORIZONTAL);
    
    wxSizer *sizerBottom = new wxBoxSizer(wxHORIZONTAL);
    
    detailPanel = new wxRichTextCtrl(parent,-1,wxT("��ϸ��Ϣ"),wxPoint(-1,-1),wxSize(-1,-1),wxRE_READONLY);
    
    sizerBottom -> Add(detailPanel,1,wxEXPAND);
    
    wxSizer *panelRight = new wxBoxSizer(wxVERTICAL);
    panelRight -> Add(sizerTop,5,wxEXPAND);
    panelRight -> Add(sizerMiddle,0,wxEXPAND|wxTOP|wxBOTTOM,5);
    panelRight -> Add(sizerBottom,4,wxEXPAND);
	
	return panelRight;
}

void MyFrame::InitToolBar(wxWindow * parent)
{
  wxImage::AddHandler( new wxPNGHandler );
  
  wxBitmap view_pic(wxT("pics/view.png"), wxBITMAP_TYPE_PNG),
  		   edit_pic(wxT("pics/edit.png"), wxBITMAP_TYPE_PNG),
  		   add_pic(wxT("pics/add.png"), wxBITMAP_TYPE_PNG),
  		   delete_pic(wxT("pics/delete.png"), wxBITMAP_TYPE_PNG),
  		   
  		   micaps_pic(wxT("pics/micaps.png"), wxBITMAP_TYPE_PNG),
  		   radar_pic(wxT("pics/radar.png"), wxBITMAP_TYPE_PNG),
  		   
  		   search_pic(wxT("pics/search.png"), wxBITMAP_TYPE_PNG),
  		   
  		   exit_pic(wxT("pics/exit.png"), wxBITMAP_TYPE_PNG);

  toolbar = new wxToolBar(parent,-1);
  toolbar-> SetWindowStyle(wxTB_TEXT);
  toolbar->AddTool(wxID_VIEW_ITEM,wxT("�鿴"), view_pic, wxT("�鿴��ϸ��Ϣ") );
  toolbar->AddTool(wxID_EDIT_ITEM, wxT("�༭"),edit_pic, wxT("�༭����"));
  toolbar->AddTool(wxID_ADD_ITEM, wxT("���"),add_pic, wxT("��Ӹ���"));
  toolbar->AddTool(wxID_DELETE_ITEM, wxT("ɾ��"),delete_pic, wxT("ɾ��ѡ�и���"));

  toolbar->AddSeparator();

  toolbar->AddTool(wxID_MICAPS,wxT("Micaps"), micaps_pic, wxT("�鿴Micaps����"));
  toolbar->AddTool(wxID_RADAR,wxT("�״�"),radar_pic, wxT("�鿴�״�����"));
  
  toolbar->AddSeparator();
    
  toolbar->AddTool(wxID_SEARCH,wxT("����"), search_pic, wxT("��������"));
  
  toolbar->AddSeparator();
  toolbar->AddTool(wxID_EXIT, wxT("�˳�"),exit_pic, wxT("�˳�����"));
  
  toolbar->Realize();

  Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED, 
      wxCommandEventHandler(MyFrame::OnQuit));
}

void MyFrame::InitAllCtrl()
{
	UpdateToggleButton();
	UpdateSortList();

    wxString describeItems[DisasterInstance::describeCount - 1] 
    			= {wxT("���"),wxT("��ʼ����"),wxT("��������"),wxT("���"),wxT("��ֵ"),wxT("��������"),wxT("Ӱ��ϵͳ"),wxT("�ƶ�·��")};
    
	wxListItem itemCol;

	for(int i=0;i<DisasterInstance::describeCount - 1;i++)
    {
    	itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    	itemCol.SetText(describeItems[i]);
    	instanceList->InsertColumn(i, itemCol);
    	instanceList->SetColumnWidth(i, 100 );
    }
	
	ReadDataAgain();
}

void MyFrame::OnToggleSortStyle(wxCommandEvent& event)
{
	switch(event.GetId())
	{
	case wxID_TOGGLE_YEAR:
		sortStyle = BYYEAR;
		break;
	case wxID_TOGGLE_MONTH:
		sortStyle = BYMONTH;
		break;
	case wxID_TOGGLE_SEARCH:
		sortStyle = BYSEARCH;
		break;
	default:
		sortStyle = BYTYPE;
		break;
	}
	
	UpdateToggleButton();
	UpdateSortList();
}
void MyFrame::UpdateSortList()
{
	//initial listctrl
	sortList->Clear();
	sortList->Append(wxT("ȫ��") );
	sortList->SetStringSelection(wxT("ȫ��") );
	sortSelectItem = wxT("ȫ��");
	
	switch(sortStyle)
	{
	case BYYEAR:
		for(int year = wxDateTime::Now().GetYear();
				year != 1955; year-- )
		{
			sortList->Append(wxString::Format(wxT("%d��"),year) );
		}
		break;
	case BYMONTH:
		for(int month = 1; month < 13; month++ )
		{
			sortList->Append(wxString::Format(wxT("%d��"),month) );
		}
		break;
	case BYSEARCH:
		break;
	default:
		for(size_t index=0;index<DisasterInstance::disasterKind; index ++)
		{
			sortList->Append(DisasterInstance::DisasterNames[index] );
		}
		break;
	}
	
	RefreshInstanceList();
	
}

void MyFrame::UpdateToggleButton()
{
	sortByType->SetValue(false);
	sortByYear->SetValue(false);
	sortByMonth->SetValue(false);
	searchResult->SetValue(false);
	
	switch(sortStyle)
	{
	case BYYEAR:
		sortByYear->SetValue(true);
		break;
	case BYMONTH:
		sortByMonth->SetValue(true);
		break;
	case BYSEARCH:
		searchResult->SetValue(true);
		break;
	default:
		sortByType->SetValue(true);
		break;
	}
}

bool MyFrame::ReadFromXmlFile()
{
	//wxMessageBox(wxT("��ʼ��ȡxml...") );
	wxXmlDocument doc;
	if(! doc.Load(dstDbPath+wxT("dstdb.xml")) )
	{
		wxMessageBox(wxT("�����ļ�����...") );
		return false;
	}
	
	if (doc.GetRoot()->GetName() != wxT("AllDisasters"))
    {
    	wxMessageBox(wxT("�ļ���ʽ����...") );
    	return false;
    }
    //wxMessageBox(wxT("file right...") );
    allInstances.clear();
    
    for(wxXmlNode *disasterSort = doc.GetRoot()->GetChildren(); 
    	disasterSort; disasterSort = disasterSort->GetNext() )
    {
    	for(wxXmlNode *instance = disasterSort->GetChildren();
    		instance; instance = instance->GetNext() )
    	{
    		//wxMessageBox(instance->GetName());
    		allInstances.push_back( DisasterInstance(instance) );
    	}
    }
    
    //wxMessageBox(wxT("ȫ����ȡ���...") );
    return allInstances.size();

}


bool MyFrame::WriteToXmlFile()
{
	wxXmlNode * rootNode = new wxXmlNode(NULL,wxXML_ELEMENT_NODE, wxT("AllDisasters") );

	std::vector<wxXmlNode *> disasterSorts;
	for(size_t index=0; index < DisasterInstance::disasterKind; index++ )
	{
		disasterSorts.push_back(new wxXmlNode(rootNode,wxXML_ELEMENT_NODE, DisasterInstance::DisasterNames[index] ) );
	}
	
	
	for(size_t kind=0; kind < DisasterInstance::disasterKind; kind++ )
	{
		for(size_t index=0;index != allInstances.size(); index++)
		{
			if(allInstances[index].GetTypeName() == DisasterInstance::DisasterNames[kind] )
			{
				disasterSorts[kind]-> AddChild(allInstances[index].GetInstanceNode() );
			}
		}	
	}
	
	wxXmlDocument doc;
	
	doc.SetRoot(rootNode);
	
	return doc.Save(dstDbPath+wxT("dstdb.xml"));
}

void MyFrame::AddInstance(wxCommandEvent& event)
{
	ChangeInstanceDlg dlg(wxT("�����ֺ���������"), ADD);
	int id = dlg.ShowModal();
	if(id == wxID_OK)
	{
		//wxMessageBox(wxT("Press ok") );
		allInstances.push_back( dlg.GetInstance() );
		
		WriteToXmlFile();
		ReadDataAgain();
	}
	else if(id == wxID_CANCEL)
	{
		//wxMessageBox(wxT("Press exit") );
	}
}

void MyFrame::ViewInstance(wxCommandEvent& event)
{
	if(! instanceList->GetSelectedItemCount() ) return;
	
	//wxMessageBox(wxT("name")+ GetSeleteInstance()->GetTypeName() );
	ChangeInstanceDlg dlg(wxT("�鿴�ֺ���������"), VIEWONLY);
	
	dlg.SetInstance(*GetSeleteInstance());
	int id = dlg.ShowModal();
	if(id == wxID_OK)
	{
		//wxMessageBox(wxT("Press ok") );
	}
}
void MyFrame::EditInstance(wxCommandEvent& event)
{
	//wxMessageBox(wxT("edit..."));
	if(! instanceList->GetSelectedItemCount() ) return;
	
	ChangeInstanceDlg dlg(wxT("�༭ѡ��ĸ���"), EDIT);
	dlg.SetInstance(*GetSeleteInstance());
	
	int id = dlg.ShowModal();
	if(id == wxID_OK)
	{
		//wxMessageBox(wxT("Press ok") );
		*GetSeleteInstance() = dlg.GetInstance();
		WriteToXmlFile();
		ReadDataAgain();
	}
}
void MyFrame::DeleteInstance(wxCommandEvent& event)
{
	if(! instanceList->GetSelectedItemCount() ) return;

	int answer = wxMessageBox(wxT("ȷ��Ҫɾ��ѡ��ĸ���"), wxT("��ʾ"),
                            wxYES_NO | wxICON_QUESTION);
  	
  	if (answer == wxYES)
	{
		allInstances.erase(GetSeleteInstance() );
	
		WriteToXmlFile();
		ReadDataAgain();
	}
}
void MyFrame::SearchInstance(wxCommandEvent& event)
{
	//wxMessageBox(wxT("search..."));
	DisasterSearchDlg searchDlg(wxT("ѡ����������"));
	searchDlg.SetCondition(condition);
	
	if(searchDlg.ShowModal() == wxID_OK)
	{
		//wxMessageBox(wxT("search ok..."));
		condition = searchDlg.GetCondition();
		
		sortStyle = BYSEARCH;

		UpdateToggleButton();
		UpdateSortList();
	}
}
void MyFrame::MicapsInstance(wxCommandEvent& event)
{
	//wxMessageBox();
	wxString instancePath = dstDbPath+wxT("micaps-data\\")
			+ GetSeleteInstance()->GetTypeName() + wxFILE_SEP_PATH
			+ GetSeleteInstance()->GetBeginDate()+wxT('-')+GetSeleteInstance()->GetEndDate();

	if(2 == micapsVersion)
	{
	
		std::ofstream fout("dst-micaps20.begin");
		fout<<"diamond  19\n"
			<<"110.0  35.0  4.0\n"
			<<"LAMBERTM.DAT  8323071\n"
			<<"0  0  1024  768\n"
			<<(micapsPath+wxT("combine\\")).mb_str()
			<<"combine\n"
			<<"10.0  10.0\n"
			<<"1  1  0";
		fout.close();

		fout.open(micapsPath+wxT("getdatadir.dat"));
		
		fout<< instancePath.mb_str();
		fout.close();

		wxString micapsSetFilename = ::wxGetCwd()+wxT("\\dst-micaps20.begin");

		//open micaps
		ShellExecute(NULL,wxT("open"),micapsPath+wxT("micaps20.exe"),micapsSetFilename+wxT(" h500.zht"),micapsPath,SW_SHOWNORMAL);

	}
	else
	{
		std::ofstream fout(micapsPath+wxT("modual\\combine\\combine.ini"));

		if(!fout.is_open())
		{
			wxMessageBox(wxT("���ܴ�micaps�����ļ�������micaps·�����ã�"),wxT("����"));
			return;
		}

		fout<<"[����]\n"
			<<"�ı��ۺ�ͼָ���ļ��̷�=false\n"
			<<"�ı��̷�=ZZYYXX\n"
			<<"���ӻ���Ŀ¼="<<instancePath.mb_str();
		fout.close();

		//open micaps
		ShellExecute(NULL,wxT("open"),micapsPath+wxT("micaps3.exe"),NULL,micapsPath,SW_SHOWNORMAL);
	}
}
void MyFrame::RadarInstance(wxCommandEvent& event)
{
	wxMessageBox(wxT("radar..."));
}

void MyFrame::OnClickSortItem(wxCommandEvent& event)
{
	sortSelectItem = event.GetString();
	//wxMessageBox(event.GetString());
	RefreshInstanceList();
}

wxString GetReportListText(const wxListCtrl *list, long row, long col)
{
	wxListItem info;
	info.SetMask(wxLIST_MASK_TEXT);
	info.SetId(row);
	info.SetColumn(col);
	if(!list->GetItem(info)) wxMessageBox(wxT("�޷���ȡ������Ϣ!"),wxT("����") );
	
	return info.GetText();
}

std::vector<DisasterInstance>::iterator 
MyFrame::GetSeleteInstance()
{
	   
    for(std::vector<DisasterInstance>::iterator it=allInstances.begin();
    	it != allInstances.end(); it++)
	{
		/*
		wxMessageBox(it->GetTypeName()+it->GetBeginDate()+it->GetEndDate()
			+wxT(':')+GetReportListText(instanceList,SeleteInstanceId,0)
			+wxT(':')+GetReportListText(instanceList,SeleteInstanceId,1)
			+wxT(':')+GetReportListText(instanceList,SeleteInstanceId,2));
			*/

		if(GetReportListText(instanceList,SeleteInstanceId,0) == it->GetTypeName()
		&& GetReportListText(instanceList,SeleteInstanceId,1) == it->GetBeginDate()
		&& GetReportListText(instanceList,SeleteInstanceId,2) == it->GetEndDate() )
		
		{
			return it;
		}
	}
	
	wxMessageBox(wxT("���ִ���") );
	return allInstances.begin();
}


void MyFrame::OnClickListItem(wxListEvent &event)
{
	SeleteInstanceId = event.GetIndex();
	
	//(wxString::Format(wxT("ѡ�����Ŀ�� %d"), SeleteInstanceId) );

	//wxMessageBox(GetSeleteInstance()->GetDetail());
	detailPanel->SetValue(GetSeleteInstance()->GetDetail() );
}

void MyFrame::ReadDataAgain()
{
	ReadFromXmlFile();
	RefreshInstanceList();
}

bool MyFrame::InstanceShoudeBeShow(const DisasterInstance &dstInstance) const
 {
 	if(wxT("ȫ��") == sortSelectItem)
 	{ 
 		if(BYSEARCH == sortStyle)
 		{
 			return InstanceAgreeSearch(dstInstance);
 		}
 		else
 		{
 			return true;
 		}
 	}
	
	switch(sortStyle)
	{
	case BYYEAR:
		return (dstInstance.GetBeginDate().substr(0,4)+wxT("��") == sortSelectItem );
		break;
	case BYMONTH:
		{
			wxString monthStr = dstInstance.GetBeginDate().substr(4,2);
			return (monthStr.AfterLast(wxT('0'))+wxT("��") == sortSelectItem );
			break;
		}
	case BYSEARCH:
		break;
	default:
		return (dstInstance.GetTypeName() == sortSelectItem);
		break;
	}
	
	return false;
 }
 
bool MyFrame::InstanceAgreeSearch(const DisasterInstance &dstInstance) const
 {
	if(condition.istype)
	{
		if(dstInstance.GetType() != condition.dstType) return false;
	}
	if(condition.isyear)
	{
		wxString yearStr = dstInstance.GetBeginDate().substr(0,4);
		if(yearStr < condition.beginYear || yearStr > condition.endYear) return false;
	}
	if(condition.ismonth)
	{
		unsigned long month,bMonth,eMonth;
		dstInstance.GetBeginDate().Mid(4,2).ToULong(&month);
		condition.beginMonth.ToULong(&bMonth);
		condition.endMonth.ToULong(&eMonth);
		
		if(month < bMonth || month > eMonth ) return false;
	}
	if(condition.isword)
	{
		if(!dstInstance.HaveWord(condition.searchWord) ) return false;
	}
	
	return true;
 }

void MyFrame::RefreshInstanceList()
{
    instanceList->DeleteAllItems();
   
	//wxMessageBox(wxString::Format(wxT("�������� %d ..."),allInstances.size()) );
    for(size_t index=0;index != allInstances.size(); index++)
	{
		if(!InstanceShoudeBeShow(allInstances[index] ) ) continue;
	
		instanceList->InsertItem(0, allInstances[index].GetTypeName() );
		instanceList->SetItem(0,1, allInstances[index].GetBeginDate() );
		instanceList->SetItem(0,2, allInstances[index].GetEndDate());
		instanceList->SetItem(0,3, allInstances[index].GetSimple() );
		instanceList->SetItem(0,4, allInstances[index].GetValue() );
		instanceList->SetItem(0,5, allInstances[index].GetBackground() );
		instanceList->SetItem(0,6, allInstances[index].GetSystem() );
		instanceList->SetItem(0,7, allInstances[index].GetPath() );

		//wxMessageBox(wxString::Format(wxT("�б� %d �������..."),index+1) );
		
	}
	instanceList->SetItemState(0,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED );
	Refresh();
	//wxMessageBox(wxT("�б�������...") );
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}


MyFrame::~MyFrame()
{
  wxConfigBase *pConfig = wxConfigBase::Get();
  if ( pConfig == NULL )
    return;
    
  //pConfig->Write(wxT("/Path/dstDb"), dstDbPath);
  
  if(2 == micapsVersion)
  {
	  std::ofstream fout(micapsPath+wxT("getdatadir.dat"));
	  fout<<"W:";
	  fout.close();
  }
  else
  {
	  std::ofstream fout(micapsPath+wxT("modual\\combine\\combine.ini"));
	  fout<<"[����]\n"
		  <<"�ı��ۺ�ͼָ���ļ��̷�=false\n"
		  <<"�ı��̷�=ZZYYXX\n"
		  <<"���ӻ���Ŀ¼=W:";
	  fout.close();
  }

}

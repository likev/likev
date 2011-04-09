/*
    change instance: view edit add
    last modify:2010 12 27
*/

#ifndef CHANGE_INSTANCE
#define CHANGE_INSTANCE


#include "wx/wx.h"
#include "wx/dateevt.h"
#include "wx/datectrl.h"
#include "wx/filepicker.h"
#include "wx/checkbox.h"
#include "wx/richtext/richtextctrl.h"
#include "wx/dnd.h"
#include "disaster-instance.h"

enum CHANGE_INSTANCE_TYPE {EDIT,ADD,VIEWONLY};

class ChangeInstanceDlg: public wxDialog
{
	wxTextCtrl *textBeginDate, *textEndDate, *textSimpleDescribe, *textWeatherBackground,
				 *textImportantSystem,*textPath, *textSignValue,*textDetailDescribe;
	wxComboBox *conboInstanceType;
	wxListBox * filenamesList;
	wxSizer *sizerFilesList;
	
	CHANGE_INSTANCE_TYPE changeType;
	
	void InitControlValue();
	void CreatTextCtrls();
	void CreatFilesListSizer();

public:
	//return to users
	DisasterInstance instance;
	
	wxString relateFilesStr;
	wxString dstDbPath;
	
	//initial from DisasterInstance
	void SetInstance(const DisasterInstance &disInstance);
	
	DisasterInstance GetInstance()
	{
		return instance;
	}
	void InitRelateFilesList();
	
	void SaveRelateFiles();

public:
	ChangeInstanceDlg(const wxString& title, CHANGE_INSTANCE_TYPE type);
	
	DECLARE_EVENT_TABLE()
public:
	void OnOk(wxCommandEvent& WXUNUSED(event) );
	void AfterDialogCreation(wxWindowCreateEvent & event);
	void OnDoubleClickListItem(wxCommandEvent &event);
	void ViewSelectFile(wxString & fullName);
	void OnClickViewFileButton(wxCommandEvent& WXUNUSED(event) );
	void DeleteSelectFile(wxCommandEvent& WXUNUSED(event) );
};

// 一个拖放目的类用来将拖动的文件名添加到列表框
class DnDFile : public wxFileDropTarget
{
public :
	DnDFile ( wxListBox * owner ) { m_owner = owner ; }
	virtual bool OnDropFiles ( wxCoord x , wxCoord y , const wxArrayString & filenames )
	{
		size_t nFiles = filenames.GetCount();
		wxString str ;
		/*
		str.Printf( wxT ( " % d files dropped " ) , ( int ) nFiles );
		m_owner->Append ( str );
		*/
		for (size_t n = 0; n < nFiles ; n ++ ) 
		{
			m_owner->Append ( filenames [n ]);
		}
		return true ;
	}
private:
	wxListBox *m_owner ;
};


#endif //ADD_INSTANCE

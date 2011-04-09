
#ifndef _SEARCH_CONDITION
#define _SEARCH_CONDITION

#include "wx/wx.h"
#include "disaster-instance.h"

struct SearchCondition
{
	bool istype,isyear,ismonth,isword;
	DisasterType dstType;
	wxString beginYear,endYear, beginMonth,endMonth, searchWord;
	
	SearchCondition()
	{
		istype = isyear = ismonth = isword = false;
		dstType = RAIN_STORM;
	}
};

class DisasterSearchDlg : public wxDialog
{

public:
	DisasterSearchDlg(const wxString& title);
	
	SearchCondition GetCondition()const
	{
		return condition;
	}
	void SetCondition(const SearchCondition &searchCondition)
	{
		condition = searchCondition;
		typeName= DisasterInstance::GetDisasterName(condition.dstType);
	}
private:
	
	SearchCondition condition;
	wxCheckBox * checkType, *checkYear, *checkMonth, *checkWord;
	wxComboBox * comboInstanceType;
	wxTextCtrl *textBeginYear, *textEndYear, *textBeginMonth, *textEndMonth, *textSearchWord;
	wxString typeName;
	
	DECLARE_EVENT_TABLE()
	void OnOk(wxCommandEvent& WXUNUSED(event) );
};

#endif //_SEARCH_CONDITION

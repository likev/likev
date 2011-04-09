
/*
    disaster instance class
    last modify:2010 12 24
*/


#ifndef DISASTER_INSTANCE
#define DISASTER_INSTANCE

#include <vector>
#include <string>
#include "wx/wx.h"
#include "wx/string.h"
#include "wx/xml/xml.h"

enum DisasterType
	{   RAIN_STORM, HAIL, THUNDER, COLD_WAVE,HEAVY_SNOW,
		HIGH_FROST, HEAVY_FOG, BIG_WIND, HIGH_TEMPH, LOW_TEMPH, 
		DROUGHT, HOT_WIND, SANDSTORM, HAZE, ICY_ROADS, 
		
		UNKNOWN
	};

class DisasterInstance
{
public:
	static const int disasterKind = 15;
	static const int describeCount = 9;
	static std::vector<wxString> DisasterNames;

private:	
	DisasterType dtype;
	wxString dateStr, 
			 simpleDescribe, 
			 weatherBackground, 
			 importantSystem, 
			 movingPath, 
			 signValue, 
			 detailDescribe,
			 relateFilesStr;
	
	
	void CreatContentNode(wxXmlNode * parent, const wxString &nodeName, const wxString &nodeContent)const
	{
		wxXmlNode *instanceSimple = new wxXmlNode(parent,wxXML_ELEMENT_NODE,nodeName) ;
		
		//something wrong?
		new wxXmlNode(instanceSimple,wxXML_TEXT_NODE,wxEmptyString,nodeContent);
	}
public:
	//
	DisasterInstance()
	{
		dtype = UNKNOWN;
	}
	
	DisasterInstance(wxString name,wxString date,wxString simpDescribe,wxString value,
				wxString background,wxString system,wxString path,wxString detail,wxString relateFilesString)
	{	
		Assign(name, date, simpDescribe, value, background, system, path, detail, relateFilesString);
	}
	
	DisasterInstance(wxXmlNode * instanceNode)
	{
		Assign(instanceNode);
	}
	
	void Assign(wxString name,wxString date,wxString simpDescribe,wxString value,
				wxString background,wxString system,wxString path,wxString detail,wxString relateFilesString)
	{
		dtype = GetDisasterType(name);
		dateStr = date;
		simpleDescribe = simpDescribe;
		weatherBackground = background; 
		importantSystem = system;
		movingPath = path;
		signValue = value;
		detailDescribe = detail;
		relateFilesStr = relateFilesString;
	}
	
	//initial from the xmlNode 
	void Assign(wxXmlNode * instanceNode);

	wxString GetDetail()const
	{ return detailDescribe; }
	
	wxString GetTypeName()const
	{ return GetDisasterName(dtype); }
	
	wxString GetBeginDate()const
	{ return dateStr.BeforeFirst('-'); }
	
	wxString GetEndDate()const
	{ return dateStr.AfterLast('-');}
	
	DisasterType GetType()const
	{ return dtype; } 
	
	wxString GetBackground()const
	{ return weatherBackground; }
	
	wxString GetSimple()const
	{ return simpleDescribe; }
	
	wxString GetValue()const
	{ return signValue; }
	
	wxString GetPath()const
	{ return movingPath; }
	
	wxString GetSystem()const
	{ return importantSystem; }
	
	wxString GetRelateFiles()const
	{ return relateFilesStr; }
	
	bool HaveWord(const wxString &searchWord)const;
	
	static DisasterType GetDisasterType(const wxString &name);
	static wxString GetDisasterName(DisasterType type);
	
	wxXmlNode * GetInstanceNode()const ;
};
	
	
#endif //DISASTER

#include "disaster-instance.h"

wxString _AllDisasterNames[] = { wxT("暴雨"),wxT("冰雹"),wxT("雷电"),wxT("寒潮"),wxT("暴雪"),
								 wxT("霜冻"),wxT("大雾"),wxT("大风"),wxT("高温"),wxT("低温"),
								 wxT("干旱"),wxT("干热风"),wxT("沙尘暴"),wxT("霾"),wxT("道路结冰")
								};

std::vector<wxString> DisasterInstance::DisasterNames(_AllDisasterNames,_AllDisasterNames+disasterKind);

DisasterType DisasterInstance::GetDisasterType(const wxString &name)
{
	//wxString DisasterNames[] = {wxT("大风"),wxT("高温"),wxT("低温"),wxT("暴雨"),wxT("暴雪")};
	
	for(size_t index = 0; index < DisasterNames.size(); index++)
	{
		if(name == DisasterNames[index]) return DisasterType(index);
	}
	return UNKNOWN;
}

wxString DisasterInstance::GetDisasterName(DisasterType type)
{
	//wxString DisasterNames[] = {wxT("大风"),wxT("高温"),wxT("低温"),wxT("暴雨"),wxT("暴雪")};
	
	if(type != UNKNOWN ) return DisasterNames[type]; 
	else return wxT("未知");
}

void DisasterInstance::Assign(wxXmlNode * instanceNode)
{
	dateStr = instanceNode -> GetName().AfterFirst('e');
	
	wxXmlNode * item = instanceNode -> GetChildren();
	
	while(item)
	{
		wxString itemName = item -> GetName(),
				 content  = item -> GetNodeContent();
		
		if(wxT("灾害天气类型") == itemName)
		{
			dtype = GetDisasterType(content);
		}
		else if(wxT("简介") == itemName)
		{
			simpleDescribe = content;
		}
		else if(wxT("天气背景") == itemName)
		{
			weatherBackground = content;
		}
		else if(wxT("影响系统") == itemName)
		{
			importantSystem = content;
		}
		else if(wxT("移动路径") == itemName)
		{
			movingPath = content;
		}
		else if(wxT("量值") == itemName)
		{
			signValue = content;
		}
		else if(wxT("详细描述") == itemName)
		{
			detailDescribe = content;
		}
		else if(wxT("相关文件") == itemName)
		{
			relateFilesStr = content;
		}
		else{}
		
		
		item = item->GetNext();
	}
}

wxXmlNode * DisasterInstance::GetInstanceNode()const
{
	wxXmlNode * instanceNode = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("date")+dateStr);
	
	CreatContentNode(instanceNode, wxT("灾害天气类型"), GetDisasterName(dtype) );
	CreatContentNode(instanceNode, wxT("简介"), simpleDescribe);
	CreatContentNode(instanceNode, wxT("天气背景"), weatherBackground);
	CreatContentNode(instanceNode, wxT("影响系统"), importantSystem);
	CreatContentNode(instanceNode, wxT("移动路径"), movingPath);
	CreatContentNode(instanceNode, wxT("量值"), signValue);
	CreatContentNode(instanceNode, wxT("详细描述"), detailDescribe);
	CreatContentNode(instanceNode, wxT("相关文件"), relateFilesStr);
	
	return instanceNode;
}

bool DisasterInstance::HaveWord(const wxString &searchWord)const
{
	if(  simpleDescribe.find(searchWord) != wxString::npos
	  || weatherBackground.find(searchWord) != wxString::npos
	  || importantSystem.find(searchWord) != wxString::npos
	  || movingPath.find(searchWord) != wxString::npos
	  || signValue.find(searchWord) != wxString::npos
	  || detailDescribe.find(searchWord) != wxString::npos
	  || relateFilesStr.find(searchWord) != wxString::npos )
	  {
	  	  return true;
	  }
	
	
	return false;
}

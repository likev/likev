#include "disaster-instance.h"

wxString _AllDisasterNames[] = { wxT("����"),wxT("����"),wxT("�׵�"),wxT("����"),wxT("��ѩ"),
								 wxT("˪��"),wxT("����"),wxT("���"),wxT("����"),wxT("����"),
								 wxT("�ɺ�"),wxT("���ȷ�"),wxT("ɳ����"),wxT("��"),wxT("��·���")
								};

std::vector<wxString> DisasterInstance::DisasterNames(_AllDisasterNames,_AllDisasterNames+disasterKind);

DisasterType DisasterInstance::GetDisasterType(const wxString &name)
{
	//wxString DisasterNames[] = {wxT("���"),wxT("����"),wxT("����"),wxT("����"),wxT("��ѩ")};
	
	for(size_t index = 0; index < DisasterNames.size(); index++)
	{
		if(name == DisasterNames[index]) return DisasterType(index);
	}
	return UNKNOWN;
}

wxString DisasterInstance::GetDisasterName(DisasterType type)
{
	//wxString DisasterNames[] = {wxT("���"),wxT("����"),wxT("����"),wxT("����"),wxT("��ѩ")};
	
	if(type != UNKNOWN ) return DisasterNames[type]; 
	else return wxT("δ֪");
}

void DisasterInstance::Assign(wxXmlNode * instanceNode)
{
	dateStr = instanceNode -> GetName().AfterFirst('e');
	
	wxXmlNode * item = instanceNode -> GetChildren();
	
	while(item)
	{
		wxString itemName = item -> GetName(),
				 content  = item -> GetNodeContent();
		
		if(wxT("�ֺ���������") == itemName)
		{
			dtype = GetDisasterType(content);
		}
		else if(wxT("���") == itemName)
		{
			simpleDescribe = content;
		}
		else if(wxT("��������") == itemName)
		{
			weatherBackground = content;
		}
		else if(wxT("Ӱ��ϵͳ") == itemName)
		{
			importantSystem = content;
		}
		else if(wxT("�ƶ�·��") == itemName)
		{
			movingPath = content;
		}
		else if(wxT("��ֵ") == itemName)
		{
			signValue = content;
		}
		else if(wxT("��ϸ����") == itemName)
		{
			detailDescribe = content;
		}
		else if(wxT("����ļ�") == itemName)
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
	
	CreatContentNode(instanceNode, wxT("�ֺ���������"), GetDisasterName(dtype) );
	CreatContentNode(instanceNode, wxT("���"), simpleDescribe);
	CreatContentNode(instanceNode, wxT("��������"), weatherBackground);
	CreatContentNode(instanceNode, wxT("Ӱ��ϵͳ"), importantSystem);
	CreatContentNode(instanceNode, wxT("�ƶ�·��"), movingPath);
	CreatContentNode(instanceNode, wxT("��ֵ"), signValue);
	CreatContentNode(instanceNode, wxT("��ϸ����"), detailDescribe);
	CreatContentNode(instanceNode, wxT("����ļ�"), relateFilesStr);
	
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

//���������õ��ĺ�������

#include "comn.h"

//�����߳�������������
UINT MyThreadProc(LPVOID pParam );

//���Ͷ��� ���÷��Žӿ�
bool send_short_message(std::string message, std::string sendto);

//������ҳ
bool DownloadHttpPage(LPCTSTR pszServerName, LPCTSTR pszURL, LPCTSTR pszLocalFile);

//������Ϣ��
class DisasterInfo
{
private:
	std::string file_content,
		info_id,
		province,
		city,
		county,
		station_number,
		conect_telephone,
		type,
		location,
		describe,
		economic_loss,
		dead_number,
		begin_time,
		end_time;

	std::string get_speicl(std::string what)
	{
		size_t pos1,pos2,pos3;

		pos1 = file_content.find(what);
		if(pos1 != file_content.npos)
		{
			pos2 = file_content.find("class=\"hei\">",pos1);
			pos3 = file_content.find("</td>",pos2);

			return file_content.substr(pos2+24,pos3-pos2-24);
		}

		return "";
	}

public:
	void init(std::string filename)
	{
		filetostr(filename,file_content);

		info_id = get_speicl("����ֱ����Ϣ���");
		province= get_speicl("ʡ��");
		city    = get_speicl("�У��أ��ݣ�");
		county  = get_speicl("�أ������У�");
		station_number=get_speicl("վ��");
		conect_telephone=get_speicl("��ϵ�绰");
		type=get_speicl("�������");
		location=get_speicl("�ֺ�����������");
		describe=get_speicl("�ֺ�Ӱ������");
		economic_loss=get_speicl("ֱ�Ӿ�����ʧ");
		dead_number=get_speicl("��������");
		begin_time=get_speicl("��ʼʱ��");
		end_time=get_speicl("����ʱ��");
	}

	std::string to_sms()
	{
		//[����]2010��4��26��12ʱ ������[�绰68882126] ��� ������ʧ100��Ԫ ����0��
		// ������ε���1000���,���ݵ���10��...

		std::string sms;
		size_t pos;

		pos = begin_time.find("ʱ");
		sms += begin_time.substr(0,pos)+"ʱ";

		sms += " "+location;
		sms += "[�绰"+conect_telephone.substr(5)+"] ";
		sms += type;
		sms += " ������ʧ"+economic_loss;
		sms += " ����"+dead_number;
		sms += " "+describe.substr(0,120)+"...";

		return sms;
	}

	std::string to_text()
	{
		std::string sms;

		sms += begin_time;

		sms += "\r\n"+location;
		sms += "[�绰"+conect_telephone+"]\r\n";
		sms += type;
		sms += "\r\n������ʧ: "+economic_loss;
		sms += "\r\n����: "+dead_number;
		sms += "\r\n��������: "+describe;

		return sms;
	}
};

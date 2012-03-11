#include "bbs-monitor.h"

#include <Mmsystem.h>

#include <conio.h>

#pragma comment(lib,"winmm.lib")//��������ͷ�ļ���

volatile bool close_alert=false;

//�����߳�������������
UINT MyThreadProc(LPVOID pParam ) //�����߳�
{
	while(!close_alert)
	{
		PlaySound("warn.wav",NULL,SND_SYNC|SND_FILENAME);
		Sleep(1000);
	}

	return 0;   // thread completed successfully
}

//���Ͷ��� ����tui3�ӿ�
bool send_short_message(std::string message, std::string sendto)
{
	std::string murl="http://www.tui3.com/api/send/?k=321898d573024997301345c36bc9606f&r=json&p=1";
	murl +=  "&t="+sendto+"&cn="+message+" lyqx";

	try
	{
	CInternetSession session("Mozilla/5.0 (Windows; U; Windows NT 6.0; zh-CN; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3");
	session.OpenURL(murl.c_str());
	}
	catch (CInternetException* pEx)
	{
		char error[1025];
		pEx->GetErrorMessage(error, 1024);
		//cout<<"ERROR!"<<error<<endl;
		pEx->Delete();
		return false;
	}

	return true;
}

bool log_to_file(const std::string &filename, const std::string &information)
{
	CTime now = CTime::GetCurrentTime();
	std::ofstream fout(filename.c_str(),std::ios_base::out|std::ios_base::app);

	if(!fout.is_open()) return false;

	fout<<now.Format("[%Y-%m-%d %H:%M:%S]: ")<<information<<std::endl;
	fout.close();

	return true;
}

std::vector<std::string>& 
	get_pat_list(std::vector<std::string>& result, std::string& content, boost::regex pat)
{
	result.clear();

	boost::smatch what;
	std::string::const_iterator start, end;
	start = content.begin();
	end = content.end();

	while(regex_search(start, end, what, pat))
	{
		result.push_back(what[1]);
		start = what[0].second;
	}

	return result;
}

bool bbs_monitor::check_items()
{
	bool find_keyword = false;

	BOOST_FOREACH(item_describe& item, items)
	{
		BOOST_FOREACH(std::string& word, keywords)
		{
			if(item.title.find(word) != std::string::npos)
			{
				std::string this_url = "http://"+host+'/'+item.url;
				
				if(alarm_history.count(this_url) ) break;
				
				std::string newinfo = 
				"����վ"+host+"����������:\n"
				"----------------------------------------------\n"
				"����: "+item.title
				+"\n����: "+this_url
				+"\n����: "+item.author
				+"\n����ʱ��: "+item.timestr;
				
				std::cout<<newinfo<<"\n";

				log_to_file("monitor.log", newinfo);

				std::cout<<"���ڷ��Ͷ���...\n";
				start_send_sms();
				std::cout<<"�����ѷ��ͣ�\n\n";

				log_to_file("monitor.log", "�����ѷ���!");

				std::cout<<"������������(�밴������ر�)...";
				log_to_file("monitor.log", "������������...");

				start_sound_alarm();
				
				std::cout<<"\n�û��رձ�����������...\n";
				log_to_file("monitor.log", "�û��ر���������...");

				find_keyword = true;
				addto_alarm_history(this_url);
			}
		}
	}

	return find_keyword;
}

void bbs_monitor::start_send_sms()
{

}

void bbs_monitor::start_sound_alarm()
{
	close_alert = false;
	
	AfxBeginThread(MyThreadProc,NULL);

	if(_getch() ) close_alert = true;

}
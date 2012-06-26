#include "bbs-monitor.h"

#include <Mmsystem.h>

#include <conio.h>

#pragma comment(lib,"winmm.lib")//导入声音头文件库

volatile bool close_alert=false;

//单独线程用于连续报警
UINT MyThreadProc(LPVOID pParam ) //报警线程
{
	while(!close_alert)
	{
		PlaySound("warn.wav",NULL,SND_SYNC|SND_FILENAME);
		Sleep(1000);
	}

	return 0;   // thread completed successfully
}

//发送短信 调用tui3接口
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
				
				alarming_item = item;
				
				std::string newinfo = 
				"	在网站"+host+"发现新帖子:\n"
				"	----------------------------------------------\n"
				"	标题: "+item.title
				+"\n	链接: "+this_url
				+"\n	作者: "+item.author
				+"\n	发布时间: "+item.timestr;
				
				std::cout<<newinfo<<"\n";

				log_to_file("monitor.log", newinfo);

				if(enable_sms) start_send_sms();

				if(enable_sound) start_sound_alarm();
				
				find_keyword = true;
				addto_alarm_history(this_url);

				break;
			}
		}
	}

	return find_keyword;
}

void bbs_monitor::start_send_sms()
{
	std::string this_url = "http://"+host+'/'+ alarming_item.url;
	
	std::string smsinfo1 = 
				"[监测到新帖]:" + alarming_item.title
				+" 发布时间:"+ alarming_item.timestr,

				smsinfo2 = "链接地址: " + this_url;

	std::cout<<"	正在发送短信...\n";

	BOOST_FOREACH(const std::string& phone, phone_numbers)
	{
		send_short_message(smsinfo1, phone);
		send_short_message(smsinfo2, phone);
	}

	std::cout<<"	已向 "<<phone_numbers.size()<<" 人发送短信！\n\n";
	log_to_file("monitor.log", "	短信已发送!");

}

void bbs_monitor::start_sound_alarm()
{
	close_alert = false;

	std::cout<<"	开启声音报警(请按任意键关闭)...";
	log_to_file("monitor.log", "	开启声音报警...");
	
	AfxBeginThread(MyThreadProc,NULL);

	if(_getch() )
	{
		close_alert = true;
		std::cout<<"\n	用户关闭本次声音报警...\n";
		log_to_file("monitor.log", "	用户关闭声音报警...");
	}

}
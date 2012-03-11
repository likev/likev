#pragma once

#include <afxinet.h>

#include <string>
#include <vector>
#include <set>

#include <boost/foreach.hpp>
#include <boost/regex.hpp>

#include "process-html.h"
#include "download-webpage.h"
#include "string-trans.h"

#include "SimpleIni.h"

bool log_to_file(const std::string &filename, const std::string &information);

std::vector<std::string>& 
	get_pat_list(std::vector<std::string>& result, std::string& content, boost::regex pat);

class bbs_monitor
{
	std::string host, path, postdata;
	boost::regex pat_itembody, pat_item;

	std::vector<item_describe> items;

	item_describe alarming_item;

	std::vector<std::string> keywords, phone_numbers;
	std::set<std::string> alarm_history;

public:

	bbs_monitor(){};

	bbs_monitor(std::string host, std::string path, std::string postdata="", 
				std::string pat_itembody_str="", std::string pat_item_str="")
	{
		this->host = host;
		this->path = path;
		this->postdata = postdata;

		if(!pat_itembody_str.size())
		{
			pat_itembody_str = "<tbody id=\"threadlist\">.*?</tbody>";
		}
		if(!pat_item_str.size())
		{
			pat_item_str =
				"<tr class=\"tr3.*?"
					"<td.*?"
					"<td.*?"
						"<a href=\"(\\S+)\" name=\"readlink\" .*?>([^><]+)<.*?"
					"</td>\\s*?"
					"<td.*?"
					"<td.*?"
					"<td.*?"
						"<a.*?>(.+?)</a><p><a [^>]*? title=\"(.+?)\".*?"
					"</td>\\s*?"
				"</tr>";
			
		}

		this->pat_itembody = boost::regex(pat_itembody_str);
		this->pat_item = boost::regex(pat_item_str);
	}

	bool monitor_once()
	{
		if(! check_connect()) return false;

		std::cout<<"正在下载网页"<<host<<"...\n\n";
		std::string htmlstr = DownHttpPage(host,path,postdata);

		if(! htmlstr.size() )
		{
			std::string tempinfo = "网页"+host+'/'+path+"下载失败!";
			log_to_file("monitor.log", tempinfo);
			std::cout<<tempinfo<<std::endl;

			return false;
		}
		std::cout<<"网页"<<host<<"成功下载，正在分析内容...\n\n";
	
		std::vector<std::string> trlist;
		get_tr_list(trlist, htmlstr, pat_itembody);
		
		get_all_title(items, trlist,  pat_item);

		//out_items();

		load_keyword();
		load_phone_numbers();
		load_alarm_history();
		
		if(! check_items() )
		{
			std::cout<<"没有在网页"<<host<<"发现关键词\n";
		}
		std::cout<<"\n\n";

		return true;
	}

	const std::vector<item_describe> & get_items()const
	{
		return items;
	}

private:

	bool check_items();

	void start_send_sms();
	void start_sound_alarm();

	void out_items()
	{
		BOOST_FOREACH(item_describe& item, items)
		{
			std::cout<<"\ntitle: "<<item.title
				<<"\nurl: "<<item.url
				<<"\ntime: "<<item.timestr
				<<"\nauthor: "<<item.author<<std::endl;
		}
	}

	template <typename T>
	void out_vector(const std::vector<T> &vec)
	{
		BOOST_FOREACH(const T& item, vec)
		{
			std::cout<<item<<" ";
		}
	}

	bool check_connect()
	{
		DWORD connect_flag;
		bool is_connect_available = InternetGetConnectedState(&connect_flag,0);

		if(! is_connect_available)
		{
			std::cout<<"网络连接不可用！\n\n";
			log_to_file("monitor.log", "connect not available..");
			return false;
		}

		return true;
	}

	bool load_keyword()
	{
		CSimpleIniA ini;
		ini.LoadFile("config.ini");

		std::string keywords_str = ini.GetValue("monitor","keywords");

		get_pat_list(keywords, keywords_str, boost::regex("[\\t \\|]*([^\\t \\|]+)[\\t \\|]*"));

		//out_vector(keywords);

		return true;
	}

	bool load_phone_numbers()
	{
		CSimpleIniA ini;
		ini.LoadFile("config.ini");

		std::string phone_str = ini.GetValue("sms","phone-numbers");
		get_pat_list(phone_numbers, phone_str, boost::regex("[#\\s\\|]*(\\d{11})[#\\s\\|]*"));

		//out_vector(phone_numbers);
		
		return true;
	}

	bool load_alarm_history()
	{
		std::string content;
		
		if(! filetostr("alarm-history", content) )
		{
			log_to_file("monitor.log", "load alarm-history error!");
			return false;
		}

		std::vector<std::string> lines;

		str_split(content,"\n", lines);

		alarm_history.clear();

		alarm_history.insert(lines.begin(),lines.end() );

		return true;
	}

	bool addto_alarm_history(const std::string& url)
	{
		std::ofstream fout("alarm-history",std::ios_base::out|std::ios_base::app);

		if(!fout.is_open())
		{
			log_to_file("monitor.log", "open alarm-history error!");
			return false;
		}

		fout<<url<<std::endl;

		return true;
	}

};
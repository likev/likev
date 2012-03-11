
#include <iostream>

#include "bbs-monitor.h"

int main()
{
	bbs_monitor dahe("bbs.dahe.cn","thread-htm-fid-450.htm"),
		shangdu("bbs.ly.shangdu.com","thread-htm-fid-29.html","type=0&search=1000&special=0&orderway=postdate&asc=DESC");

	std::string appinfo = 
		"BBS网站 内容关键词监测程序(1.0)\n"
		"作者:许方璐 2012年3月10日\n"
		"修改配置方法: 请编辑程序所在目录下的config.ini文件\n\n";
	
	
	std::cout<<appinfo;
	
	while(true)
	{
		std::cout<<"开始监测网页...\n\n";
		dahe.monitor_once();
		shangdu.monitor_once();

		CSimpleIniA ini;
		ini.LoadFile("config.ini");

		long interval = ini.GetLongValue("monitor","interval",10);

		std::cout<<"本次监测结束, "<<interval<<"分钟后将再次监测...\n"
			"----------------------------------------------\n\n";
		
		std::cout<<appinfo;

		Sleep(interval*1000*60);
	}

	return 0;
}
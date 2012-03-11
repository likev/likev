
#include <iostream>

#include "bbs-monitor.h"

int main()
{
	bbs_monitor dahe("bbs.dahe.cn","thread-htm-fid-450.htm"),
		shangdu("bbs.ly.shangdu.com","thread-htm-fid-29.html","type=0&search=1000&special=0&orderway=postdate&asc=DESC");

	std::string appinfo = 
		"BBS��վ ���ݹؼ��ʼ�����(1.0)\n"
		"����:��� 2012��3��10��\n"
		"�޸����÷���: ��༭��������Ŀ¼�µ�config.ini�ļ�\n\n";
	
	
	std::cout<<appinfo;
	
	while(true)
	{
		std::cout<<"��ʼ�����ҳ...\n\n";
		dahe.monitor_once();
		shangdu.monitor_once();

		CSimpleIniA ini;
		ini.LoadFile("config.ini");

		long interval = ini.GetLongValue("monitor","interval",10);

		std::cout<<"���μ�����, "<<interval<<"���Ӻ��ٴμ��...\n"
			"----------------------------------------------\n\n";
		
		std::cout<<appinfo;

		Sleep(interval*1000*60);
	}

	return 0;
}
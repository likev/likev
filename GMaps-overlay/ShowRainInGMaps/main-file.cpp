/*
  下载实时GPRS雨量
  最后修改: 2010.7.18 11:03
*/

#include "comn.h"
#include "gprs-rain-line.h"


int main()
{
	using namespace std;

	string server1 = "172.18.152.239", server2 = "www.hnaws.com", server,
	url = "./HNAWS/RTinfo/rtdatadisp.asp?CityFlag=HNLY&CityName=%C2%E5%D1%F4%CA%D0&Top_X=110.9882&Top_Y=35.1468&Bot_X=113.0480&Bot_Y=33.5470";
	string url2 = "simpleversion/infodisplay.asp?Cityflag=HNLY&InfoT=historical&DispT=intable&StartT=2010-7-16%2020:00&EndT=2010-7-17%2020:00";
	
	int i=0;
	cout<<"选择联网模式( 1-内网  2-外网 ): ";
	cin>>i;

	if(i==1) server=server1;
	else server=server2;
		
	GprsRainRecord test;
	
	while(1)
	{
		test.get_web_content(server,url);
		
		test.update_js_file("script/rain-datas.js");

		CTime cur= CTime::GetCurrentTime();
		cout<<"本次处理时间:"<<cur.Format("%H:%M:%S")<<endl;
		cout<<"--------------------------------------------------\n\n";
		Sleep(1*60*1000);
	}

}
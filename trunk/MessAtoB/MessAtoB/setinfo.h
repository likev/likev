//站点信息以及天气状况编码

#include "stdafx.h"
#include <map>

#ifndef SETINFO_WETH
#define SETINFO_WETH

using std::map;using std::string;using std::vector;

class SetInfo{

public:
	//站点信息
	map<int,string> stname;

	//天气状况
	map<string,string> weth;

	//风向风速
	map<string,string> windx,windv;

	SetInfo(void)
	{
		stname[57073] = "洛阳市区"; stname[57099] = "吉利";stname[57071] = "孟津";
		stname[57076] = "偃师";       stname[57074] = "伊川";stname[57078] = "汝阳";
		stname[57070] = "新安";       stname[57065] = "宜阳";stname[57066] = "洛宁";
		stname[57162] = "嵩县";       stname[57077] = "栾川";


		weth["0.0"] = "晴天"; 
		weth["1.0"] = "多云"; 
		weth["2.0"] = "阴天"; 
		weth["3.0"] = "阵雨"; 
		weth["4.0"] = "雷阵雨"; 
		weth["5.0"] = "雷雨冰雹"; 
		weth["6.0"] = "雨夹雪"; 
		weth["7.0"] = "小雨"; 
		weth["8.0"] = "中雨"; 
		weth["9.0"] = "大雨"; 
		weth["10.0"] = "暴雨"; 
		weth["11.0"] = "大暴雨"; 
		weth["12.0"] = "特大暴雨"; 
		weth["13.0"] = "阵雪"; 
		weth["14.0"] = "小雪"; 
		weth["15.0"] = "中雪"; 
		weth["16.0"] = "大雪"; 
		weth["17.0"] = "暴雪"; 
		weth["18.0"] = "雾"; 
		weth["19.0"] = "冻雨"; 
		weth["20.0"] = "沙尘暴"; 
		weth["29.0"] = "浮尘"; 
		weth["30.0"] = "扬沙";  



		windx["0.0"] = "静风";
		windx["1.0"] = "东北";
		windx["2.0"] = "东";
		windx["3.0"] = "东南";
		windx["4.0"] = "南";
		windx["5.0"] = "西南";
		windx["6.0"] = "西";
		windx["7.0"] = "西北";
		windx["8.0"] = "北";
		windx["9.0"] = "旋转风";

		windv["0.0"] = "小于等于3级";
		windv["1.0"] = "3-4级";
		windv["2.0"] = "4-5级";
		windv["3.0"] = "5-6级";
		windv["4.0"] = "6-7级";
		windv["5.0"] = "7-8级";
		windv["6.0"] = "8-9级";
		windv["7.0"] = "9-10级";
		windv["8.0"] = "10-11级";
		windv["9.0"] = "11-12级";
	}
};

class StnName{
public:
	//站点信息
	vector<string> nm;

	StnName()
	{
		nm.assign(11,"");
		nm[0] = "洛阳市区"; nm[1] = "吉利";nm[2] = "孟津";
		nm[3] = "偃师";       nm[4] = "伊川";nm[5] = "汝阳";
		nm[6] = "新安";       nm[7] = "宜阳";nm[8] = "洛宁";
		nm[9] = "嵩县";       nm[10] = "栾川";
	}
};


#endif
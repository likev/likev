//本程序中用到的函数和类

#include "comn.h"

//单独线程用于连续报警
UINT MyThreadProc(LPVOID pParam );

//发送短信 调用飞信接口
bool send_short_message(std::string message, std::string sendto);

//下载网页
bool DownloadHttpPage(LPCTSTR pszServerName, LPCTSTR pszURL, LPCTSTR pszLocalFile);

//灾情信息类
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

		info_id = get_speicl("灾情直报信息编号");
		province= get_speicl("省份");
		city    = get_speicl("市（地，州）");
		county  = get_speicl("县（区，市）");
		station_number=get_speicl("站号");
		conect_telephone=get_speicl("联系电话");
		type=get_speicl("灾情类别");
		location=get_speicl("灾害发生地名称");
		describe=get_speicl("灾害影响描述");
		economic_loss=get_speicl("直接经济损失");
		dead_number=get_speicl("死亡人数");
		begin_time=get_speicl("开始时间");
		end_time=get_speicl("结束时间");
	}

	std::string to_sms()
	{
		//[灾情]2010年4月26日12时 宜阳县[电话68882126] 大风 经济损失100万元 死亡0人
		// 经调查刮到树1000余棵,房屋倒塌10间...

		std::string sms;
		size_t pos;

		pos = begin_time.find("时");
		sms += begin_time.substr(0,pos)+"时";

		sms += " "+location;
		sms += "[电话"+conect_telephone.substr(5)+"] ";
		sms += type;
		sms += " 经济损失"+economic_loss;
		sms += " 死亡"+dead_number;
		sms += " "+describe.substr(0,120)+"...";

		return sms;
	}

	std::string to_text()
	{
		std::string sms;

		sms += begin_time;

		sms += "\r\n"+location;
		sms += "[电话"+conect_telephone+"]\r\n";
		sms += type;
		sms += "\r\n经济损失: "+economic_loss;
		sms += "\r\n死亡: "+dead_number;
		sms += "\r\n灾情描述: "+describe;

		return sms;
	}
};

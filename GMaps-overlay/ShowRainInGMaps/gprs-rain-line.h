/*处理gprs实时雨量或查询雨量表格的一行
  最后修改 2010 7 15 1:00
*/
#ifndef GPRS_RAIN_LINE
#define GPRS_RAIN_LINE

#include "comn.h"
#include "string-trans.h"
#include "http-deal.h"

class GprsRainLine
{
	std::string station_id, station_name, gprs_id, last_time;
	double value;

public:
	GprsRainLine()
	{
		value = 0;
	}
	GprsRainLine(const std::string &line_str,bool realtime)
	{
		deal_line_str(line_str,realtime);
	}

	std::string get_station_id()const
	{
		return station_id;
	}
	std::string get_gprs_id()const
	{
		return gprs_id;
	}
	std::string get_station_name()const
	{
		return station_name;
	}
	std::string get_last_time()const
	{
		return last_time;
	}
	double get_value()const
	{
		return value;
	}
	
	//实时或历史查询
	void deal_line_str(const std::string &line_str,bool realtime)
	{
		size_t pos1=0;
		pos1 = line_str.find("<td",pos1);
		station_id = get_tag_content(line_str.substr(pos1), "td");

		pos1 = line_str.find("<td",++pos1);
		station_name = get_tag_content(line_str.substr(pos1), "td");

		pos1 = line_str.find("<td",++pos1);
		gprs_id = get_tag_content(line_str.substr(pos1), "td");

		if(realtime)
		{
			pos1 = line_str.find("<td",++pos1);
			last_time = get_tag_content(line_str.substr(pos1), "td");
		}

		pos1 = line_str.find("<td",++pos1);
		std::string val_str = get_tag_content(line_str.substr(pos1), "td");

		if(  (val_str.find("-")!=val_str.npos)
		   ||(val_str.find("&nbsp;")!=val_str.npos) )
		{
			value = 0;
		}
		else
		{
			value = string_to<double>(val_str);
		}
	}

};

class GprsRainRecord
{
private:
	std::vector<GprsRainLine> records;
	std::string webserver,weburl,last_time,file_name, file_content;
	bool is_download, isrealtime;

private:
	//处理每一行雨量数据
	void deal_record()
	{
		size_t pos1, pos2;

		pos1 = file_content.find("class='lasttime'>");
		pos1 = file_content.find("资料时间",pos1)+10;
		pos2 = file_content.find("&nbsp",pos1);

		last_time = file_content.substr(pos1,pos2-pos1);

		pos1 = file_content.find("<table width='100%' class='tInfo'>");

		std::string table_content = get_tag_content(file_content.substr(pos1),"table");

		pos1 = table_content.find("</tr>"); //清除表格头
		//std::cout<<table_content;

		records.clear();
		pos1 = table_content.find("<tr", ++pos1);
		while(pos1 != table_content.npos)
		{
			records.push_back(GprsRainLine(table_content.substr(pos1),isrealtime) );
			pos1 = table_content.find("<tr", ++pos1);
		}

	}
public:
	GprsRainRecord()
	{
	}

	//下载实时雨量数据
	void get_web_content(std::string server,std::string url)
	{
		webserver=server;
		weburl = url;
		file_name = "webdata";

		is_download = DownloadHttpPage(server.c_str(),url.c_str(),file_name.c_str());

		if(is_download)
		{
			filetostr(file_name,file_content);
		}
	}


	//更新js文件
	void update_js_file(std::string file,bool realtime=true)
	{
		isrealtime = realtime;
		if(is_download) deal_record();


		std::string js_content, update_content;
		filetostr(file,js_content);

		size_t pos1, pos2;
		pos1 = js_content.find("//begin");
		pos2 = js_content.find("//end");

		js_content.erase(pos1,pos2-pos1);

		update_content = "//begin\n";

		update_content += "var recordTime = '"+last_time+"';\n\n";
		update_content += "var rainDatas = {";

		for(std::vector<GprsRainLine>::iterator it=records.begin();
			it != records.end(); it++)
		{
			if(it->get_value()>0)
			{
				update_content += "\n  "+it->get_station_id()+":"+to_string(it->get_value())+",";
			}
		}

		update_content += "\n}\n";

		pos2 = update_content.rfind(",");
		if(pos2 != update_content.npos)
		{
			update_content.erase(pos2,1);
		}

		js_content.insert(pos1,update_content);

		strtofile(file,js_content);

	}

};
#endif  //GPRS_RAIN_LINE
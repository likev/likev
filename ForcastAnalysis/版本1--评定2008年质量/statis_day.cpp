#include "comn.h"
#include "statis_result.h"
#include "deal-database.h"
#include "analyse_record.h"


bool stat_day(std::string worker, CTime when, 
									  std::map<int, stat_result> & statis_result)
{
	using namespace std;

	string filename = get_filename(worker,when);
	if(filename.size()<1)
		return false;

	string filepath = "person-forcast/"+filename;

	ifstream fin(filepath.c_str());
	if(!fin.is_open())
	{
		cout<<"打开文件 "<<filename<<"失败！"<<endl;
		return false;
	}

	city_fst record_per_day;
	
	string sline;
	while(getline(fin,sline) )
	{
		if(sline.size()<30) continue;
		record_per_day.time = when;
		read_city_fst(sline,record_per_day);
		analyse_record(record_per_day, statis_result);
	}

	return true;
}

bool analyse_record(const city_fst &record_per_day, 
					std::map<int, stat_result> & statis_result )
{
	using namespace std;

	extern string person_result_details_filename;

	ofstream fout(person_result_details_filename.c_str(),ios_base::out|ios_base::app);
	if(!fout.is_open())
	{
		cout<<"打开文件 "<<person_result_details_filename<<" 失败！"<<endl;
	}

	CTime when = record_per_day.time;	
	string time_str = when.Format("%Y-%m-%d日").GetBuffer();

	int stn_num = record_per_day.station_num;

	if(!statis_result.count(stn_num))
		return false;

	statis_result[stn_num].avail_days += 1;

	analyse_rain(record_per_day, statis_result, fout);

	analyse_min_temph(record_per_day, statis_result, fout);

	analyse_max_temph(record_per_day, statis_result, fout);
	
	fout.close();
	return true;
}

std::string get_filename(std::string worker, CTime when)
{
	CString search_name;
	search_name ="person-forcast/" + when.Format("%Y%m%d") + "1*." + worker.c_str();

	CFileFind findf;

	bool isfind = findf.FindFile(search_name);

	std::string filename;
	if(isfind)
	{
		findf.FindNextFileA();
		filename = findf.GetFileName().GetBuffer();
	}

	return filename;
}

//从rain-temph.mdb数据库中获取降水或温度值
bool get_rain_temph_val(int i, int stn, CTime tm, double & val)
{
	using namespace std;
	std::string dbname="files/rain-temph.mdb", colname, sql_statement;

	std::string time_str = tm.Format("#%Y-%m-%d#").GetBuffer();

	std::ostringstream sout;
	sout<<'v'<<stn;
	colname = sout.str();

	switch(i)
	{
	case 1:
		time_str = tm.Format("#%Y-%m-%d %H:00:00#").GetBuffer();
		sql_statement = "SELECT "+colname+" FROM rain_last12hour WHERE date = " + time_str;
		break;
	case 2:
		sql_statement = "SELECT "+colname+" FROM min_temph WHERE date = " + time_str;
		break;
	case 3:
		sql_statement = "SELECT "+colname+" FROM max_temph WHERE date = " + time_str;
		break;
	default:
		break;
	}

	return read_from_db(dbname.c_str(),sql_statement.c_str(),val);
}

bool analyse_rain(const city_fst &record_per_day, 
					std::map<int, stat_result> & statis_result,
					std::ofstream &fout)
{
	using namespace std;

	CTime when = record_per_day.time;	
	string time_str = when.Format("%Y-%m-%d").GetBuffer();

	int stn_num = record_per_day.station_num;

		//处理降水预报
	for(int i=0; i!=record_per_day.israin.size(); ++i)
	{
		double rainval=0;
		if(get_rain_temph_val(1,stn_num,when+CTimeSpan(0,12*(i+1),0,0),rainval))
		{
			bool israinb = rainval > 0.01,
				 israin = ( israinb || beql(rainval,0.001) );//包含微量降水

			if(record_per_day.israin[i] || israinb)
			{
				statis_result[stn_num].rain_all[i] += 1;

				if(record_per_day.israin[i] && israin)
				{
					statis_result[stn_num].rain_right[i] += 1;
				}
				else if(israinb)
				{
					statis_result[stn_num].rain_miss[i] +=1;
					fout<<time_str<<' '<<stn_num<<' '<<12*(i+1)<<"小时降水 漏报"<<endl;
				}
				else
				{
					statis_result[stn_num].rain_empty[i] +=1;
					fout<<time_str<<' '<<stn_num<<' '<<12*(i+1)<<"小时降水 空报"<<endl;
				}
			}
			
		}
	}

	return true;
}

bool analyse_min_temph(const city_fst &record_per_day, 
					std::map<int, stat_result> & statis_result,
					std::ofstream &fout)
{
	using namespace std;

	CTime when = record_per_day.time;	
	string time_str = when.Format("%Y-%m-%d").GetBuffer();

	int stn_num = record_per_day.station_num;

	for(int i=0; i!=record_per_day.min_t.size(); ++i)
	{
		double min_temp=0;
		if(get_rain_temph_val(2,stn_num,when+CTimeSpan(0,24*(i+1),0,0),min_temp) )
		{	
			double f_min_t=record_per_day.min_t[i],
				   difference = min_temp-f_min_t, abs_diff = abs(difference);

			if( abs_diff <2 || beql(abs_diff,2.0))
			{
				statis_result[stn_num].min_t[i] += 1;
			}
			else if(difference > 0)
			{
				statis_result[stn_num].min_t_low[i] += 1;

				fout<<time_str<<' '<<stn_num<<' '<<24*(i+1)<<"最低温度 预报偏低： ";
				fout<<"预报值："<<f_min_t<<"   实际值："<<min_temp<<endl;
			}
			else
			{
				statis_result[stn_num].min_t_high[i] += 1;

				fout<<time_str<<' '<<stn_num<<' '<<24*(i+1)<<"最低温度 预报偏高： ";
				fout<<"预报值："<<f_min_t<<"   实际值："<<min_temp<<endl;
			}
		}
	}

	return true;
}

bool analyse_max_temph(const city_fst &record_per_day, 
					std::map<int, stat_result> & statis_result,
					std::ofstream &fout)
{
	using namespace std;

	CTime when = record_per_day.time;	
	string time_str = when.Format("%Y-%m-%d").GetBuffer();

	int stn_num = record_per_day.station_num;

	for(int i=0; i!=record_per_day.max_t.size(); ++i)
	{
		double max_temp=0;
		if(get_rain_temph_val(3,stn_num,when+CTimeSpan(0,24*(i+1),0,0),max_temp) )
		{
			double f_max_t = record_per_day.max_t[i],
				   difference = max_temp-f_max_t, abs_diff = abs(difference);

			if( abs_diff <2 || beql(abs_diff,2.0) )
			{
				statis_result[stn_num].max_t[i] += 1;
			}
			else if(difference > 0)
			{
				statis_result[stn_num].max_t_low[i] += 1;

				fout<<time_str<<' '<<stn_num<<' '<<24*(i+1)<<"最高温度 预报偏低： ";
				fout<<"预报值："<<f_max_t<<"   实际值："<<max_temp<<endl;
			}
			else
			{
				statis_result[stn_num].max_t_high[i] += 1;

				fout<<time_str<<' '<<stn_num<<' '<<24*(i+1)<<"最高温度 预报偏高： ";
				fout<<"预报值："<<f_max_t<<"   实际值："<<max_temp<<endl;
			}
		}
	}

	return true;
}
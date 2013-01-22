#include "Poco/Util/XMLConfiguration.h"
#include "Poco/RegularExpression.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/StreamCopier.h"
#include "Poco/Thread.h"
#include "Poco/File.h"
#include "Poco/Exception.h"
#include "Poco/Glob.h"
#include "Poco/DateTime.h"
#include "Poco/TimeSpan.h"
#include <Poco/DateTimeFormatter.h>


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>



//取结构的一部分
struct Diamond4Head
{
	double lon_span, lat_span;
	double min_lon, max_lon, min_lat, max_lat;
	int lon_num, lat_num;
	int overlay;

	Diamond4Head()
	{
		lon_span = lat_span = 0;
		min_lon = max_lon = min_lat = max_lat = lon_num = lat_num = 0;
		overlay = 0;
	}

	bool operator == (const Diamond4Head& right)const
	{
		if(    min_lon == right.min_lon
			&& max_lon == right.max_lon
			&& min_lat == right.min_lat
			&& max_lat == right.max_lat
			&& lon_num == right.lon_num
			&& lat_num == right.lat_num
			&& overlay == right.overlay) return true;
		else return false;
	}
	bool operator != (const Diamond4Head& right)const
	{
		if(right == *this) return false;
		else return true;
	}
};

bool read_diamond4(const std::string &path, Diamond4Head & head, std::vector<double> &vec)
{
	std::ifstream fin(path);
	if( !fin.is_open() ) return false;

	std::string temp;
	
	fin>>temp>>temp>>temp>>temp
		>>temp>>temp>>temp>>temp;

	fin>>head.overlay>>head.lon_span>>head.lat_span;

	fin>>head.min_lon>>head.max_lon>>head.min_lat>>head.max_lat;
	fin>>head.lon_num>>head.lat_num;

	fin>>temp>>temp>>temp>>temp>>temp;

	double val;
	vec.clear();

	while(fin>>val)
	{
		vec.push_back(val);
	}

	if(vec.size() != head.lon_num * head.lat_num ) return false;

	return true;
}

double op_accretion_index (double T, double rh)
{ 
	if(T>0 || T<-14) return 0;
	else return 2 * ( rh-50 ) * ( T * (T+14)/-49 ); 
}

int op_accretion_VV (double I, double w)
{
	int result = 0;

	if(w <= -0.2 )
	{
		if(I >=0 && I <4) result = 1;
		if(I >=4 && I <7) result = 2;
		if(I >= 7) result = 3;
	}
	return result; 
}

class T639IceAccretion{

public:
	T639IceAccretion()
	{
		tDir = "W:/T639/T_4";
		rhDir = "W:/T639/RH_4";
		omegaDir = "W:/T639/OMEGA_4";

		beginDay = -1;
		beginHour = 8;

		Poco::LocalDateTime current;
		
		current -= Poco::Timespan(0, current.hour(), 0, 0, 0);
		begintime = current + Poco::Timespan(beginDay, beginHour, 0, 0, 0);
	}

	//每一层 ——> 每一个时次 ——> 温度、湿度、垂直速度
	void calc_all_layers()
	{
		std::vector<std::string>  layers;
		get_layers(layers);

		std::vector<std::string>::const_iterator it = layers.begin();

		for(; it != layers.end(); it++)
		{
			calc_layer( *it );
		}
	}

	void generate_head(const std::string& type, std::string& headstr)
	{
		int period;

		std::istringstream ssin(curPeriod);
		ssin>>period;

		Poco::LocalDateTime forcastTime = begintime + Poco::Timespan(period*Poco::Timespan::HOURS);
		
		std::string beginstr = Poco::DateTimeFormatter::format(begintime, "%y%m%d%H"),
			beginstr2 = Poco::DateTimeFormatter::format(begintime, "%y %m %d %H"),
			forcastStr = Poco::DateTimeFormatter::format(forcastTime, "%m月%d日%H时");
		headstr = "diamond 4 "+beginstr+"_"+forcastStr+"T639_";

		std::ostringstream sout1, sout2;

		sout1<<curHead.overlay<<"hPa";
		sout2<<beginstr2<<' '<<period<<' '<<curHead.overlay<<' '<<curHead.lon_span<<' '<<curHead.lat_span;
		sout2<<' '<<curHead.min_lon<<' '<<curHead.max_lon<<' '<<curHead.min_lat<<' '<<curHead.max_lat;
		sout2<<' '<<curHead.lon_num<<' '<<curHead.lat_num;
		if(type == "II")
		{
			headstr += sout1.str() + "积冰指数预报 " + sout2.str() + " 10 0.00 100.00 2 50.00";
		}
		else if(type == "VV")
		{
			headstr += sout1.str() + "积冰程度预报 " + sout2.str() + " 1 0.00 3.00 2 1.00";
		}
	}

	void generate_file(const std::vector<double>& vec, const std::string& type, const std::string& layer, const std::string &filename)
	{
		Poco::File("out/"+type+'/'+layer).createDirectories();
		std::ofstream fout("out/" + type+'/'+layer+ '/'+ filename);

		std::string headstr;
		generate_head(type, headstr);

		fout<<headstr;

		std::vector<double>::size_type it = 0;

		for(; it != vec.size(); it++)
		{
			if(! (it%curHead.lon_num) ) fout<<std::endl;
			fout<<vec[it]<<' ';
		}
		fout.close();
	}

	void calc_file(const std::string& layer, const std::string& filename)
	{
		Diamond4Head headT, headRh, headW;
		std::vector<double> vecT, vecRh, vecI, vecW, vecV;
		//"W:/T639/T_4/600/13012002.000"
		bool validT = read_diamond4(tDir+'/'+layer+'/'+ filename, headT, vecT),
			validRh = read_diamond4(rhDir+'/'+layer+'/'+ filename, headRh, vecRh),
			validW = read_diamond4(omegaDir+'/'+layer+'/'+ filename , headW, vecW);

		if( validT && validRh && headT == headRh )
		{//可以计算指数
			curHead = headT;

			vecI.resize(vecT.size() );
			std::transform(vecT.begin(), vecT.end(), vecRh.begin(), vecI.begin(), op_accretion_index );

			generate_file(vecI,"II", layer, filename );

			if( validW && headT == headW )
			{//计算预报
				vecV.resize(vecT.size() );
				std::transform(vecI.begin(), vecI.end(), vecW.begin(), vecV.begin(), op_accretion_VV );

				generate_file(vecV,"VV", layer, filename );
			}
		}
		else
		{
			std::cout<<" read T or Rh false ";
		}
	}

	void calc_layer(const std::string& layer)
	{
		std::string daystr = Poco::DateTimeFormatter::format(begintime, "%y%m%d%H");//
		
		std::vector<std::string> periods;

		get_period(layer, daystr, periods);

		std::vector<std::string>::iterator it = periods.begin();

		for (; it != periods.end(); ++it)
		{
			curPeriod = *it;
			calc_file(layer, daystr + '.' + *it);
		}
	}

private:
	std::string tDir, rhDir, omegaDir;
	int beginDay, beginHour;

	Diamond4Head curHead;
	Poco::LocalDateTime begintime;

	std::string curPeriod;

private:
	void get_layers(std::vector<std::string> & layers)
	{
		
		Poco::DirectoryIterator pfile( tDir ), end;

		layers.clear();

		while (pfile != end)
		{
			if( pfile->isDirectory() )
			{
				layers.push_back( pfile.name() );

				std::cout << pfile.name() << std::ends;

			}

			pfile++;
		}
	}

	void get_period(const std::string& layer, const std::string& daystr, std::vector<std::string> & periods)
	{
		std::set<std::string> files;
		Poco::Glob::glob(tDir+'/'+layer+'/'+daystr+".*", files);

		std::cout<<tDir+'/'+layer+'/'+daystr+".*\n";

		std::set<std::string>::iterator it = files.begin();

		periods.clear();

		for (; it != files.end(); ++it)
		{
			Poco::Path path(*it);

			periods.push_back( path.getExtension() );

			std::cout << path.getExtension() << std::ends;
		}
	}
};


int main()
{
	/*
	*/
	T639IceAccretion t639;
	t639.calc_all_layers();

	return 0;
}
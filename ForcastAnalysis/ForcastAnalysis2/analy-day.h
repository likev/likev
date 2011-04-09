#include "comn.h"
#include "statis_result.h"

//根据数据库名称和查询语句从数据库中读取double值，未找到或出现错误则返回false。
bool read_from_db(const char *dbname,const char * sql_statement, double &val);

bool analyse_record(const city_fst &record_per_day, 
					std::map<int, stat_result> & statis_result );

bool analyse_rain(const city_fst &record_per_day, 
					std::map<int, stat_result> & statis_result,
					std::ofstream &fout);


bool analyse_min_temph(const city_fst &record_per_day, 
					std::map<int, stat_result> & statis_result,
					std::ofstream &fout);

bool analyse_max_temph(const city_fst &record_per_day, 
					std::map<int, stat_result> & statis_result,
					std::ofstream &fout);

std::string get_filename(CString floder, CTime when);

//从rain-temph.mdb数据库中获取降水或温度值
bool get_rain_temph_val(int i, int stn, CTime tm, double & val);

//输出统计结果
void person_result_out(std::map<int, stat_result> & statis, std::string &result);
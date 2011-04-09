#include "comn.h"
#include "statis_result.h"

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

std::string get_filename(std::string worker, CTime when);

//��rain-temph.mdb���ݿ��л�ȡ��ˮ���¶�ֵ
bool get_rain_temph_val(int i, int stn, CTime tm, double & val);
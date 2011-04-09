#include <comn.h>
#include "read_aws_from_mysql.h"
#include "map-useful.h"

template <typename T>
void out(const T &a)
{
	std::cout<<"\n\n------------------\n"<<a.size()<<std::endl;
	for(T::const_iterator it = a.begin();
		it != a.end(); it++)
	{
		std::cout<<it->first.Format("%Y-%m-%d %H:%M:%S  ")<<it->second<<std::endl;
	}
}



typedef std::map<CTime,double>::iterator map_iter_type;

std::pair<map_iter_type,map_iter_type> 
GetRainBeginEnd(map_iter_type itb, map_iter_type ite, int max_hour_span)
{
	map_iter_type begin= std::find_if(itb,ite,is_map_value_nzero<CTime,double>),end,
		begin_next = begin;

	if(begin == ite) return std::make_pair(ite,ite);

	do
	{
		end = std::find_if(begin_next,ite,is_map_value_zero<CTime,double>);
		if(end == ite) break;

		begin_next = std::find_if(end,ite,is_map_value_nzero<CTime,double>);
		if(begin_next == ite) break;
	}while((begin_next->first - end->first).GetTotalHours()<=max_hour_span);

	return std::make_pair(begin,end);
}
// ת��ΪСʱ��ˮ
//ɾ���м��0ֵ
void ToHourRain(std::map<CTime,double> & records)
{
	if(records.size() <3) return;

	bool del=false;
	for(std::map<CTime,double>::iterator it = ++records.begin();
		it != --records.end();it++)
	{
		std::map<CTime,double>::iterator p1 = it, p2=p1;
		p1--;  //������һλ��
		p2++;  //������һλ��

		if(!(p1->second || p2->second) && !it->second)
		{
			records.erase(it);
			it = p1; //��ָ��ָ��ɾ��Ԫ����һλ��
		}
	}
}
// ת��Ϊ�ۼƽ�ˮֵ
void ToAccumulatedRain(std::map<CTime,double> & records)
{
	ToHourRain(records);

	using std::map;using std::pair;

	//�洢ÿ�ν�ˮ���ۼƽ�ˮ��
	map<CTime,double> result;

	//�ϴν�ˮ������ʱ��
	map_iter_type lastend;

	//��ˮ����ʼĩ
	std::pair<map_iter_type,map_iter_type> rainproc;

	lastend = records.begin();

	while(lastend != records.end() )
	{
		//���ν�ˮ
		rainproc = GetRainBeginEnd(lastend, records.end(), 12);

		map<CTime,double> thisresult;
		map_partial_sum(lastend, rainproc.second, thisresult);

		out(thisresult);

		result.insert(thisresult.begin(),thisresult.end());

		lastend = rainproc.second;

	}
	records = result;
	

}




void test();

void format_time(CTime time)
{
	using namespace std;
	cout<<time.Format("%Y-%m-%d %H:%M:%S  ")<<endl;
}
int main()
{
	using namespace std;

	CTime t(2010,4,12,7,0,0);

	format_time(awssql::NearTime(t,8));
	format_time(awssql::NearTime(t,8,false));


	//test();
}

void test()
{
	std::map<double,double> m1,m2;
	
	for(int i=0;i<10;i++)
	{
		m1[i] = i;
	}

	map_partial_sum(m1.begin(),m1.end(),m2);
	

	//std::partial_sum(m1.begin(),m1.end(),m2.begin(),add_pair_value<const double,const double>);

}
#include "comn.h"
#include <numeric>

#include "city_forecast.h"
#include "statis_result.h"

std::string person_result_filename, person_result_details_filename;

void init_time_worker(CTime &stat_begin, CTime &stat_end, std::string &worker);

//���ͳ����Ϣ
void person_result_out(std::map<int, stat_result> & statis, std::string &result);

void main_deal()
{
	using namespace std;

	cout<<"��ʼ�����ݣ�\n\n";
	CTime stat_begin, stat_end;
	string worker = "400";

	init_time_worker(stat_begin, stat_end, worker);

	cout<<"\n��ʼ����� ���ڷ�������...\n\n";

	map<int, stat_result> statistics;

	ifstream fin("stations_numbers.txt");
	if(!fin.is_open())
	{
		cout<<"�Ҳ���վ�������ļ� stations_numbers.txt��"<<endl;
	}

	int stn_number=99999;
	while(fin>>stn_number)
	{
		statistics[stn_number] = stat_result();
	}
	fin.close();


	for(CTime t=stat_begin; t<=stat_end; t += CTimeSpan(1,0,0,0) )
	{
		//find certain people file

		stat_day(worker,t,statistics);

		cout<<"\r                                      \r"
			"�����: "<<((t-stat_begin).GetDays()+1)*100.0/((stat_end-stat_begin).GetDays()+1)<<" %";

	}

	string person_result;
	person_result_out(statistics, person_result);

	cout<<endl<<endl<<person_result;

	string yes_or_no;
	
	cout<<endl<<"��������ݷ���.  ����Ϊ�ļ�(Y/N)?";
	cin>>yes_or_no;

	if(yes_or_no!="n" && yes_or_no!="N")
	{
		ofstream fout(person_result_filename.c_str());
		if(!fout.is_open())
		{
			cout<<"�����ļ� "<<person_result_filename<<" ʧ�ܣ�"<<endl;
		}

		fout<<endl<<endl<<person_result<<endl;
		fout.close();

		cout<<"�ļ��ѱ���Ϊ "<<person_result_filename<<endl;
	}

	cout<<"\n�鿴��ϸ����(Y/N)?";
	cin>>yes_or_no;

	if(yes_or_no!="n" && yes_or_no!="N")
	{
		system(person_result_details_filename.c_str());
	}


}

void init_time_worker(CTime &stat_begin, CTime &stat_end, std::string &worker)
{
	using namespace std;

	ostringstream sout;

	int year,month,day;
	cout<<"���뿪ʼʱ��(�� 2008 7 1 )��";
	cin>>year>>month>>day;

	stat_begin = CTime(year,month,day,20,0,0);
	sout<<year<<'.'<<month<<'.'<<day<<"--";

	cout<<"�������ʱ��(�� 2008 7 31)��";
	cin>>year>>month>>day;

	stat_end = CTime(year,month,day,20,0,0);
	sout<<year<<'.'<<month<<'.'<<day<<"--";

	cout<<"����Ԥ��Ա����    (�� 402): ";
	while(cin>>worker)
	{
		if(worker>"401" && worker<"407")
			break;
	}

	sout<<worker;
	person_result_filename = person_result_details_filename = sout.str();
	person_result_filename += "--result.txt";
	person_result_details_filename +="--result--details.txt";

	//����ļ�����

	ofstream fout(person_result_details_filename.c_str());
	if(!fout.is_open())
	{
		cout<<"���ļ� "<<person_result_details_filename<<" ʧ�ܣ�"<<endl;
	}
	fout.close();
}


void person_result_out(std::map<int, stat_result> & statis, std::string &result)
{
	using namespace std;

	ostringstream sout;
	
	vector<int> stn, all, right, wrong1, wrong2, lastline;

	int i=0, width=10;

//---------------------------------------------------------------------------------------
	//------��ˮԤ��
	sout<<"��ˮԤ����\n\n";
		  
	sout<<"    վ��  �ܽ�ˮ����  ��ȷ����   �ձ�����  ©������  ��ȷ��(%)\n"
	      "-----------------------------------------------------------------\n";
	for(map<int, stat_result>::iterator it=statis.begin();it != statis.end(); ++it)
	{
		stn.push_back((*it).first);
		all.push_back(accumulate((*it).second.rain_all.begin(),(*it).second.rain_all.end(),0 ));
		right.push_back(accumulate((*it).second.rain_right.begin(),(*it).second.rain_right.end(),0 ) );
		wrong1.push_back(accumulate((*it).second.rain_empty.begin(),(*it).second.rain_empty.end(),0 ) );
		wrong2.push_back(accumulate((*it).second.rain_miss.begin(),(*it).second.rain_miss.end(),0 ) );

		sout<<setw(width)<<stn[i]<<setw(width)<<all[i]<<setw(width)<<right[i]
			<<setw(width)<<wrong1[i]<<setw(width)<<wrong2[i]<<setw(width)<<right[i]*100.0/all[i]<<endl;
		++i;
	}

	lastline.push_back(accumulate(all.begin(),all.end(),0 ) );
	lastline.push_back(accumulate(right.begin(),right.end(),0 ) );
	lastline.push_back(accumulate(wrong1.begin(),wrong1.end(),0) );
	lastline.push_back(accumulate(wrong2.begin(),wrong2.end(),0) );

	sout<<endl<<setw(width)<<"�ܼ� "<<setw(width)<<lastline[0]<<setw(width)<<lastline[1]<<setw(width)<<lastline[2]
	    <<setw(width)<<lastline[3]<<setw(width)<<lastline[1]*100.0/lastline[0]<<endl;

//-------------------------------------------------------------------------------------------------------
	stn.resize(0);
	all = right = wrong1 = wrong2 = lastline = stn;

	i = 0;

	//----����¶�Ԥ��
	sout<<"\n\n����¶ȣ�\n\n";
		  
	sout<<"    վ��  ��Ԥ������  ��ȷ����   ƫ�ߴ���  ƫ�ʹ���  ��ȷ��(%)\n"
	      "-----------------------------------------------------------------\n";
	
	for(map<int, stat_result>::iterator it=statis.begin();it != statis.end(); ++it)
	{
		stn.push_back((*it).first);
		all.push_back((*it).second.avail_days*2);
		right.push_back(accumulate((*it).second.max_t.begin(),(*it).second.max_t.end(),0 ) );
		wrong1.push_back(accumulate((*it).second.max_t_high.begin(),(*it).second.max_t_high.end(),0 ) );
		wrong2.push_back(accumulate((*it).second.max_t_low.begin(),(*it).second.max_t_low.end(),0 ) );

		sout<<setw(width)<<stn[i]<<setw(width)<<all[i]<<setw(width)<<right[i]
			<<setw(width)<<wrong1[i]<<setw(width)<<wrong2[i]<<setw(width)<<right[i]*100.0/all[i]<<endl;
		++i;
	}

	lastline.push_back(accumulate(all.begin(),all.end(),0 ) );
	lastline.push_back(accumulate(right.begin(),right.end(),0 ) );
	lastline.push_back(accumulate(wrong1.begin(),wrong1.end(),0) );
	lastline.push_back(accumulate(wrong2.begin(),wrong2.end(),0) );

	sout<<endl<<setw(width)<<"�ܼ� "<<setw(width)<<lastline[0]<<setw(width)<<lastline[1]<<setw(width)<<lastline[2]
	    <<setw(width)<<lastline[3]<<setw(width)<<lastline[1]*100.0/lastline[0]<<endl;

//-------------------------------------------------------------------------------------------
	stn.resize(0);
	all = right = wrong1 = wrong2 = lastline = stn;

	i = 0;

	//----����¶�Ԥ��
	sout<<"\n\n����¶ȣ�\n\n" ;
	sout<<"    վ��  ��Ԥ������  ��ȷ����   ƫ�ߴ���  ƫ�ʹ���  ��ȷ��(%)\n"
		  "-----------------------------------------------------------------\n";
	
	for(map<int, stat_result>::iterator it=statis.begin();it != statis.end(); ++it)
	{
		stn.push_back((*it).first);
		all.push_back((*it).second.avail_days*2);
		right.push_back(accumulate((*it).second.min_t.begin(),(*it).second.min_t.end(),0 ) );
		wrong1.push_back(accumulate((*it).second.min_t_high.begin(),(*it).second.min_t_high.end(),0 ) );
		wrong2.push_back(accumulate((*it).second.min_t_low.begin(),(*it).second.min_t_low.end(),0 ) );

		sout<<setw(width)<<stn[i]<<setw(width)<<all[i]<<setw(width)<<right[i]
			<<setw(width)<<wrong1[i]<<setw(width)<<wrong2[i]<<setw(width)<<right[i]*100.0/all[i]<<endl;
		++i;
	}

	lastline.push_back(accumulate(all.begin(),all.end(),0 ) );
	lastline.push_back(accumulate(right.begin(),right.end(),0 ) );
	lastline.push_back(accumulate(wrong1.begin(),wrong1.end(),0) );
	lastline.push_back(accumulate(wrong2.begin(),wrong2.end(),0) );

	sout<<endl<<setw(width)<<"�ܼ� "<<setw(width)<<lastline[0]<<setw(width)<<lastline[1]<<setw(width)<<lastline[2]
	    <<setw(width)<<lastline[3]<<setw(width)<<lastline[1]*100.0/lastline[0]<<endl;

	result = sout.str();

}
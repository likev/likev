
#include <numeric>
#include <afxdao.h>
#include "city_forecast.h"
#include "analy-day.h"


//ȡ��DAO���ݿ��������
#pragma warning( disable : 4995 )

//��ʵ���������ݿ�
bool insertDB(const char *dbname,const char * table, COleDateTime datet,std::vector<double> &vals)
{

	using namespace std;

	CDaoDatabase daoDb;

	COleVariant OleV1,OleV2 ;//���ں���ֵ�ֶ�


	daoDb.Open(dbname,0,0,";PWD=1234%hnyl@20070701%");                 //�����ݿ�
	CDaoRecordset Record(&daoDb) ;  //�����¼��

	CString Sql = "SELECT * FROM ";
	CString SqlW;
	SqlW.Format(" WHERE date= #%s# ",datet.Format("%Y-%m-%d") );

	Record.Open ( dbOpenDynaset, Sql+table+SqlW+"  ORDER BY date" ) ; //��ʼ����¼��

	if(!Record.IsOpen())
		return false;


	OleV1  = datet;

	bool isfind = (Record.GetRecordCount()>0);

	//cout<<Record.GetRecordCount()<<" "<<Record.GetAbsolutePosition();

	if(isfind)  //�ҵ����޸�
	{
		Record.Edit();
	}
	else  //û�ҵ����
	{
		Record.AddNew ();
	}

	Record.SetFieldValue(1,OleV1);

	for(int i=0;i<9;++i)
	{
		OleV2 = vals[i];
		Record.SetFieldValue(i+2,OleV2);
	}

	//
	//cout<<"\r                                                                  \r";
	//cout<<"����ɣ� "<< 100.0*(j*n+i+1)/(m*n)<<"%";

	//cout<<date<<"        "<<names[i]<<"       "<<vals[i][j]<<endl;
	Record.Update(); //��������


	daoDb.Close(); //�ر����ݿ�
	AfxDaoTerm(); //
	return true;
}



void readVal()
{

	using namespace std;

	string name="files/XQZL.csv_format.txt";
	//cout<<"Input the text name:";
	//cin>>name;
	ifstream fin(name.c_str());

	vector<double> vals(9,0);
	COleDateTime datet(2008,6,1,0,0,0);
	CString datestr; 

	string s,sline;

	getline(fin,s);

	while(getline(fin,sline))
	{
		istringstream ssin(sline);

		ssin>>s;

		while( s != datet.Format("%m/%d/%y").GetBuffer() )
		{
			datet += COleDateTimeSpan(1,0,0,0);
		}

		for(int i=0;i<9;++i)
		{
			ssin>>s;
		}

		for(int i=0;i<9;++i)
		{
			ssin>>vals[i];
		}

		insertDB("files/rain-temph.mdb","min_temph",datet,vals);

		datet += COleDateTimeSpan(1,0,0,0);
	}
	cout<<"���ݴ������"<<endl;
}


bool read_from_db(const char *dbname,const char * sql_statement, double &val)
{

	using namespace std;

	CDaoDatabase daoDb;

	COleVariant OleV1;

	daoDb.Open(dbname,0,0,";PWD=271828");                 //�����ݿ�
	CDaoRecordset Record(&daoDb);  //�����¼��

	Record.Open (dbOpenDynaset, sql_statement) ; //��ʼ����¼��

	if(!Record.IsOpen())
		return false;

	if(Record.GetRecordCount()<1)
		return false;

	Record.MoveFirst();

	Record.GetFieldValue(0,OleV1);

	val = OleV1.dblVal;

	daoDb.Close(); //�ر����ݿ�
	AfxDaoTerm(); //
	return true;
}


bool stat_day(std::string worker, CTime when, 
			  std::map<int, stat_result> & statis_result)
{
	using namespace std;

	string filename = get_filename(worker.c_str(),when);
	if(filename.size()<1)
		return false;

	string filepath = "person-forcast/"+filename;

	ifstream fin(filepath.c_str());
	if(!fin.is_open())
	{
		cout<<"���ļ� "<<filename<<"ʧ�ܣ�"<<endl;
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

	//extern 
	string person_result_details_filename="log.txt";

	ofstream fout(person_result_details_filename.c_str(),ios_base::out|ios_base::app);
	if(!fout.is_open())
	{
		cout<<"���ļ� "<<person_result_details_filename<<" ʧ�ܣ�"<<endl;
	}

	CTime when = record_per_day.time;	
	string time_str = when.Format("%Y-%m-%d��").GetBuffer();

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

//����ʱ���ȡ�ļ���
//���� �ж�16ʱ 4ʱ����
std::string get_filename(CString floder, CTime when)
{
	when -= CTimeSpan(0,8,0,0);
	CString search_name;
	search_name =floder+ 
		"\\Z_SEVP_C_BFLB_"+when.Format("%Y%m%d%H")+"*_P_RFFC-SPCC-*.TXT";

	CFileFind findf;

	BOOL isfind = findf.FindFile(search_name);

	CString filename;
	if(isfind)
	{
		findf.FindNextFileA();
		filename = findf.GetFilePath();
	}

	return filename.GetBuffer();
}

//��rain-temph.mdb���ݿ��л�ȡ��ˮ���¶�ֵ
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
		if(tm.GetHour() < 20)
		{
			tm -= CTimeSpan(1,0,0,0);
			time_str = tm.Format("#%Y-%m-%d#").GetBuffer();
		}
		sql_statement = "SELECT "+colname+" FROM max_temph WHERE date = " + time_str;
		break;
	default:
		break;
	}

	bool returnval;
	try
	{
		returnval=read_from_db(dbname.c_str(),sql_statement.c_str(),val);
	}
	catch(CDaoException *e)
	{
		//cout<<(e->m_pErrorInfo->m_strDescription).GetBuffer()<<endl;
		e->Delete();

		AfxDaoTerm(); //
		return false;
	}

	return returnval;
}

bool analyse_rain(const city_fst &record_per_day, 
				  std::map<int, stat_result> & statis_result,
				  std::ofstream &fout)
{
	using namespace std;

	CTime when = record_per_day.time;	
	string time_str = when.Format("%Y-%m-%d").GetBuffer();

	int stn_num = record_per_day.station_num;

	//����ˮԤ��
	for(int add_times=0; add_times!=record_per_day.israin.size(); ++add_times)
	{
		double rainval=0;
		if(get_rain_temph_val(1,stn_num,when+CTimeSpan(0,12*(add_times+1),0,0),rainval))
		{
			bool israinb = rainval > 0.01,
				israin = ( israinb || beql(rainval,0.001) );//����΢����ˮ

			if(record_per_day.israin[add_times] || israinb)
			{
				statis_result[stn_num].rain_all[add_times] += 1;

				if(record_per_day.israin[add_times] && israin)
				{
					statis_result[stn_num].rain_right[add_times] += 1;
				}
				else if(israinb)
				{
					statis_result[stn_num].rain_miss[add_times] +=1;
					fout<<time_str<<' '<<stn_num<<' '<<12*(add_times+1)<<"Сʱ��ˮ ©��"<<endl;
				}
				else
				{
					statis_result[stn_num].rain_empty[add_times] +=1;
					fout<<time_str<<' '<<stn_num<<' '<<12*(add_times+1)<<"Сʱ��ˮ �ձ�"<<endl;
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

	for(int add_days=0; add_days!=record_per_day.min_t.size(); ++add_days)
	{
		double min_temp=0;
		if(get_rain_temph_val(2,stn_num,when+CTimeSpan(0,24*(add_days+1),0,0),min_temp) )
		{	
			double f_min_t=record_per_day.min_t[add_days],
				difference = min_temp-f_min_t, abs_diff = abs(difference);

			if( abs_diff <2 || beql(abs_diff,2.0))
			{
				statis_result[stn_num].min_t[add_days] += 1;
			}
			else if(difference > 0)
			{
				statis_result[stn_num].min_t_low[add_days] += 1;

				fout<<time_str<<' '<<stn_num<<' '<<24*(add_days+1)<<"����¶� Ԥ��ƫ�ͣ� ";
				fout<<"Ԥ��ֵ��"<<f_min_t<<"   ʵ��ֵ��"<<min_temp<<endl;
			}
			else
			{
				statis_result[stn_num].min_t_high[add_days] += 1;

				fout<<time_str<<' '<<stn_num<<' '<<24*(add_days+1)<<"����¶� Ԥ��ƫ�ߣ� ";
				fout<<"Ԥ��ֵ��"<<f_min_t<<"   ʵ��ֵ��"<<min_temp<<endl;
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

	for(int add_days=0; add_days!=record_per_day.max_t.size(); ++add_days)
	{
		double max_temp=0;
		if(get_rain_temph_val(3,stn_num,when+CTimeSpan(0,24*(add_days+1),0,0),max_temp) )
		{
			double f_max_t = record_per_day.max_t[add_days],
				difference = max_temp-f_max_t, abs_diff = abs(difference);

			if( abs_diff <2 || beql(abs_diff,2.0) )
			{
				statis_result[stn_num].max_t[add_days] += 1;
			}
			else if(difference > 0)
			{
				statis_result[stn_num].max_t_low[add_days] += 1;

				fout<<time_str<<' '<<stn_num<<' '<<24*(add_days+1)<<"����¶� Ԥ��ƫ�ͣ� ";
				fout<<"Ԥ��ֵ��"<<f_max_t<<"   ʵ��ֵ��"<<max_temp<<endl;
			}
			else
			{
				statis_result[stn_num].max_t_high[add_days] += 1;

				fout<<time_str<<' '<<stn_num<<' '<<24*(add_days+1)<<"����¶� Ԥ��ƫ�ߣ� ";
				fout<<"Ԥ��ֵ��"<<f_max_t<<"   ʵ��ֵ��"<<max_temp<<endl;
			}
		}
	}

	return true;
}

//���ͳ�ƽ��
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
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <afxwin.h>         // MFC 核心和标准组件
#include <afxext.h>         // MFC 扩展
#include <afxdisp.h>        // MFC 自动化类
#include <afxdao.h>

using namespace std;
class point
{
public:
	int x,y;
};

void daoDB(const vector<vector<string> > &a)
{
	ifstream fin("5_10_08-08.csv");

	string s, date;
	CString strSQL;
	vector<double> d;

	CDaoDatabase daoDb;

	try
	{
	daoDb.Open("test.mdb");

	while(!fin.eof() && getline(fin,s) )
	{
		d.assign(9,-1);
		istringstream sinn(s);
		sinn>>date;
//		cout<<date<<endl<<endl;
		
		for(int i=0;i<9;i++)
		{sinn>>d[i]; }
		

		for(size_t j=0;j<d.size();j++)
		{
			for(size_t k=0;k<a[j].size();k++)
			{

		         
				 strSQL.Format("INSERT INTO mytable2 VALUES('%s','%s',%.3f)",a[j][k].c_str(),date.c_str(),d[j]);

		         daoDb.Execute(strSQL);
			}

		}

	}
	daoDb.Close();
	AfxDaoTerm();
	}
	catch(CDaoException)
	{

	}
}

void intiname(vector<string> &a)
{

	ifstream fin("xiangzhen.txt");

	string s;
	while(fin>>s)
	{
		a.push_back(s);
	}
	fin.close();

}

void zo()
{	ifstream fin("a.txt");
	ofstream fout("b.txt");

	int x,y;
	string s;
	while(fin>>x>>y)
	{
		getline(fin,s);
		fout<<int(x*0.8+0.5)<<"    "<<int(y*0.8+0.5)<<s<<endl;
	
	}
}


bool insertDB(const char *dbname,const char * table, vector<long> & val8,vector<long> & val)
{

	CDaoDatabase daoDb;

	COleDateTime Dfirst(2005,1,1,0,0,0),DT;//日期
	COleVariant OleV1,OleV2 ;//日期和数值字段


	try
	{
		daoDb.Open(dbname);                 //打开数据库
		CDaoRecordset Record(&daoDb) ;  //构造记录集

		CString Sql = "SELECT * FROM ";
		Record.Open ( dbOpenDynaset, Sql+table ) ; //初始化记录集
		
		if(!Record.IsOpen())
			return false;

		Record.MoveFirst();

		while(!Record.IsEOF())
		{
			Record.GetFieldValue (0, OleV1) ;
			Record.GetFieldValue (2, OleV2) ;

			DT = COleDateTime(OleV1);
			size_t i = DT.GetDayOfYear() - Dfirst.GetDayOfYear();

			if(DT.GetHour()==8 && !DT.GetMinute() ) //8时整
			{
				val8[i] = OleV2.lVal;
				//fout<<DT.Format("%Y%m%d      ").GetBuffer()<<OleV2.lVal<<endl;//今日20时			
			}
			else if(DT.GetHour()==20 && !DT.GetMinute() ) //20时整
			{
				val[i] = OleV2.lVal;
			}

			Record.MoveNext();//移向下一条记录
		}
	}
	catch(CDaoException *e)
	{
		cout<<(e->m_pErrorInfo->m_strDescription).GetBuffer()<<endl;
		e->Delete();

		AfxDaoTerm(); //
		return false;
	}

	daoDb.Close(); //关闭数据库
	AfxDaoTerm(); //
	return true;
}

void outvec(string filename,const vector<string> &tablename,const vector<COleDateTime> &d,
			     const vector<vector<long> > &a)
{
	filename += "vals20.txt";
	ofstream fout(filename.c_str());
//输入表头
	fout.width(10);
	fout<<"日期";
	for(size_t i=0;i<tablename.size();++i)
	{
		fout.width(10);
		fout<<tablename[i];
	}
	fout<<endl<<endl;

	//输出数据
	for(size_t j=0;j<a[0].size(); ++j)
	{
		fout.width(10);
		fout<<d[j].Format("%Y%m%d").GetBuffer();
		for(size_t i=0;i<a.size(); ++i)
		{
			fout.width(10);
			fout<<a[i][j];
		}
		fout<<endl;
	}
}

void dealval(void)
{
	string dbname="data_s2005.mdb";

	cout<<"输入数据库名称：";
	cin>>dbname;

	dbname += ".mdb";

	COleDateTime Dfirst(2005,1,1,0,0,0), Dend(2005,12,31,0,0,0);
	int days = (Dend - Dfirst).GetDays()+1;
	
    vector<string> tablename;
	intiname(tablename);

	vector<COleDateTime> AllDays(days);
	for(size_t i=0;i<days;i++)
	{
		AllDays[i] = Dfirst + COleDateTimeSpan(i,0,0,0);
	}

	vector<vector<long> > vals(tablename.size(),vector<long>(days,0));
	vector<vector<long> > vals8(tablename.size(),vector<long>(days,0));
	vector<bool> vald(tablename.size(),false);

	for(size_t i=0;i<vals.size();++i)
	{
		vald[i] = !insertDB(dbname.c_str(), tablename[i].c_str(),vals8[i],vals[i]);

		if(vald[i]) continue;

		//处理8点数据
		long m=0;
		for(size_t j=0;j<vals[i].size()-1;++j)
		{
			m = vals[i][j]-vals8[i][j]; //20时减8时雨量
			if(m<0) m=0;

			vals8[i][j] = m+vals8[i][j+1];

		}
	}

	for(size_t i=0,j=0;i<vals.size();)
	{
		if(vald[j++])
		{
			tablename.erase(tablename.begin()+i);
			vals.erase(vals.begin()+i); //没有此乡镇站的记录
			vals8.erase(vals8.begin()+i);
		}
		else
			++i;
	}

	for(size_t j=0;j<vals[0].size();)
	{
		bool d = true;
		for(size_t i=0;i<vals.size();++i)//遍历当前列
		{
			if(vals[i][j])
			{
				d=false;
				break;
			}
		}

		if(d)
		{
			for(size_t i=0;i<vals.size();++i)
			{
				vals[i].erase(vals[i].begin()+j);
			}
			AllDays.erase(AllDays.begin()+j);

		}
		else
		{
			++j;
		}
	}

	outvec(dbname,tablename,AllDays,vals);

}

int main()
{
	/**/	

	dealval();

}
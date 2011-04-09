#include "comn.h"
#include "afxdao.h"


#pragma warning( disable : 4995 )

using namespace std;

//��ʵ���������ݿ�
bool insertDB(const char *dbname,const char * table, COleDateTime datet,vector<double> &vals)
{

	CDaoDatabase daoDb;

	COleVariant OleV1,OleV2 ;//���ں���ֵ�ֶ�

	try
	{
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


	}
	catch(CDaoException *e)
	{
		cout<<(e->m_pErrorInfo->m_strDescription).GetBuffer()<<endl;
		e->Delete();

		AfxDaoTerm(); //
		return false;
	}

	daoDb.Close(); //�ر����ݿ�
	AfxDaoTerm(); //
	return true;
}



void readVal()
{
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
	CDaoDatabase daoDb;

	COleVariant OleV1;

	try
	{
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
	}
	catch(CDaoException *e)
	{
		cout<<(e->m_pErrorInfo->m_strDescription).GetBuffer()<<endl;
		e->Delete();

		AfxDaoTerm(); //
		return false;
	}

	daoDb.Close(); //�ر����ݿ�
	AfxDaoTerm(); //
	return true;
}

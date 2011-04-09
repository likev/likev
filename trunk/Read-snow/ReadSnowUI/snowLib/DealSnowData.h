#ifndef _DEAL_SNOW_DATA
#define _DEAL_SNOW_DATA

/*
	��½FTP������ѩ�۲��ļ� 
	�趨��ʱ�䷶Χ��վ��� ��ͨ���ӿ�GetAccumulateSnow()�����ۼƽ�ѩ�������ѩ��

	����޸ģ���� 2011 2 12�� 2ʱ
*/

#include "comn.h"
#include "FtpSnowFiles.h"
#include "SnowFile.h"

class DealSnowData
{
	FtpSnowFiles ftpSnow;
	std::vector<SnowFile> snowFiles;

	//����վ��
	std::vector<std::string> allStations;

	//ÿһ�д���һ��վ��ĸ�ʱ�μ�¼
	std::vector< std::vector<SnowInfo> > allStationsRecord;

	CTime timeBegin, timeEnd;
	
	bool haveDeal, haveDown;

	bool ReadAndDealFiles()
	{
		//ʱ������
		std::vector<CTime> timeList = GetTimeList();

		for(size_t index=0; index != timeList.size(); index++)
		{
			ftpSnow.DownGivenTimeFile(timeList[index]);

			std::string filename = timeList[index].Format("snow/%Y%m%d%H_SNOW.TXT");
			snowFiles.push_back(SnowFile(filename) );

		}

		return haveDown = true;
	}

	bool GetDataFromFiles()
	{
		if(!haveDown ) ReadAndDealFiles();

		//ʱ������
		std::vector<CTime> timeList = GetTimeList();

		for(size_t index=0; index != timeList.size(); index++)
		{
			for(int row=0;row<allStationsRecord.size();row++)
			{
				SnowInfo newInfo = snowFiles[index].GetStationSnow(allStations[row]);
				allStationsRecord[row].push_back(newInfo);
			}
		}

		return haveDeal = true;
	}

public:
	
	DealSnowData():haveDown(false),haveDeal(false){};

	DealSnowData(CTime begin,CTime end)
	{
		SetTimeRange( begin, end);
	};

	void SetTimeRange(CTime begin,CTime end)
	{
		timeBegin = begin;
		timeEnd   = end;

		haveDown = false;
		haveDeal = false;
	}

	CTime GetBeginTime()const
	{
		return timeBegin;
	}
	CTime GetEndTime()const
	{
		return timeEnd;
	}

	bool SetStations(const std::vector<std::string> & stations)
	{
		allStations = stations;
		allStationsRecord.clear();
		allStationsRecord.resize(stations.size());

		haveDeal = false;

		return !stations.empty();
	}

	const std::vector<std::string>& GetStations()const
	{
		return allStations;
	}


	std::vector<CTime> GetTimeList()const
	{
		CTime cur=timeBegin;
		//ʱ������
		std::vector<CTime> timelist;
		//����ÿһ���ÿһ��ʱ�ν��д���
		int hours[7]={6,7,8,11,14,17,20};
		while(cur <= timeEnd)
		{
			for(int index=0;index<7;index++)
			{
				cur += CTimeSpan(0,hours[index]-cur.GetHour(),0,0);

				if(cur <= timeBegin) continue;
				if(cur > timeEnd) break;

				timelist.push_back(cur);
			}

			cur += CTimeSpan(1,-cur.GetHour(),0,0);

		}
		return timelist;
	}


	const std::vector< std::vector<SnowInfo> >&
		GetAllStationsRecord()
	{
		if(!haveDeal) GetDataFromFiles();

		return allStationsRecord;
	}

	bool isOK(){ return haveDeal; }

	std::vector<SnowInfo> GetAccumulateSnow()
	{
		if(!haveDeal) GetDataFromFiles();

		std::vector<SnowInfo> accumulateSnow;

		if(haveDeal)
		{
			for(int index=0;index<allStationsRecord.size();index++)
			{
				SnowInfo acumSnow = 
					std::accumulate(allStationsRecord[index].begin(),allStationsRecord[index].end(),SnowInfo() );

				accumulateSnow.push_back(acumSnow);
			}
		}

		return accumulateSnow;
	}

};

#endif //_DEAL_SNOW_DATA
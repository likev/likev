#ifndef _SNOW_FILE
#define _SNOW_FILE

#include "comn.h"
#include "SnowInfo.h"

class SnowFile
{
	std::map<std::string,SnowInfo> allRecords;

public:
	
	SnowFile(){};
	SnowFile(std::string filename)
	{
		InitFromFile(filename);
	};

	bool InitFromFile(std::string filename)
	{
		std::ifstream fin(filename.c_str());

		if(!fin.is_open())
		{
			return false;
		}

		std::string timeStr,stationID, equleSign;
		double lon,lat,snowDepth,snowVolumn;

		fin>>timeStr;

		while(timeStr != "NNNN")
		{
			fin>>stationID>>lon>>lat>>snowDepth>>snowVolumn>>equleSign;
			
			allRecords[stationID] = SnowInfo(snowVolumn/10,snowDepth/10);

			fin>>timeStr;
		}

		return true;
	}

	SnowInfo GetStationSnow(const std::string& stationID)
	{
		if(allRecords.count(stationID) )
		{
			return allRecords[stationID];
		}
		
		return SnowInfo();
	}

};

#endif //_SNOW_FILE
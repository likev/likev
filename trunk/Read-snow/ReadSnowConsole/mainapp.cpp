#include "comn.h"
#include "FtpSnowFiles.h"
#include "SnowFile.h"
#include "DealSnowData.h"

int main()
{
	using namespace std;

	DealSnowData dsd(CTime(2011,2,9,5,0,0), CTime(2011,2,10,15,0,0) );

	//ËùÓÐÕ¾µã
	std::string stations[9] = {"57065","57066","57070","57071","57077","57078","57162","57074","57076"};
	dsd.SetStations(vector<string> (stations,stations+9));

	vector<SnowInfo> allStationsRecord = dsd.GetAccumulateSnow();

	for(int index=0;index<allStationsRecord.size();index++)
	{
		cout<<stations[index]<<": "<<allStationsRecord[index].GetDepth()<<"  "<<allStationsRecord[index].GetVolumn()<<endl;
	}
}
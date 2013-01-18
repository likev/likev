#include "Poco/Util/XMLConfiguration.h"
#include "Poco/RegularExpression.h"
#include "Poco/Net/FTPClientSession.h"
#include "Poco/StreamCopier.h"
#include "Poco/Thread.h"
#include "Poco/Util/Timer.h"
#include "Poco/Exception.h"

#include "string-trans.h"

#include <iostream>
#include <vector>
#include <sstream>

std::string getLastTimeStr(const std::string & dir)
{
	using Poco::AutoPtr;
	using Poco::Util::XMLConfiguration;

	AutoPtr<XMLConfiguration> pConf(new XMLConfiguration("snow-config.xml") );
	
	return pConf->getString("lasttime."+dir);
}

std::vector<std::string> & getDirList(std::vector<std::string> & dirs)
{
	using Poco::AutoPtr;
	using Poco::Util::XMLConfiguration;

	AutoPtr<XMLConfiguration> pConf(new XMLConfiguration("snow-config.xml") );
	
	int count = pConf->getInt("dircount");

	for(int i=0; i<count; i++)
	{
		dirs.push_back(pConf->getString("dirname["+to_string(i)+"]") );
	}
	return dirs;
}

void setLastTimeStr(const std::string & dir, const std::string & timestr)
{
	using Poco::AutoPtr;
	using Poco::Util::XMLConfiguration;

	AutoPtr<XMLConfiguration> pConf(new XMLConfiguration("snow-config.xml") );
	
	pConf->setString("lasttime."+dir, timestr);
	pConf->save("snow-config.xml");
}



bool singleInfo(const std::string & subject, std::string & info)
{
	Poco::RegularExpression rg1("^([0-9]{5}) ([0-9]{14}) .+^RE .{28} ([0-9/,]{2}) ([0-9/,]{5}) .+^SP ([0-9/,]{4})",
		Poco::RegularExpression::RE_MULTILINE| Poco::RegularExpression::RE_DOTALL| Poco::RegularExpression::RE_NEWLINE_ANYCRLF);

	Poco::RegularExpression::MatchVec matchs;
	int m = rg1.match(subject,0,matchs);

	if(6 != m) return false;
	//std::cout<<m<<matchs.size()<<"\n"<<subject<<std::endl;
	//std::cin>>info;
	std::vector< std::string > record;
	std::vector< bool > lossrecord(5, false);
	for(size_t i=1; i!=matchs.size(); i++)
	{
		record.push_back( subject.substr(matchs[i].offset, matchs[i].length) );
		lossrecord[i-1] = std::string::npos != record[i-1].find('/');
	}
	

	if(lossrecord[3] && lossrecord[4] )//Í¬Ê±È±²â
	{
		return false;
	}

	for(size_t i=2; i<5; i++)
	{
		if(lossrecord[i])
		{
			record[i] = "99999";
		}
		else if( std::string::npos != record[i].find(',') )
		{
			record[i] = "1";
		}
		else if(i>2)
		{
			record[i] += '0';
		}
	}

	for(size_t i=0; i<record.size(); i++)
	{
		info += record[i] + ' ';
	}
	info[info.size()-1] = '\n';

	return true;
}

void pocoPost2(const std::string &url, const std::string &key, const std::string &value);

void dealfile(const std::string & subject)
{
	Poco::RegularExpression rg1("^[0-9]{5}.+?=$",Poco::RegularExpression::RE_MULTILINE|
		Poco::RegularExpression::RE_DOTALL|
		Poco::RegularExpression::RE_NEWLINE_ANYCRLF);
	//std::cout<<rg1.match(subject)<<std::endl;
	std::string::size_type offset = 0;
	std::string singleRecord, postInfo;

	int count = 0;

	while(rg1.extract(subject,offset,singleRecord))
	{
		singleInfo(singleRecord, postInfo);

		offset += singleRecord.size();

		count++;
	}

	std::cout<<postInfo<<std::endl;

	if(postInfo.size()) pocoPost2("http://area.sinaapp.com/snow/update-mysql-from-post.php", "app-content", postInfo);
}

void pocoFtp1(const std::string &dir)
{
	Poco::Net::FTPClientSession session("172.18.152.9");
	session.login("sjgx2012", "sjgx2012");

	session.setWorkingDirectory("/"+dir+"/aws");
	std::istream &ftpin = session.beginList("");

	std::string str;
	std::vector<std::string > filelist;
	while(ftpin>>str)
	{
		filelist.push_back(str);
	}
	session.endList();

	std::string lastTimeStr = getLastTimeStr(dir), thisTimeStr = lastTimeStr;

	for(size_t i=0; i!=filelist.size(); i++)
	{
		std::string resp, timestr;
		session.sendCommand("MDTM",filelist[i],resp);
		Poco::RegularExpression rg1("[0-9]{14}$");
		rg1.extract(resp,timestr);

		/*std::cout<<timestr<<std::endl;*/
		if(timestr > lastTimeStr)//deal new file
		{
			std::string content;
			Poco::StreamCopier::copyToString( session.beginDownload( filelist[i] ), content);
			session.endDownload();

			std::cout<<"deal file "<<filelist[i]<<"...\n";
			dealfile(content);
			
			if(timestr>thisTimeStr) thisTimeStr = timestr;
		}
	}

	setLastTimeStr(dir, thisTimeStr);
	
	session.close();
}


int main()
{
	
	while(1)
	{
		try
		{
			std::vector<std::string> dirs;
			getDirList(dirs);

			for(size_t i=0; i<dirs.size(); i++)
			{
				std::cout<<"deal dir "<<dirs[i]<<"....\n";
				pocoFtp1(dirs[i]);
			}
		}
		catch(Poco::Exception &exc)
		{
			std::cout<<"exc"<<exc.displayText();
		}

		int wait = 5;
		std::cout<<"waiting "<<wait<<" minutes...\n";
		Poco::Thread::sleep(1000*60*wait);
	}

}
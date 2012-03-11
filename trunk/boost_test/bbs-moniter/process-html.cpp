#include "process-html.h"

#include <vector>
#include <string>
#include <boost/foreach.hpp>

std::vector<std::string>& get_tr_list(std::vector<std::string>& trlist, std::string& html, boost::regex pat)
{
	trlist.clear();

	boost::smatch what;
	std::string itembody;
	if(regex_search(html, what, pat))
	{
		itembody = what[0];
	}

	boost::regex pat_tr("<tr.+?</tr>");
	std::string::const_iterator start, end;
	start = itembody.begin();
	end = itembody.end();

	while(regex_search(start, end, what, pat_tr))
	{
		trlist.push_back(what[0]);
		start = what[0].second;
	}

	return trlist;
}

std::vector<item_describe> & 
get_all_title(std::vector<item_describe> & items, std::vector<std::string>& trlist, boost::regex pat)
{
	items.clear();

	BOOST_FOREACH(std::string &tr, trlist)
	{
		boost::smatch what;
		if(regex_search(tr, what, pat))
		{
			// what[0] contains the whole string 

			item_describe item;

			item.url = what[1];
			item.title = what[2];
			item.author = what[3];
			item.timestr = what[4];

			items.push_back(item);
		}

	}

   return items;

}
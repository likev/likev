#pragma once

#include <boost/regex.hpp>
#include <vector>
#include <string>

struct item_describe{
	std::string title, url, author, timestr;
};

//����html�����tbody pat���������trlist�ﲢ����������
std::vector<std::string>& 
get_tr_list(std::vector<std::string>& trlist, std::string& html, boost::regex pat_tbody);

//����trlist��item pat������洢��items�ﲢ����������
std::vector<item_describe> &
get_all_title(std::vector<item_describe> & items, std::vector<std::string>& trlist, boost::regex pat_item);
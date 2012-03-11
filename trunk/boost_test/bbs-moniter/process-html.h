#pragma once

#include <boost/regex.hpp>
#include <vector>
#include <string>

struct item_describe{
	std::string title, url, author, timestr;
};

//传入html代码和tbody pat，结果存在trlist里并返回其引用
std::vector<std::string>& 
get_tr_list(std::vector<std::string>& trlist, std::string& html, boost::regex pat_tbody);

//传入trlist和item pat，结果存储在items里并返回其引用
std::vector<item_describe> &
get_all_title(std::vector<item_describe> & items, std::vector<std::string>& trlist, boost::regex pat_item);
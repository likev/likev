#pragma once

#include <map>

//关联对象的相加 比较等模板函数
template <typename K,typename V>
std::pair<K,V> add_pair_value(const std::pair<K,V> &left,const std::pair<K,V> &right)
{
	return std::pair<K,V>(right.first, left.second + right.second);
}

template <typename K,typename V>
bool equal_pair_key(const std::pair<K,V> &left,const std::pair<K,V>&right)
{
	return left.first == right.first;
}

template <typename K,typename V>
bool equal_pair_value(const std::pair<K,V> &left,const std::pair<K,V>&right)
{
	return left.second == right.second;
}

template <typename K,typename V>
bool less_pair_key(const std::pair<K,V> &left,const std::pair<K,V>&right)
{
	return left.first < right.first;
}

template <typename K,typename V>
bool less_pair_value(const std::pair<K,V> &left,const std::pair<K,V>&right)
{
	return left.second < right.second;
}

template <typename K,typename V>
bool grater_pair_key(const std::pair<K,V> &left,const std::pair<K,V>&right)
{
	return left.first > right.first;
}

template <typename K,typename V>
bool grater_pair_value(const std::pair<K,V> &left,const std::pair<K,V>&right)
{
	return left.second > right.second;
}

template <typename K,typename V>
void map_partial_sum(typename std::map<K,V>::iterator it1, typename std::map<K,V>::iterator it2, std::map<K,V> & dest)
{
	if(it1 == it2) return;
	dest.clear();

	std::pair<K,V> val(it1->first,it1->second);

	for(dest.insert(val); ++it1 != it2;)
	{
		val = add_pair_value(val,std::pair<K,V>(it1->first,it1->second));
		dest.insert(val);
	}
}

template <typename K,typename V>
bool is_map_value_zero(const std::pair<K,V> &left)
{
	if(!left.second)
		return true;

	return false;
}

template <typename K,typename V>
bool is_map_value_nzero(const std::pair<K,V> &left)
{
	return !is_map_value_zero(left);
}
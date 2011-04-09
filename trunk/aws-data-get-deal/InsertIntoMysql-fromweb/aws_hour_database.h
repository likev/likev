//处理自动站小时数据记录与数据库交互的操作
#include "aws_hour_record.h"

//从文件中获取数据
bool get_aws_hrcods_from_file(const CTime &curtime,	std::vector<aws_hour_record> &records);


// 设置读取时间
void SetLastReadTime(CTime last_time);
//获取配置时间
void GetLastReadTime(CTime &last_time);

//处理插入数据库的具体操作
void deal_all_proc();
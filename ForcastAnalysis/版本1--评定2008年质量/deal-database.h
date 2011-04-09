#include "comn.h"

//根据数据库名称和查询语句从数据库中读取double值，未找到或出现错误则返回false。
bool read_from_db(const char *dbname,const char * sql_statement, double &val);
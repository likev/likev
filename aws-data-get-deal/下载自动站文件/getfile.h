#include <comn.h>
#include <afxinet.h>

//提示用户输入站号 开始时间 结束时间
//然后启动下载文件
void getfile(void);

//下载需要的文件 保存至当前目录webfiles文件夹下
//下载时间区间为 [begin,end]
void get_files_by_time(std::string station_num, CTime begin,CTime end);
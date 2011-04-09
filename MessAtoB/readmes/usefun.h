//程序中用到的功能函数声明

//将文本内容读入字符串str
std::string & filetostr(std::string file,std::string & str);

//将实数a保留l位小数(四舍五入) 然后转化为字符串
std::string dtos(double a, int l=1);
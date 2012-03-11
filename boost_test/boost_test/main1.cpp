#include <boost/regex.hpp>
#include <iostream>
#include <string>

int main()
{
    std::string line;
    boost::regex pat( "ab.cd" );//������ʽ

    while (std::cin)
    {
        std::getline(std::cin, line);
        boost::smatch matches;//ƥ�伯
        if (boost::regex_match(line, matches, pat))
            std::cout << matches[0] << std::endl;
    }
}


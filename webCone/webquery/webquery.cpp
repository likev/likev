// webquery.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>
#include <ctime>
#include <Wininet.h>


int main()
{
HINTERNET hNet = ::InternetOpen("MSDN SurfBear",
                                PRE_CONFIG_INTERNET_ACCESS,
                                NULL,
                                INTERNET_INVALID_PORT_NUMBER,
                                0) ;


}


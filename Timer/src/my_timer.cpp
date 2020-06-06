#include "my_timer.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

void getSecTime()
{
	time_t timeNow;  //实际就是long int
	
	timeNow = time(NULL);   // 方式一、获取从1970年1月1日0点0分到现在的秒数
	
	cout << timeNow <<endl;
	
	time(&timeNow);	// 方式二、获取从1970年1月1日0点0分到现在的秒数
	
	cout <<timeNow << endl;
}
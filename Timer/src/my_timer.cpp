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


void getCurrentTime(char* curTime, int type)
{
	time_t timeNow;  //实际就是long int	
	timeNow = time(NULL);   // 获取从1970年1月1日0点0分到现在的秒数
	
	struct tm * stTm = NULL;
	stTm = localtime(&timeNow);
	
	switch(type)
	{
		case YYYYMMDD:
		{
			//年需要加1900  月需要加1
			// 2020-6-6
			sprintf(curTime, "%d-%d-%d", stTm->tm_year+1900, stTm->tm_mon+1, stTm->tm_mday);
		}break;
		case YYYYMMDDHHMMSS:
		{
			// 2020-6-6 19:56:13
			sprintf(curTime, "%d-%d-%d %d:%d:%d", stTm->tm_year+1900, stTm->tm_mon+1, stTm->tm_mday, stTm->tm_hour, stTm->tm_min, stTm->tm_sec );
		}break;
		default:
		break;
	}
}
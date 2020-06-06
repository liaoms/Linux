#include "my_timer.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <time.h>
#include <sys/time.h>

using namespace std;

void getSecTime()
{
	time_t timeNow;  //实际就是long int
	
	timeNow = time(NULL);   // 方式一、获取从1970年1月1日0点0分到现在的秒数
	
	cout << timeNow <<endl;
	
	time(&timeNow);	// 方式二、获取从1970年1月1日0点0分到现在的秒数
	
	cout <<timeNow << endl;
}


void getCurrentTime(char* curTime, int type, int offset)
{
	time_t timeNow;  //实际就是long int	
	timeNow = time(NULL);   // 获取从1970年1月1日0点0分到现在的秒数
	
	timeNow += offset*24*60*60;   //计算偏移天数，支持前后偏移
	
	struct tm * stTm = NULL;
	stTm = localtime(&timeNow);
	
	switch(type)
	{
		case YYYYMMDD:
		{
			//年需要加1900  月需要加1
			// 2020-6-6
			sprintf(curTime, "%04d-%02d-%02d", stTm->tm_year+1900, stTm->tm_mon+1, stTm->tm_mday);
		}break;
		case YYYYMMDDHHMMSS:
		{
			// 2020-6-6 19:56:13
			sprintf(curTime, "%04d-%02d-%02d %02d:%02d:%02d", stTm->tm_year+1900, stTm->tm_mon+1, stTm->tm_mday, stTm->tm_hour, stTm->tm_min, stTm->tm_sec );
		}break;
		default:
		break;
	}
}
	   
void getdifTime()
{
	struct timeval beginTv;
	struct timeval endTv;
	
	gettimeofday(&beginTv, NULL);
	
	usleep(100);
	
	//gettimeofday参数2为时区参数结构体，不常用，直接给NULL
	gettimeofday(&endTv, NULL);
	
	//获取两段时间微妙间隔
	int usec = (endTv.tv_sec - beginTv.tv_sec) * 1000000 + (endTv.tv_usec - beginTv.tv_usec);
	
	cout << "时间间隔 : " << usec << " 微妙" << endl; 

}
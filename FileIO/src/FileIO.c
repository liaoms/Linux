#include "FileIO.h"

#include <stdio.h>
#include <string.h>

int txtFileTest()
{
	FILE *pF = NULL;
	char* filePath = "/home/delphi/myshare/GitHub/Linux/FileIO/data/test.txt";
	
	/*
	 * r+ : 可读可写，文件必须存在
	 * w+ : 可读可写，文件不存在创建，存在重清空 
	 * a+ : 可读可写，文件不存在创建，存在追加写
	*/
	pF = fopen(filePath, "w+");  
	
	if(NULL == pF)
	{
		printf("open file fail[%s]\n", filePath);
		return -1;
	}
	printf("open file succeed[%s]\n", filePath);
	
	int i=0;
	for(; i<5; i++)
	{
		fprintf(pF, "%s\n", "Evrey thing is possible");
	}
	
	//重新定位到文件开头
	fseek(pF, 0, SEEK_SET);
	
	char buf[1024] = {0};
	while(1)
	{
		memset(buf, 0x00, sizeof(buf));
		char* ret = fgets(buf, sizeof(buf), pF);
		
		if(NULL != ret)
		{
			printf("buf = %s", buf);
		}
		else
		{
			break;
		}
	}
	
	if(NULL != pF)
	{
		fclose(pF);
		pF = NULL;
	}
}
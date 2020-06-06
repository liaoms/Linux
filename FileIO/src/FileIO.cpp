#include "FileIO.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

struct stData
{
	char name[64];
	int age;
	int height;	
	char addr[256];
	
	stData()
	{
		memset(name, 0x00, sizeof(name));
		age = 0;
		height  =0;	
		memset(addr, 0x00, sizeof(addr));
	}
	
	void clear()
	{
		memset(name, 0x00, sizeof(name));
		age = 0;
		height  =0;	
		memset(addr, 0x00, sizeof(addr));
	}
	
};

int txtFileTest()
{
	FILE *pF = NULL;
	string filePath = "/home/delphi/myshare/GitHub/Linux/FileIO/data/test.txt";
	
	/*
	 * r+ : 可读可写，文件必须存在
	 * w+ : 可读可写，文件不存在创建，存在重清空 
	 * a+ : 可读可写，文件不存在创建，存在追加写
	*/
	pF = fopen(filePath.c_str(), "w+");  
	
	if(NULL == pF)
	{
		printf("open file fail[%s]\n", filePath.c_str());
		return -1;
	}
	printf("open file succeed[%s]\n", filePath.c_str());
	
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

int binFileTest()
{
	stData m_Jack;
	m_Jack.age = 22;
	m_Jack.height = 180;
	strcpy(m_Jack.name, "jack");
	strcpy(m_Jack.addr, "shenzhen");
	
	FILE *pF = NULL;
	string filePath = "/home/delphi/myshare/GitHub/Linux/FileIO/data/test.bin";
	
	/*
	 * rb+ : 二进制可读可写，文件必须存在
	 * wb+ : 二进制可读可写，文件不存在创建，存在重清空 
	 * ab+ : 二进制可读可写，文件不存在创建，存在追加写
	*/
	pF = fopen(filePath.c_str(), "wb+");  
	
	if(NULL == pF)
	{
		printf("open file fail[%s]\n", filePath.c_str());
		return -1;
	}
	printf("open file succeed[%s]\n\n", filePath.c_str());
	
	int blobSize = sizeof(m_Jack);
	fwrite(&blobSize, 1, sizeof(int), pF);  //先写结构体大小
	fwrite(&m_Jack, 1, blobSize, pF);		//再写结构体内容
	
	
	
	//重新定位到文件开头
	fseek(pF, 0, SEEK_SET);
	
	int blobSizeTmp = 0;
	stData m_tmp;

	int ret = fread(&blobSizeTmp, 1, sizeof(int), pF);  //先取结构体大小
	if(0 == ret)
	{
		cout << "read bin file fail" << endl;
	}
	else
	{
		cout << "blobSizeTmp = " << blobSizeTmp << endl;
		cout << "sizeof(stData) = " << sizeof(stData) << endl;
		
		ret = fread(&m_tmp, 1, blobSizeTmp, pF);   //再取结构体内容
		if(0 != ret)
		{
			cout << "name = " << m_tmp.name << endl;
			cout << "age = " << m_tmp.age << endl;
			cout << "height = " << m_tmp.height << endl;
			cout << "addr = " << m_tmp.addr << endl;
		}
	}
		
	if(NULL != pF)
	{
		fclose(pF);
		pF = NULL;
	}
	
	 
	
	
}
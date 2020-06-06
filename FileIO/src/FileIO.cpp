#include "FileIO.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

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
		fflush(pF);  //强制将缓冲区写入文件
	}
	
	// SEEK_SET:从文件头偏移   
	// SEEK_CUR:从文件当前读取位置偏移 
	// SEEK_END:从文件末尾位置偏移 
	
	//fseek(pF, 0, SEEK_SET);  // 方式一、重新定位到文件开头
	
	rewind(pF);		// 方式二、重新定位到文件开头
	
	char buf[1024] = {0};
	while(1)
	{
		long index = ftell(pF);  //返回文件读取位置
		printf("index = %ld  ", index);
			
		memset(buf, 0x00, sizeof(buf));
		char* ret = fgets(buf, sizeof(buf), pF);
		
		if(NULL != ret)
		{
			printf("buf = %s", buf);
		}
		else
		{
			printf("\n");
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
	
	fflush(pF);  //强制将缓冲区写入文件
	
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


int cpyFileWithBin(char* srcFile, char* desFile)
{
	/*
	 * rb+ : 二进制可读可写，文件必须存在
	 * wb+ : 二进制可读可写，文件不存在创建，存在重清空 
	 * ab+ : 二进制可读可写，文件不存在创建，存在追加写
	*/
	
	FILE* pFRead = NULL;
	pFRead = fopen(srcFile, "rb");  //二进制只读打开
	
	if(NULL == pFRead)
	{
		printf("open file fail[%s]\n", srcFile);
		return -1;
	}
	printf("open file succeed[%s]\n\n", srcFile);
	
	FILE* pFWrite = NULL;
	pFWrite = fopen(desFile, "wb");  //二进制只写打开	
	if(NULL == pFWrite)
	{
		printf("open file fail[%s]\n", desFile);
		fclose(pFRead);
		pFRead = NULL;
		return -1;
	}
	printf("open file succeed[%s]\n\n", desFile);
	
	int readLen = 0;
	char buf[500] = {0};
	
	
	while(1)
	{
		readLen = fread(&buf, 1, sizeof(buf), pFRead); 
		
		if(0 == readLen)
		{
			break;
		}
		
		fwrite(&buf, 1, readLen, pFWrite);  
		fflush(pFWrite);  //强制将缓冲区写入文件
	}
		
	fclose(pFRead);
	fclose(pFWrite);
	
	//rename("/home/delphi/myshare/GitHub/Linux/FileIO/data/FileIO.cpp", "/home/delphi/myshare/GitHub/Linux/FileIO/data/FileIObak.cpp");
	unlink(desFile);
	
	return 0;
}

int createDirIfNoExist(char * filePath)
{
	if( 0 != access(filePath, F_OK) )
	{
		if( 0 == mkdir(filePath, 00755) )  //创建目录权限为755
		{
			cout << "Create FilePath [" << filePath <<"] succeed!" << endl;
		}
		else
		{
			cout << "Create FilePath [" << filePath <<"] failed!" << endl;
		}
	}
	else
	{
		cout << "filePath [" << filePath << "] already exist！" << endl; 
	}
}

int readDir(char* filePath)
{
	if( 0 != access(filePath, F_OK) )
	{
		cout << "filePath [" << filePath << "] not exist！" << endl; 
	}
	else
	{
		DIR * pDir = NULL;
		pDir = opendir(filePath);
		
		if(NULL == pDir)
		{
			cout << "open filePath [" << filePath << "] faild！" << endl; 
		}
		
		struct dirent* m_dirent = NULL;
		while(1)
		{
			m_dirent = readdir(pDir);
			if(NULL != m_dirent)
			{
				if( !strncmp(m_dirent->d_name, ".", 1) )
				{
					continue;
				}
				cout <<"fileName = " << m_dirent->d_name << endl;
				cout << "fileType = " << m_dirent->d_type << endl <<endl;
			}
			else
			{
				break;
			}
		}
		
		closedir(pDir);
	}
}
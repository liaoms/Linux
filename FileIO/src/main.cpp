#include "FileIO.h"
#include <stdio.h> 
#include <unistd.h>

int main(int argc, char* argv[])
{
	//txtFileTest();
	//binFileTest();
	cpyFileWithBin("/home/delphi/myshare/GitHub/Linux/FileIO/src/FileIO.cpp", "/home/delphi/myshare/GitHub/Linux/FileIO/data/FileIO.cpp");
	//createDirIfNoExist("/home/delphi/myshare/GitHub/Linux/FileIO/data1");
	//readDir("/home/delphi/myshare/GitHub/Linux/FileIO/data");
	return 0;
}

#ifndef __FILEIO_H__
#define __FILEIO_H__

int txtFileTest();

int binFileTest();

int cpyFileWithBin(char* srcFile, char* desFile);

int createDirIfNoExist(char * filePath);

int readDir(char* filePath);

#endif
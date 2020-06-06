#include "my_timer.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	//getSecTime();
	
	char cruTime[64]  ={0};
	getCurrentTime(cruTime, YYYYMMDDHHMMSS, -2);
	
	cout << cruTime << endl;
	return 0;
}

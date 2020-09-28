#include<iostream>
#include<cstdlib>
#include<sstream>

using namespace std;

void LRU(const char* FileName[], int CacheLines){

}

void FIFO(const char* FileName[], int CacheLines){

}

void OPTIMAL(const char* FileName[], int CacheLines){

}

int main(int argc, char* argv[]){
	
	stringstream Cache_lines(argv[3]);
	int cl = 0;
	Cache_lines >> cl;

	if(argv[1] == "LRU")
	{
		LRU(argv[2], cl);
	}
	else if (argv[1] == "FIFO")
	{
		FIFO(argv[2], cl);
	}
	else if (argv[1] == "OPTIMAL")
	{
		OPTIMAL(argv[2], cl);
	}

}
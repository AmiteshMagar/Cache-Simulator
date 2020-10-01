#include<iostream>
#include<sstream>

using namespace std;

int main(int argc, char* argv[]){
	
	string temp = argv[1];
	stringstream Cache_lines(argv[3]);
	int cl = 0;
	Cache_lines >> cl;
	
	if(temp.compare("LRU") == 0)
	{
		cout << "LRU" << endl;
	}
	else if (temp.compare("FIFO") == 0)
	{
		cout << "FIFO" << endl;
	}
	else if (temp.compare("OPTIMAL") == 0)
	{
		cout << "OPTIMAL" << endl;
	}
	else
		cout << "Incorrect arguments entered" << endl;
	return 0;

}
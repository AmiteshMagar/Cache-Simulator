#include<iostream>
#include<cstdlib>
#include<sstream>
#include<bits/stdc++.h>

using namespace std;

int misscount = 0;
int hitcount = 0;
int mastercount = 0;

class Entry{
public:
    string data;
    Entry* next;
    Entry(string val){
        data = val;
        next = NULL;
    }
};

struct Fifo_Q{
    Node* FirstOut;
    Node* FirstIn;
    Fifo_Q()
    {
        FirstOut =NULL;
        FirstIn = NULL;
    }

    void Dequeue(){
        if(FirstOut == NULL)
            return;

        Node *dummy = FirstOut;
        FirstOut = FirstOut->next;
        
        if(FirstOut == NULL)
            FirstIn = NULL;
    }

    void Enqueue(string value){
        Node *dummy = new Node(value);

        if(FirstIn == NULL){
            FirstOut = FirstIn = dummy;
            return;
        }

        FirstIn -> next = dummy;
        FirstIn = dummy;
    }
};

void LRU(string filename, int CacheLines){

}

void FIFO(string filename, int CacheLines){

Fifo_Q Fifo_queue;

}

void OPTIMAL(string filename, int CacheLines){

}

int main(int argc, char* argv[]){
	
	string RepPolicy = argv[1];
	string FileName = argv[2];
	stringstream Cache_lines(argv[3]);
	int cl = 0;
	Cache_lines >> cl;
	
	if(RepPolicy.compare("LRU") == 0)
	{
		
	}
	else if (RepPolicy.compare("FIFO") == 0)
	{
		FIFO(FileName, cl);
	}
	else if (RepPolicy.compare("OPTIMAL") == 0)
	{
		
	}
	else
		cout << "Incorrect Replacement Policy entered" << endl;
	return 0;

}
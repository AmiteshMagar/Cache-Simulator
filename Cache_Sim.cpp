#include<iostream>
#include<cstdlib>
#include<sstream>
#include<bits/stdc++.h>

using namespace std;

//Declaring Global variables
int misscount = 0;
int hitcount = 0;
int mastercount = 0;
int comp_miss = 0;
int capcity_miss = 0;

//Defining a cache entry as a node in a Linked List
//Every entry of the cache stores data as well as the pointer to
//the address of the next entry in the cache.

//To preserve logic, The oldest input data in the current cache structure 
//is the last entry in the structure.
class Entry{
public:
    string data;
    Entry* next;
    Entry(string val){
        data = val;
        next = NULL;
    }
};

//Defining unique data structure for FIFO cache
struct Fifo_Q{
    Node* FirstOut;
    Node* FirstIn;
    Fifo_Q()
    {
        FirstOut =NULL;
        FirstIn = NULL;
    }

    //Function for removing a node from cache LL
    void Dequeue(){
        if(FirstOut == NULL)
            return;

        Node *dummy = FirstOut;
        FirstOut = FirstOut->next;
        
        if(FirstOut == NULL)
            FirstIn = NULL;
    }

    //Function for adding an entry to the cache LL
    void Enqueue(string value){
        Node *dummy = new Node(value);

        if(FirstIn == NULL){
            FirstOut = FirstIn = dummy;
            return;
        }

        FirstIn -> next = dummy;
        FirstIn = dummy;
    }
    //In FIFO replacement policy, the Enque operation will
    //always be followed by the Dequeue operation whenever the cache limit is full
};

//Function for executing LRU Replacement policy
void LRU(string filename, int CacheLines){

}

//Function for executing FIFO Replacement policy
void FIFO(string filename, int CacheLines){

Fifo_Q Fifo_queue;

}

//Function for executing OPTIMAL strategy of cache entry replacement
void OPTIMAL(string filename, int CacheLines){

}

//driver code
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
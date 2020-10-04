#include<iostream>
#include<cstdlib>
#include<sstream>
#include<bits/stdc++.h>
#include<fstream>

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
//is the first entry in the structure.
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

    //Structure like a regular waiting line queue,
    //person to go out is at head, 
    //to go in, join queue from the tail

    //FirstOut is the head of the Cache block
    //FirstIn is the tail of the Cache block

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

        if(FirstOut == NULL){
            FirstOut = FirstIn = dummy;
            return;
        }

        FirstIn -> next = dummy;
        FirstIn = dummy;
    }

    //Function for reading queue and checking if data already exists
    bool Readqueue(string value){
		Node* dummy = FirstOut;
    	
    	if(FirstOut == NULL) //Empty queue, value absent --> return 1
    		return TRUE;

    	while (dummy != NULL){  // check if value exists in the queue
    		if ((dummy->data) == value){
    			hitcount++;
    			return FALSE; // Value present in the queue return --> 0
    		}    	
    		dummy = dummy->next;
    	}
    	return TRUE; //Value checked and absent, return --> 1
    		
    }
    //In FIFO replacement policy, the Enqueue operation will
    //always be followed by the Dequeue operation whenever the cache limit is full
};

//Function for executing LRU Replacement policy
void LRU(string filename, int CacheLines){

}

//Function for executing FIFO Replacement policy
void FIFO(string filename, int CacheLines){

	string line;
	int lineReg = 0;
	//creating object for FIFO
	Fifo_Q Fifo_queue;

	ifstream InFile;
	InFile.open(filename);
	while(InFile){
		getline(InFile, line);
		istringstream ss(line);
		do{
			string word;
			ss >> word;

			mastercount++;

			if(word !="" && word! = " "){
				//Queue codes
				if (Fifo_queue.Readqueue(word)){ //Executed only whn the cache
					misscount++; 				 // does not hold the value were looking for

					while(lineReg < CacheLines){
						//Executed when the cache is not full
						Fifo_queue.Enqueue(word);
						lineReg++;
						comp_miss++;

					}
					while(lineReg = CacheLines){
						//Executed when the cache is full
						Fifo_queue.Enqueue(word);
						Fifo_queue.Dequeue();

					}
				}
				//No special hit code for FIFO
			}
		}while(ss);
		if(InFile.eof())
			break;
	}
}

//Function for executing OPTIMAL strategy of cache entry replacement
void OPTIMAL(string filename, int CacheLines){

}

//driver code
int main(int argc, char* argv[]){
	
	string RepPolicy = argv[1];
	string InputFileName = argv[2];
	stringstream Cache_lines(argv[3]);
	int cl = 0;
	Cache_lines >> cl;
	
	if(RepPolicy.compare("LRU") == 0)
	{
		
	}
	else if (RepPolicy.compare("FIFO") == 0)
	{
		FIFO(InputFileName, cl);
	}
	else if (RepPolicy.compare("OPTIMAL") == 0)
	{
		
	}
	else
		cout << "Incorrect Replacement Policy entered" << endl;
	return 0;

}
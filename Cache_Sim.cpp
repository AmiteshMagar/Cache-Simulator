#define FALSE 0
#define TRUE 1

#include<bits/stdc++.h>
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<string>

using namespace std;

//Declaring Global variables
int misscount = 0;
int hitcount = 0;
int mastercount = 0;
int comp_miss = 0;
int capacity_miss = 0;

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

//Defining the nodes for victim cache
class vcEntry{
public:
	string vData;
	vcEntry* link;
	vcEntry(string value){
		vData = value;
		link = NULL;
	}
}

//Defining uniqu data structure for Victim Cache
struct VictimCache{
    vcEntry* vHead;
    vcEntry* vTail;
    VictimCache()
    {
        vHead =NULL;
        vTail = NULL;
    }
    
    void Add(string value){
        vcEntry *temp = new vcEntry(value);

        if(vTail == NULL){
            vHead = vTail = temp;
            return;
        }

        vTail -> link = temp;
        vTail = temp;
    }
    int Read(string value){
        vcEntry* dummy = vHead;
        
        if(vHead == NULL) //Empty queue, value absent --> return 1
            return TRUE;

        while (dummy != NULL){  // check if value exists in the queue
            if ((dummy->data) == value){
                return FALSE; // Value present in the queue return --> 0
            }       
            dummy = dummy->next;
        }
        return TRUE; //Value checked and absent, return --> 1           
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

        Entry *dummy = FirstOut;
        FirstOut = FirstOut->next;
        
        if(FirstOut == NULL)
            FirstIn = NULL;
    }

    //Function for adding an entry to the cache LL
    void Enqueue(string value){
        Entry *dummy = new Entry(value);

        if(FirstOut == NULL){
            FirstOut = FirstIn = dummy;
            return;
        }

        FirstIn -> next = dummy;
        FirstIn = dummy;
    }

    //Function for reading queue and checking if data already exists
    int Readqueue(string value){
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
	//creating object for FIFO
	Fifo_Q Fifo_queue;
	VictimCache vc;

	string sub;
	string ofName = "19122002_FIFO_";
	sub = filename;
	sub.erase((sub.end() - 4),sub.end());
	ofName.append(sub);
	ofName.append("_");
	ofName.append(to_string(CacheLines));
	ofName.append(".txt");

	ifstream InFile;
	ofstream OutFile;

	OutFile.open(ofName);
	OutFile <<endl;
	InFile.open(filename);

	while(InFile){
		getline(InFile, line);
		istringstream ss(line);
		do{
			string word;
			ss >> word;
			if((word !="") && (word != " ")){
				mastercount++;
				//Queue codes
				if (Fifo_queue.Readqueue(word)){ //miss code --Executed only when the cache
					misscount++; 				 // does not hold the value were looking for

					if (CacheLines > 0){
						//Executed when the cache is not full
						Fifo_queue.Enqueue(word);
						CacheLines--;
						comp_miss++;
						vc.Add(word);
						OutFile <<"Miss"<<endl;

					}
					else{
						//Executed when the cache is full, two types of misses are possible
						//Compulsary if miss in Victim cache
						//capacity if hit in Victim cache
						Fifo_queue.Enqueue(word);
						Fifo_queue.Dequeue();
						if(vc.Read(word)){
							vc.Add(word);
							comp_miss++;
							OutFile <<"Miss"<<endl;
						}
						else{
							capacity_miss++;
							OutFile <<"Miss"<<endl;
						}
					}
				}
				else{
					hitcount++;
					OutFile <<"Hit"<<endl;
				}
			}
		}while(ss);
		if(InFile.eof())
			break;
	}
	OutFile.seekp(0, ios::beg);
	OutFile<< "Total Accesses : "<< mastercount<<endl;
	OutFile<< "Total Misses : " << misscount << endl;
	OutFile<< "Total Hits : "<< hitcount <<endl;
	OutFile<< "Compulsary Misses : "<< comp_miss<<endl;
	OutFile<< "Capacity Misses : "<< capacity_miss <<endl;
	OutFile.close();
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
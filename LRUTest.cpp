#define FALSE 0
#define TRUE 1

#include<bits/stdc++.h>
#include<iostream>
#include<sstream>
#include<cstdlib>
#include<fstream>
#include<algorithm>
#include<string>

using namespace std;

int misscount = 0;
int hitcount = 0;
int mastercount = 0;
int comp_miss = 0;
int capacity_miss = 0;

class Entry{
public:
    string data;
    Entry* next;
    Entry(string val){
        data = val;
        next = NULL;
    }
};

class vcEntry{
public:
	string vData;
	vcEntry* link;
	vcEntry(string value){
		vData = value;
		link = NULL;
	}
};

struct LRU_Q{
    Entry* FirstOut;
    Entry* FirstIn;

    //Structure like a regular waiting line queue,
    //person to go out is at head, 
    //to go in, join queue from the tail

    //FirstOut is the head of the Cache block
    //FirstIn is the tail of the Cache block

    LRU_Q()
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
        //free(dummy);
        
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
		Entry* dummy = FirstOut;
    	
    	if(FirstOut == NULL) //Empty queue, value absent --> return 1
    		return TRUE;

    	while (dummy != NULL){  // check if value exists in the queue
    		if ((dummy->data) == value){
    			return FALSE; // Value present in the queue return --> 0
    		}    	
    		dummy = dummy->next;
    	}
    	return TRUE; //Value checked and absent, return --> 1
    		
    }
    void Popqueue(string value){

    	if(FirstOut == NULL || FirstOut->next == NULL)
    		return;

    	Entry *dummy1 = FirstIn; //tracker

    	if(dummy1 ->data == value){
    		FirstIn = FirstIn ->next;
            //free(dummy1);
        }
    	Entry *dummy2 = FirstOut;//traverser
    	while ((dummy2->next) != NULL){
    		if((dummy2 ->next->data) == value){
    			dummy2 ->next = dummy2->next->next;
                //free(dummy2->next);
    		}
    		dummy2 = dummy2->next;
    	}
    }
    //In LRU replacement policy, the Enqueue operation will
    //always be followed by the Dequeue operation whenever the cache limit is full
};

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
            if ((dummy->vData) == value){
                return FALSE; // Value present in the queue return --> 0
            }       
            dummy = dummy->link;
        }
        return TRUE; //Value checked and absent, return --> 1
            
    }
};

void LRU(string filename, int CacheLines){

	string line;
	//creating object for LRU
	LRU_Q LRU_queue;
	VictimCache vc;

	string sub;
	string ofName = "19122002_LRU_";
	sub = filename;
	sub.erase((sub.end() - 4),sub.end());
	ofName.append(sub);
	ofName.append("_");
	ofName.append(to_string(CacheLines));
	ofName.append(".txt");

	ifstream InFile;
	ofstream OutFileLRU;

	OutFileLRU.open(ofName, ios::out | ios::trunc);
	OutFileLRU << "Due to unknown mechanism, i am unable\nto print stats at the top of the page, please scroll down to the bottom where the stats\nhave been appended"<<endl <<endl;

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
				if (LRU_queue.Readqueue(word)){ //miss code --Executed only when the cache
					misscount++; 				 // does not hold the value were looking for

					if (CacheLines > 0){
						//Executed when the cache is not full
						OutFileLRU <<"Miss"<<endl;
						LRU_queue.Enqueue(word);
						CacheLines--;
						comp_miss++;
						vc.Add(word);

					}
					else{
						//Executed when the cache is full, two types of misses are possible
						//Compulsary if miss in Victim cache
						//capacity if hit in Victim cache
						OutFileLRU <<"Miss"<<endl;
						LRU_queue.Enqueue(word);
						LRU_queue.Dequeue();
						if(vc.Read(word)){
							vc.Add(word);
							comp_miss++;
						}
						else{
							OutFileLRU <<"Miss"<<endl;
							capacity_miss++;
						}
					}
				}
				else{//LRU Hitcode

					OutFileLRU <<"Hit"<<endl;
					LRU_queue.Popqueue(word);
					LRU_queue.Enqueue(word);

					hitcount++;
				}
			}
		}while(ss);
		if(InFile.eof())
			break;
	}
	
	
	OutFileLRU<< endl<<"Total Accesses : "<< mastercount<<endl;
	OutFileLRU<< "Total Misses : " << misscount << endl;
	OutFileLRU<< "Total Hits : "<< hitcount <<endl;
	OutFileLRU<< "Compulsary Misses : "<< comp_miss<<endl;
	OutFileLRU<< "Capacity Misses : "<< capacity_miss <<endl;
	OutFileLRU.close();
}

int main(int argc, char* argv[]){

	string RepPolicy = argv[1];
	string InputFileName = argv[2];
	stringstream Cache_lines(argv[3]);
	int cl = 0;
	Cache_lines >> cl;

	LRU(InputFileName, cl);
	return 0;
}

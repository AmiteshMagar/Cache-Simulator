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
int cl=0;

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
};

//Defining the nodes for our index table
class indexLine{
public:
	string iData;
	int lastOcc;
	indexLine* next;
	indexLine(string value, int occur){
		iData = value;
		lastOcc = occur;
		next = NULL;
	}
};

//Defining index table for OPTIMAL cache
struct IndexTable{
	indexLine *FirstOut, *FirstIn;


	IndexTable()
    {
        FirstOut =NULL;
        FirstIn = NULL;
    }

	//simple function to add lines into your index table
	void Addition(string value, int posn){
		indexLine *dummy = new indexLine(value, posn);
		if(FirstIn == NULL){
			FirstOut = FirstIn = dummy;
			return;
		}

		FirstIn -> next = dummy;
		FirstIn = dummy;
	}
	//simple function to check if a line exists using the string associated value
	int Reader(string value){
		indexLine* dummy = FirstOut;
    	
    	if(FirstOut == NULL) //Empty queue, value absent --> return 1
    		return TRUE;

    	while (dummy != NULL){  // check if value exists in the queue
    		if ((dummy->iData) == value){
    			return FALSE; // Value present in the queue return --> 0
    		}    	
    		dummy = dummy->next;
    	}
    	return TRUE; //Value checked and absent, return --> 1	
    }

    void Popper(string value){

    	if(FirstOut == NULL || FirstOut->next == NULL)
    		return;

    	indexLine *dummy1 = FirstIn; //tracker

    	if(dummy1 ->iData == value)
    		FirstIn = FirstIn ->next;

    	indexLine *dummy2 = FirstOut;//traverser
    	while ((dummy2->next) != NULL){
    		if((dummy2 ->next->iData) == value){
    			dummy2 ->next = dummy2->next->next;
    		}
    		dummy2 = dummy2->next;
    	}
    }
    int PointPosition(string value){
    	if(FirstOut == NULL)
    		return -1;

    	indexLine *dummy = FirstOut;
    	while(dummy != NULL){
    		if( dummy->iData == value){
    			return dummy->lastOcc;
    		}
    	}
    	return -1;
    	
    }
};

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
            if ((dummy->vData) == value){
                return FALSE; // Value present in the queue return --> 0
            }       
            dummy = dummy->link;
        }
        return TRUE; //Value checked and absent, return --> 1           
    }
};

//Defining unique data structure for LRU Cache
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
//Defining unique data structure for FIFO cache
struct Fifo_Q{
    Entry* FirstOut;
    Entry* FirstIn;

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
		Entry* dummy = FirstOut;
    	
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

//Defining unique data structure for OPTIMAL Cache
struct OPTI_Q{
	Entry* FirstOut;
    Entry* FirstIn;

    //Structure like a regular waiting line queue,
    //person to go out is at head, 
    //to go in, join queue from the tail

    //FirstOut is the head of the Cache block
    //FirstIn is the tail of the Cache block

    OPTI_Q()
    {
        FirstOut =NULL;
        FirstIn = NULL;
    }

    //Function for removing a node from cache LL
    void Dequeue(IndexTable id){

    	if(FirstOut == NULL)
    		return;

        Entry *dummy = FirstOut;
        int max =0;
        max = id.PointPosition(dummy->data);
        cout << "---"<<max<< " Inside dequeue" << endl;
        dummy = dummy->next;
        while( dummy != NULL){
        	if((id.PointPosition(dummy->data)) > max){
        		max = id.PointPosition(dummy->data);
        		cout << "---"<<max <<endl;
        	}
        	dummy = dummy->next;
        }
        Entry *dummy2 = FirstOut;
        while(dummy2 != NULL){
        	if((id.PointPosition(dummy2->data) == max) /*|| (id.PointPosition(dummy2->data)<mastercount)*/){
        		dummy2->next = dummy2->next->next;
        		return;
        	}
        	else
        		dummy2 = dummy2->next;
    	}
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
};

//Function for executing LRU Replacement policy
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
	ofName.append(".out");

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
	ofName.append(".out");

	ifstream InFile;
	ofstream OutFileFIFO;

	OutFileFIFO.open(ofName);
	OutFileFIFO <<endl;
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
						OutFileFIFO <<"Miss"<<endl;

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
							OutFileFIFO <<"Miss"<<endl;
						}
						else{
							capacity_miss++;
							OutFileFIFO <<"Miss"<<endl;
						}
					}
				}
				else{
					hitcount++;
					OutFileFIFO <<"Hit"<<endl;
				}
			}
		}while(ss);
		if(InFile.eof())
			break;
	}
	OutFileFIFO.seekp(0, ios::beg);
	OutFileFIFO<< "Total Accesses : "<< mastercount<<endl;
	OutFileFIFO<< "Total Misses : " << misscount << endl;
	OutFileFIFO<< "Total Hits : "<< hitcount <<endl;
	OutFileFIFO<< "Compulsary Misses : "<< comp_miss<<endl;
	OutFileFIFO<< "Capacity Misses : "<< capacity_miss <<endl;
	OutFileFIFO.close();
}

//Function for executing OPTIMAL strategy of cache entry replacement
void OPTIMAL(string filename, int CacheLines){

	IndexTable id;
	ifstream InputFile;
	int datacount = 0;
	string line;

	int LineReg = CacheLines;

	string sub;
	string ofName = "19122002_OPTIMAL_";
	sub = filename;
	sub.erase((sub.end() - 4),sub.end());
	ofName.append(sub);
	ofName.append("_");
	ofName.append(to_string(CacheLines));
	ofName.append(".out");
	

	InputFile.open(filename);

	while(InputFile){
		getline(InputFile, line);
		stringstream ss(line);
		do{
			string word;
			ss >> word;
			if((word != "") && (word != " ")){

				if(id.Reader(word)){//absent in index table
					id.Addition(word, datacount);
				}
				else{//Index table hit code
					id.Popper(word);
					id.Addition(word, datacount);
				}
				datacount++;
			}
		}while(ss);
		if(InputFile.eof())
			break;
	}
	InputFile.close();
	//print value of index table
	indexLine *n = id.FirstOut;

    while(n != NULL){
        cout << n->iData << " - and position - "<< n->lastOcc << endl;
        n = n-> next;}

	//Code executes perfectly upto this point

	string line2;
	OPTI_Q OPTI_queue;
	VictimCache vc;

	ifstream InFile;
	ofstream OutFileOPTI;

	OutFileOPTI.open(ofName, ios::out | ios::trunc);
	OutFileOPTI << "Due to unknown mechanism, i am unable\nto print stats at the top of the page, please scroll down to the bottom where the stats\nhave been appended"<<endl <<endl;

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
				if (OPTI_queue.Readqueue(word)){ //miss code --Executed only when the cache
					misscount++; 				 // does not hold the value were looking for

					if (CacheLines > 0){
						//Executed when the cache is not full
						OutFileOPTI <<word<<"  Miss"<<endl;
						OPTI_queue.Enqueue(word);
						CacheLines--;
						comp_miss++;
						vc.Add(word);

					}
					else{
						//Executed when the cache is full, two types of misses are possible
						//Compulsary if miss in Victim cache
						//capacity if hit in Victim cache
						OutFileOPTI <<word<<"  Miss"<<endl;
						OPTI_queue.Enqueue(word);
						OPTI_queue.Dequeue(id);
						if(vc.Read(word)){
							vc.Add(word);
							comp_miss++;
						}
						else{
							OutFileOPTI <<word<<"  Miss"<<endl;
							capacity_miss++;
						}
					}
				}
				else{//OPTI Hitcode

					OutFileOPTI <<word<<" Hit"<<endl;
					OPTI_queue.Popqueue(word);
					OPTI_queue.Enqueue(word);

					hitcount++;
				}
			}
		}while(ss);
		if(InFile.eof())
			break;
	}
	OutFileOPTI<< endl<<"Total Accesses : "<< mastercount<<endl;
	OutFileOPTI<< "Total Misses : " << misscount << endl;
	OutFileOPTI<< "Total Hits : "<< hitcount <<endl;
	OutFileOPTI<< "Compulsary Misses : "<< comp_miss<<endl;
	OutFileOPTI<< "Capacity Misses : "<< capacity_miss <<endl;
	OutFileOPTI.close();

}

//driver code
int main(int argc, char* argv[]){
	
	string RepPolicy = argv[1];
	string InputFileName = argv[2];
	stringstream Cache_lines(argv[3]);
	Cache_lines >> cl;
	
	if(RepPolicy.compare("LRU") == 0)
	{
		LRU(InputFileName, cl);
	}
	else if (RepPolicy.compare("FIFO") == 0)
	{
		FIFO(InputFileName, cl);
	}
	else if (RepPolicy.compare("OPTIMAL") == 0)
	{
		OPTIMAL(InputFileName, cl);
	}
	else
		cout << "Incorrect Replacement Policy entered" << endl;
	


	return 0;

}
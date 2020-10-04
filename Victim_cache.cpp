#define FALSE 0
#define TRUE 1

#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
#include<sstream>

using namespace std;

class Node{
public:
    string data;
    Node* next;
    Node(string val){
        data = val;
        next = NULL;
    }
};

struct VictimCache{
    Node* vHead;
    Node* vTail;
    VictimCache()
    {
        vHead =NULL;
        vTail = NULL;
    }
    
    void Add(string value){
        Node *temp = new Node(value);

        if(vTail == NULL){
            vHead = vTail = temp;
            return;
        }

        vTail -> next = temp;
        vTail = temp;
    }
    int Read(string value){
        Node* dummy = vHead;
        
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


int main(){
    VictimCache vc;
    string str = "x[0] y[2] j[9] x[0] y[1]";

    istringstream ss(str);
    do{
        string word;
        ss >> word;
        if(word !="" && word != " "){
            if(vc.Read(word)){
                vc.Add(word);
                cout << word<<" - data had not occured previously, compulsary miss" << endl;
            }
            else
                cout << word << " - data was recorded previosly, capacity miss" << endl;
        }        
    }while(ss);

    //Code preserves unique object logic
return 0;
}
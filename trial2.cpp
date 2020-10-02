#include<bits/stdc++.h>
#include<sstream>
#include<iostream>
#include<algorithm>

using namespace std;

int main(int argc, char* argv[]){
	
	ifstream InFile;
	InFile.open("sample.txt");
	string str ;

	while(InFile){
		getline(InFile, str);
		istringstream ss(str);
		do{
			string word;
			ss >> word;
			if(word != "" && word !=" "){
				//Cache Manipulation code goes here
				
				cout << word << endl;
			}
		}while(ss);
		if(InFile.eof())
			break;
	}

	//String stream method
	/*
	do{
		string word;
		ss >> word;
		if(word != ""){
		
			//Cache manipulation code goes here

		}
	}while(ss);*/


	/*--Normal method--/
	string word = "";
	char check;
	
	for(int i=0; i<len; i++){
		check = str[i];
		
		if(check != ' ')
			word = word + check;
		else if(check == ' ' || check == '\0'){
			cout << word << endl;
			word = "";
		}
	}*/

/*
	str.erase(remove(str.begin(),str.end(),' '), str.end());
	char ch = str[1];
	cout << str <<endl;
	cout << ch << endl;*/

	return 0;
}
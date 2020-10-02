#include<iostream>
#include<fstream>

using namespace std;

int main(){
	//fstream fio;

	ifstream infile;

	string line="";

	//fio.open("sample.txt", ios::app | ios::in);
	infile.open("sample.txt");

	cout << "Reading from the file" << endl << endl;

	while(infile){
		getline(infile, line);
		cout << line << endl;
		if (infile.eof())
			break;
	}

	infile.close();

	// ios::in reads a file for reading
	// ios:: our opens a file for writing into it
	// ios::app opens a file and appends all the inputs at its end, it also does not delete presaved text
	// ios::ate opens the file and moves the control to the end of the file
	// ios::trunc removes the data that already exists in a file

	//Entering data to be stored into the file 

	//Step for recording OUTPUT.
/*
	while(fio){
		getline(cin, line);
		if(line == "-1")
			break;

		fio << line << endl;
	}*/

	//Reading data from a given file. We still use the getline() feature

	//Step for reading INPUT

/*
	fio.seekg(0, ios::beg);

	while(fio){
		getline(fio, line);

		cout << line << endl;
	}

	fio.close();
*/
	return 0;
}
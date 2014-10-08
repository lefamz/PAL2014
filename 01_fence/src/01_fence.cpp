//============================================================================
// Name        : 01_fence.cpp
// Author      : Michal Zajačík
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "01_fence.hpp"




int main() {

	int nNodes;
	string line;

#if DEBG

	ifstream myfile("examples/01.txt");

	if(myfile.is_open()){
		myfile >> nNodes;
		cout << nNodes << endl;

		int array[2][nNodes];

		getline(myfile,line);

		for(int i = 0;i<nNodes;i++){
			getline(myfile,line);
			cout << "newLine: " << endl;
			stringstream ss;
			int digit;
			char buff[10];
			ss << line;

			int pos = 0;
			while(ss.getline(buff,10,' ')){

				digit=atoi(buff);
				cout << "Digit: "<< digit << endl;
				array[pos][i]=digit;
				pos++;
			}

		}
		myfile.close();
	}
#else
	cin >> nNodes;
	cout << "nNodes: " << nNodes;
	int array[2][nNodes];

	getline(cin,line);

	for(int i=0;i<nNodes;i++){
		getline(cin,line);
		cout << "newLine: " << endl;

		stringstream ss;
		ss << line;

		int digit;
		char buff[10];

		int pos = 0;
		while(ss.getline(buff,10,' ')){
			digit=atoi(buff);
			cout << "Digit: "<< digit << endl;
			array[pos][i]=digit;
			pos++;
		}
	}

#endif



	return 0;
}

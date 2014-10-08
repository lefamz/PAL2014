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
	int **array;


#if DEBG

	ifstream myfile("examples/01.txt");

	if(myfile.is_open()){
		myfile >> nNodes;
	//	cout << nNodes << endl;

		array = new int*[nNodes];

		for(int i=0;i<nNodes;i++){
			array[i] = new int[2];
		}

		getline(myfile,line);

		for(int i = 0;i<nNodes;i++){
			getline(myfile,line);
	//		cout << "newLine: " << endl;
			stringstream ss;
			int digit;
			char buff[10];
			ss << line;

			int pos = 0;
			while(ss.getline(buff,10,' ')){

				digit=atoi(buff);
//				cout << "Digit: "<< digit << endl;
				array[pos][i]=digit;
				pos++;
			}

		}
		myfile.close();
	}
#else
	cin >> nNodes;
	cout << "nNodes: " << nNodes;


	array = new int*[nNodes];

	for(int i=0;i<nNodes;i++){
		array[i] = new int[2];
	}

	getline(cin,line);

	for(int i=0;i<nNodes;i++){
		getline(cin,line);
	//	cout << "newLine: " << endl;

		stringstream ss;
		ss << line;

		int digit;
		char buff[10];

		int pos = 0;
		while(ss.getline(buff,10,' ')){
			digit=atoi(buff);
		//	cout << "Digit: "<< digit << endl;
			array[pos][i]=digit;
			pos++;
		}
	}

#endif

	double dst = 0;
	double d = 0;
	for(int i=0;i<nNodes-1;i++){
		d = dist(array[0][i],array[1][i],array[0][i+1],array[1][i+1]);
	//	cout << d << endl;
		dst+=d;

	}
	d = dist(array[0][nNodes-1],array[1][nNodes-1],array[0][0],array[1][0]);
	dst+= d;

	//cout << d << endl;
	cout << ((int)ceil(5*dst)) << endl;



	return 0;
}

double dist(int x,int y,int w, int z){
	return sqrt(((x-w)*(x-w)) + ((y-z)*(y-z)));
}

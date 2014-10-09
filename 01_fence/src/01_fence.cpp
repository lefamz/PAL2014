//============================================================================
// Name        : 01_fence.cpp
// Author      : Michal Zajačík
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "01_fence.hpp"




int main() {

	unsigned int nNodes;
	string line;
	unsigned int **array;


#if DEBG

	ifstream myfile("examples/01.txt");

	if(myfile.is_open()){
		myfile >> nNodes;

		array = new unsigned int*[nNodes];

		for(unsigned int i=0;i<nNodes;i++){
			array[i] = new unsigned int[2];
		}

		getline(myfile,line);

		for(unsigned int i = 0;i<nNodes;i++){
			getline(myfile,line);
			stringstream ss;
			unsigned int digit;
			char buff[1000];
			ss << line;

			unsigned int pos = 0;
			while(ss.getline(buff,1000,' ')){

				digit=atoi(buff);
				array[i][pos]=digit;
				pos=1;
			}

		}
		myfile.close();
	}
#else
	cin >> nNodes;

	array = new unsigned int*[nNodes];

	for(unsigned int i=0;i<nNodes;i++){
		array[i] = new unsigned int[2];
	}

	getline(cin,line);

	for(unsigned int i=0;i<nNodes;i++){
		getline(cin,line);

		stringstream ss;
		ss << line;

		unsigned int digit;
		char buff[1000];

		unsigned int pos = 0;
		while(ss.getline(buff,1000,' ')){
			digit=atoi(buff);
			array[i][pos]=digit;
			pos=1;
		}
	}

#endif

	double dst = 0;
	double d = 0;
	for(unsigned int i=0;i<nNodes-1;i++){
		d = dist(array[i][0],array[i][1],array[i+1][0],array[i+1][1]);
		dst+=d;

	}
	d = dist(array[nNodes-1][0],array[nNodes-1][1],array[0][0],array[0][1]);
	dst+= d;

	cout << ((int)ceil(5*dst)) << endl;

	for(unsigned int i=0;i<nNodes;i++) delete [] array[i];
	delete [] array;

	return 0;
}

double dist(unsigned int x,unsigned int y, unsigned int w, unsigned int z){
	return sqrt(((x-w)*(x-w)) + ((y-z)*(y-z)));
}

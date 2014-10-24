#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <inttypes.h>
#include <list>
#include <vector>
#include <sstream>
#include <math.h>
#include <algorithm>

#include "definitions.hpp"
#include "classes.hpp"

#define DBG 1

#if DBG
#include <ctime>
//#include <tr1/unordered_map>
#endif
using namespace std;

sint calculateITL(nint,vector<Edge> *);
void controlDump(nint,vector<Edge> *);
void createStructure(sint,nint,vector< list<Edge *> > * ,vector<Edge> *);
void loadData(string,sint &,nint &,vector< list<Edge *> > *,vector<Edge> *);
void deleteData(vector< list<Edge *> > *,vector<Edge > *);
//bool edgeComparator();

#endif /*MAIN_H*/


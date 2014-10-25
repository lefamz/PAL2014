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

#define DBG 0

#if DBG
#include <ctime>
//#include <tr1/unordered_map>
#endif
using namespace std;

sint calculateITL(vector<Edge> *,vector< list<Edge *> > *);
void controlDump(nint,vector<Edge> *);
void createStructure(vector< list<Edge *> > * ,vector<Edge> *);
void loadData(string,sint &,nint &,vector< list<Edge *> > *,vector<Edge> *);
void deleteData(vector< list<Edge *> > *,vector<Edge > *);
//bool edgeComparator();

#endif /*MAIN_H*/


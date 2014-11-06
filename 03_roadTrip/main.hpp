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
#include <limits>

#include "definitions.hpp"
#include "classes.hpp"

#define DBG 1

using namespace std;

void loadData(std::string file, nint& nNNodes, nint& nONodes, nint &nNodes, nint &nEdges,
	      nint &maxDist,nint &home,nint &target,vector<pNN> ** graph,
	      vector<pNN> ** gasGraph,vector<nint> & oysterCities);


#endif /*MAIN_H*/


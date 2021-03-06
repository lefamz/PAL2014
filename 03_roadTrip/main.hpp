#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <inttypes.h>
#include <vector>
#include <queue>
#include <sstream>
#include <limits>

#include "definitions.hpp"

#define DBG 1

using namespace std;

void loadData(std::string file, nint& nNNodes, nint& nONodes, nint &nNodes, nint &nEdges,
	      nint &maxDist,nint &home,nint &target,vector<pNN> ** graph,
	      vector<pNN> ** gasGraph,vector<nint> & oysterCities);

void limitedDijkstra(vector<pNN> [],vector<nint> &,nint,nint,nint,nint);
void dijkstra(vector<pNN> [],vector<nint> &,nint,nint,nint);

#endif /*MAIN_H*/


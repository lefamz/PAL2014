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

#include "definitions.hpp"
#include "classes.hpp"

#define DBG 1

using namespace std;
void loadData(string,sint &,nint &,vector<Node *> *,vector<Edge *> *);
void deleteData(vector<Node *> *,vector<Edge *> *);

#endif /*MAIN_H*/


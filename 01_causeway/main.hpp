#include <iostream>
#include <string>
#include <fstream>
#include <inttypes.h>
#include <vector>
#include <sstream>
#include <math.h>

#include "definitions.hpp"

#ifndef MAIN_H
#define MAIN_H

#include "Node.cpp"

#endif /*MAIN_H*/

#define DBG 1



using namespace std;

mdouble dist(mint,mint,mint,mint);
void deleteNodeVector(vector<Node *> * toDel);
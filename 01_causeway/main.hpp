#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <inttypes.h>
#include <vector>
#include <sstream>
#include <math.h>

#include "definitions.hpp"
#include "Node.cpp"

#define DBG 1


#endif /*MAIN_H*/

using namespace std;

mdouble dist(mint,mint,mint,mint);
void deleteNodeVector(vector<Node *> * toDel);
bool intersects(mint [],mint [],mint [],mint []);
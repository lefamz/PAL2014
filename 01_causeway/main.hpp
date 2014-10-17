#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <inttypes.h>
#include <list>
#include <sstream>
#include <math.h>
#include <bitset>

#include "definitions.hpp"
#include "Node.cpp"

#define DBG 0


#endif /*MAIN_H*/

using namespace std;

mdouble dist(mint,mint,mint,mint);
bool possible(mint ****,list<mint> *,mint);
void deleteNodeList(list<Node *> * toDel);
mint intersects(mint [],mint [],mint [],mint []);
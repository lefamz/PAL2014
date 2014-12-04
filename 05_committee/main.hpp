#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <inttypes.h>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <string>
#include <set>
#include <stack>
#include <queue>

#include "definitions.hpp"
#include "classes.hpp"

#define DBG 1

using namespace std;

void insertIntoPrefixTree(CharNode & root,string s,nint D);
void printTree(CharNode & root);
nint calculateSupport(CharNode & root,nint D, nint K, nint aSize);
#endif /*MAIN_H*/


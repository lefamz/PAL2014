#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <inttypes.h>
#include <vector>
#include <queue>
#include <sstream>
#include <limits>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>

#include "definitions.hpp"
#include "classes.hpp"

#define DBG 1

using namespace std;

//string findLexSmallest2(string str);
string findLexSmallest(string str);
string findReprez(vector<nint> &,vector<string> &);
string vec2String(vector<string>);

#endif /*MAIN_H*/


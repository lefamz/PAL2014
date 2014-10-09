#include "main.hpp"
#include <algorithm>

class Node{
  
public:
  Node(mint level,mdouble l);
  
  // ids of coords in this set
  std::vector<mint> *ids;
  mdouble len;
  
  void cpyIds(std::vector<mint> * oldIDs);
};
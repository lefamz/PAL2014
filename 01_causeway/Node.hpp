#ifndef NODE_HPP
  #include "definitions.hpp"
  #include <algorithm>
  #include <list>
  #include <bitset>
  
  using namespace std;
#endif

class Node{
  
public:
  Node(mdouble l);
  ~Node();
  
  // mask of ids of not assigned  ids avalable for next set
  mint avNodesMask;
  // mask ids of coords in this set
  std::list<mint> * nodes;
  
  void printNode();
  
  mdouble len;
};
#ifndef NODE_HPP
  #include "definitions.hpp"
  #include <algorithm>
  #include <vector>
#endif

class Node{
  
public:
  Node(mdouble l);
  ~Node();
  
  // mask of ids of not assigned  ids avalable for next set
  mint avNodesMask;
  // mask ids of coords in this set
  mint idsMask;
  
  mdouble len;
};
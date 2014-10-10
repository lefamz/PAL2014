#ifndef NODE_HPP
  #include "definitions.hpp"
  #include <algorithm>
  #include <vector>
#endif

class Node{
  
public:
  Node(mint level,mdouble l,mint nNodes);
  ~Node();
  
  // ids of not assigned  ids avalable for next set
  std::vector<mint> * availableIDs;
  // ids of coords in this set
  std::vector<mint> * ids;
  mdouble len;
  
  void cpyIds(std::vector<mint> * oldIDs);
  void cpyAvaiIds(std::vector<mint> * oldAvaiIDs);
};
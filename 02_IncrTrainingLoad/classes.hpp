#ifndef CLASSES_HPP
#define CLASSES_HPP

#include "definitions.hpp"
#include <iostream>
#include <list>

using namespace std;

class Edge{
public:
  Edge(sint node1,sint node2,sint l){
    if(node1 > node2){
      leftNode=node2;
      rightNode=node1;
    } else {
      leftNode=node1;
      rightNode=node2;
    }
    
    ITL = 0;
    estimatedITL=0;
    len = l;
    
  }
  
  bool operator < (const Edge & e) const {
    //std::cout << "CMP";
    return this->len > e.len;
  }
  
  sint leftNode,rightNode;
  sint ITL,estimatedITL;
  sint len;
  list<Edge *> leftEdges,rightEdges;
};
#endif //CLASSES_HPP

#ifndef CLASSES_HPP
#define CLASSES_HPP

#include "definitions.hpp"
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
    
    ITL=0;
    len = l;
  }
  
  nint id;
  sint leftNode,rightNode;
  sint ITL;
  sint len;
  list<Edge *> leftEdges,rightEdges;
};

class Node{
public:
  Node(sint i){
    id = i;
  }
  sint id;
  list<Edge *> incEdges;
};
#endif //CLASSES_HPP

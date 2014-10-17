#include "Node.hpp"

Node::Node(mdouble l){
    len = l;  
    nodes = new std::list<mint>();
}

Node::~Node(){
 //std::cout << "Destr" << std::endl;
  delete nodes;
}

void Node::printNode(){
  list<mint>::iterator it = nodes->begin();
  cout << "Len: " << len << " avnodes: " << (bitset<16>)avNodesMask << " Nodes: ";
  for(it;it!=nodes->end();++it){
    cout << *it << " ";
  }
  cout << endl;
}

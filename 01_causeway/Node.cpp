#include "Node.hpp"

Node::Node(mint level, mdouble l){
    ids = new std::vector<mint>(level);
    len = l;
    
    (*ids)[0]=2;
    (*ids)[1]=2;
}

void Node::cpyIds(std::vector<mint> * oldIDs){
  std::copy(oldIDs,oldIDs+oldIDs->size(),this->ids);
}
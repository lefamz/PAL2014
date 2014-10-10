#include "Node.hpp"

Node::Node(mint level, mdouble l,mint nNodes){
    availableIDs = new std::vector<mint>(nNodes);
    
    for (mint i=0;i<nNodes;i++){
      (*availableIDs)[i]=i;
    }
    
    ids = new std::vector<mint>(level+1);
    len = l;
    
}

Node::~Node(){
  std::cout << "Destructor Node called .. " << std::endl;
  delete availableIDs;
  delete ids;
}


void Node::cpyIds(std::vector<mint> * oldIDs){
  std::copy((*oldIDs).begin(),(*oldIDs).end(),(*this->ids).begin());
}

void Node::cpyAvaiIds(std::vector<mint> * oldAvaiIDs){
  std::copy((*oldAvaiIDs).begin(),(*oldAvaiIDs).end(),(*this->availableIDs).begin());
}

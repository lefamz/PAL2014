#ifndef CLASSES_HPP
#define CLASSES_HPP

#include "definitions.hpp"

class CharNode{
public:
  // character
  sint ch=(sint)'!';
  nint level=0;
  nint accepted=0;
 // bool hasChildren = false;
  
  CharNode * children[27]={ 0 };
  
  CharNode(){
  }
  
  CharNode(sint c){
    ch =c;
  }
};
#endif //CLASSES_HPP
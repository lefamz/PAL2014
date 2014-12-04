#ifndef CLASSES_HPP
#define CLASSES_HPP

#include "definitions.hpp"

class CharNode{
public:
  // character
  sint ch;
  nint level;
  nint accepted;
  
  CharNode * children[27];
  
  CharNode(){
    ch = '!';
    level = 0;
  }
  
  CharNode(sint c){
    ch =c;
  }
};
#endif //CLASSES_HPP
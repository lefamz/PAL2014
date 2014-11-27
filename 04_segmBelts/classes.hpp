#ifndef CLASSES_HPP
#define CLASSES_HPP

#include "definitions.hpp"
#include <string>

class MyChar{
public:
  // character
  sint ch;
  // from .. index of original letter, index ... index of this letter
  nint from,index;
  // going in the word to the right, or to the left?
  bool rDir;
  
  MyChar(){}
  
  MyChar(bool dir, sint c, nint i, nint f){
    rDir = dir;
    ch =c;
    index=i;
    from=f;
  }
  
  bool operator<(const MyChar & o) const{
    return ((this->ch) > o.ch);
  }
};

class MyString{
public:
  std::string str;
  nint from, index;
  bool rDir;
  
  MyString(){};
  
  MyString(bool dir,std::string s,nint i, nint f){
    str = s;
    rDir = dir;
    index=i;
    from=f;
  }
  
  bool operator<(const MyString & o) const{
    return ((this->str) > o.str);
  }
};
#endif //CLASSES_HPP
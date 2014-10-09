#include "main.hpp"

#ifndef MAIN_H
#define MAIN_H

#include "Node.cpp"

#endif /*MAIN_H*/

int main(int argc, char **argv) {
    
  mint maxLen = 0;
  mint nNodes = 0;
  mint **coords;
  
  Node root(2,2);
  
  std::vector<mint> * p;
  p = root.ids;
  
  cout << (*p)[0] << " " << (*p)[1] << endl;
  
  std::vector<mint> * arr = new std::vector<mint>(2);
  
  (*arr)[0]=1;
  (*arr)[1]=2;
  
  root.cpyIds(arr);
  
  cout << (*p)[0] << " " << (*p)[1] << endl;

#if DBG
    cout << "Hello, world!" << sizeof(mint) << endl;
#else
#endif
    
    
#if DBG
  ifstream fileStream ("../examples/pub01.out");
  string buff;
  getline(fileStream,buff);
  cout << "Correct result: " << buff << endl;
  fileStream.close();
#endif

  return 0;
}

#include "main.hpp"

int main(int argc, char **argv) {
    
  mint maxLen = 0;
  mint nNodes = 0;
  mint ** coords;
  mdouble ** dists;
  
 /* Node root(2,2);
  
  std::vector<mint> * p;
  p = root.ids;
  
  cout << (*p)[0] << " " << (*p)[1] << endl;
  
  std::vector<mint> * arr = new std::vector<mint>(2);
  
  (*arr)[0]=1;
  (*arr)[1]=2;
  
  root.cpyIds(arr);
  
  cout << (*p)[0] << " " << (*p)[1] << endl; */

  string s;
  char buff[6];
  stringstream ss;
  
#if DBG
  ifstream inFile ("../examples/pub01.in");  
  getline(inFile,s);    
#else
  getline(cin,s);
#endif
  ss << s;
  ss.getline(buff,6,' ');
  nNodes = (mint)(atoi(buff));
    
 // TODO buff se mozna musi  po pouziti zas smazat
    
  ss.getline(buff,6,' ');
  maxLen = (mint)(atoi(buff));
    
  cout << nNodes << " " << maxLen << endl;
  
  coords = new mint * [nNodes];
  
  for(mint i=0;i<nNodes;i++){
    coords[i] = new mint[2];
  }
  
  dists = new mdouble * [nNodes];
  
  for(mint i=0;i<nNodes;i++){
    dists[i] = new mdouble[nNodes];
  }
  
#if DBG
  for(mint i=0;i<nNodes;i++){
    s.clear();
    ss.clear();
    
    getline(inFile,s);
    ss << s;
    
    ss.getline(buff,6,' ');
    coords[i][0] = (mint)(atoi(buff));
    ss.getline(buff,6,' ');
    coords[i][1] = (mint)(atoi(buff));
  }
  
  inFile.close();
  
#else
  for(mint i=0;i<nNodes;i++){
    s.clear();
    ss.clear();
    
    getline(cin,s);
    ss << s;

    ss.getline(buff,6,' ');
    coords[i][0] = (mint)(atoi(buff));
    ss.getline(buff,6,' ');
    coords[i][1] = (mint)(atoi(buff));
  }
#endif
    
#if DBG
  ifstream fileStream ("../examples/pub01.out");
  s.clear();
  getline(fileStream,s);
  cout << "Correct result: " << s << endl;
  fileStream.close();
#endif
  
/*  for(mint i=0;i<nNodes;i++){
    for(mint j=0;j<2;j++){
      cout << coords[i][j] << " ";
    }
    
    cout << endl;
  }
*/  

  for(mint i=0;i<nNodes;i++){
    for(mint j=0;j<nNodes;j++){
      if(j>i){
	dists[i][j]=dist(coords[i][0],coords[i][1],coords[j][0],coords[j][1]);
      } else if (j<i) {
	dists[i][j] = dists[j][i];
      } else {
	dists[i][i]=0;
      }
    }
  }
  
  /*for(mint i=0;i<nNodes;i++){
    for(mint j=0;j<nNodes;j++){
      cout << dists[i][j] << " ";
    }
    cout << endl;
  }*/
  
  vector<Node *> * oldGen;
  oldGen = new vector<Node *>(nNodes);
  vector<Node *> * newGen;
  
  mint level = 0;
  
  for(mint i = 0;i<nNodes;i++){
    (*oldGen)[i]= new Node(0,(mdouble)0,nNodes);
  }
  /*
  while(level<nNodes){
    
   // newGen = new vector<Node *>(pow(nNodes,level));
  }
  */
  
  for(mint i=0;i<nNodes;i++) delete [] coords[i];
  for(mint i=0;i<nNodes;i++) delete [] dists[i];
  
  delete [] dists;
  delete [] coords;
  
  deleteNodeVector(oldGen);
  
  return 0;
}

mdouble dist(mint x,mint y,mint w,mint z){
  return sqrt(((x-w)*(x-w)) + ((y-z)*(y-z)));
}

void deleteNodeVector(vector<Node *> * toDel){
  for(mint i = 0; i < (*toDel).size();i++){
    delete (*toDel)[i];
  }
  
  delete toDel;
}
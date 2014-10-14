#include "main.hpp"

int main(int argc, char **argv) {
    
  mint maxLen = 0;
  mint nNodes = 0;
  mint ** coords;
  mdouble ** dists;
  uint8_t ** conflicts;
  
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
  
  mint nEdges = ceil((nNodes*(nNodes-1))/2);
    
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
    (*oldGen)[i]= new Node(0);
  }
  
  uLong oldGenSize = nNodes;
  
  mint x[2];
  mint y[2];
  mint w[2];
  mint z[2];
  
  x[0] = 1; x[1] = 0;
  y[0] = 1; y[1] = 2;
  w[0] = 0; w[1] = 3;
  z[0] = 4; z[1] = 3;
  
  cout << "Intersects: " << intersects(x,y,w,z) << endl;
  
  /*while(level<nNodes){
    oldGenSize = oldGen->size();
    newGen = new vector<Node *>(oldGenSize * (nNodes-level-1));
    level++;
  }*/
  
  
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

bool intersects(mint x[], mint y[], mint w[], mint z[]){
  mdouble denominator = ((x[0] - y[0])*(w[1] - z[1])) - ((x[1] - y[1])*(w[0] - z[0]));
  
  if (denominator == 0) return 0;
  
  mdouble a = ((x[0]*y[1]) - (x[1]*y[0]));
  mdouble b = ((w[0]*z[1]) - (w[1]*z[0]));
  
  mdouble interX = ((a*(w[0] - z[0])) - ((x[0] - y[0])*b))/denominator;
  mdouble interY = ((a*(w[1] - z[1])) - ((x[1] - y[1])*b))/denominator;
  
#if DBG
  cout << "inter x: " << interX << " interY: " << interY << endl;
#endif
  
  mint minA=0,maxA=0,minB=0,maxB=0;
  
  minA=min(x[0],y[0]);
  maxA=max(x[0],y[0]);
  minB=min(x[1],y[1]);
  maxB=max(x[1],y[1]);

#if DBG
  cout << "minX: " << minA << " maxX: " << maxA << endl;
  cout << "minY: " << minB << " maxY: " << maxB << endl;
#endif
  
  bool inFirst = (interX <= maxA) && (interX >= minA) && (interY >= minB) && (interY <= maxB);
  
  minA=min(w[0],z[0]);
  maxA=max(w[0],z[0]);
  minB=min(w[1],z[1]);
  maxB=max(w[1],z[1]);
  
#if DBG
  cout << "minX: " << minA << " maxX: " << maxA << endl;
  cout << "minY: " << minB << " maxY: " << maxB << endl;
#endif
  
  bool inSecond = (interX <= maxA) && (interX >= minA) && (interY >= minB) && (interY <= maxB);
  
  if (inFirst && inSecond) return 1;
  return 0;
}
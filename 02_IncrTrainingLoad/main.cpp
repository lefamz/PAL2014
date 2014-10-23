#include "main.hpp"

int main(int argc, char **argv) {
    string file = "../examples/pub01";
    vector<Node> * nodes = new vector<Node>();
    vector<Edge> * edges = new vector<Edge>();
    
    sint nNodes;
    nint nEdges;
    
    loadData(file,nNodes,nEdges,nodes,edges);
    
    sort(edges->begin(),edges->end());
    
    cout << edges->capacity()<<endl;
    cout << (*edges)[0].leftNode << " "<< (*edges)[0].rightNode << endl;
    
    deleteData(nodes,edges);
}


void loadData(string file, sint & nNodes, nint & nEdges,
	      vector<Node> * nodes,vector<Edge> * edges){
    string s;
    char buff[7];
    stringstream ss;
   
#if DBG
    string inadr = file;
    inadr.append(".in");
    
    ifstream inFile (inadr.data());  
    getline(inFile,s);
#else
    getline(cin,s);
#endif
    ss << s;
    
    ss.getline(buff,5,' ');
    nNodes = (sint)(atoi(buff));
   // nodes->reserve(nNodes);
    
    ss.getline(buff,7,' ');
    nEdges = (nint)(atoi(buff));
   // edges->reserve(nEdges);
    
    ss.clear();
    s.clear();
    
#if DBG
    cout << "nNodes: " << nNodes <<  " nEdges: " << nEdges << endl;
#endif
    for(sint i=0;i<nNodes;i++){
      Node n;
      nodes->push_back(n);
    }
    
    for(nint i=0;i<nEdges;i++){
#if DBG
      getline(inFile,s);      
#else
      getline(cin,s);
#endif
      ss << s;
      
      ss.getline(buff,5,' ');
      sint from = (sint)(atoi(buff));
      
      ss.getline(buff,7,' ');
      sint to = (sint)(atoi(buff));
      
      ss.getline(buff,6,' ');
      sint len = (sint)(atoi(buff));
      
#if DBG
      cout <<"i: " << i << " " << from << " " << to << " "  << len << endl;
#endif
      
      Edge e(from,to,len);
      (*edges).push_back(e);
      
      s.clear();
      ss.clear();

    }
    
#if DBG
      inFile.close();
#endif   
}

void deleteData(std::vector< Node >* n, std::vector< Edge >* e){
  sint c = (*n).capacity();
  nint c2 = (*e).capacity();
  
 // for(sint i=0;i<c;i++) delete (*n)[i];
 // for(nint i=0;i<c2;i++) delete (*e)[i];
  
  delete n;
  delete e;
}

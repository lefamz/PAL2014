#include "main.hpp"

int main(int argc, char **argv) {
    string file = "../examples/pub09";
    vector< list<Edge *> > * nodes = new vector< list<Edge *> >();
    vector<Edge> * edges = new vector<Edge>();
    
    sint nNodes;
    nint nEdges;
    
    clock_t begin = clock();
    
    loadData(file,nNodes,nEdges,nodes,edges);    
    createStructure(nNodes,nEdges,nodes,edges);
 //   controlDump(nEdges,edges);
  //  calculateITL(nEdges,edges);
    
   // tr1::unordered_map<string, int> map;
    
    
    clock_t end = clock();
   
   cout << (double)(end-begin)/CLOCKS_PER_SEC << endl;

   
    
    deleteData(nodes,edges);
}

sint calculateITL(nint nEdges,vector<Edge> * edges){
  sint maxITL = 0;
  
  vector<Edge>::iterator it;
  
  vector<Edge *> currITL;
  list<Edge *> front;
  sint prevNode;
  
  for(it=edges->begin();it!=edges->end();++it){
    Edge e = (*it);
    front.push_back(&e);
  }
  
 /**/ while(!front.empty()){
    Edge e = *(front.front());
    front.pop_front();
    
    list<Edge *>::iterator ofspring;
    for(ofspring=e.)
    
  }/**/
  
  
  
}

void controlDump(nint nEdges,vector<Edge> * edges){
   /**/  for(int i = 0;i<nEdges;i++) {
      cout << i << " len: " << (*edges)[i].len << endl;
      cout << "left neigh: " << (*edges)[i].leftEdges.size() << endl;
      cout << "right neigh: " << (*edges)[i].rightEdges.size() << endl;
      
     if(i == 2)  cout << (*edges)[i].leftEdges.front()->len << endl;
	
    }/**/
}

void createStructure(sint nNodes,nint nEdges,vector< list<Edge *> > * nodes,vector<Edge> * edges){
  
   
  
   vector<Edge>::iterator it;
   
  /*/ for(it=edges->begin();it!=edges->end();++it){
      Edge * pE = &(*it);
      cout << pE <<  " " << pE->len << endl;;
      
   }
   
   cout << endl;/**/
  /**/   sort(edges->begin(),edges->end());
  
  for(it=edges->begin();it!=edges->end();++it){
      Edge * pE = &(*it);
      (*nodes)[(*pE).leftNode].push_back(pE);
      (*nodes)[(*pE).rightNode].push_back(pE);
     // cout << pE << " " << pE->len <<endl;
   }/**/
   
   for(it=edges->begin();it!=edges->end();++it){
     
     Edge * e = &(*it);
     
     list<Edge *>::iterator ed;
     list<Edge *> neighbours;
     
     neighbours = (*nodes)[e->leftNode];
     for(ed=neighbours.begin();ed!=neighbours.end();++ed){
	if(e->len > (*ed)->len){
	  e->leftEdges.push_back(*ed);
	}
     }
     
     neighbours = (*nodes)[e->rightNode];
     for(ed=neighbours.begin();ed!=neighbours.end();++ed){
	if(e->len > (*ed)->len){
	  e->rightEdges.push_back(*ed);
	}
     }

   }
   
   
}


void loadData(string file, sint & nNodes, nint & nEdges,
	      vector< list<Edge *> > * nodes,vector<Edge> * edges){
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
    nodes->reserve(nNodes);
    
    ss.getline(buff,7,' ');
    nEdges = (nint)(atoi(buff));
    edges->reserve(nEdges);
    
    ss.clear();
    s.clear();
    
#if DBG
  //  cout << "nNodes: " << nNodes <<  " nEdges: " << nEdges << endl;
#endif
    for(sint i=0;i<nNodes;i++){
      list<Edge *> l;
      nodes->push_back(l);
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
    //  cout << from << " " << to << " "  << len << endl;
#endif
      
      Edge e(from,to,len);
      
      (*edges).push_back(e);
      
  /* /  
   //  tady to nejde kvuli tomu sortu! bez nej to tady pujde 
      Edge * pE = &((*edges)[i]);
      
      (*nodes)[from].push_back(pE);
      (*nodes)[to].push_back(pE);/**/
      
      s.clear();
      ss.clear();

    }
    
#if DBG
      inFile.close();
#endif   
}

void deleteData(std::vector< list<Edge *> > * n, std::vector< Edge >* e){
 // sint c = (*n).capacity();
 // nint c2 = (*e).capacity();
  
 // for(sint i=0;i<c;i++) delete (*n)[i];
 // for(nint i=0;i<c2;i++) delete (*e)[i];
  
  delete n;
  delete e;
}

#include "main.hpp"

int main(int argc, char **argv) {
    string file = "../examples/pub08";
    vector< list<Edge *> > * nodes = new vector< list<Edge *> >();
    vector<Edge> * edges = new vector<Edge>();
    
    sint nNodes;
    nint nEdges;
    
   // clock_t begin = clock();
    
    loadData(file,nNodes,nEdges,nodes,edges);    
    createStructure(nodes,edges);
 //   controlDump(nEdges,edges);
    cout << calculateITL(edges,nodes) << endl;
    
   // tr1::unordered_map<string, int> map;
    
    
  //  clock_t end = clock();
   
  // cout << (double)(end-begin)/CLOCKS_PER_SEC << endl;

   
    
    deleteData(nodes,edges);
}

sint calculateITL(vector<Edge> * edges,vector< list<Edge *> > * nodes){
  sint maxITL = 0;
  
  vector<Edge>::iterator edIt;
  list<Edge *>::iterator lIt;
  
  for(edIt=edges->begin();edIt!=edges->end();++edIt){
    sint left = (*edIt).leftNode;
    sint right = (*edIt).rightNode;
    sint len = (*edIt).len;
    
    list<Edge *> lefties = (*nodes)[left];
    list<Edge *> righties = (*nodes)[right];
    
    nint i = 0;
    sint hlp = 0;
    
    for(lIt=lefties.begin();lIt!=lefties.end();++lIt){
      Edge * e = (*lIt);
      if(len > e->len){
	i++;
	if(left == e->leftNode && hlp < e->rightITL){
	  hlp = e->rightITL;
	}
	if (left == e->rightNode && hlp < e->leftITL){
	  hlp = e->leftITL;
	}
      }
    }
    
    if(i>0){
      (*edIt).leftITL = (*edIt).len + hlp;
    } else {
      (*edIt).leftITL=(*edIt).len;
    }
    
    i = 0;
    hlp = 0;
    
    for(lIt=righties.begin();lIt!=righties.end();++lIt){
      Edge * e = (*lIt);
      if(len > e->len){
	i++;
	if(right == e->leftNode && hlp < e->rightITL){
	  hlp = e->rightITL;
	}
	if (right == e->rightNode && hlp < e->leftITL){
	  hlp = e->leftITL;
	}
      }
    }
    
    if(i>0){
      (*edIt).rightITL = (*edIt).len + hlp;
    } else {
      (*edIt).rightITL=(*edIt).len;
    }
    
    if (maxITL < (*edIt).leftITL){
      maxITL = (*edIt).leftITL;
    } else if(maxITL < (*edIt).rightITL){
      maxITL = (*edIt).rightITL;
    }
   // cout << (*edIt).leftITL << " " << (*edIt).rightITL << endl;
    
  }
  
  return maxITL;
}

void controlDump(nint nEdges,vector<Edge> * edges){
   /**/  for(int i = 0;i<nEdges;i++) {
    
	
    }/**/
}

void createStructure(vector< list<Edge *> > * nodes,vector<Edge> * edges){
  
   
  
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
   
 /*  for(it=edges->begin();it!=edges->end();++it){
     
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

   }*/
   
   
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

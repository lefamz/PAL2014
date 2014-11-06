#include "main.hpp"

int main(int argc, char **argv) {
    // petrol limit
    nint maxDist;
    // normal nodes
    nint nNNodes;
    // nodes with Oyster(Petrol station)
    nint nONodes;
    // all nodes together
    nint nNodes;
    nint nEdges;
    // start and end node
    nint home,target;
    
    const nint infinity = std::numeric_limits<nint>::max();
      
    vector<pNN> * origGraph;
    vector<pNN> * gasGraph;
    vector<nint> oysterCities; 
    
    loadData("../examples/pub01",nNNodes,nONodes,nNodes,nEdges,maxDist,home,target,&origGraph,&gasGraph,oysterCities);
    
    return 0;
}
/**/
void loadData(std::string file, nint& nNNodes, nint& nONodes, nint &nNodes, nint &nEdges,
	      nint &maxDist,nint &home,nint &target,vector<pNN> ** graph,
	      vector<pNN> ** gasGraph,vector<nint> & oysterCities){
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
    
    ss.getline(buff,7,' ');
    nONodes = (sint)(atoi(buff));
   
    ss.getline(buff,7,' ');
    nNNodes = (sint)(atoi(buff));
    
    nNodes = nONodes + nNNodes;
    
    *graph = new vector<pNN>[nNodes];
    *gasGraph = new vector<pNN>[nNodes];    
    
    ss.getline(buff,7,' ');
    nEdges = (nint)(atoi(buff));
    
    ss.getline(buff,7,' ');
    maxDist = (nint)(atoi(buff));
    
    ss.getline(buff,7,' ');
    home = (nint)(atoi(buff));
    
    ss.getline(buff,7,' ');
    target = (nint)(atoi(buff));
    
    ss.clear();
    s.clear();
    
#if DBG
    cout << "nNodes: " << nNodes <<  " nEdges: " << nEdges << " nONodes: " << nONodes << " nNNodes: " << nNNodes << " maxDist: " << maxDist
    << " h: " << home << " t: " << target << endl;
#endif
  
    for(nint i=0;i<nONodes;i++){
#if DBG
      getline(inFile,s);      
#else
      getline(cin,s);
#endif
      ss << s;
       
      ss.getline(buff,7,' ');
      nint index = (sint)(atoi(buff));
      oysterCities.push_back(index);  
#if DBG
      cout << index << endl;
#endif    
      s.clear();
      ss.clear();

    }
    
    /*for(int i=0;i<nNodes;i++){
      cout << origGraph[i].size() << endl;
    }*/
    
    for(nint i=0;i<nEdges;i++){
#if DBG
      getline(inFile,s);      
#else
      getline(cin,s);
#endif
      
      ss << s;
      
      ss.getline(buff,7,' ');
      nint from = (nint)(atoi(buff));
      
      ss.getline(buff,7,' ');
      nint to = (nint)(atoi(buff));
      
      ss.getline(buff,7,' ');
      nint len = (nint)(atoi(buff));
      
      (*graph)[from].push_back(pNN(len,to));
      (*graph)[to].push_back(pNN(len,from));
#if DBG
   cout << i << " ---- "<< from << " " << to << " "  << len << endl;
#endif    
      s.clear();
      ss.clear();

    }
#if DBG
      inFile.close();
#endif   
}
/**/

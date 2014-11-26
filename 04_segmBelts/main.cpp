#include "main.hpp"

int main(int argc, char **argv) {
   return 0;
}


void loadData(std::string file, nint& nNNodes, nint& nONodes, nint &nNodes, nint &nEdges,
	      nint &maxDist,nint &home,nint &target,vector<pNN> ** graph,
	      vector<pNN> ** gasGraph,vector<nint> & oysterCities){
    string s;
    nint buffSize = 50;
    char buff[buffSize];
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
    
    ss.getline(buff,buffSize,' ');
    nONodes = (nint)(atoi(buff));
   
    ss.getline(buff,buffSize,' ');
    nNNodes = (nint)(atoi(buff));
    
    nNodes = nONodes + nNNodes;
    
    *graph = new vector<pNN>[nNodes];
    *gasGraph = new vector<pNN>[nNodes];    
    
    ss.getline(buff,buffSize,' ');
    nEdges = (nint)(atoi(buff));
    
    ss.getline(buff,buffSize,' ');
    maxDist = (nint)(atoi(buff));
    
    ss.getline(buff,buffSize,' ');
    home = (nint)(atoi(buff));
    
    ss.getline(buff,buffSize,' ');
    target = (nint)(atoi(buff));
    
    ss.clear();
    s.clear();
    
#if DBG
  /*  cout << "nNodes: " << nNodes <<  " nEdges: " << nEdges << " nONodes: " << nONodes << " nNNodes: " << nNNodes << " maxDist: " << maxDist
    << " h: " << home << " t: " << target << endl;*/
#endif
  
    for(nint i=0;i<nONodes;i++){
#if DBG
      getline(inFile,s);      
#else
      getline(cin,s);
#endif
      ss << s;
       
      ss.getline(buff,buffSize,' ');
      nint index = (nint)(atoi(buff));
      oysterCities.push_back(index);  
#if DBG
   //   cout << index << endl;
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
      
      ss.getline(buff,buffSize,' ');
      nint from = (nint)(atoi(buff));
      
      ss.getline(buff,buffSize,' ');
      nint to = (nint)(atoi(buff));
      
      ss.getline(buff,buffSize,' ');
      nint len = (nint)(atoi(buff));
      
      (*graph)[from].push_back(pNN(to,len));
      (*graph)[to].push_back(pNN(from,len));
#if DBG
  // cout << i << " ---- "<< from << " " << to << " "  << len << endl;
#endif    
      s.clear();
      ss.clear();

    }
#if DBG
      inFile.close();
#endif   
}

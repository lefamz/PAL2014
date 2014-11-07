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
    
    vector<nint> firstStage(nNodes,infinity);
    limitedDijkstra(origGraph,firstStage,home,target,maxDist,nNodes);
    
    if(firstStage[target] < infinity){
      cout << firstStage[target] << endl;
      return 0;
    }
    
    
     /**/for(int i=0;i<nNodes;i++){
      cout << firstStage[i] << endl;
    }/**/
    
    for(nint i =0;i<nONodes;i++){
      nint oCity = oysterCities[i];
      cout << oCity << endl;
      //TODO podminka spatne
      if(firstStage[oCity] < infinity && i!=home){
	gasGraph[home].push_back(pNN(firstStage[oCity],oCity));
	//gasGraph[oCity].push_back(pNN(firstStage[oCity],home));
	vector<nint> secondStage(nNodes,infinity);
	limitedDijkstra(origGraph,secondStage,oCity,target,maxDist,nNodes);
	
	//TODO propojit oysterCities mezi sebou a propojit oysterCities s cilem, dijkstru na vsechny o cities
	for(nint j =0;j<nNodes;j++) cout << secondStage[j] << " ";
	cout << endl;
      }
    }
    
    for(nint i = 0;i<nNodes;i++){
      cout << gasGraph[i].size() << " ";
    }
    cout << endl;
    
    return 0;
}

void limitedDijkstra(vector<pNN> graph[],vector<nint> & dists,nint start,nint target,nint maxDist,nint nNodes){
  // vertexes  
  nint u,v;
  //distances
  nint d,w;
  
  priority_queue< pNN ,vector<pNN>, greater<pNN> > queue;
  
  queue.push(pNN(0,start));
  
  dists[start]=0;
  
  while(!queue.empty()){
    // vertex
    u = queue.top().second;
    //distance
    d = queue.top().first;
    
    queue.pop();
    
    if(dists[u] < d){
      continue;
    }
    
    //     if(u==target) return;
    
    // neighbour search
    for(nint i=0;i<graph[u].size();i++){
      v = graph[u][i].first;
      w = graph[u][i].second;
      
      nint nDist = dists[u] + w;
      
      if(nDist <= maxDist && dists[v] > nDist){
	dists[v] = nDist;
	queue.push(pNN(nDist,v));
      }
    }
  } 
}

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
  //  cout << "nNodes: " << nNodes <<  " nEdges: " << nEdges << " nONodes: " << nONodes << " nNNodes: " << nNNodes << " maxDist: " << maxDist
   // << " h: " << home << " t: " << target << endl;
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
      
      ss.getline(buff,7,' ');
      nint from = (nint)(atoi(buff));
      
      ss.getline(buff,7,' ');
      nint to = (nint)(atoi(buff));
      
      ss.getline(buff,7,' ');
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

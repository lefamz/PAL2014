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
    
    loadData("../examples/pub07",nNNodes,nONodes,nNodes,nEdges,maxDist,home,target,&origGraph,&gasGraph,oysterCities);
    
    vector<nint> firstStage(nNodes,infinity);
    limitedDijkstra(origGraph,firstStage,home,target,maxDist,nNodes);
    
    
  /**/  if(firstStage[target] < infinity){
      cout << firstStage[target] << endl;
      return 0;
    }
    
  /*/  
    cout << "firstStage: ";
     for(int i=0;i<nNodes;i++){
      cout << firstStage[i] << " ";
    }
    cout << endl;
    /**/
    
    for(nint i =0;i<nONodes;i++){
      nint oCity = oysterCities[i];
   //   cout << oCity << endl;
      
      if(oCity!=home && oCity!=target){
	
	if (firstStage[oCity] < infinity){	    
	  gasGraph[home].push_back(pNN(oCity,firstStage[oCity]));
	//gasGraph[oCity].push_back(pNN(firstStage[oCity],home));
	}
	
	vector<nint> secondStage(nNodes,infinity);
	limitedDijkstra(origGraph,secondStage,oCity,target,maxDist,nNodes);
	
	for(nint j =0;j<nONodes;j++){
	  nint oCity2 = oysterCities[j];
	//  cout << secondStage[oCity2] << " ";
	  if (secondStage[oCity2] < infinity){
	    gasGraph[oCity].push_back(pNN(oCity2,secondStage[oCity2]));
	//    gasGraph[oCity2].push_back(pNN(oCity,secondStage[oCity2]));
	  }
	}
	
	if(secondStage[target] < infinity){
	  gasGraph[oCity].push_back(pNN(target,secondStage[target]));
	}
	//cout << endl;
      }
    }
    
   /* for(nint i = 0;i<nNodes;i++){
      cout << gasGraph[i].size() << " ";
    }
    cout << endl;*/
    
    firstStage.assign(nNodes,infinity);
    
    dijkstra(gasGraph,firstStage,home,target,nNodes);
    
    cout << firstStage[target] << endl;
    
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

void dijkstra(vector<pNN> graph[],vector<nint> & dists,nint start,nint target, nint nNodes){
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
    
   // if(u==target) return;
    
    // neighbour search
    for(nint i=0;i<graph[u].size();i++){
      v = graph[u][i].first;
      w = graph[u][i].second;
      
      nint nDist = dists[u] + w;
      
      if(dists[v] > nDist){
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
    nONodes = (nint)(atoi(buff));
   
    ss.getline(buff,7,' ');
    nNNodes = (nint)(atoi(buff));
    
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
       
      ss.getline(buff,7,' ');
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

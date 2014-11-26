#include "main.hpp"

int main(int argc, char **argv) {
   map<string,string> mp;
   mp.insert(pSS("bds","1 2 3"));
   mp.insert(pSS("abcd","1"));
   
   
   
   
   map<string,string>::iterator it;
   string h = mp["abcd"];
   mp.erase("abcd");
   mp.insert(pSS("aaaaaaaaaaa",h.append(" 4")));
   /*it = mp.find("abcd");
   
   if (it != mp.end()){
      
      string h = (*it).second;
      
      mp.erase(it);
      
      mp.insert(pSS("ddddd",h.append(" 4")));

   }*/
   
   it = mp.begin();
   for(it;it!=mp.end();++it){
     cout << (*it).first << " " << (*it).second << endl;
   }
   
   cout << findLexSmallest("aaaa") << endl;
   cout << "aaaa" << endl << endl;
   
   cout << findLexSmallest("aaaba") << endl;
   cout << "aaaab" << endl << endl;
   
   cout << findLexSmallest("baaa") << endl;
   cout << "aaab" << endl << endl;
   
   cout << findLexSmallest("aabaa") << endl;
   cout << "aaaab" << endl << endl;
   
   cout << findLexSmallest("sssdfdgtrrwvafgfdth") << endl;
   cout << "afgfdthsssdfdgtrrwv" << endl << endl;
   
   cout << findLexSmallest("bacdfcab") << endl;
   cout << "abbacdfc" << endl << endl;
   
   cout << findLexSmallest("bbaaccaadd") << endl;
   cout << "aaccaaddbb" << endl << endl;
   return 0;
}

string vec2String(vector<string> vec){
  stringstream ss;
  for(int i = 0;i<vec.size();i++){
    ss << vec[i];
  }
  
  return ss.str();
}

string findReprez(vector<string> disks){
   // array for roots of tree, candidates for beginning of lex smallest word
  vector<sint> smallestDisks;
  
  string smallest = disks[0];
  
  for(nint i = 0;i<disks.size();i++){
    
    string disk = disks[i];
    
    if(disk < smallest){
      smallestDisks.clear();
      smallestDisks.push_back(i);
      smallest = disk;      
    } else if(smallest == disk){
      smallestDisks.push_back(i);
    }
  }
  
  if (smallestDisks.size()==disks.size()) return vec2String(disks);
  
  priority_queue<MyString> queue1;
  priority_queue<MyString> queue2;  
  priority_queue<MyString> * queue;
  /*
  for(nint i = 0;i<smallestLetters.size();i++){
    queue1.push(MyChar(0,c,smallestLetters[i],smallestLetters[i]));
    queue1.push(MyChar(1,c,smallestLetters[i],smallestLetters[i]));
  }
  
  nint level = 0;
  MyChar b;
  
  while(1){
    
    if(level%2 == 0){
      queue = &queue1;
      queue2 = priority_queue<MyChar>();
    } else {
      queue = &queue2;
      queue1 = priority_queue<MyChar>();
    }
    
    b = queue->top();
  //  cout << "level " << level << " New B set: " << (char)b << endl;
    
    if(level == str.size()-1) break;
    
    while(!queue->empty()){
      MyChar c = queue->top();
      //cout << (char)b.ch << " " << (char)c.ch << endl;
      if(b.ch < c.ch){
	break;
      } else {
	nint neighbour;
	sint neighChar;
	if(c.rDir){
	  neighbour = (c.index + 1) % str.size();
	  neighChar = (sint)str[neighbour];
	} else {
	  neighbour = (c.index + (str.size() - 1)) % str.size();
	  neighChar = (sint)str[neighbour];
	}
	
	if(level%2 == 0){
	 queue2.push(MyChar(c.rDir,neighChar,neighbour,c.from));
	// cout << "do levelu: " << level+1 << " " <<  (char) neighChar << " pos " << neighbour << endl;
	} else {
	 queue1.push(MyChar(c.rDir,neighChar,neighbour,c.from));
	// cout << "do levelu: " << level+1 << " " <<  (char) neighChar << " pos " << neighbour << endl;
	}
	
	queue->pop();
     }
      
   //  cout << "b check: " << (char)b << endl;
   }
   
   level++;
  
  }
  
  MyChar start = queue->top();
  stringstream ss;
  
  if (start.rDir){
      ss << str[start.from];
      for (nint i = (start.from + 1) % str.size();i!=start.from;i=(i+1)%str.size()){
	ss << str[i];
      }
  } else {
     ss << str[start.from];
     for (nint i=(start.from + (str.size()-1))%str.size();i!=start.from;i = (i + (str.size()-1))%str.size()){
       ss << str[i];
     }
  }
  
  return ss.str();*/
  
  return 0;
}

string findLexSmallest(string str){
  
  // array for roots of tree, candidates for beginning of lex smallest word
  vector<sint> smallestLetters;
  
  sint c = numeric_limits<sint>::max();
  
  for(nint i = 0;i<str.size();i++){
    
    sint stringChar = (sint)str[i];
    
    if(stringChar < c){
      smallestLetters.clear();
      smallestLetters.push_back(i);
      c = stringChar;      
    } else if(c == stringChar){
      smallestLetters.push_back(i);
    }
  }
  
  if (smallestLetters.size()==str.size()) return str;
  
  priority_queue<MyChar> queue1;
  priority_queue<MyChar> queue2;  
  priority_queue<MyChar> * queue;
  
  for(nint i = 0;i<smallestLetters.size();i++){
    queue1.push(MyChar(0,c,smallestLetters[i],smallestLetters[i]));
    queue1.push(MyChar(1,c,smallestLetters[i],smallestLetters[i]));
  }
  
  nint level = 0;
  MyChar b;
  
  while(1){
    
    if(level%2 == 0){
      queue = &queue1;
      queue2 = priority_queue<MyChar>();
    } else {
      queue = &queue2;
      queue1 = priority_queue<MyChar>();
    }
    
    b = queue->top();
  //  cout << "level " << level << " New B set: " << (char)b << endl;
    
    if(level == str.size()-1) break;
    
    while(!queue->empty()){
      MyChar c = queue->top();
      //cout << (char)b.ch << " " << (char)c.ch << endl;
      if(b.ch < c.ch){
	break;
      } else {
	nint neighbour;
	sint neighChar;
	if(c.rDir){
	  neighbour = (c.index + 1) % str.size();
	  neighChar = (sint)str[neighbour];
	} else {
	  neighbour = (c.index + (str.size() - 1)) % str.size();
	  neighChar = (sint)str[neighbour];
	}
	
	if(level%2 == 0){
	 queue2.push(MyChar(c.rDir,neighChar,neighbour,c.from));
	// cout << "do levelu: " << level+1 << " " <<  (char) neighChar << " pos " << neighbour << endl;
	} else {
	 queue1.push(MyChar(c.rDir,neighChar,neighbour,c.from));
	// cout << "do levelu: " << level+1 << " " <<  (char) neighChar << " pos " << neighbour << endl;
	}
	
	queue->pop();
     }
      
   //  cout << "b check: " << (char)b << endl;
   }
   
   level++;
  
  }
  
  MyChar start = queue->top();
  stringstream ss;
  
  if (start.rDir){
      ss << str[start.from];
      for (nint i = (start.from + 1) % str.size();i!=start.from;i=(i+1)%str.size()){
	ss << str[i];
      }
  } else {
     ss << str[start.from];
     for (nint i=(start.from + (str.size()-1))%str.size();i!=start.from;i = (i + (str.size()-1))%str.size()){
       ss << str[i];
     }
  }
  
  return ss.str();
}

/*
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
/*#endif
  
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
    
/*    for(nint i=0;i<nEdges;i++){
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
*/
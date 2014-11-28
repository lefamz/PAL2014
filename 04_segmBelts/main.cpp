#include "main.hpp"

int main(int argc, char **argv) {
  nint N,D1,D2;
  
  string s;
  
  const nint buffSize = 10000;
  char buff[buffSize];
  stringstream ss;
  
 // cout << ("abs" < "hdh") << endl;
   
#if DBG
    string inadr = "../examples/pub05";
    inadr.append(".in");
    
    ifstream inFile (inadr.data());  
    getline(inFile,s);
#else
    getline(cin,s);
#endif
    ss << s;
   // cout << s << endl;
    ss.getline(buff,buffSize,' ');
    N = (nint)(atoi(buff));
   
    ss.getline(buff,buffSize,' ');
    D1 = (nint)(atoi(buff));
    
    ss.getline(buff,buffSize,' ');
    D2 = (nint)(atoi(buff));
    
    ss.clear();
    s.clear();
    
#if DBG
  //  cout << "N of belts: " << N <<  " D1(len of disk): " << D1 << " D2(n of disks): " << D2 << endl;
#endif


////////////////// data structures

unordered_map<string,nint> hashMap;
vector<vector<nint> > groups;
int groupID = 0;

unordered_map<string,string> diskCache;
unordered_map<string,string>::iterator cacheIterator;

////////////////// end data structures

  
for(nint i=0;i<N;i++){
#if DBG
      getline(inFile,s);      
#else
      getline(cin,s);
#endif
      ss << s;
       
      ss.getline(buff,buffSize,' ');
      nint id = (nint)(atoi(buff));
  
#if DBG
    //  cout << id << endl;
#endif
    string beltReprez;
    vector<string> disks;
    vector<nint> smallestDisks;
      // array<char>
	
    ss.getline(buff,D1+1,' ');
	
    string diskReprez;
	
    cacheIterator=diskCache.find(buff);
    if (cacheIterator == diskCache.end()){
      diskReprez=findLexSmallest(buff);
      diskCache.insert(pair<string,string>(buff,diskReprez));
    } else {
      diskReprez=(*cacheIterator).second;
    }
	
    string smallest=diskReprez;
	
    smallestDisks.push_back(0);
    disks.push_back(diskReprez);
    //   cout << "cmp: " << smallest << " a "<< diskReprez << endl;
    //    cout << diskReprez << endl;
	
    for (nint j = 1;j<D2;j++){
	ss.getline(buff,D1+1,' ');
	cacheIterator=diskCache.find(buff);
	
	if (cacheIterator == diskCache.end()){
	  diskReprez=findLexSmallest(buff);
	  diskCache.insert(pair<string,string>(buff,diskReprez));
	} else {
	  diskReprez=(*cacheIterator).second;
	}
      
	if(diskReprez < smallest){
	  //  cout << "Ding" << endl;
	  smallest=diskReprez;
	  smallestDisks.clear();
	  smallestDisks.push_back(j);
	} else if(smallest==diskReprez){
	  smallestDisks.push_back(j);
	}

      //cout << diskReprez << endl;
      //cout << "smallest: " << smallest << " sz: " << smallestDisks.size() << endl;
    
	disks.push_back(diskReprez);
      }
        
      if(smallestDisks.size()==D2) beltReprez = vec2String(disks);
      else beltReprez = findBeltReprez(smallestDisks,disks);      
      
      //cout << beltReprez << endl;
  
      s.clear();
      ss.clear();
      
      unordered_map<string,nint>::iterator it = hashMap.find(beltReprez);
      
      if(it == hashMap.end()){
	hashMap.insert(pair<string,nint>(beltReprez,groupID));
	groupID++;
	vector<nint> vec;
	vec.push_back(id);
	groups.push_back(vec);
      } else {
	nint grId = (*it).second;
	groups[grId].push_back(id);
      }

}
#if DBG
      inFile.close();
#endif   
      
cout << groups.size() << endl;
  
struct comparator{
  inline bool operator()(const vector<nint> & a, const vector<nint> & b){
  //cout << "cmp " << a.size() << " " << b.size() << endl;
    if (a.size() != b.size()){
      return (a.size() > b.size());
    } else {
      return a[0] < b[0];
    }
  }
    
};

sort(groups.begin(),groups.end(),comparator());
  
for(nint i=0;i<groups.size();i++){
  for(nint j=0;j<groups[i].size();j++){
    cout << groups[i][j] << " ";
  }
  cout << endl;
}
   
return 0;
}

string vec2String(vector<string> vec){
  stringstream ss;
  for(nint i = 0;i<vec.size();i++){
    ss << vec[i];
  }
  
  return ss.str();
}

string findBeltReprez(vector<nint> & smallestDisks, vector<string> & disks){
  
  nint smallest = smallestDisks[0];
  
  priority_queue<MyString> queue1;
  priority_queue<MyString> queue2;  
  priority_queue<MyString> * queue;
  
  for(nint i = 0;i<smallestDisks.size();i++){
    queue1.push(MyString(0,disks[smallest],smallestDisks[i],smallestDisks[i]));
    queue1.push(MyString(1,disks[smallest],smallestDisks[i],smallestDisks[i]));
  }
  
  nint level = 0;
  MyString b;
  
  while(1){
    
    if(level%2 == 0){
      queue = &queue1;
      queue2 = priority_queue<MyString>();
    } else {
      queue = &queue2;
      queue1 = priority_queue<MyString>();
    }
    
    b = queue->top();
  //  cout << "level " << level << " New B set: " << (char)b << endl;
    
    if(level == disks.size()-1 || queue->size()==1) break;
    
    while(!queue->empty()){
      MyString c = queue->top();
      //cout << (char)b.ch << " " << (char)c.ch << endl;
      if(b.str < c.str){
	break;
      } else {
	nint neighbour;
	string neighStr;
	if(c.rDir){
	  neighbour = (c.index + 1) % disks.size();
	  neighStr = disks[neighbour];
	} else {
	  neighbour = (c.index + (disks.size() - 1)) % disks.size();
	  neighStr = disks[neighbour];
	}
	
	if(level%2 == 0){
	 queue2.push(MyString(c.rDir,neighStr,neighbour,c.from));
	// cout << "do levelu: " << level+1 << " " <<  (char) neighChar << " pos " << neighbour << endl;
	} else {
	 queue1.push(MyString(c.rDir,neighStr,neighbour,c.from));
	// cout << "do levelu: " << level+1 << " " <<  (char) neighChar << " pos " << neighbour << endl;
	}
	
	queue->pop();
     }

   }
   
   level++;
  
  }
  
  MyString start = queue->top();
  stringstream ss;
  
  if (start.rDir){
      ss << disks[start.from] << " ";
      for (nint i = (start.from + 1) % disks.size();i!=start.from;i=(i+1)%disks.size()){
	ss << disks[i] << " ";
      }
  } else {
     ss << disks[start.from] << " ";
     for (nint i=(start.from + (disks.size()-1))%disks.size();i!=start.from;i = (i + (disks.size()-1))%disks.size()){
       ss << disks[i] << " ";
     }
  }
  
  return ss.str();
}

string findLexSmallest(string str){
 
  // array for roots of tree, candidates for beginning of lex smallest word
  vector<nint> smallestLetters;
  
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
    
    if(level == str.size()-1 || queue->size()==1) break;
    
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

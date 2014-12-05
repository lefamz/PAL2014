#include "main.hpp"

int main(int argc, char **argv) {
  nint N,D,K,aSize;
  string alphabet;
  
  CharNode root;
  
  string s;
  
  const nint buffSize = 1000000;
  char buff[buffSize];
  stringstream ss;
  
#if DBG  
    string inadr = "../examples/pub04";
    inadr.append(".in");
    
    ifstream inFile (inadr.data());  
    getline(inFile,s); 
#else
    getline(cin,s);
#endif  
    
    ss << s;
    ss.getline(buff,buffSize,' ');
    alphabet = buff;
    
    aSize = alphabet.size();
 
    ss.getline(buff,buffSize,' ');
    N = (nint)(atoi(buff));
   
    ss.getline(buff,buffSize,' ');
    D = (nint)(atoi(buff));
    
    ss.getline(buff,buffSize,' ');
    K = (nint)(atoi(buff));
    
    ss.clear();
    s.clear();
    
#if DBG
    cout << "N of committee: " << N <<  " D(min numbers of committee): " << D << " K(word len): " << K << " alphabet: " << alphabet << " its sz: " << aSize << endl;
#endif
    
    for (nint i = 0;i<N;i++){
#if DBG 
      getline(inFile,s);  
#else
      getline(cin,s);
#endif
      set<string> acceptedWords;
      
      nint nWords = (nint)(atoi(s.data()));
#if DBG
   //   cout << "nWords: " << nWords << endl;
#endif     
      for(nint j = 0;j<nWords;j++){
	ss.clear();
	s.clear();
#if DBG 
	getline(inFile,s);  
	
#else
	getline(cin,s);
#endif	
	//if((int)(s[s.length()-1] - 'a' < 0)){
	   // acceptedWords.insert(s.substr(0,s.length()-1));
	//  s.erase(s.length()-1);
	//  acceptedWords.insert(s.substr(0,s.length()-1));
	//} else {
	//if(s[s.length()-1] == 13) cout << "ding" << endl;
	  acceptedWords.insert(s);
	//}
	 
	
      }
      
      set<string>::iterator it;
      for(it=acceptedWords.begin();it!=acceptedWords.end();++it){
	string str = (*it);
	/**/if(str[str.length()-1] == 13){
	  if((str.size()-1) > K) continue;
	  insertIntoPrefixTree(root,str,D, true);	  
	}
	else{/**/
	  if((str.size()) > K) continue;
	  insertIntoPrefixTree(root,str,D, false);
	}
      }

    }
    
 /*   string l = "abcd";
    string l2 = "abcf";
    string l3 = "abc";
    string l4 = "abcde";
    
    
    insertIntoPrefixTree(root,l3,2);
    insertIntoPrefixTree(root,l,2);
    insertIntoPrefixTree(root,l2,2);
    
    insertIntoPrefixTree(root,l4,2);*/
    
  //  printTree(root);
    
  //  cout << "------------------------" << endl;
    
    cout << calculateSupport(root,D,K,aSize) << endl;
    
    deletePrefixTree(root);
    
  
return 0;
}

void deletePrefixTree(CharNode & root){
  cout << "Not yet implemented!" << endl;
}

nint calculateSupport(CharNode & root,nint D, nint K, nint aSize){
  stack<CharNode> st;
  st.push(root);
  nint res = 0;
  
  while(!st.empty()){
    CharNode cN = st.top();
    st.pop();
    
    if(cN.accepted >= D){
      nint level = cN.level;
      if(level == K){
	res=(res+1) % 100000;
      } else {
	nint hlp = aSize;
	for(nint i=1;i<(K-level);i++){
	
	  hlp = (aSize * hlp) % 100000;
	  
	}
	
	res=(res+hlp) % 100000;
      }
      
      continue;
    }
    
    for(nint i =0;i<27;i++){
      if(cN.children[i]!=0) st.push(*(cN.children[i]));
    }
    
  }
  
  return res;
}

void insertIntoPrefixTree(CharNode & root,string s,nint D, bool strangeChar){
 
  CharNode * node = & root;
  
  nint maxAccepted=0;
  nint sz = 0;
  
  if(strangeChar){
    sz = s.length()-1;
  } else {
    sz = s.length();
  }
  
  for(nint i = 0; i<sz; i++){
	sint c = s[i]-'a';    
	
	if(node->children[c]==0){
	  CharNode * chn = new CharNode(c);
	//  cout << "insert:" << chn->ch <<  endl;
	  chn->level=(node->level)+1;
	  //chn->accepted=0;
	  node->children[c]=chn;
	//  node->hasChildren = true;
	}
	
	node = (node->children[c]);
	
	if(node->accepted >= D){
	  return;
	}
	
	if(maxAccepted < node->accepted){
	  maxAccepted = node->accepted;
	}    
	
  }
    
  node->accepted=maxAccepted+1;
  
  if (node->accepted < D){
      stack<CharNode> st;
      
      for(nint i=0;i<27;i++){
	if(node->children[i]!= 0) st.push(*(node->children[i]));
      }
      
      while(!st.empty()){
	CharNode cN = st.top();
	st.pop();

	if(cN.accepted > 0) cN.accepted++;
	
	for(nint i=0;i<27;i++){
	    if(cN.children[i]!=0){
	      st.push(*(cN.children[i]));
	    }
	}
      }
      
  } else {
    for(nint i=0;i<27;i++) node->children[i]=0;
  }
}

void printTree(CharNode & root){
  queue<CharNode> l1;
  queue<CharNode> l2;
  queue<CharNode> * q;
  
  l1.push(root);
  nint level = 0;
  q = & l1;
  while(!q->empty()){
    
      
    while(!q->empty()){
      
      CharNode node = q->front();
      q->pop();
      
      cout << (char)(node.ch+'a') << " accepted: " << node.accepted << " ";
      
      for(nint i = 0;i<27;i++){
	if(node.children[i]!=0){
	//  cout << "push" << endl;
	  if(level%2 == 0){
	    l2.push(*(node.children[i]));
	  } else {
	    l1.push(*(node.children[i]));
	  }
	  
	}  
	  
      }
      
    }
    
    cout << endl;
    
     if(level%2 == 0){
	q=&l2;
     } else {
	q=&l1;
     }
     
     level++;
   
  } 
}

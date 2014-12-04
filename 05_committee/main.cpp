#include "main.hpp"

int main(int argc, char **argv) {
  nint N,D,K,aSize;
  string alphabet;
  
  CharNode root;
  
  string s;
  
  const nint buffSize = 100002;
  char buff[buffSize];
  stringstream ss;
  
#if DBG  
    string inadr = "../examples/pub01";
    inadr.append(".in");
    
    ifstream inFile (inadr.data());  
    getline(inFile,s);
    cout << s << endl;
    
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
      cout << "nWords: " << nWords << endl;
#endif     
      for(nint j = 0;j<nWords;j++){
	ss.clear();
	s.clear();
#if DBG 
	getline(inFile,s);  
	cout << s << endl;
#else
	getline(cin,s);
#endif
	acceptedWords.insert(s);
      }

    }
    
    string l = "abcd";
    string l2 = "abcf";
    string l3 = "abc";
    string l4 = "abcde";
    
    
    insertIntoPrefixTree(root,l3,2);
    insertIntoPrefixTree(root,l,2);
    insertIntoPrefixTree(root,l2,2);
    
    insertIntoPrefixTree(root,l4,2);
    
    printTree(root);
  
return 0;
}

void insertIntoPrefixTree(CharNode & root,string & s,nint D){
 
  CharNode * node = & root;
  
  nint maxAccepted=0;
 
  for(nint i = 0; i<s.size(); i++){
	sint c = s[i]-'a';    
	
	if(node->children[c]==0){
	  CharNode * chn = new CharNode(c);
	  cout << "insert:" << chn->ch <<  endl;
	  chn->level=node->level+1;
	  chn->accepted=0;
	  node->children[c]=chn;
	}
	
	node = (node->children[c]);
	
	if(node->accepted == D){
	  return;
	}
	
	if(maxAccepted < node->accepted){
	  maxAccepted = node->accepted;
	}    
	
  }
    
  node->accepted=maxAccepted+1;
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
      
      cout << (char)(node.ch+'a') << " level: " << node.level << " " << " accepted: " << node.accepted << " ";
      
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

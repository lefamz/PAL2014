#include "main.hpp"

int main(int argc, char **argv) {
    
  mint maxLen = 0;
  mint nNodes = 0;
  mint ** coords;
  mdouble ** dists;
  
  string file = "../examples/pub02";

  string s;
  char buff[6];
  stringstream ss;
  
  
#if DBG
  string inadr = file;
  ifstream inFile (inadr.append(".in").data());  
  getline(inFile,s);    
#else
  getline(cin,s);
#endif
  ss << s;
  ss.getline(buff,6,' ');
  nNodes = (mint)(atoi(buff));
    
 // TODO buff se mozna musi  po pouziti zas smazat
    
  ss.getline(buff,6,' ');
  maxLen = (mint)(atoi(buff));
    
  //scout << nNodes << " " << maxLen << endl;
  
  coords = new mint * [nNodes];
  
  for(mint i=0;i<nNodes;i++){
    coords[i] = new mint[2];
  }
  
  dists = new mdouble * [nNodes];
  
  for(mint i=0;i<nNodes;i++){
    dists[i] = new mdouble[nNodes];
  }
  

    
#if DBG
  for(mint i=0;i<nNodes;i++){
    s.clear();
    ss.clear();
    
    getline(inFile,s);
    ss << s;
    
    ss.getline(buff,6,' ');
    coords[i][0] = (mint)(atoi(buff));
    ss.getline(buff,6,' ');
    coords[i][1] = (mint)(atoi(buff));
  }
  
  inFile.close();
  
#else
  for(mint i=0;i<nNodes;i++){
    s.clear();
    ss.clear();
    
    getline(cin,s);
    ss << s;

    ss.getline(buff,6,' ');
    coords[i][0] = (mint)(atoi(buff));
    ss.getline(buff,6,' ');
    coords[i][1] = (mint)(atoi(buff));
  }
#endif
    
#if DBG
  
  ifstream fileStream (file.append(".out").data());  
  s.clear();
  getline(fileStream,s);
  cout << "Correct result: " << s << endl;
  fileStream.close();
#endif
  
/*/  for(mint i=0;i<nNodes;i++){
    for(mint j=0;j<2;j++){
      cout << coords[i][j] << " ";
    }
    
    cout << endl;
  }
/**/  

  for(mint i=0;i<nNodes;i++){
    for(mint j=0;j<nNodes;j++){
      if(j>i){
	dists[i][j]=dist(coords[i][0],coords[i][1],coords[j][0],coords[j][1]);
      } else if (j<i) {
	dists[i][j] = dists[j][i];
      } else {
	dists[i][i]=0;
      }
    }
  }
  
  mint **** conflicts = new mint *** [nNodes];
  
  for(mint i=0;i<nNodes;i++){
    conflicts[i] = new mint ** [nNodes];
    for(mint j=0;j<nNodes;j++){
      conflicts[i][j] = new mint * [nNodes];
      for(mint k=0;k<nNodes;k++){
	conflicts[i][j][k] = new mint[nNodes];
	for(mint l=0;l<nNodes;l++){
	  conflicts[i][j][k][l]=intersects(coords[i],coords[j],coords[k],coords[l]);
	}
      }
    }
  }
  
  /*for(mint i=0;i<nNodes;i++){
    for(mint j=0;j<nNodes;j++){
      cout << dists[i][j] << " ";
    }
    cout << endl;
  }/**/
  
  list<Node *> * oldGen = new list<Node *>();
  list<Node *> * newGen = new list<Node *>();
  list<Node *>::iterator it;
  
  mint level = 0;
  
  // bit mask of available vertices
  mint avVertices = pow(2,nNodes) - 1;
  
  for(mint i = 0;i<nNodes;i++){
    Node * n = new Node(0);
    n->avNodesMask = avVertices xor 1 << i;
  //  cout <<"Node #: " << i << " AvNodeMask: " << (bitset<16>) n->avNodesMask << endl;
    n->nodes->push_back(i);
    oldGen->push_back(n);
  }
  
for(it=oldGen->begin();it!=oldGen->end();++it){
  //    cout << "next from old: " << endl;
      
 //     (*it)->printNode();
    
      for(mint i=0;i<nNodes;i++){
//	cout << "next to add: " << i << endl;
	 
	 if((*it)->avNodesMask & 1 << i){
		mdouble len = (*it)->len + dists[(*it)->nodes->back()][i];
		Node * n = new Node(len);
		
		list<mint>::iterator ns;
	      
		ns = (*it)->nodes->begin();
		
		for(ns;ns!=(*it)->nodes->end();++ns){
		  n->nodes->push_back(*ns);
		  //cout << *ns << endl;
		}
		
		n->nodes->push_back(i);
		
		n->avNodesMask = (*it)->avNodesMask xor 1 << i;
		
//		cout << "added: " << i << endl;
		newGen->push_back(n);
		
		//break;
	      	   
	 }
	 
      }
      
      newGen->pop_back();
      
    }
 
    deleteNodeList(oldGen);
    oldGen->clear();
    delete oldGen;
    
    oldGen=newGen;
    
    level++;
  
   /**/ while(level<nNodes){
    
   // oldGenSize = oldGen->size();
    
    newGen = new list<Node *>();
    
    
    for(it=oldGen->begin();it!=oldGen->end();++it){
  //    cout << "next from old: " << endl;
      
 //     (*it)->printNode();
    
      for(mint i=0;i<nNodes;i++){
//	cout << "next to add: " << i << endl;
	 
	 if((*it)->avNodesMask & 1 << i){
	   if(possible(conflicts,(*it)->nodes,i)){
	      
	      mdouble addedToFirstDist = dists[i][(*it)->nodes->front()];
	      mdouble len = (*it)->len + dists[(*it)->nodes->back()][i];
	      
	      if (len + addedToFirstDist <= maxLen) {
		Node * n = new Node(len);
		
		list<mint>::iterator ns;
	      
		ns = (*it)->nodes->begin();
		
		for(ns;ns!=(*it)->nodes->end();++ns){
		  n->nodes->push_back(*ns);
		  //cout << *ns << endl;
		}
		
		n->nodes->push_back(i);
		
		n->avNodesMask = (*it)->avNodesMask xor 1 << i;
		
//		cout << "added: " << i << endl;
		newGen->push_back(n);
		
		//break;
	      }
	   }
	   
	 }
	 
      }
      
    }
    
    if(newGen->empty() || level+1 == nNodes){
      it = oldGen->begin();
      list<mint>::iterator iter;
      Node * chosen = *it;
      mdouble mLen = (*it)->len + dists[chosen->nodes->front()][chosen->nodes->back()];
      mint n = (*it)->nodes->size();
      
      for(it;it!=oldGen->end();++it){
	
        mdouble tmp = (*it)->len + dists[(*it)->nodes->front()][(*it)->nodes->back()];
	
	if (tmp < mLen){
	  mLen = tmp;
	  chosen = *it;
	}
      }
      
      

      
      cout << (int)ceil(mLen) << endl;
      break;
    }
    
    deleteNodeList(oldGen);
    oldGen->clear();
    delete oldGen;
    
    oldGen=newGen;
    
    level++;
  }/**/
  
  
  for(mint i=0;i<nNodes;i++) delete [] coords[i];
  for(mint i=0;i<nNodes;i++) delete [] dists[i];
  
  for(mint i=0;i<nNodes;i++){
    for(mint j=0;j<nNodes;j++){
      for(mint k=0;k<nNodes;k++){
	
	  delete [] conflicts[i][j][k];
	
      }
      delete [] conflicts[i][j];
    }
    delete [] conflicts[i];
  }
  
  delete [] dists;
  delete [] coords;
  delete [] conflicts;
  
  deleteNodeList(oldGen);
  delete oldGen;
 // deleteNodeList(newGen);
//  delete newGen;
  return 0;
}

mdouble dist(mint x,mint y,mint w,mint z){
  return sqrt(((x-w)*(x-w)) + ((y-z)*(y-z)));
}

void deleteNodeList(list<Node *> * toDel){
  list<Node *>::iterator it;
  for (it=(*toDel).begin();it!=(*toDel).end();++it){
    delete *it;
  }
}

bool possible(mint **** conflicts,list<mint> * nodeList, mint node){
  if (nodeList->size() < 2) return 1;
  
  list<mint>::iterator it = nodeList->begin();
  
  // posledni uzel
  list<mint>::iterator last = --nodeList->end();
 
  
  mint first = nodeList->front();
  
  mint end = nodeList->back();
//  cout << "end: " << end << endl;
  
  mint res  = 0;
  mint res2 = 0;
  
  // jedeme do predposledniho uzlu
  for(it;it!=last;++it){
    
      mint f,s;
      f = (*it);
      ++it;
      s = (*it);
      
      
      
      if (it != last){
	res = conflicts[f][s][end][node];
	
	/*cout << "f "<< f << " s " << s << " end " << end << " node " << node << " first " << first << endl;
	  cout << "Sit nto last " << res << endl;*/
	
	if (res > 0) return 0;
	
	/*
	  res2 = conflicts[f][s][node][first];
	  if ((f==first) && (res2 != 4 || res > 0)){
	  
	   
	    return 0;
	    
	}else if ((f!=first) && (res > 0 || res2 > 0)){
	  
	  cout << "f "<< f << " s " << s << " end " << end << " node " << node << " first " << first << endl;
	 cout << "Sit 1: " << res << " " << res2 << endl;
	  return 0;
	  
	}*/
	
      } else {
	res = conflicts[f][s][end][node];
	
	if (res == 0){
	/*  cout << "f "<< f << " s " << s << " end " << end << " node " << node << " first " << first << endl;
	  cout << "Sit last " << res << endl;*/
	}
	/*cout << "f "<< f << " s " << s << " end " << end << " node " << node << " first " << first << endl;
	  cout << "Sit last " << res << endl;
	*/
	if (res == 4) return 1;
	/*res2 = conflicts[f][s][node][first];
	
	if((res==4 || res == 0) && (res2==4 || res2==0)){
	  cout << "f "<< f << " s " << s << " end " << end << " node " << node << " first " << first << endl;
	  cout << "Sit2 " << res << " " << res2 << endl;
	  return 1; 
	} else {
	 cout << "f "<< f << " s " << s << " end " << end << " node " << node << " first " << first << endl;
	  cout << "Sit3 " << res << " " << res2 << endl;
	 return 0;
	  
	}*/
      }
 
  //    cout << "res " << res << endl;     
      --it;
  }
  
  return 0;
}

// return 0 pokud se neprotinaji,
// 1 pokud jsou totozne, nebo se prekryvaji,
// 2 pokud se natvrdo protinaji
// 3 pokud maji spolecny koncovy bod
// 4 pokud se protinaji v koncovem bode

mint intersects(mint x[], mint y[], mint w[], mint z[]){
  
  //cout << x[0] << " " << x[1] << " " << y[0] << " " << y[1] << " " << w[0] << " " << w[1] << " " << z[0] << " " << z[1] << endl; 
  
  mdouble deltaY=y[1]-x[1];
  mdouble deltaX=y[0]-x[0];
  
  mdouble deltaX2 = z[0]-w[0];
  mdouble deltaY2 = z[1]-w[1];
  
  mdouble alpha = 1;
  mdouble c = min(x[1],y[1]);
  
  if (deltaX!=0){
    alpha = (deltaY)/(deltaX);
    c = x[1] - alpha*x[0];
  }
  
  mdouble beta = 1;
  mdouble d = min(w[1],z[1]);
  
  if (deltaX2!=0){
    beta = (deltaY2)/(deltaX2);
    d = w[1] - beta*w[0];
  }
  
  mdouble safetyZone = pow(10,-9);

  mdouble minA=0,maxA=0,minB=0,maxB=0;
  
  bool inPoint=0;
  
  if ((x[0]==w[0] && x[1]==w[1]) || (x[0]==z[0] && x[1]==z[1])){
      inPoint=1;
  } else if ((y[0]==w[0] && y[1]==w[1]) || (y[0]==z[0] && y[1]==z[1])){
      inPoint=1;
  }
/*/
#if DBG
  cout << "Alpha: " << alpha << " beta: " << beta << " c: " << c << " d: " << d << endl;
#endif /**/
  
  // jsou rovnobezne
  if (alpha == beta){
    // kdyz nejsou obe svisle jsou mimobezky
    if ((deltaX!=0 || deltaX2!=0) && c!=d) return 0;
    
    //lezi v jedne primce, takze bud mimo, nebo se prekryvaji, nebo jsou uplne totozne
    
    bool firstIn,secondIn;
   
    
    mdouble dist1,dist2;
    dist1=dist(x[0],x[1],y[0],y[1]);
    dist2=dist(w[0],w[1],z[0],z[1]);
    
    if (dist1 >= dist2){
      minA=min(x[0],y[0])-safetyZone;
      maxA=max(x[0],y[0])+safetyZone;
      minB=min(x[1],y[1])-safetyZone;
      maxB=max(x[1],y[1])+safetyZone;
      
      firstIn = (w[0] <= maxA) && (w[0] >= minA) && (w[1] >= minB) && (w[1] <= maxB);    
      secondIn = (z[0] <= maxA) && (z[0] >= minA) && (z[1] >= minB) && (z[1] <= maxB);
      
    } else {
      minA=min(w[0],z[0])-safetyZone;
      maxA=max(w[0],z[0])+safetyZone;
      minB=min(w[1],z[1])-safetyZone;
      maxB=max(w[1],z[1])+safetyZone;
      
      firstIn = (x[0] <= maxA) && (x[0] >= minA) && (x[1] >= minB) && (x[1] <= maxB);    
      secondIn = (y[0] <= maxA) && (y[0] >= minA) && (y[1] >= minB) && (y[1] <= maxB);
    }
    
    
    if ((firstIn || secondIn) && inPoint){
      return 3;
    }
    
    if(firstIn || secondIn) return 1;
    
    return 0;
  }
    
  mdouble interX = (d-c)/(alpha-beta);
  mdouble interY = (alpha*d - beta*c)/(alpha-beta);
/* /
#if DBG
  cout << "inter x: " << interX << " interY: " << interY << endl;
#endif
/**/  
  minA=min(x[0],y[0])-safetyZone;
  maxA=max(x[0],y[0])+safetyZone;
  minB=min(x[1],y[1])-safetyZone;
  maxB=max(x[1],y[1])+safetyZone;
/*/
#if DBG
  cout << "minX: " << minA << "InterX: " << interX <<" maxX: " << maxA << endl;
  cout << "minY: " << minB << "InterY: " << interY << " maxY: " << maxB << endl;
#endif
/**/  
  bool inFirst = (interX <= maxA) && (interX >= minA) && (interY >= minB) && (interY <= maxB);
  
  minA=min(w[0],z[0])-safetyZone;
  maxA=max(w[0],z[0])+safetyZone;
  minB=min(w[1],z[1])-safetyZone;
  maxB=max(w[1],z[1])+safetyZone;
/*/  
#if DBG
cout << "minX: " << minA << "InterX: " << interX <<" maxX: " << maxA << endl;
  cout << "minY: " << minB << "InterY: " << interY << " maxY: " << maxB << endl;
#endif
/**/  
  bool inSecond = (interX <= maxA) && (interX >= minA) && (interY >= minB) && (interY <= maxB);

 // cout << inFirst << " " << inSecond << " " << inPoint << endl;
  
  if (inFirst && inSecond && inPoint) return 4;
  if (inFirst && inSecond) return 2;
  return 0;

}

/*bool intersects2(mint x[], mint y[], mint w[], mint z[]){
  mdouble denominator = ((x[0] - y[0])*(w[1] - z[1])) - ((x[1] - y[1])*(w[0] - z[0]));
  
  if (denominator == 0){
    //TODO usecky jsou pak rovnobezne, budto mimobezky, nbo jedna v druhe
    return 0;
  }
  
  mdouble a = ((x[0]*y[1]) - (x[1]*y[0]));
  mdouble b = ((w[0]*z[1]) - (w[1]*z[0]));
  
  mdouble interX = ((a*(w[0] - z[0])) - ((x[0] - y[0])*b))/denominator;
  mdouble interY = ((a*(w[1] - z[1])) - ((x[1] - y[1])*b))/denominator;
  
#if DBG
  cout << "inter x: " << interX << " interY: " << interY << endl;
#endif
  
  mint minA=0,maxA=0,minB=0,maxB=0;
  
  minA=min(x[0],y[0]);
  maxA=max(x[0],y[0]);
  minB=min(x[1],y[1]);
  maxB=max(x[1],y[1]);

#if DBG
  cout << "minX: " << minA << " maxX: " << maxA << endl;
  cout << "minY: " << minB << " maxY: " << maxB << endl;
#endif
  
  bool inFirst = (interX <= maxA) && (interX >= minA) && (interY >= minB) && (interY <= maxB);
  
  minA=min(w[0],z[0]);
  maxA=max(w[0],z[0]);
  minB=min(w[1],z[1]);
  maxB=max(w[1],z[1]);
  
#if DBG
  cout << "minX: " << minA << " maxX: " << maxA << endl;
  cout << "minY: " << minB << " maxY: " << maxB << endl;
#endif
  
  bool inSecond = (interX <= maxA) && (interX >= minA) && (interY >= minB) && (interY <= maxB);
  
  if (inFirst && inSecond) return 1;
  return 0;
}*/

  //cout << intersects(coords[8],coords[9],coords[9],coords[2]) << endl;
 
  /*/list<mint> * ls = new list<mint>();
  ls->push_back(4);
  ls->push_back(5);
  ls->push_back(6);
  
  for (mint i =0;i<nNodes;i++){
    if(i!=4 && i!=5 && i!=6){
      cout << "isPossible: " << possible(conflicts,ls,i) << endl;
    }
  }
  /**/
 
 /* mint x[2];
  mint y[2];
  mint w[2];
  mint z[2];*/
  
 /* x[0] = 0; x[1] = 0;
  y[0] = 3; y[1] = 4;
  w[0] = 1; w[1] = 0;
  z[0] = 4; z[1] = 4;
  // 0
  /**/
  
  /* x[0] = 0; x[1] = 0;
  y[0] = 3; y[1] = 4;
  w[0] = 0; w[1] = 0;
  z[0] = 4; z[1] = 4;
  // 1
  /**/
  
  /* x[0] = 0; x[1] = 0;
  y[0] = 3; y[1] = 4;
  w[0] = 1; w[1] = 0;
  z[0] = 4; z[1] = 7;
  // 1
  /**/
 
 /* x[0] = 1; x[1] = 0;
  y[0] = 1; y[1] = 2;
  w[0] = 1; w[1] = 3;
  z[0] = 1; z[1] = 4;
  // 0
  /**/
  
  /* x[0] = 1; x[1] = 0;
  y[0] = 1; y[1] = 3;
  w[0] = 2; w[1] = 2;
  z[0] = 2; z[1] = 4;
  // 0
  /**/
  
 /* x[0] = 1; x[1] = 0;
  y[0] = 1; y[1] = 3;
  w[0] = 1; w[1] = 2;
  z[0] = 1; z[1] = 4;
  // 1
  /**/
  
  /* x[0] = 0; x[1] = 0;
  y[0] = 3; y[1] = 3;
  w[0] = 4; w[1] = 4;
  z[0] = 5; z[1] = 5;
  // 0
  /**/
  
  /* x[0] = 0; x[1] = 2;
  y[0] = 4; y[1] = 2;
  w[0] = 2; w[1] = 0;
  z[0] = 2; z[1] = 4;
  // 1
  /**/
  
  /* x[0] = 0; x[1] = 0;
  y[0] = 4; y[1] = 4;
  w[0] = 4; w[1] = 5;
  z[0] = 0; z[1] = 9;
  // 0
  /**/
  
 // cout << "Intersects: " << intersects(x,y,w,z) << endl; /**/
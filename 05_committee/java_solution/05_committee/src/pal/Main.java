package pal;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;
import java.util.TreeSet;

public class Main {
    public static final int nCHildren = 27;
    public static final int modulo = 100000;

    public static void main(String[] args) throws IOException{
        int N,D,K,aSize;
        CharNode root= new CharNode();
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(reader.readLine()," ");
        aSize = (tokenizer.nextToken()).length();
        N = Integer.parseInt(tokenizer.nextToken());
        D = Integer.parseInt(tokenizer.nextToken());
        K = Integer.parseInt(tokenizer.nextToken());

        String s;

        for(int i =0;i<N;i++){
            int nWords = Integer.parseInt(reader.readLine());
            TreeSet<String> acceptedWords = new TreeSet<>();
            for(int j=0;j<nWords;j++){
                acceptedWords.add(reader.readLine());
            }

            while(!acceptedWords.isEmpty()){
                s = acceptedWords.pollFirst();
                if(s.length() > K) continue;
                insertIntoPrefixTree(root,s,D);
            }

        }

        System.out.println(calculateSupport(root, D, K, aSize));
    }

    private static int calculateSupport(CharNode root,int D,int K,int aSize){
        Stack<CharNode> st = new Stack<>();
        st.push(root);

        int res = 0;

        while(!st.isEmpty()){
            CharNode cN = st.pop();
            if(cN.accepted >= D){
                int level = cN.level;
                if(level == K){
                    res=(res+1)%modulo;
                } else {
                    int hlp = aSize;
                    for(int i=1;i<(K-level);i++){
                        hlp = (aSize * hlp) % modulo;
                    }

                    res=(res+hlp)%modulo;
                }
                continue;
            }

            for(int i=0;i<nCHildren;i++){
                if(cN.children[i]!=null) st.push(cN.children[i]);
            }
        }

        return res;
    }

    private static void insertIntoPrefixTree(CharNode root, String s,int D){
        CharNode node = root;
        int maxAccepted=0;

        for(int i = 0;i<s.length();i++){
            int c = s.charAt(i)-'a';
            if(node.children[c]==null){
                CharNode chn = new CharNode(c);
                chn.level=node.level+1;
                node.children[c]=chn;
            }

            node = node.children[c];

            if(node.accepted >= D){
                return;
            }

            if(maxAccepted<node.accepted){
                maxAccepted=node.accepted;
            }
        }

        node.accepted=maxAccepted+1;

        if(node.accepted < D){
            Stack<CharNode> st = new Stack<>();

            for (int i = 0; i < nCHildren; i++) {
                if (node.children[i] != null) st.push(node.children[i]);
            }


            while(!st.isEmpty()){
                CharNode cN = st.pop();

                if(cN.accepted > 0) cN.accepted++;
                
                for(int i=0;i<nCHildren;i++){
                    if(cN.children[i]!=null) st.push(cN.children[i]);
                }

            }
        } else {
            node.children=new CharNode[nCHildren];
        }
    }


}

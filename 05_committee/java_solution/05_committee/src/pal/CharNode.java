package pal;

/**
 * Created by michal on 12/5/14.
 */
public class CharNode {
    public int level=0,accepted=0,ch=(int)'!';

    CharNode[] children = null;

    public CharNode(){
        children = new CharNode[Main.nCHildren];
    }
    public CharNode(int c){
        ch=c;
        children = new CharNode[Main.nCHildren];
    }
}

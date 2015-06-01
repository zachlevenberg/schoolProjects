//-----------------------------------------------------------------------------
//Zachary Levenberg
//ID: 1049451
//12b
//5/27/15
//This file implements a lookup dictionary using a binary search tree
// Dictionary.java
//-----------------------------------------------------------------------------

public class Dictionary implements DictionaryInterface{

	private class Node{
		String key;
		String value;
		Node left;
		Node right;

		Node(String k, String v){
			key = k;
			value = v;
			left = null;
			right = null;
		}
	}

	private Node root;
	private int numItems;

	public Dictionary(){
		root = null;
		numItems = 0;
	}

	//private functions-------------------------------------------------------------

	private Node findKey(Node R, String k){
		if((R==null) || k.equals(R.key)){
			return R;
		}
		if(k.compareTo(R.key) < 0){
			return findKey(R.left, k);
		} else{
			return findKey(R.right, k);
		}
	}

	// findLeftmost()
	// returns the leftmost Node in the subtree rooted at R, or NULL if R is NULL.
	private Node findLeftmost(Node R){
		Node L = R;
		if( L!=null ) for( ; L.left!=null; L=L.left) ;
		return L;
	}


	// findParent()
	// returns the parent of N in the subtree rooted at R, or returns NULL 
	// if N is equal to R. (pre: R != NULL)
	private Node findParent(Node N, Node R){
		Node P = null;
		if(N!=R){
			P = R;
			while(P.left!=N && P.right!= N){
				if(N.key.compareTo(P.key) < 0){
					P = P.left;
				} else {
					P = P.right;
				}
			}
		}
		return P;
	}


	// printInOrder()
	// prints the (key, value) pairs belonging to the subtree rooted at R in order
	// of increasing keys to file pointed to by out.
	private void printInOrder(StringBuffer sb, Node R){
		if( R!=null ){
			printInOrder(sb, R.left);
			sb.append(R.key).append(" ").append(R.value).append("\n");
			printInOrder(sb, R.right);	   
		}
	}

	//public functions-----------------------------------------------------------

	// isEmpty()
	// returns true if this Dictionary is empty, false otherwise
	// pre: none
	public boolean isEmpty(){
		if(root==null){
			return true;
		} else {
			return false;
		}
	}

	// size()
	// returns the number of entries in this Dictionary
	// pre: none
	public int size(){
		return numItems;
	}

	// lookup()
	// returns value associated key, or null reference if no such key exists
	// pre: none
	public String lookup(String key){
		Node c;
		c = findKey(root, key);
		if(c==null){
			return null;
		} else{
			return c.value;
		}
	}

	// insert()
	// inserts new (key,value) pair into this Dictionary
	// pre: lookup(key)==null
	public void insert(String key, String value) throws KeyCollisionException{
		Node N, A, B;
		if( findKey(root, key)!=null ){
			throw new KeyCollisionException("cannot insert duplicate keys");		
		}
		N = new Node(key, value);
		B = null;
		A = root;
		while( A!=null ){
			B = A;
			if( key.compareTo(A.key)<0 ) A = A.left;
			else A = A.right;
		}
		if( B==null ) root = N;
		else if( key.compareTo(B.key)<0) B.left = N;
		else B.right = N;
		numItems++;
	}

	// delete()
	// deletes pair with the given key
	// pre: lookup(key)!=null
	public void delete(String key) throws KeyNotFoundException{
		Node N, P, S;
		N = findKey(root, key);
		if( N==null ){
			throw new KeyNotFoundException("cannot delete non-existent found");
		}
		if( N.left==null && N.right==null ){
			if( N==root ){
				root = null;
			}else{
				P = findParent(N, root);
				if( P.right==N ) P.right = null;
				else P.left = null;
			}
		}else if( N.right==null ){
			if( N==root ){
				root = N.left;
			}else{
				P = findParent(N, root);
				if( P.right==N ) P.right = N.left;
				else P.left = N.left;
			}
		}else if( N.left==null ){
			if( N==root ){
				root = N.right;
			}else{
				P = findParent(N, root);
				if( P.right==N ) P.right = N.right;
				else P.left = N.right;
			}
		}else{  // N->left!=NULL && N->right!=NULL
			S = findLeftmost(N.right);
			N.key = S.key;
			N.value = S.value;
			P = findParent(S, N);
			if( P.right==S ) P.right = S.right;
			else P.left = S.right;
		}
		numItems--;
	}

	// makeEmpty()
	// pre: none
	public void makeEmpty(){
		root = null;
		numItems = 0;
	}

	// toString()
	// returns a String representation of this Dictionary
	// overrides Object's toString() method
	// pre: none
	public String toString(){
		StringBuffer sb = new StringBuffer();
		printInOrder(sb, root);
		return new String(sb);
	}

}



//-----------------------------------------------------------------------------
// Dictionary.java
// Dictionary ADT
//-----------------------------------------------------------------------------

public class Dictionary implements DictionaryInterface{

	private class Node {
		String key;
		String value;
		Node next;

		Node(String someKey, String someValue){
			key = someKey;
			value = someValue;
			next = null;
		}
	}

	private Node head;
	private int numItems;


	public Dictionary(){
		head = new Node("","");
		head.next = null;
		numItems = 0;
	}


	// isEmpty()
	// returns true if this Dictionary is empty, false otherwise
	// pre: none
	public boolean isEmpty(){
		if(numItems == 0){
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
		Node N = head;
		int i = 0;
		while(N.next != null){
			if(N.next.key == key){
				return N.next.value;
			}
			N = N.next;
		}
		return null;
	}

	// insert()
	// inserts new (key,value) pair into this Dictionary
	// pre: lookup(key)==null
	public void insert(String key, String value) throws KeyCollisionException{
		if(lookup(key) != null){
			throw new KeyCollisionException("connot insert duplicate keys");
		}
		if(numItems == 0){
			Node C = new Node(key, value);
			head.next = C;
			numItems++;
		} else {
			Node N = head;
			while(N.next != null) N = N.next;
			Node C = new Node(key, value);
			N.next = C;
			numItems++;
		}
	}

	// delete()
	// deletes pair with the given key
	// pre: lookup(key)!=null
	public void delete(String key) throws KeyNotFoundException{

		if(lookup(key) == null){
			throw new KeyNotFoundException("connot delete non-existend key");
		}
		
		if(head.next.key == key){
			head.next = head.next.next;
		} else {
		Node N = new Node(key,"");
		N.next = head.next;
		while(N.next.next.key != key){
			N = N.next;
		}
		N.next.next = N.next.next.next;
		}	


		numItems--;
	}

	// makeEmpty()
	// pre: none
	public void makeEmpty(){
		head.next = null;
		numItems = 0;
	}

	// toString()
	// returns a String representation of this Dictionary
	// overrides Object's toString() method
	// pre: none
	public String toString(){
		StringBuffer sb = new StringBuffer();
		Node N = new Node("","");
		N.next = head.next;
		if(N.next == null){
			sb.append("\n");
			return new String(sb);	
		}
		for( ; N.next!=null; N.next=N.next.next) sb.append(N.next.key).append(" ").append(N.next.value).append("\n");
		return new String(sb);
	}	
}

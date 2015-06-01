///-----------------------------------------------------------------------------
// Zachary Levenberg
// ID: 1049451
// 12m
// 5/19/15
// List.java
// List ADT
//-----------------------------------------------------------------------------

public class List<T> implements ListInterface<T>{

	private class Node{
		T item;
		Node next;

		Node(T x){
			item = x;
			next = null;
		}
	}

	private Node head;
	private int numItems;
	private T empty;

	public List(){
		head = new Node(empty);
		numItems = 0;
	}

	// isEmpty
	// pre: none
	// post: returns true if this List is empty, false otherwise
	public boolean isEmpty(){
		if(numItems == 0){
			return true;
		} else {
			return false;
		}
	}

	// size
	// pre: none
	// post: returns the number of elements in this List
	public int size(){
		return numItems;
	}


	// get
	// pre: 1 <= index <= size()
	// post: returns item at position index
	public T get(int index) throws ListIndexOutOfBoundsException{
		if((index < 1) || (index > size())){
			throw new ListIndexOutOfBoundsException("get(): invalid index: " + index);
		}

		Node N = head;
		for(int i = 0; i < index; i++){
			N = N.next;
		}
		return N.item;
	}

	// add
	// inserts newItem in this List at position index
	// pre: 1 <= index <= size()+1
	// post: !isEmpty(), items to the right of newItem are renumbered
	public void add(int index, T newItem) throws ListIndexOutOfBoundsException
	{
		if((index < 1) || (index > size() + 1)){
			throw new ListIndexOutOfBoundsException("add(): invalid index: " + index);
		}
		Node N = head;
		if(size() == 0){
			N.next = new Node(newItem);
		} else {
			for(int i = 0; i < index - 1; i++){
				N = N.next;
			}
			Node C = new Node(newItem);
			C.next = N.next;
			N.next = C;
		}
		numItems++;
	}

	// remove
	// deletes item from position index
	// pre: 1 <= index <= size()
	// post: items to the right of deleted item are renumbered
	public void remove(int index) throws ListIndexOutOfBoundsException{
		if((index < 1) || (index > size())){
			throw new ListIndexOutOfBoundsException("remove(): invalid index: " + index);
		}
		Node N = head;
		for(int i = 0; i < index - 1; i++){
			N = N.next;
		}
		N.next = N.next.next;
		numItems--;
	
	}

	// removeAll
	// pre: none
	// post: isEmpty()
	public void removeAll(){
		head = null;
		numItems = 0;
	}
	
	public String toString(){
		StringBuffer sb = new StringBuffer();
		Node N = new Node(empty);
		N.next = head.next;
		if(N.next == null){
			return new String(sb);	
		}
		for( ; N.next!=null; N.next=N.next.next){
			sb.append(N.next.item.toString()).append(" ");
		}
		return new String(sb);
	}	

	@SuppressWarnings("unchecked")
	public boolean equals(Object rhs){
		boolean eq = false;
		List<T> R = null;

		if(this.getClass() == rhs.getClass()){
			R = (List<T>) rhs;
			for(int i = 1; i < this.size()+1; i++){
				if(this.get(i) != R.get(i)){
					eq = false;
					break;
				} else {
					eq = true;
				}
			}
		}
		return eq;
	}
}

//-----------------------------------------------------------------------------
//Zachary Levenberg
//ID: 1049451
//12b
//5/14/15
// Queue.java
// Queue ADT
//-----------------------------------------------------------------------------

public class Queue implements QueueInterface{

	private class Node {
		Job thisJob;
		Node next;

		Node(Object newJob){
			thisJob = ((Job)newJob);
			next = null;
		}
	}

	private Job emptyJob;
	private Node head;
	private int numItems;


	public Queue(){
		head = new Node(emptyJob);
		head.next = null;
		numItems = 0;
	}

	// isEmpty()
	// pre: none
	// post: returns true if this Queue is empty, false otherwise
	public boolean isEmpty(){
		if(numItems == 0){
			return true;
		} else {
			return false;
		}
	}

	// size()
	// returns the number of entries in this Queue
	// pre: none
	public int length(){
		return numItems;
	}

	// enqueue()
	// adds newItem to back of this Queue
	// pre: none
	// post: !isEmpty()
	public void enqueue(Object newItem) {
		if(numItems == 0){
			Node C = new Node(newItem);
			head.next = C;
			numItems++;
		} else {
			Node N = head;
			while(N.next != null) N = N.next;
			Node C = new Node(newItem);
			N.next = C;
			numItems++;
		}
	}

	// dequeue()
	// deletes and returns item from front of this Queue
	// pre: !isEmpty()
	// post: this Queue will have one fewer element
	public Object dequeue() throws QueueEmptyException{

		Job C = head.next.thisJob;
		if(length() > 1){
			head.next = head.next.next;
		} else {
			head.next = null;
		}
		numItems--;
		return C;
	}

	// peek()
	// pre: !isEmpty()
	// post: returns item at front of Queue
	public Object peek() throws QueueEmptyException{
		if(head.next != null){
			return head.next.thisJob;
		} else {
		throw new QueueEmptyException("this Queue is empty");
		}
	}

	// dequeueAll()
	// sets this Queue to the empty state
	// pre: !isEmpty()
	// post: isEmpty()
	public void dequeueAll() throws QueueEmptyException{
	head.next = null;
	numItems = 0;
	}

	// toString()
	// returns a String representation of this Dictionary
	// overrides Object's toString() method
	// pre: none
	public String toString(){
		StringBuffer sb = new StringBuffer();
		Node N = new Node(emptyJob);
		N.next = head.next;
		if(N.next == null){
			
			return new String(sb);	
		}
		for( ; N.next!=null; N.next=N.next.next){
			sb.append(N.next.thisJob.toString()).append(" ");
		}
		return new String(sb);
	}	
}

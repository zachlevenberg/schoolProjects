//-----------------------------------------------------------------------------
// Zachary Levenberg
// ID: 1049451
// 12m
// 5/19/15
// ListTest.java
// A test client for the List ADT
//-----------------------------------------------------------------------------

public class ListTest{

	public static void main(String[] args){

		//test with intgers

		System.out.println("Begin interlist test:");
		System.out.println();

		List<Integer> a = new List<Integer>();
		List<Integer> b = new List<Integer>();
		List<List<Integer>> c = new List<List<Integer>>();
		//int i, j, k;

		a.add(1, 1);
		a.add(2, 2);
		a.add(3, 3);
		b.add(1, 10);
		b.add(2, 20);
		b.add(3, 30);
		c.add(1, a);
		c.add(2, b);

		System.out.println("a: "+a);
		System.out.println("b: "+b);
		System.out.println("c: "+c);
		System.out.println("a.equals(A) is "+a.equals(a));
		System.out.println("a.equals(B) is "+a.equals(b));
		System.out.println("a.equals(C) is "+a.equals(c));
		System.out.println("a.size() is "+a.size());
		System.out.println("b.size() is "+b.size());
		System.out.println("c.size() is "+c.size());

		a.remove(1);
		b.remove(2);

		System.out.println("a.size() is "+a.size());
		System.out.println("b.size() is "+b.size());
		System.out.println("b.get(1) is "+b.get(1));
		System.out.println("c: "+c);
		System.out.println();
		try{
			System.out.println(a.get(200));
		}catch(ListIndexOutOfBoundsException e){
			System.out.println("Caught Exception: ");
			System.out.println(e);
			System.out.println("Continuing without interuption");
		}

		try{
			a.add(200, 10);
		}catch(ListIndexOutOfBoundsException e){
			System.out.println("Caught Exception: ");
			System.out.println(e);
			System.out.println("Continuing without interuption");
		}

		try{
			a.remove(200);
		}catch(ListIndexOutOfBoundsException e){
			System.out.println("Caught Exception: ");
			System.out.println(e);
			System.out.println("Continuing without interuption");
		}
		System.out.println();
		System.out.println("a.get(2) is "+a.get(2));
		System.out.println("c.get(1) is "+c.get(1));
		a.removeAll();
		b.removeAll();
		System.out.println("a.size() is "+a.size());
		System.out.println("b.size() is "+b.size());

		System.out.println();
		System.out.println();	

		//test with strings

		System.out.println("Begin stringlist test:");
		System.out.println();


		List<String> A = new List<String>();
		List<String> B = new List<String>();
		List<List<String>> C = new List<List<String>>();
		//int i, j, k;

		A.add(1, "one");
		A.add(2, "two");
		A.add(3, "three");
		B.add(1, "ten");
		B.add(2, "twenty");
		B.add(3, "thirty");
		C.add(1, A);
		C.add(2, B);

		System.out.println("A: "+A);
		System.out.println("B: "+B);
		System.out.println("C: "+C);
		System.out.println("A.equals(A) is "+A.equals(A));
		System.out.println("A.equals(B) is "+A.equals(B));
		System.out.println("A.equals(C) is "+A.equals(C));
		System.out.println("A.size() is "+A.size());
		System.out.println("B.size() is "+B.size());
		System.out.println("C.size() is "+C.size());

		A.remove(1);
		B.remove(2);

		System.out.println("A.size() is "+A.size());
		System.out.println("B.size() is "+B.size());
		System.out.println("B.get(1) is "+B.get(1));
		System.out.println("C: "+C);
		System.out.println();
		try{
			System.out.println(A.get(200));
		}catch(ListIndexOutOfBoundsException e){
			System.out.println("Caught Exception: ");
			System.out.println(e);
			System.out.println("Continuing without interuption");
		}
		System.out.println();
		System.out.println("A.get(2) is "+A.get(2));
		System.out.println("C.get(1) is "+C.get(1));


	}
}

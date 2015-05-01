//-----------------------------------------------------------------------------
// DictionaryTest.java
// Testing Dictionary ADT
//-----------------------------------------------------------------------------

public class DictionaryTest{

	public static void main(String[] args){


		Dictionary A = new Dictionary();

		//Test size
		System.out.println("size of ADT" + A.size());

		//Test insert
		A.insert("cat","a");
		if(A.size() == 1){
			System.out.println("size of ADT is 1");
		} else {
			System.out.println("oops SIZE error");
		}
		A.insert("dog","b");
		if(A.size() == 2){
			System.out.println("size of ADT is 2");
		} else {
			System.out.println("oops SIZE error");
		}

		//Test clear
		A.makeEmpty();
		if(A.size() == 0){
			System.out.println("size of ADT is EMPTY");
		} else {
			System.out.println("oops EMPTY ERRORRRR");
		}
		
		//Test lookup
		A.insert("cat","a");
		String test = null;
		test = A.lookup("cat");
		if(test != null) {
			System.out.println("if a = " + test + " test is passed");
		} else {
			System.out.println("oops");
		}
		A.insert("dog","x");
		test = A.lookup("dog");
		if(test != null) {
			System.out.println("if x = " + test + " test is passed");
		} else {
			System.out.println("oops");
		}
		test = A.lookup("2");
		if(test!= null) {
			System.out.println("oops");
		} else {
			System.out.println("lookup test passed");
		}

		//Duplicate Exceptions
		try{
			A.insert("7","a");
		} catch (KeyCollisionException e){
			System.out.println("Duplicate key caught");
		}
		
		//Delete
		A.delete("7");
		if(A.lookup("7") == null){
			System.out.println("7 is deleted");
		}

		//Delete Exception
		try{
			A.delete("7");
		} catch (KeyNotFoundException e){
			System.out.println("Cannot Delete found");
		}
	}
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ce12blab1;

/**
 *
 * @author Zach
 */
public class Etrema {
    public static int maxArray(int[] A, int p, int r) {
		if(r - p == 0) {
			return A[p];
		}
		int q = (p + r)/2;
		return max(maxArray(A, p, q), maxArray(A, q+1, r));
	}

	public static int minArray(int[] A, int p, int r) {
		if(r - p == 0) {
			return A[p];
		}
		int q = (p + r)/2;
		return min(minArray(A, p, q), minArray(A, q+1, r));
	}

	private static int max(int A, int B) {
		if( A >= B) {
			return A;
		} else {
			return B;
		}
	}

	private static int min(int A, int B) {
		if( A <= B) {
			return A;
		} else {
			return B;
		}
	}

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        int[] B = {-1, 2, 6, 3, 9, 2, -3, -2, 11, 5, 7};
	System.out.println( "max = " + maxArray(B, 0, B.length-1) );
	System.out.println( "min = " + minArray(B, 0, B.length-1) );
    }
    
}

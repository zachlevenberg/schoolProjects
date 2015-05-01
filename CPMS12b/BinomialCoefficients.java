//-----------------------------------------------------------------------------
// BinomialCoefficients.java
//-----------------------------------------------------------------------------

public class BinomialCoefficients{
   
   public static int C(int n, int k){
      if(k>n)
         return 0;
      else if(k==0 || k==n)
         return 1;
      else
         return C(n-1, k-1)+C(n-1,k);
   }

   public static void main(String[] args){

      int n = Integer.parseInt(args[0]);
	  int k = Integer.parseInt(args[1]);
      System.out.println(C(n,k));
   }
}

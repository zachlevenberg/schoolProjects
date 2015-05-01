//----------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//Zachary Levenberg
//ID: 1049451
//12b
//4/14/15
//This program search file, and returns the line numbers of any targets found.
//Search.java
//---------------------------------------------------------------------------------------

//----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class Search {

	// binarySearch()
	// pre: Array A[p..r] is sorted
	public static String binarySearch(String[][] A, int p, int r,  String target){
		int q;
		if(p > r) {
			return String.format("%s not found", target);
		}else{
			q = (p+r)/2;
			if(target.compareTo(A[q][0]) == 0){
				return String.format("%s found on line %s", A[q][0], A[q][1]);
			}else if(target.compareTo(A[q][0]) < 0){
				return binarySearch(A, p, q-1, target);
			}else{ // target > A[q]
				return binarySearch(A, q+1, r, target);
			}
		}
	}

	// mergeSort()
	// sort subarray A[p...r]
	public static void mergeSort(String[][] A, int p, int r){
		int q;
		if(p < r) {
			q = (p+r)/2;
			// System.out.println(p+" "+q+" "+r);
			mergeSort(A, p, q);
			mergeSort(A, q+1, r);
			merge(A, p, q, r);
		}
	}

	// merge()
	// merges sorted subarrays A[p..q] and A[q+1..r]
	public static void merge(String[][] A, int p, int q, int r){
		int n1 = q-p+1;
		int n2 = r-q;
		String[][] L = new String[n1][2];
		String[][] R = new String[n2][2];
		int i, j, k;

		for(i=0; i<n1; i++){
			L[i][0] = A[p+i][0];
			L[i][1] = A[p+i][1];
		}
		for(j=0; j<n2; j++){
			R[j][0] = A[q+j+1][0];
			R[j][1] = A[q+j+1][1];
		}
		i = 0; j = 0;
		for(k=p; k<=r; k++){
			if( i<n1 && j<n2 ){
				if( L[i][0].compareTo(R[j][0]) < 0){
					A[k][0] = L[i][0];
					A[k][1] = L[i][1];
					i++;
				}else{
					A[k][0] = R[j][0];
					A[k][1] = R[j][1];
					j++;
				}
			}else if( i<n1 ){
				A[k][0] = L[i][0];
				A[k][1] = L[i][1];
				i++;
			}else{ // j<n2
				A[k][0] = R[j][0];
				A[k][1] = R[j][1];
				j++;
			}
		}
	}

	public static int lineCount(String file[]) throws IOException {

		// count lines, words, and chars in file
		Scanner in = new Scanner(new File(file[0]));


		int lineCount = 0;
		while( in.hasNextLine() ){
			in.nextLine();
			lineCount++;
		}
		in.close();
		return lineCount;
	}

	public static String[][] getWords(String file[], int lineCount) throws IOException{

		String[][] list;
		list = new String[lineCount][2];

		Scanner in2 = new Scanner(new File(file[0]));

		int i = 0;
		while( in2.hasNextLine() ){
			list[i][0] = in2.nextLine();
			list[i][1] = Integer.toString(i+1);
			i++;
		}
		in2.close();
		return list;
	}

	public static void main(String[] args) throws IOException {

		// check number of command line arguments is at least 1
		if(args.length < 1){
			System.out.println("Usage: Search File target1 [target2 ..]");
			System.exit(1);
		}

		int fileLength = lineCount(args);
		String[][] myList = getWords(args, fileLength);

		mergeSort(myList, 0, fileLength-1);

		int j = 1;
		for(j = 1; j < args.length; j++){
			System.out.println(binarySearch(myList, 0, fileLength-1, args[j]));
		}
	}
}

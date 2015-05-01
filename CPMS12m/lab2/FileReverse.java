//---------------------------------------------------------------------------------------
//Zachary Levenberg
//ID: 1049451
//12m
//4/14/15
//This program takes any file, and returns individual strings in reverse character order.
//FileReverse.java
//---------------------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class FileReverse{

	public static String stringReverse(String s, int n){
		String temp = null;
		if(n > 1){
			temp = s.substring(n-1,n).concat(stringReverse(s, n-1));
			return temp;
		} else {
			return s.substring(0,1);
		}
	}

	public static void main(String[] args) throws IOException{
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		String[] token = null;
		int n;

		// check number of command line arguments is at least 2
		if(args.length < 2){
			System.out.println("Usage: FileCopy infile outfile");
			System.exit(1);
		}

		// open files
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));
		// read lines from in, write lines to out
		while( in.hasNextLine() ){
			line = in.nextLine().trim() + " ";
			token = line.split("\\s+");
			for(int i = 0; i < token.length; i++){
				String newLine = stringReverse(token[i], token[i].length());
				out.println( newLine );
			}
		}
			// close files
			in.close();
			out.close();
	}
}


//-----------------------------------------------------------------------------
// QueueTest.java
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class QueueTest{



	public static Job getJob(Scanner in) {
		String[] s = in.nextLine().split(" ");
		int a = Integer.parseInt(s[0]);
		int d = Integer.parseInt(s[1]);
		return new Job(a, d);
	}


	public static void main(String[] args) throws IOException{

		// check number of command line arguments is at least 3
		if(args.length < 1){
			System.out.println("Usage: Simulation File");
			System.exit(1);
		}

		// open file
		Scanner jobfile = new Scanner(new File(args[0]));

		//Get number of jobs
		String numJobStr = jobfile.nextLine();
		int numJobs = Integer.parseInt(numJobStr);

		//Create Job array
		Job jobList[] = new Job[numJobs];

		//Put jobs into Job array
		for(int i = 0; i < numJobs; i++){
			jobList[i] = getJob(jobfile);
		}


		for(int i = 1; i < numJobs; i++){
			Queue myQueue = new Queue();
			for(int j = 0; j < numJobs; j++){
				myQueue.enqueue(jobList[j]);
			}

			System.out.println("processor" + i);
			System.out.println(myQueue.toString());
			System.out.println(((Job)myQueue.dequeue()).getFinish());
			System.out.println(myQueue.toString());
			myQueue.dequeueAll();
			System.out.println(myQueue.toString());


		}

	}
}


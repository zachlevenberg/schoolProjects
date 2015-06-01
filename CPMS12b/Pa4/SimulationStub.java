//-----------------------------------------------------------------------------
// SimulationStub.java
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class Simulation{

	//-----------------------------------------------------------------------------
	//
	// The following function may be of use in assembling the initial backup and/or
	// storage queues.  You may use it as is, alter it as you see fit, or delete it
	// altogether.
	//
	//-----------------------------------------------------------------------------

	public static Job getJob(Scanner in) {
		String[] s = in.nextLine().split(" ");
		int a = Integer.parseInt(s[0]);
		int d = Integer.parseInt(s[1]);
		return new Job(a, d);
	}

	//-----------------------------------------------------------------------------
	//
	// The following stub for function main contains a possible algorithm for this
	// project.  Follow it if you like.  Note that there are no instructions below
	// which mention writing to either of the output files.  You must intersperse
	// those commands as necessary.
	//
	//-----------------------------------------------------------------------------



	public static void main(String[] args) throws IOException{

		// check number of command line arguments is at least 3
		if(args.length < 3){
			System.out.println("Usage: Simulation File target1 target2");
			System.exit(1);
		}

		// open file
		Scanner jobfile = new Scanner(new File(args[0]));

		//Get number of jobs
		String numJobStr = jobfile.nextLine();
		int numJobs = Integer.parseInt(numJobStr);

		//Create Job array
		Job jobList[] = new Job[numbJobs];

		//Put jobs into Job array
		for(int i = 0; i < numJobs; i++){:q
			jobList[i] = getJob(jobfile);
		}


		for(int i = 1; i < numJobs; i++){
			Queue myQueue = new Queue();
			for(int j = 0; j < numJobs; j++){
				myQueue.enqueue(jobList[j];
						}

						System.out.println("processor" + i);
						System.out.println(myQueue.toString());


						}

						//    1.  check command line arguments
						//
						//    2.  open files for reading and writing
						//
						//    3.  read in m jobs from input file
						//
						//    4.  run simulation with n processors for n=1 to n=m-1  {
						//
						//    5.      declare and initialize an array of n processor Queues and any 
						//            necessary storage Queues
						//
						//    6.      while unprocessed jobs remain  {
						//
						//    7.          determine the time of the next arrival or finish event and 
						//                update time
						//
						//    8.          complete all processes finishing now
						//
						//    9.          if there are any jobs arriving now, assign them to a processor 
						//                Queue of minimum length and with lowest index in the queue array.
						//
						//    10.     } end loop
						//
						//    11.     compute the total wait, maximum wait, and average wait for 
						//            all Jobs, then reset finish times
						//
						//    12. } end loop
						//
						//    13. close input and output files

	}
}


//-----------------------------------------------------------------------------
//Zachary Levenberg
//ID: 1049451
//12b
//5/14/15
//This file simulates the time it takes for arrivals to be processed
// SimulationStub.java
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class Simulation{

public static Job getJob(Scanner in) {
	String[] s = in.nextLine().split(" ");
	int a = Integer.parseInt(s[0]);
	int d = Integer.parseInt(s[1]);
	return new Job(a, d);
}

public static void main(String[] args) throws IOException{

	// check number of command line arguments is at least 1
	if(args.length < 1){
		System.out.println("Usage: Simulation File");
		System.exit(1);
	}

	// open file
	Scanner jobfile = new Scanner(new File(args[0]));
	String fileIn = new String(args[0].split("[.]")[0]);
	String traceName = new String(fileIn.concat(".trc"));
	String reportName = new String(fileIn.concat(".rpt"));
	PrintWriter trace = new PrintWriter(new FileWriter(traceName));
	PrintWriter report = new PrintWriter(new FileWriter(reportName));

	//Get number of jobs
	String numJobStr = jobfile.nextLine();
	int numJobs = Integer.parseInt(numJobStr);

	//Create Job arrays
	Job jobList[] = new Job[numJobs];

	//Put jobs into Job array
	for(int i = 0; i < numJobs; i++){
		jobList[i] = getJob(jobfile);
	}

	//Print header for report file
	report.println("Report file: " + reportName);
	report.println(numJobs + " Jobs:");
	for(int i = 0; i < numJobs; i++){	
		report.print(jobList[i].toString() + " ");
	}
	report.println();
	report.println();
	report.println("***********************************************************");

	//Print head for trace file
	trace.println("Trace file: " + traceName);
	trace.println(numJobs + " Jobs:");
	for(int i = 0; i < numJobs; i++){	
		trace.print(jobList[i].toString() + " ");
	}
	trace.println();
	trace.println();


	//Loop for each number of processors
	for(int numProcessors = 1; numProcessors < numJobs; numProcessors++){

		trace.println("*****************************");
		trace.println(numProcessors + " processor" + (numProcessors>1?"s:":":"));
		trace.println("*****************************");

		//Create Processor Queue Array and The main Queue and initialize
		Queue processor[] = new Queue[numProcessors];
		for(int i = 0; i < numProcessors ; i++){
			processor[i] = new Queue();
		}
		Queue mainQueue = new Queue();
		for(int i = 0; i < numJobs; i++){
			jobList[i].resetFinishTime();
			mainQueue.enqueue(jobList[i]);
		}

		//Run simulation
		int time = 0;
		int totalProcessed = 0;
		boolean changeFlag = true;
	
		while(totalProcessed != numJobs){


			//Check for any finished jobs
			for(int i = 0; i < numProcessors; i++){
				if(!processor[i].isEmpty()){
					if(((Job)processor[i].peek()).getFinish() <= time){
						changeFlag = true;						
						totalProcessed++;
						mainQueue.enqueue(processor[i].dequeue());
						if(!processor[i].isEmpty()){
							((Job)(processor[i].peek())).computeFinishTime(time);
						}
					}
				}
			}

			//If there is an arrival
			if(!mainQueue.isEmpty()){
				while((!mainQueue.isEmpty()) && (((Job)mainQueue.peek()).getArrival() == time)){
					changeFlag = true;
					
					int nextProcessor = 0;
					//pick the shortest line if more than 1 processor
					for(int i = 0; i < numProcessors; i++){
						if(processor[nextProcessor].length() > processor[i].length()){
							nextProcessor = i;

						}
					}
					//If line is empty, calculate finish time, Else, add to queue with finish time
					if(processor[nextProcessor].isEmpty()){
						//compute finish time and add to processor queue
						processor[nextProcessor].enqueue(mainQueue.dequeue());
						((Job)processor[nextProcessor].peek()).computeFinishTime(time);
					} else { 
						processor[nextProcessor].enqueue(mainQueue.dequeue());
					}
				}
			}



			//print results to trace file
			if(changeFlag){
				trace.println("time=" + time);
				changeFlag = false;
				trace.println("0: " + mainQueue.toString());
				for(int i = 0; i < numProcessors; i ++){
					trace.println((i+1) + ": " + processor[i].toString());
				}
				trace.println();
			}
			time++;
		}

		//Calculate averages
		int totalWait = 0;
		int maxWait = 0;
		float averageWait =0;
		for(int i = 0; i < numJobs; i++){	
			int temp = ((Job)mainQueue.dequeue()).getWaitTime();
			totalWait += temp;
			if(maxWait <= temp){
				maxWait = temp;
			}
		}
		averageWait = ((float)totalWait)/((float)numJobs);
		report.print(numProcessors + " processor" + (numProcessors>1?"s: ":": "));
		report.format("totalWait=%d, maxWait=%d, averageWait=%.2f", totalWait, maxWait, averageWait);
		report.println();


	}

	trace.close();
	report.close();
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


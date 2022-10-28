/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_rr.cpp
 * @author Jordan Aquino and Jamison Coombs
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"
#include <algorithm> // for std::sort to sort the PCBs since they will not complete in order of name
		     // and we will want to re-organize them based on name  
		     //
// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here
//
//


/**
 * @brief Construct a new SchedulerRR object
 */
SchedulerRR::SchedulerRR(int time_quantum ){
	quantum = time_quantum;
}
/**
 * @brief Destroy the SchedulerRR object
 */
SchedulerRR::~SchedulerRR() {

}
/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerRR:: init(std::vector<PCB>& process_list){
	for(PCB pcb : process_list){
		// insert pcb to beginning
		readyqueue.insert(readyqueue.begin(),pcb);
	}
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerRR:: print_results() {
	for (unsigned int i = 0; i < finished.size(); i++){
		std::cout<< finished[i].name <<" turn-around time = "<< finished[i].turnaround_time << ", waiting time = " << finished[i].waiting_time<< '\n';
	}
}
/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerRR:: simulate(){
	// time elapsed throughout the simulation
	unsigned int elapsed_time = 0;
	while( finished.size() < 8){
		
		// grab pcb from end, doing this way since its easy to add and remove like this
		// the pcb at the end of the vector named "readyqueue" is effectively the first
		// item on the queue
		auto curr = readyqueue.back();
		
		//remove pcb after storing it into curr
		readyqueue.pop_back(); 		
		
		// determine how long the process will run. 
		// If the burst time is less than or equal to the time quantum,
		// than the process will run for the burst time. Otherwise, it will run the duration of the time quantum
		auto running_time = (quantum < curr.burst_time)? quantum: curr.burst_time;
		
				// simulate the running of the process
		std::cout<<"Running process " << curr.name << " for " << running_time << " time units.\n";
	        
		//update elapsed time
		elapsed_time+=running_time;
		
		// update waiting time for the process about to be ran
		// all arrival times in this homework is 0: but I am accounting for it regardless
		// subtracting the current waiting time from the elapsed time before we add,
		// so that we do not double count any time units 
		curr.waiting_time += (elapsed_time - curr.waiting_time - curr.arrival_time);


		// adjust the new burst time now that the process has ran for some period of time	
		curr.burst_time = curr.burst_time - running_time;
		
		
		// if the burst time is 0, the process is complete. 
		if(curr.burst_time == 0){
			//subtract burst time from waiting time before inserting to finished
			curr.waiting_time-=curr.burst_time;
			// now insert to finished
			finished.push_back(curr);
		}else{
			// put the process back into the ready queue to be run again
			// reminder: the beginning of the readyqueue vector is the END of
			// the actual queue in terms of when processes run.
			readyqueue.insert(readyqueue.begin(), curr);
		}
	}
	// finished simulation, time to sort PCBs
	std::sort(finished.begin(), finished.end(), PCB::compareId);

}

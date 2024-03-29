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

/**
 * @brief Construct a new SchedulerRR object
 */
SchedulerRR::SchedulerRR(int time_quantum ){
	quantum = time_quantum;
	// to pass cppcheck
	average_waiting_time = 0;
	average_turnaround_time = 0;

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
	std::cout<< "Average turnaround time = " << average_turnaround_time << " Average waiting time = " << average_waiting_time << '\n'; 

}
/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerRR:: simulate(){
	double n  = (double)readyqueue.size();
	// time elapsed throughout the simulation
	unsigned int elapsed_time = 0;
	unsigned int total_w = 0; // total wait time
	unsigned int total_t = 0; // total turnaround time
	while( finished.size() < n){
		
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
		elapsed_time+= running_time;
	
		// adjust the new burst time now that the process has ran for some period of time	
		curr.burst_time = curr.burst_time - running_time;
	
		// adjust ran_time
		curr.ran_time += running_time;	
		
		// if the burst time is 0, the process is complete. 
		if(curr.burst_time == 0){
			
			// turnaround time will equal elapsed time at this moment
			curr.turnaround_time = elapsed_time;
	
			// waiting time = turnaround_time - burst_time 
			// ( we are using ran_time, because burst time is decreased as we run -
			// ran_time represents the original burst time value) 
			curr.waiting_time = curr.turnaround_time - curr.ran_time;

			// add to turnaround_time total for computing the average later
			total_t+=curr.turnaround_time;

			//add to waiting_time total for computing average later 
			total_w+= curr.waiting_time;

			// now insert to finished
			finished.push_back(curr);
		}else{
			// put the process back into the ready queue to be run again
			// reminder: the beginning of the readyqueue vector is the END of
			// the actual queue in terms of when processes run.
			readyqueue.insert(readyqueue.begin(), curr);
		}
	}
	this->average_waiting_time = double(total_w/n);
	this->average_turnaround_time = double(total_t/n);
	// finished simulation, time to sort PCBs
	std::sort(finished.begin(), finished.end(), PCB::compareId);

}

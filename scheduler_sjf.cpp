/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Jamison Coombs
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
//  Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"

// member functions init, print_results, and simulate here

/**
 * @brief Construct a new SchedulerSJF object
 */
SchedulerSJF::SchedulerSJF()
{
    waitingTime = 0;
}
/**
 * @brief Destroy the SchedulerSJF object
 */
SchedulerSJF::~SchedulerSJF() {}
/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerSJF::init(std::vector<PCB> &process_list)
{
    completedProcesses.reserve(process_list.size());
    for (auto &curr : process_list)
    {
        // Add process to the queue
        sjfQueue.push(curr);
    }
}
/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerSJF::print_results()
{
    for (auto &curr : completedProcesses)
    {
        cout << curr.name << " turn-around time = " << curr.turnaround_time << ", waiting time = " << curr.waiting_time << endl;
    }
    cout << "Average turn-around time = " << avgTurnAround << ", Average waiting time = " << avgWaitingTime << endl;
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerSJF::simulate()
{
    unsigned int n = sjfQueue.size();
    while (sjfQueue.empty() == false)
    {
        PCB curr = sjfQueue.top(); // set curr to the top element in the queue
        cout << "Running Process " << curr.name << " for " << curr.burst_time << " time units\n";
        // calculate waiting times and turnaround times and add those to the averages
        curr.waiting_time = waitingTime;
        avgWaitingTime += waitingTime;
        waitingTime += curr.burst_time;
        curr.turnaround_time = waitingTime;
        avgTurnAround += waitingTime;

        completedProcesses.push_back(curr); // Add pcb to the completed processes
        sjfQueue.pop(); // pop the waiting queue
    }
    // When done simulating sort the completed process list from lowest to highest ID
    sort(completedProcesses.begin(), completedProcesses.end(), PCB::compareId);
    // calculate the average waiting time and turnaround time
    avgWaitingTime = avgWaitingTime / n;
    avgTurnAround = avgTurnAround / n;
}

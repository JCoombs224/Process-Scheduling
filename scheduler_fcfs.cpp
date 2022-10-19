/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Jamison Coombs
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
//  Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"

/**
 * @brief Construct a new SchedulerFCFS object
 *
 */
SchedulerFCFS::SchedulerFCFS()
{
    waitingTime = 0;
}

/**
 * @brief Destroy the SchedulerFCFS object
 */
SchedulerFCFS::~SchedulerFCFS() {}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerFCFS::init(std::vector<PCB> &process_list)
{
    for (long unsigned int i = 0; i < process_list.size(); i++)
    {
        // Print process information when adding
        cout << "Process " << i << ": " << process_list.at(i).name << " has priority " << process_list.at(i).priority
             << " and burst time " << process_list.at(i).burst_time << endl;

        // Add process to the queue
        pQueue.push_back(process_list.at(i));
    }
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerFCFS::print_results()
{
    for (long unsigned int i = 0; i < pQueue.size(); i++)
    {
        PCB curr = pQueue.at(i);
        cout << curr.name << " turn-around time = " << curr.turnaround_time << ", waiting time = " << curr.arrival_time << endl;
    }
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerFCFS::simulate()
{
    cout << pQueue.size();
    for (long unsigned int i = 0; i < pQueue.size(); i++)
    {
        PCB &curr = pQueue.at(i);
        cout << "Running Process " << curr.name << " for " << curr.burst_time << " time units\n";
        curr.arrival_time = waitingTime;
        waitingTime += curr.burst_time;
        curr.turnaround_time = waitingTime;
    }
}
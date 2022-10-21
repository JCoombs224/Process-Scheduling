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

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and
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
    for (long unsigned int i = 0; i < process_list.size(); i++)
    {
        // Add process to the queue
        pSjfQueue.push_back(process_list.at(i));
    }
}
/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerSJF::print_results()
{
    cout << pSjfQueue.size() << endl;
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerSJF::simulate()
{
    cout << pSjfQueue.size() << endl;
    /** while (pQueue.empty() == false)
    {
        PCB curr = pQueue.top();
        cout << "Running Process " << curr.name << " for " << curr.burst_time << " time units\n";
        curr.arrival_time = waitingTime;
        waitingTime += curr.burst_time;
        curr.turnaround_time = waitingTime;
        pQueue.pop();
    } */
}

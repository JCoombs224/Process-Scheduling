/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#include "scheduler_priority.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here

/**
 * @brief Construct a new SchedulerPriority object
 */
SchedulerPriority::SchedulerPriority()
{
    waitingTime = 0;
}

/**
 * @brief Destroy the SchedulerPriority object
 */
SchedulerPriority::~SchedulerPriority() {}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerPriority::init(std::vector<PCB>& process_list)
{
    completedProcesses.reserve(process_list.size());
    for (auto &curr : process_list)
    {
        // Add process to the queue
        pQueue.push(curr);
    }
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerPriority::print_results()
{
    for (auto &curr : completedProcesses)
    {
        cout << curr.name << " turn-around time = " << curr.turnaround_time << ", waiting time = " << curr.arrival_time << endl;
    }
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerPriority::simulate()
{
     while (pQueue.empty() == false)
    {
        PCB curr = pQueue.top();
        cout << "Running Process " << curr.name << " for " << curr.burst_time << " time units\n";
        curr.arrival_time = waitingTime;
        waitingTime += curr.burst_time;
        curr.turnaround_time = waitingTime;
        completedProcesses.push_back(curr);
        pQueue.pop();
    }
    sort(completedProcesses.begin(), completedProcesses.end(), PCB::compareId);
}

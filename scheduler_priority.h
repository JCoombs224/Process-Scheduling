/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.h
 * @author Jamison Coombs
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#ifndef ASSIGN3_SCHEDULER_PRIORITY_H
#define ASSIGN3_SCHEDULER_PRIORITY_H

#include "scheduler.h"
#include <vector>
#include <bits/stdc++.h>

class SchedulerPriority : public Scheduler {
private:
    priority_queue<PCB, vector<PCB>, PCB::comparePriority> pQueue;
    vector<PCB> completedProcesses;
    unsigned int waitingTime; // Global waiting time for priority schedular
    double avgTurnAround = 0;
    double avgWaitingTime = 0;
public:
    /**
     * @brief Construct a new SchedulerPriority object
     */
    SchedulerPriority();

    /**
     * @brief Destroy the SchedulerPriority object
     */
    ~SchedulerPriority() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void simulate() override;

};


#endif //ASSIGN3_SCHEDULER_PRIORITY_H

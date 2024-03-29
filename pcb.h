/**
 * Assignment 1: priority queue of processes
 * @file pcb.h
 * @author Jamison Coombs & Jordan Aquino
 * @brief This is the header file for the PCB class, a process control block.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
//  Remember to addPCB sufficient comments to your code

#pragma once
#include <iostream>
#include <string>
using namespace std;

/**
 * @brief A process control block (PCB) Process control block(PCB) is a data structure representing a process in the system.
 *       It contains the following fields:
 *       - process ID (PID)
 *       - process name
 *       - burst time
 *       - priority
 *      You may add more fields if you need.
 *      ADDED FIELD
 *      - waiting time
 */
class PCB
{
public:
    // Name of the process
    string name;
    // The unique process ID
    unsigned int id;
    // The priority of a process. Larger number represents higher priority
    unsigned int priority;
    // The CPU burst time of the process
    unsigned int burst_time;
    // The arrival time of the process
    unsigned int arrival_time;
    // The turn-around time of the process
    unsigned int turnaround_time;
    // The waiting time for a proccess (USED IN RR)
    unsigned int waiting_time;
    // time the process has ran (USED IN RR)
    unsigned int ran_time;

    /**
     * @brief Construct a new PCB object
     * @param id: each process has a unique ID
     * @param priority: the priority of the process in the range 1-50. Larger number represents higher priority
     * @param state the state of the process.
     */
    PCB(string name, unsigned int id = 0, unsigned int priority = 1, unsigned int burst_time = 0)
    {
        this->id = id;
        this->name = name;
        this->priority = priority;
        this->burst_time = burst_time;
        this->arrival_time = 0;
        this->waiting_time = 0;
        this->turnaround_time = 0;
        this->ran_time = 0;
    }

    /**
     * @brief Destroy the PCB object.
     *
     */
    ~PCB() {}

    /**
     * @brief Print the PCB object.
     */
    void print()
    {
        cout << "Process " << id << ": " << name << " has priority " << priority << " and burst time "
             << burst_time << endl;
    }

    /**
     * @brief Compare the burst times and if they are the same return the process that arrived first.
     *
     */
    struct compareBurstTime
    {
        bool operator()(const PCB pcb1, const PCB pcb2)
        {
            if (pcb1.burst_time == pcb2.burst_time)
            {
                return !compareId(pcb1, pcb2);
            }
            return pcb1.burst_time > pcb2.burst_time;
        }
    };

    /**
     * @brief Compare the priority and if they are the same return the process that arrived first.
     *
     */
    struct comparePriority
    {
        bool operator()(const PCB pcb1, const PCB pcb2)
        {
            if (pcb1.priority == pcb2.priority)
            {
                return !compareId(pcb1, pcb2);
            }
            return pcb1.priority < pcb2.priority;
        }
    };
    /**
     * @brief Compares the priority for the priority round-robin scheduler. And returns the pcb with the 
     *        highest priority. If two pcbs have the same priority then it will compare the run-times and
     *        return the pcb with the least run time. If the run times are the same then it will return the
     *        pcb with the lowest ID value.
     */
    struct priorityRrComparator
    {
        bool operator()(const PCB pcb1, const PCB pcb2)
        {
            // First check if the priorities of the 2 pcbs are the same
            if (pcb1.priority == pcb2.priority)
            {
                // If the pcbs have the same amount of time they have been ran then compare the IDs
                if(pcb1.ran_time == pcb2.ran_time)
                    return !compareId(pcb1, pcb2);
                // Otherwise return the pcb with the lowest run time.
                return pcb1.ran_time > pcb2.ran_time;
            }
            // If the priorities are different return teh pcb with the highest priority
            return pcb1.priority < pcb2.priority;
        }
    };

    /**
     * @brief Return the process that arrived first based on the lower id.
     *
     */
    static bool compareId(PCB pcb1, PCB pcb2)
    {
        return pcb1.id < pcb2.id;
    }

    

};

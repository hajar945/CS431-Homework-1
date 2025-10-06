#include <iostream>
#include <vector>
#include <algorithm> // for min()
#include "functions.h"
using namespace std;

struct Process {
    int id, arrivalTime, burstTime, remainingTime, 
        completionTime, waitingTime, turnaroundTime;
};

void rrfunc()
{
    cout << "\n\nRound Robin (RR)\n";
    vector<int> gantt;
    int quantum = 2;
    int n = 5;
    vector<Process> p(n);

    // setting pid, arrivalTime and burstTime
    p[0] = { 1, 0, 2 };
    p[1] = { 2, 1, 1 };
    p[2] = { 3, 2, 8 };
    p[3] = { 4, 3, 4 };
    p[4] = { 5, 4, 5 };

    // set the remainingTime for each process to its burstTime initially
    for (int i = 0; i < n; i++) {
        p[i].remainingTime = p[i].burstTime;
    }

    // this queue will hold the indices of processes that have arrived and are ready to run
    vector<int> readyQueue;
    int currentTime = 0;        // tracks the current time 
    int completed = 0;          // counter for how many processes have finished.
	int processPointer = 0;     // pointer to track which processes have been added to the ready queue

    // main loop continues as long as not all processes are completed
    while (completed < n) {
        // Step 1: add any newly arrived processes to the ready queue
        while (processPointer < n && p[processPointer].arrivalTime <= currentTime) {
            readyQueue.push_back(processPointer);
            processPointer++;
        }

        // Step 2: If the ready queue is not empty, run the next proc
        if (!readyQueue.empty()) {
            // get the index of the process at the front of the queue
            int currentProcessIndex = readyQueue.front();
            readyQueue.erase(readyQueue.begin()); // remove it from the front

            // how long this process will run
            // either the quantum or the remaining time, whichever is smaller
			int timeToRun = min(quantum, p[currentProcessIndex].remainingTime); 

            // Step 3: load the Gantt chart for each time unit the process runs
            for (int j = 0; j < timeToRun; j++) {
                gantt.push_back(p[currentProcessIndex].id);
            }

            // update the process's remaining time
            p[currentProcessIndex].remainingTime -= timeToRun;
			currentTime += timeToRun; // update current time and move forward

            // Step 4: check if the process has finished.
            if (p[currentProcessIndex].remainingTime == 0) {
                completed++;
                p[currentProcessIndex].completionTime = currentTime;
                p[currentProcessIndex].turnaroundTime = p[currentProcessIndex].completionTime - p[currentProcessIndex].arrivalTime;
                p[currentProcessIndex].waitingTime = p[currentProcessIndex].turnaroundTime - p[currentProcessIndex].burstTime;
            }
            else {
                // if not finished, add it back to the queue for its next turn
                // but check again for any new arrivals that might've happened during its run
                while (processPointer < n && p[processPointer].arrivalTime <= currentTime) {
                    readyQueue.push_back(processPointer);
                    processPointer++;
                }
                readyQueue.push_back(currentProcessIndex);
            }
        }
        // Step 5: if the ready queue IS empty, the cpu is idle
        else {
            gantt.push_back(0); // push the idle marker (0)
			currentTime++;      // proceed to next unit of time
        }
    }

    // print the final stats table
    double totalWT = 0, totalTAT = 0;
    for (auto& proc : p) {
        totalWT += proc.waitingTime;
        totalTAT += proc.turnaroundTime;
        cout << "P" << proc.id << " CT " << proc.completionTime << " - AT " << proc.arrivalTime << " = TAT " << proc.turnaroundTime << endl;
    }
    cout << " \nAvg TAT = " << totalTAT / n << endl;



    // Print the Gantt Chart
    cout << "\nGantt Chart: ";
    if (!gantt.empty()) {
        int current_pid = gantt[0];
        int start_time = 0;
        for (size_t time = 1; time < gantt.size(); ++time) {
            if (gantt[time] != current_pid) {
                if (current_pid == 0) {
                    cout << "(IDLE, " << start_time << ", " << time << "), ";
                }
                else {
                    cout << "(P" << current_pid << ", " << start_time << ", " << time << "), ";
                }
                current_pid = gantt[time];
                start_time = time;
            }
        }
        // Print the last segment
        if (current_pid == 0) {
            cout << "(IDLE, " << start_time << ", " << gantt.size() << ")";
        }
        else {
            cout << "(P" << current_pid << ", " << start_time << ", " << gantt.size() << ")";
        }
    }
    cout << endl;
}
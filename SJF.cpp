#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"
using namespace std;

int ab;
struct Process {
    int id, arrivalTime, burstTime, remainingTime, completionTime, waitingTime, turnaroundTime;
};

// comparison function to sort the processes by arrival time
// https://brainly.com/question/35271164

// Function to compare processes based on arrival time
bool compare(Process a, Process b)
{
    return a.arrivalTime < b.arrivalTime;
    /* This process will always return TRUE
    if above condition comes*/
}

bool compare2(Process a, Process b)
{
    return a.burstTime < b.burstTime && a.arrivalTime <= ab;
    /* This process will always return TRUE
    if above condition comes*/
}

// https://www.hindicodingcommunity.com/2023/02/c-program-for-preemptive-sjf-shortest.html
// https://www.includehelp.com/algorithms/shortest-job-first-scheduling-algorithm.aspx
void sjffunc() {
    vector<int> gantt;
    cout << "\n\nShortest Job First (SJF)\n";
    
    int n = 5, currentTime = 0, completed = 0;

    vector<Process> p(n);

    // Only set id, arrivalTime and burstTime
    p[0] = {1, 0, 3};
    p[1] = {2, 2, 6};
    p[2] = {3, 4, 4};
    p[3] = {4, 6, 5};
    p[4] = {5, 8, 2};
    
    // set the remainingTime to burstTime at first
    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        p[i].remainingTime = p[i].burstTime;
    }
    
  
    sort(p.begin(), p.end(), compare);

    // initial values

    p[0].completionTime = p[0].burstTime + p[0].arrivalTime;
    p[0].turnaroundTime = p[0].completionTime - p[0].arrivalTime;
    p[0].waitingTime = p[0].turnaroundTime - p[0].burstTime;

    for (int i = 1; i < n; i++)
    {

        ab = p[i - 1].completionTime;
        sort(p.begin() + i, p.begin() + n, compare2);
        if (p[i - 1].completionTime < p[i].arrivalTime)
        {
            p[i].completionTime = p[i - 1].completionTime + p[i].burstTime + (p[i].arrivalTime - p[i - 1].completionTime);

        }
        else
        {

            p[i].completionTime = p[i - 1].completionTime + p[i].burstTime;

        }
       

        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;

    }
    
    // Populate the Gantt chart vector after all calculations are done
    // The 'p' vector is now sorted in the order of execution.
     int last_completion_time = 0;
    for (int i = 0; i < n; ++i) {
    // The time this process starts is its completion time minus its burst time
    int start_time = p[i].completionTime - p[i].burstTime;
       
    // Check for idle time between the last process and this one
    if (start_time > last_completion_time) {
    for (int t = last_completion_time; t < start_time; ++t) {
    gantt.push_back(0); // 0 represents an idle CPU
    }
    }
    // Add the current process to the gantt chart for its burst duration
    for (int t = 0; t < p[i].burstTime; ++t) {
     gantt.push_back(p[i].id);
    }
    // Update the time for the next iteration
    last_completion_time = p[i].completionTime;
    }
    
    double totalWT = 0, totalTAT = 0;for (auto& proc : p) {
        totalWT += proc.waitingTime;
        totalTAT += proc.turnaroundTime;
        cout << "\nP" << proc.id << " CT " << proc.completionTime << " - AT " << proc.arrivalTime << " = TAT " << proc.turnaroundTime << endl;
   }
        cout << " \nAvg TAT = " << totalTAT / n << endl;

        // printing the gantt chart:
        cout << "\nGantt Chart: ";
        // First, we must check if the timeline has anything in it. If not, we can't print.
        if (!gantt.empty()) {

            // We need to keep track of the segment we are currently looking at. A segment has:
            // 1. A process ID. We start by looking at the process at the very beginning (time 0).
            int process_id_of_current_segment = gantt[0];

            // 2. A start time. The first segment always starts at time 0.
            int start_time_of_current_segment = 0;

            // Now, we loop through the entire timeline, starting from the second moment (time 1),
            // looking for the exact moment the process ID changes.
            for (int time = 1; time < gantt.size(); ++time) {

                // Is the process at this 'time' DIFFERENT from the one in our current segment?
                if (gantt[time] != process_id_of_current_segment) {

                    // YES, it's different! This means our segment just ended at the current 'time'.
                    // So, let's print the segment that just finished.
                    if (process_id_of_current_segment == 0) {
                        cout << "(IDLE, " << start_time_of_current_segment << ", " << time << "), ";
                    }
                    else {
                        cout << "(P" << process_id_of_current_segment << ", " << start_time_of_current_segment << ", " << time << "), ";
                    }

                    // Now, we start tracking the NEW segment.
                    // The new segment's process is the one at the current 'time'.
                    process_id_of_current_segment = gantt[time];
                    // The new segment's start time is the current 'time'.
                    start_time_of_current_segment = time;
                }
            }

            // The loop above only prints when a process CHANGE occurs.
            // This means the VERY LAST segment will never be printed by the loop.
            // We have to print the last segment manually here. Its end time is the total timeline length.
            if (process_id_of_current_segment == 0) {
                cout << "(IDLE, " << start_time_of_current_segment << ", " << gantt.size() << ")";
            }
            else {
                cout << "(P" << process_id_of_current_segment << ", " << start_time_of_current_segment << ", " << gantt.size() << ")";
            }
        }

        cout << endl;



 }
#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"
using namespace std;

int currentTime; // global var to track current time 
struct Process {
    int id, arrivalTime, burstTime, remainingTime, completionTime, 
        waitingTime, turnaroundTime;
};

// https://brainly.com/question/35271164

// Function to compare processes based on arrival time
bool compare(Process a, Process b)
{
    return a.arrivalTime < b.arrivalTime;
    
}
// Function to compare processes based on burst time
bool compare2(Process a, Process b)
{
    return a.burstTime < b.burstTime && a.arrivalTime <= currentTime;
    
}

// https://www.hindicodingcommunity.com/2023/02/c-program-for-preemptive-sjf-shortest.html
// https://www.includehelp.com/algorithms/shortest-job-first-scheduling-algorithm.aspx
void sjffunc() {
    vector<int> gantt;
    cout << "\n\nShortest Job First (SJF)\n";
    
    int n = 5, completed = 0;

    vector<Process> p(n);

    // setting pid, arrivalTime and burstTime
    p[0] = {1, 0, 3};
    p[1] = {2, 2, 6};
    p[2] = {3, 4, 4};
    p[3] = {4, 6, 5};
    p[4] = {5, 8, 2};
    
    // set remainingTime to burstTime initially because each process hasn’t started yet
    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        p[i].remainingTime = p[i].burstTime;
    }
    
    // sorts the process list from earliest arrival to latest
    sort(p.begin(), p.end(), compare);


    p[0].completionTime = p[0].burstTime + p[0].arrivalTime; // first process starts as soon as it arrives and runs for its burstTime
    p[0].turnaroundTime = p[0].completionTime - p[0].arrivalTime; // TAT = total time from arrival to finish
	p[0].waitingTime = p[0].turnaroundTime - p[0].burstTime; // WT = TAT - time spent running

	for (int i = 1; i < n; i++) // for each remaining process
    {

        currentTime = p[i - 1].completionTime;
		sort(p.begin() + i, p.begin() + n, compare2); // sort the remaining arrived processes by shortest burstTime
		if (p[i - 1].completionTime < p[i].arrivalTime) // if next proc hasn't arrived yet when current one finishes
        {
            //cpu is idle until next proc arrives
			// so add the idle time (next proc's arrival - current proc's completion) to the next proc's burstTime
            p[i].completionTime = p[i - 1].completionTime + p[i].burstTime + (p[i].arrivalTime - p[i - 1].completionTime);

        }
        else
        {
            // if not, run next proc immediately after prev process
            p[i].completionTime = p[i - 1].completionTime + p[i].burstTime;

        }
       

		p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;// TAT = total time from arrival to finish
		p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime; // WT = TAT - time spent running

    }
    

    // load up the Gantt chart vector after all calculations are done
	int last_completion_time = 0; // tracking the end of the last process added to the chart
    for (int i = 0; i < n; ++i) {
    // the time this process starts is its completion time minus its burst time
    int start_time = p[i].completionTime - p[i].burstTime;
       
    // check for idle time between the last process and this one
    if (start_time > last_completion_time) {
		for (int t = last_completion_time; t < start_time; ++t) { // if there's idle time, fill it with 0s
            gantt.push_back(0); // 0 represents an idle CPU
        }
    }
    // add the current process to the gantt chart for its burst time
    for (int t = 0; t < p[i].burstTime; ++t) {
        gantt.push_back(p[i].id);
    }
    // update the time for the next iteration
    last_completion_time = p[i].completionTime;
    }
    
    double totalWT = 0, totalTAT = 0;
    for (auto& proc : p) {
		totalWT += proc.waitingTime; // sum up all waiting times
		totalTAT += proc.turnaroundTime; // sum up all turnaround times
        cout << "P" << proc.id << " CT " << proc.completionTime << " - AT " << proc.arrivalTime << " = TAT " << proc.turnaroundTime << endl;
    }
    cout << " \nAvg TAT = " << totalTAT / n << endl;

        // printing the gantt chart
        cout << "\nGantt Chart: ";
        // first, check if the timeline has anything in it. If not, can't print
        if (!gantt.empty()) {

            // must keep track of the segment currently being look at. A segment has:
            // 1. a process ID. start by looking at the proc at the very start (time 0)
            int process_id_of_current_segment = gantt[0];

            // 2. a start time. the first segment always starts at time 0.
            int start_time_of_current_segment = 0;

            // loop through the entire timeline, starting from the second moment (time 1),
            // looking for the exact moment the process ID changes.
            for (int time = 1; time < gantt.size(); ++time) {

                // is the process at this 'time' DIFFERENT from the one in our current segment?
                if (gantt[time] != process_id_of_current_segment) {

                    // yes it's different, means our segment just ended at the current time
                    // print the segment that just finished
                    if (process_id_of_current_segment == 0) {
                        cout << "(IDLE, " << start_time_of_current_segment << ", " << time << "), ";
                    }
                    else {
                        cout << "(P" << process_id_of_current_segment << ", " << start_time_of_current_segment << ", " << time << "), ";
                    }

                    // start tracking the NEW segment.
                    // new segment's process is the one at the current 'time'
                    process_id_of_current_segment = gantt[time];
                    // new segment's start time is the current 'time'
                    start_time_of_current_segment = time;
                }
            }

            // the loop above only prints when a process CHANGE happens
            // this means the VERY LAST segment will never be printed by the loop
            // we got to print the last segment manually here. Its end time is the total timeline length
            if (process_id_of_current_segment == 0) {
                cout << "(IDLE, " << start_time_of_current_segment << ", " << gantt.size() << ")";
            }
            else {
                cout << "(P" << process_id_of_current_segment << ", " << start_time_of_current_segment << ", " << gantt.size() << ")";
            }
        }

        cout << endl;



 }
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
    // Output the waiting time and turnaround time for each process
cout << "Process\tWaiting Time\tTurnaround Time";
        for (int i = 0; i < n; ++i) {
cout << "\nP" << p[i].id << "\t" << p[i].waitingTime << "\t\t" << p[i].turnaroundTime << " \n";
        }

        double totalWT = 0, totalTAT = 0;
        for (auto& proc : p) {
            totalWT += proc.waitingTime;
            totalTAT += proc.turnaroundTime;
            cout << "\nP" << proc.id << " CT " << proc.completionTime << " - AT " << proc.arrivalTime << " = TAT " << proc.turnaroundTime << endl;
        }
        cout << " \nAvg TAT = " << totalTAT / n << endl;

        // print the gantt chart:
        cout << "\nGantt Chart ";
        int prev = -1, start = 0;
        for (size_t i = 0; i < gantt.size(); ++i) {
            if (gantt[i] != prev) {
                if (prev != -1 && prev != 0) {
                    cout << "(P" << prev << ", " << start << ", " << i << "), ";
                }
                start = i;
                prev = gantt[i];
            }
        }
        // Print the last segment
        if (prev != 0) {
            cout << "(P" << prev << ", " << start << ", " << gantt.size() << ")";
        }
        cout << endl;

 }
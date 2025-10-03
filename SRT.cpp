#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"
using namespace std;

struct Process {
    int id, arrivalTime, burstTime, remainingTime, waitingTime, turnaroundTime, completionTime;
};
void srtfunc() {
    cout << "\n\nShortest Remaining Time (SRT)\n";
    vector<int> gantt;

    int n = 5, currentTime = 0, completed = 0;

    vector<Process> p(n);
	

    // Only set id, arrivalTime and burstTime
    p[0] = {1, 0, 3};
    p[1] = {2, 2, 6};
    p[2] = {3, 4, 4};
    p[3] = {4, 6, 5};
    p[4] = {5, 8, 2};
    cout << n << " processes are considered" << endl;
	// set the remainingTime to burstTime at first
    for (int i = 0; i < n; i++) {
        p[i].remainingTime = p[i].burstTime;
    }

    while (completed < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0 && (idx == -1 || p[i].remainingTime < p[idx].remainingTime)) {
                idx = i;
            }
        }
        if (idx != -1) {
            p[idx].remainingTime--;
            gantt.push_back(p[idx].id); // record which process ran
            currentTime++;
            if (p[idx].remainingTime == 0) {
                p[idx].completionTime = currentTime;
                p[idx].turnaroundTime = currentTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                completed++;
            }
        }
        else {
            gantt.push_back(0); // 0 means cpu is idle
            currentTime++;
        }
    }

    double totalWT = 0, totalTAT = 0;
    for (auto& proc : p) {
        totalWT += proc.waitingTime;
        totalTAT += proc.turnaroundTime;
        cout << "P" << proc.id << " CT " << proc.completionTime << " - AT " << proc.arrivalTime << " = TAT " << proc.turnaroundTime << endl;
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
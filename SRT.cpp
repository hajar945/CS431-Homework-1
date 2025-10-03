#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"
using namespace std;

struct Process {
    int id, arrivalTime, burstTime, remainingTime, waitingTime, turnaroundTime, completionTime;
};

void srtfunc() {
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
            currentTime++;
            if (p[idx].remainingTime == 0) {
                p[idx].completionTime = currentTime;
                p[idx].turnaroundTime = currentTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                completed++;
            }
        }
        else {
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


    // Visual representation of the FCFS schedule (Gantt chart in text)
    // https://labex.io/tutorials/cpp-c-program-for-fcfs-scheduling-algorithm-96161
    cout << "\n================= Gantt Chart =================" << endl;
    cout << " ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].burstTime; j++) {
            cout << "--";
        }
    }
    cout << endl << "|";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].burstTime - 1; j++) {
            cout << " ";
        }
        cout << "P" << i + 1;
        for (int j = 0; j < p[i].burstTime - 1; j++) {
            cout << " ";
        }
        cout << "|";
    }

    cout << endl << " ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].burstTime; j++) {
            cout << "--";
        }
    }

    cout << endl;
    cout << "0";
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        current_time += p[i].burstTime;
        for (int j = 0; j < p[i].burstTime * 2 - 1; j++) {
            cout << " ";
        }
        if (current_time < 10) cout << " ";
        cout << current_time;
    }
    cout << endl;
}
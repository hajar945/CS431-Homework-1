#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Shortest Remaining Time First (SRTF) Scheduling Algorithm
// https://www.geeksforgeeks.org/dsa/shortest-remaining-time-first-preemptive-sjf-scheduling-algorithm/
struct Process {
    int id, arrivalTime, burstTime, remainingTime, waitingTime, turnaroundTime, completionTime;
};

int main() {
    int n, currentTime = 0, completed = 0;
    cout << "Enter number of processes: ";
    cin >> n;
	cout << "Number of processes: " << n << endl;
    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter arrival time and burst time for process P" << p[i].id << ": ";
        cin >> p[i].arrivalTime >> p[i].burstTime;
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
}
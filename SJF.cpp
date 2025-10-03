#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"
using namespace std;

struct Process {
    int id, arrivalTime, burstTime, remainingTime, waitingTime, turnaroundTime, completionTime
};

// comparison function to sort the processes by arrival time
// https://brainly.com/question/35271164
bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;

}

// https://www.hindicodingcommunity.com/2023/02/c-program-for-preemptive-sjf-shortest.html
void sjffunc() {

    
    int n = 5, currentTime = 0, completed = 0;
    vector<Process> p(n);

        // Only set id, arrivalTime and burstTime
        p[0] = { 1, 0, 3 };
        p[1] = { 2, 2, 6 };
        p[2] = { 3, 4, 4 };
        p[3] = { 4, 6, 5 };
        p[4] = { 5, 8, 2 };
        cout << n << " processes are considered" << endl;

        sort(p.begin(), p.end(), compareArrivalTime);
        int currentTime = 0;
        // std::vector turnaroundTime(n, 0);
        int completedProcesses = 0;

        while (completedProcesses < n) {
            int shortestJobIdx = -1;
            for (int i = 0; i < n; ++i) {
                if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0)
                {
                    if (shortestJobIdx == -1 || p[i].remainingTime < p[shortestJobIdx].remainingTime) {
                        shortestJobIdx = i;
                    }
                }
            }
            if (shortestJobIdx == -1) {
                currentTime++;
            }
            else {
                p[shortestJobIdx].remainingTime--;
                currentTime++;
                if (p[shortestJobIdx].remainingTime == 0) {
                    completedProcesses++;
                    waitingTime[shortestJobIdx] = currentTime - processes[shortestJobIdx].arrivalTime - processes[shortestJobIdx].burstTime;
                    turnAroundTime[shortestJobIdx] = currentTime - processes[shortestJobIdx].arrivalTime;

                }

            }

        }
 }
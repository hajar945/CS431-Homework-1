#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"

using namespace std;
// Shortest Remaining Time First (SRTF) Scheduling Algorithm
// https://www.geeksforgeeks.org/dsa/shortest-remaining-time-first-preemptive-sjf-scheduling-algorithm/
struct Process {
    int id, arrivalTime, burstTime, remainingTime, waitingTime, turnaroundTime, completionTime;
};

int main() {
    //srtfunc();
    sjffunc();
    return 0;
}
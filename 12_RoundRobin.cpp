#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Struct to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

// Function to calculate waiting time, turnaround time, and finish time for each process
void calculateWaitingTurnaroundFinishTime(vector<Process> &processes, int timeQuantum, vector<int> &waitingTime, vector<int> &turnaroundTime, vector<int> &finishTime) {
    int n = processes.size();
    int currentTime = 0;
    int completed = 0;
    queue<int> readyQueue;

    // Initializing remaining time for each process
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Track if a process is in the ready queue or not
    vector<bool> inQueue(n, false);

    // Add processes to the queue if they have arrived
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= currentTime) {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }

    while (completed < n) {
        if (!readyQueue.empty()) {
            int i = readyQueue.front();
            readyQueue.pop();

            // Execute process for the minimum of time quantum or remaining time
            int executeTime = min(timeQuantum, processes[i].remaining_time);
            currentTime += executeTime;
            processes[i].remaining_time -= executeTime;

            // Check if any new processes have arrived during the execution
            for (int j = 0; j < n; j++) {
                if (!inQueue[j] && processes[j].arrival_time <= currentTime) {
                    readyQueue.push(j);
                    inQueue[j] = true;
                }
            }

            // If the process is not finished, put it back in the queue
            if (processes[i].remaining_time > 0) {
                readyQueue.push(i);
            } else {
                // Process is complete
                completed++;
                finishTime[i] = currentTime;
                turnaroundTime[i] = finishTime[i] - processes[i].arrival_time;
                waitingTime[i] = turnaroundTime[i] - processes[i].burst_time;
            }
        } else {
            // If the queue is empty, move time forward until the next process arrives
            currentTime++;
            for (int j = 0; j < n; j++) {
                if (!inQueue[j] && processes[j].arrival_time <= currentTime) {
                    readyQueue.push(j);
                    inQueue[j] = true;
                }
            }
        }
    }
}

// Function to display Gantt chart
void displayGanttChart(vector<Process> &processes, vector<int> &finishTime) {
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < processes.size(); i++) {
        cout << "| P" << processes[i].id << " ";
    }
    cout << "|\n";

    // Display timeline
    cout << "0 ";
    for (int time : finishTime) {
        cout << time << " ";
    }
    cout << endl;
}

int main() {
    int n, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    vector<Process> processes(n);
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> finishTime(n, 0);

    // Input process information
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
    }

    calculateWaitingTurnaroundFinishTime(processes, timeQuantum, waitingTime, turnaroundTime, finishTime);
    displayGanttChart(processes, finishTime);

    cout << "Process ID\tArrival Time\tBurst Time\tTurnaround Time\tFinish Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time
             << "\t\t" << processes[i].burst_time << "\t\t" << turnaroundTime[i]
             << "\t\t" << finishTime[i] << "\t\t" << waitingTime[i] << endl;
    }

    return 0;
}

/*
Enter the number of processes: 3
Enter the time quantum: 2
Enter arrival time for process 1: 0
Enter burst time for process 1: 3
Enter arrival time for process 2: 1
Enter burst time for process 2: 5
Enter arrival time for process 3: 2
Enter burst time for process 3: 2

Gantt Chart:
| P1 | P2 | P3 |
0 7 10 6
Process ID      Arrival Time    Burst Time      Turnaround Time Finish Time     Waiting Time
1               0               3               7               7               4
2               1               5               9               10              4
3               2               2               4               6               2
*/

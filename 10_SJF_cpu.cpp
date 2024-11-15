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
    int priority;
};

// Comparison function for the priority queue (Preemptive)
struct ComparePriority {
    bool operator()(const Process& a, const Process& b) {
        return a.priority > b.priority;
    }
};

// Function for Preemptive Priority Scheduling
void preemptivePriorityScheduling(vector<Process>& processes, int n) {
    // Manually sort processes based on arrival time (earlier arrival first)
    sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    int currentTime = 0;
    priority_queue<Process, vector<Process>, ComparePriority> readyQueue;
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> finishTime(n, 0);
    vector<int> remainingBurstTime(n); // To track remaining burst time of processes
    vector<bool> isInQueue(n, false); // To track if a process is already in the queue
    int completed = 0;

    // Initialize remaining burst time with the initial burst times
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = processes[i].burst_time;
    }

    while (completed < n) {
        // Add processes that have arrived and are not in the queue
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && remainingBurstTime[i] > 0 && !isInQueue[i]) {
                readyQueue.push(processes[i]);
                isInQueue[i] = true; // Mark the process as added to the queue
            }
        }

        // Process the one with the highest priority (preemptive)
        if (!readyQueue.empty()) {
            Process current = readyQueue.top();
            readyQueue.pop();

            int processId = current.id - 1;

            // Execute the process for one unit of time
            remainingBurstTime[processId]--;
            currentTime++;

            // If the process is completed
            if (remainingBurstTime[processId] == 0) {
                finishTime[processId] = currentTime;
                waitingTime[processId] = finishTime[processId] - processes[processId].arrival_time - processes[processId].burst_time;
                turnaroundTime[processId] = finishTime[processId] - processes[processId].arrival_time;
                completed++;
            } else {
                // Push the process back to the queue with reduced burst time
                readyQueue.push(current);
            }
        } else {
            currentTime++; // If no process is ready, just increment time
        }
    }

    // Display results
    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tFinish Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" 
             << processes[i].priority << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << "\t\t" << finishTime[i] << endl;
    }
}


// Function for Non-Preemptive Priority Scheduling
void nonPreemptivePriorityScheduling(vector<Process>& processes, int n) {
    // Manually sort processes based on priority (higher priority first)
    sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.priority > b.priority;
    });

    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> finishTime(n, 0);
    finishTime[0] = processes[0].burst_time;
    turnaroundTime[0] = processes[0].burst_time - processes[0].arrival_time;
    waitingTime[0] = turnaroundTime[0] - processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        finishTime[i] = finishTime[i - 1] + processes[i].burst_time;
        turnaroundTime[i] = finishTime[i] - processes[i].arrival_time;
        waitingTime[i] = turnaroundTime[i] - processes[i].burst_time;
    }

    // Display results
    cout << "Gantt Chart:\n";
    int totalTime = 0;
    for (const Process& process : processes) {
        cout << "| P" << process.id << " ";
        for (int i = 0; i < process.burst_time; i++) {
            cout << " ";
        }
        totalTime += process.burst_time;
    }
    cout << "|\n";
    cout << "0 ";
    for (int time : finishTime) {
        cout << " " << time << " ";
    }
    cout << endl;

    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tFinish Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" 
             << processes[i].priority << "\t\t" << turnaroundTime[i] << "\t\t" << finishTime[i] << "\t\t" << waitingTime[i] << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process information
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority for process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }


 


        cout << "\nPreemptive Priority Scheduling\n";
        preemptivePriorityScheduling(processes, n);
   
        cout << "\nNon-Preemptive Priority Scheduling\n";
        nonPreemptivePriorityScheduling(processes, n);
  
        
  

    return 0;
}

/*
Enter the number of processes: 7
Enter arrival time for process 1: 0
Enter burst time for process 1: 3
Enter priority for process 1: 2
Enter arrival time for process 2: 2
Enter burst time for process 2: 5
Enter priority for process 2: 6
Enter arrival time for process 3: 1
Enter burst time for process 3: 4
Enter priority for process 3: 3
Enter arrival time for process 4: 4
Enter burst time for process 4: 2
Enter priority for process 4: 5
Enter arrival time for process 5: 6
Enter burst time for process 5: 9
Enter priority for process 5: 7
Enter arrival time for process 6: 5
Enter burst time for process 6: 4
Enter priority for process 6: 4
Enter arrival time for process 7: 7
Enter burst time for process 7: 10
Enter priority for process 7: 10

Preemptive Priority Scheduling
Process ID      Arrival Time    Burst Time      Priority        Waiting Time    Turnaround Time Finish Time
1               0               3               2               0               3               3
3               1               4               3               18              22              23
2               2               5               6               1               6               8
4               4               2               5               13              15              19
6               5               4               4               18              22              27
5               6               9               7               2               11              17
7               7               10              10              20              30              37

Non-Preemptive Priority Scheduling
Gantt Chart:
| P7           | P5          | P2      | P4   | P6     | P3     | P1    |
0  10  19  24  26  30  34  37
Process ID      Arrival Time    Burst Time      Priority        Turnaround Time Finish Time     Waiting Time
7               7               10              10              3               10              -7
5               6               9               7               13              19              4
2               2               5               6               22              24              17
4               4               2               5               22              26              20
6               5               4               4               25              30              21
3               1               4               3               33              34              29
1               0               3               2               37              37              34
*/

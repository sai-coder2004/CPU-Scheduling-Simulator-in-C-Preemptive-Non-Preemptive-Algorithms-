# CPU Scheduling Simulator in C++ (Preemptive and Non-Preemptive Algorithms)

This project is a command-line based CPU Scheduling Simulator implemented in C++. It supports both **preemptive** and **non-preemptive** CPU scheduling algorithms, allowing users to simulate various scheduling strategies and view detailed performance metrics.

---

## ✅ Features

### Non-Preemptive Algorithms:
- First-Come-First-Serve (FCFS)
- Shortest Job First (SJF)
- Longest Job First (LJF)
- Highest Response Ratio Next (HRRN)

### Preemptive Algorithms:
- Round Robin (RR)
- Shortest Remaining Time First (SRTF)
- Longest Remaining Time First (LRTF)

### Output Metrics:
- Process table (Arrival Time, Burst Time, Start, Finish, Turnaround Time, Waiting Time, Response Time)
- Average Turnaround Time
- Average Waiting Time
- Average Response Time
- Throughput (Processes per unit time)

---

## 🔧 Files

├── main.cpp # User input & main logic
├── Non_preemptive.cpp # Contains FCFS, SJF, LJF, HRRN implementations
├── Preemptive.cpp # Contains RR, SRTF, LRTF implementations

---
##  How to Compile and Run
### Step 1: Compile the program
```bash
g++ main.cpp -o scheduler
./scheduler

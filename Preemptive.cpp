#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> p;
typedef pair<int, p> pp;

class Abs {
protected:
    priority_queue<pp, vector<pp>, greater<pp>> process;
    struct Info {
        int arrival, burst, start, finish, tat, wt, rt;
    };
    unordered_map<int, Info> mpp;
    int n = 0, mini = INT_MAX, time = 0;

public:
    virtual void run() = 0;

    void addProcess(int id, int at, int bt) {
        process.push({at, {id, bt}});
    }

    void print() {
        if (n == 0) {
            cout << "No processes scheduled.\n";
            return;
        }

        int totalTAT = 0, totalWT = 0, totalRT = 0;

        cout << "\n--- Output Matrix ---\n";
        cout << left << setw(12) << "Process"
             << setw(12) << "Arrival"
             << setw(12) << "Burst"
             << setw(12) << "Start"
             << setw(12) << "Finish"
             << setw(12) << "TAT"
             << setw(12) << "WT"
             << setw(12) << "RT" << endl;

        for (auto &[id, info] : mpp) {
            cout << left << setw(12) << id
                 << setw(12) << info.arrival
                 << setw(12) << info.burst
                 << setw(12) << info.start
                 << setw(12) << info.finish
                 << setw(12) << info.tat
                 << setw(12) << info.wt
                 << setw(12) << info.rt << endl;

            totalTAT += info.tat;
            totalWT += info.wt;
            totalRT += info.rt;
        }

        cout << fixed << setprecision(2);
        cout << "\nAverage TAT      : " << (float)totalTAT / n << endl;
        cout << "Average WT       : " << (float)totalWT / n << endl;
        cout << "Average RT       : " << (float)totalRT / n << endl;
        cout << "Throughput       : " << ((float)n / (time - mini)) << " processes/unit time\n";
    }

    virtual ~Abs() {}
};
class RR : public Abs {
    int quantum;

public:
    RR(int q) : quantum(q) {}
void run() override {
    struct P {
        int id, at, bt, rt;
    };

    vector<P> proc;
    map<int, int> pidToIndex;
    priority_queue<pp, vector<pp>, greater<pp>> copy = process;
    int index = 0;
    mini = INT_MAX;
    while (!copy.empty()) {
        auto [at, temp] = copy.top();
        auto [id, bt] = temp;
        proc.push_back({id, at, bt, bt});
        pidToIndex[id] = index++;
        mpp[id] = {at, bt, -1, 0, 0, 0, bt};
        mini = min(mini, at);
        copy.pop();
    }
    n = proc.size();
    time = 0;
    queue<int> ready;
    unordered_map<int, bool> visited;
    int completed = 0;
    for (auto &p : proc) {
        if (p.at <= time && !visited[p.id]) {
            ready.push(p.id);
            visited[p.id] = true;
        }
    }
    while (completed < n) {
        if (ready.empty()) {
            time++;
            for (auto &p : proc) {
                if (p.at <= time && !visited[p.id]) {
                    ready.push(p.id);
                    visited[p.id] = true;
                }
            }
            continue;
        }
        int pid = ready.front();
        ready.pop();
        int idx = pidToIndex[pid];
        auto &p = proc[idx];
        Info &info = mpp[pid];

        if (info.start == -1)
            info.start = time;
        int exec = min(quantum, p.rt);
        int prev_time = time;
        time += exec;
        p.rt -= exec;
        for (auto &pp : proc) {
            if (!visited[pp.id] && pp.at > prev_time && pp.at <= time) {
                ready.push(pp.id);
                visited[pp.id] = true;
            }
        }

        if (p.rt > 0) {
            ready.push(pid);
        } else {
            completed++;
            info.finish = time;
            info.rt = info.start - info.arrival;
            info.tat = info.finish - info.arrival;
            info.wt = info.tat - info.burst;
        }
    }
}


    ~RR() {}
};
class SRTF : public Abs {
public:
    void run() override {
        struct P {
            int id, at, bt, rt;
        };
        vector<P> proc;
        map<int, int> pidToIndex;
        priority_queue<pp, vector<pp>, greater<pp>> copy = process;
        int index = 0;
        mini = INT_MAX;
        while (!copy.empty()) {
            auto [at, temp] = copy.top();
            auto [id, bt] = temp;
            proc.push_back({id, at, bt, bt});
            pidToIndex[id] = index++;
            mpp[id] = {at, bt, -1, 0, 0, 0, bt};
            mini = min(mini, at);
            copy.pop();
        }
        n = proc.size();
        time = 0;
        int completed = 0;
        vector<bool> done(n, false);
        while (completed < n) {
            int idx = -1;
            int shortest = INT_MAX;

            for (int i = 0; i < n; ++i) {
                if (!done[i] && proc[i].at <= time && proc[i].rt < shortest && proc[i].rt > 0) {
                    shortest = proc[i].rt;
                    idx = i;
                }
            }

            if (idx == -1) {
                time++; 
                continue;
            }
            auto &p = proc[idx];
            Info &info = mpp[p.id];

            if (info.start == -1)
                info.start = time;
            p.rt--;
            time++;
            if (p.rt == 0) {
                done[idx] = true;
                completed++;
                info.finish = time;
                info.rt = info.start - info.arrival;
                info.tat = info.finish - info.arrival;
                info.wt = info.tat - info.burst;
            }
        }
    }

    ~SRTF() {}
};
class LRTF : public Abs {
public:
    void run() override {
        struct P {
            int id, at, bt, rt;
        };

        vector<P> proc;
        map<int, int> pidToIndex;
        priority_queue<pp, vector<pp>, greater<pp>> copy = process;
        int index = 0;
        mini = INT_MAX;
        while (!copy.empty()) {
            auto [at, temp] = copy.top();
            auto [id, bt] = temp;
            proc.push_back({id, at, bt, bt});
            pidToIndex[id] = index++;
            mpp[id] = {at, bt, -1, 0, 0, 0, bt};
            mini = min(mini, at);
            copy.pop();
        }
        n = proc.size();
        time = 0;
        int completed = 0;
        vector<bool> done(n, false);
        while (completed < n) {
            int idx = -1;
            int longest = -1;
            for (int i = 0; i < n; ++i) {
                if (!done[i] && proc[i].at <= time && proc[i].rt > longest) {
                    longest = proc[i].rt;
                    idx = i;
                }
            }
            if (idx == -1) {
                time++;
                continue;
            }
            auto &p = proc[idx];
            Info &info = mpp[p.id];
            if (info.start == -1)
                info.start = time;
            p.rt--;
            time++;
            if (p.rt == 0) {
                done[idx] = true;
                completed++;
                info.finish = time;
                info.rt = info.start - info.arrival;
                info.tat = info.finish - info.arrival;
                info.wt = info.tat - info.burst;
            }
        }
    }

    ~LRTF() {}
};


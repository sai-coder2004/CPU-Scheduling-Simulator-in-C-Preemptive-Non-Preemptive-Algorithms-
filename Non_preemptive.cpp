#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> p;
typedef pair<int, p> pp;

class Abstract {
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

        int totalTAT = 0, totalWT = 0;

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
        }

        cout << fixed << setprecision(2);
        cout << "\nAverage TAT      : " << (float)totalTAT / n << endl;
        cout << "Average WT       : " << (float)totalWT / n << endl;
        cout << "Average RT       : " << (float)totalWT / n << endl;
        cout << "Throughput       : " << ((float)n / (time - mini)) << " processes/unit time\n";
    }

    virtual ~Abstract() {}
};

class fcfs : public Abstract {
public:
    void run() override {
        n = process.size();
        int finish_time;
        while (!process.empty()) {
            int at = process.top().first;
            int id = process.top().second.first;
            int bt = process.top().second.second;
            process.pop();
            mini = min(mini, at);

            int start_time = max(time, at);
            finish_time = start_time + bt;
            time = finish_time;

            Info info;
            info.arrival = at;
            info.burst = bt;
            info.start = start_time;
            info.finish = finish_time;
            info.tat = finish_time - at;
            info.wt = start_time - at;
            info.rt = start_time - at;
            mpp[id] = info;
        }
    }
};

class sjf : public Abstract {
private:
    priority_queue<pp, vector<pp>, greater<pp>> pq;

public:
    void run() override {
        n = process.size();
        vector<pp> temp;
        while (!process.empty()) {
            temp.push_back(process.top());
            process.pop();
        }
        sort(temp.begin(), temp.end());

        int idx = 0;
        time = 0;
        mini = INT_MAX;

        while (idx < temp.size() || !pq.empty()) {
            while (idx < temp.size() && temp[idx].first <= time) {
                int at = temp[idx].first;
                int id = temp[idx].second.first;
                int bt = temp[idx].second.second;
                mini = min(mini, at);
                pq.push({bt, {id, at}});
                idx++;
            }

            if (!pq.empty()) {
                int bt = pq.top().first;
                int id = pq.top().second.first;
                int at = pq.top().second.second;
                pq.pop();

                int start_time = max(time, at);
                int finish_time = start_time + bt;
                time = finish_time;

                Info info;
                info.arrival = at;
                info.burst = bt;
                info.start = start_time;
                info.finish = finish_time;
                info.tat = finish_time - at;
                info.wt = start_time - at;
                info.rt = start_time - at;
                mpp[id] = info;
            } else if (idx < temp.size()) {
                time = temp[idx].first;
            }
        }
    }
};

class ljf : public Abstract {
private:
    priority_queue<pair<int, pair<int, int>>> pq;

public:
    void run() override {
        n = process.size();
        vector<pp> temp;
        while (!process.empty()) {
            temp.push_back(process.top());
            process.pop();
        }
        sort(temp.begin(), temp.end());

        int idx = 0;
        time = 0;
        mini = INT_MAX;

        while (idx < temp.size() || !pq.empty()) {
            while (idx < temp.size() && temp[idx].first <= time) {
                int at = temp[idx].first;
                int id = temp[idx].second.first;
                int bt = temp[idx].second.second;
                mini = min(mini, at);
                pq.push({bt, {id, at}});
                idx++;
            }

            if (!pq.empty()) {
                int bt = pq.top().first;
                int id = pq.top().second.first;
                int at = pq.top().second.second;
                pq.pop();

                int start_time = max(time, at);
                int finish_time = start_time + bt;
                time = finish_time;

                Info info;
                info.arrival = at;
                info.burst = bt;
                info.start = start_time;
                info.finish = finish_time;
                info.tat = finish_time - at;
                info.wt = start_time - at;
                info.rt = start_time - at;
                mpp[id] = info;
            } else if (idx < temp.size()) {
                time = temp[idx].first;
            }
        }
    }
};
class hrrn : public Abstract {
public:
    void run() override {
        n = process.size();
        vector<pp> temp;
        while (!process.empty()) {
            temp.push_back(process.top());
            process.pop();
        }
        sort(temp.begin(), temp.end());

        int idx = 0;
        time = 0;
        mini = INT_MAX;
        vector<bool> done(temp.size(), false);

        while (true) {
            bool any = false;
            double max_hr = -1.0;
            int chosen_idx = -1;

            for (int i = 0; i < temp.size(); ++i) {
                if (done[i]) continue;
                int at = temp[i].first;
                int id = temp[i].second.first;
                int bt = temp[i].second.second;

                if (at <= time) {
                    any = true;
                    mini = min(mini, at);
                    double wt = time - at;
                    double hr = (wt + bt) / (double)bt;
                    if (hr > max_hr) {
                        max_hr = hr;
                        chosen_idx = i;
                    }
                }
            }

            if (!any) {
                if (idx >= temp.size()) break;
                time = temp[idx].first;
                continue;
            }

            int at = temp[chosen_idx].first;
            int id = temp[chosen_idx].second.first;
            int bt = temp[chosen_idx].second.second;
            done[chosen_idx] = true;

            int start_time = time;
            int finish_time = start_time + bt;
            time = finish_time;

            Info info;
            info.arrival = at;
            info.burst = bt;
            info.start = start_time;
            info.finish = finish_time;
            info.tat = finish_time - at;
            info.wt = start_time - at;
            info.rt = start_time - at;
            mpp[id] = info;
        }
    }
};


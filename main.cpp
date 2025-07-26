#include<iostream>
#include "Non_preemptive.cpp"
#include "Preemptive.cpp"
using namespace std;
int main() {
    string s;
    int p;
    Abstract*schd=NULL;
    Abs*schd1=NULL;
    cout<<"Enter 1 for Non_preemptive Scheduling algo and 0 for Preemptive scheduling algo : "<<endl;
    cin>>p;
    if(cin.fail()) {
    cout << "Invalid input. Exiting.\n";
    return 0;
}
    if(p==1){
    cout << "Select Algorithm (CASE SENSITIVE):\n";
    cout << "1. FCFS\n2. SJF\n3. LJF\n4.HRNN\n";
    cin >> s;
    }
    else if(p==0){
        cout << "Select Algorithm (CASE SENSITIVE):\n";
        cout <<"1.RR\n2.SRTF\n3.LRTF\n"<<endl;
        cin >> s;
    }
    else{
        cout<<"Invlaid choice";
        return 0;
    }

    if (s == "FCFS") schd = new fcfs();
    else if (s == "SJF") schd = new sjf();
    else if (s == "LJF") schd = new ljf();
    else if(s=="HRNN")schd=new hrrn();
    else if(s=="RR"){
        int time_qu;
        cout<<"Enter time_quantum"<<endl;
        cin>>time_qu;
        schd1=new RR(time_qu);
    }
    else if(s=="SRTF")schd1=new SRTF();
    else if(s=="LRTF")schd1=new LRTF();
    
    else {
        cout << "Invalid choice. Exiting.\n";
        return 0;
    }

    int x;
    cout << "Enter 1 to add process, or 0 to execute: ";
    cin >> x;
    if(cin.fail()){
        cout<<"Invalid input. Exiting...";
        return 0;
    }
    while (x) {
        int id, at, bt;
        cout << "Enter Process ID, Arrival Time, and Burst Time: ";
        cin >> id >> at >> bt;
        if(cin.fail()){
        cout<<"Invalid input. Exiting...";
        return 0;
    }
        if(p==1)schd->addProcess(id, at, bt);
        else if(p==0)schd1->addProcess(id,at,bt);
        cout << "Enter 1 to add another process, or 0 to execute: ";
        cin >> x;
    }

    cout << "\n--- Execution Start ---\n";
    if(p==1){
    schd->run();       
    schd->print();}
    else if(p==0){
        schd1->run();
        schd1->print();
    }
    cout << "--- Execution End ---\n";

    delete schd;
    return 0;
}

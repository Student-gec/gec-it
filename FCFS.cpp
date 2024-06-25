1) FCFS WITHOUT ARRIVAL TIME
#include<iostream>
using namespace std;

int waitingtime(int n,int bt[],int wt[])
 {
 cout<<"The waiting time for process 1 is :0"<<endl;
 wt[0]=0;
 for(int i=1;i<n;i++)
  {
   wt[i]=wt[i-1]+bt[i-1];
   cout<<"The waiting time for process "<<i<<" is: "<<wt[i]<<endl;
  }
 } 
int turnaroundtime(int n,int bt[],int wt[],int TT[])
 { 
  for(int i=0;i<n;i++)
  {
   TT[i]=bt[i]+wt[i];
   cout<<"The turnaround time for process "<<i<<" is: "<<TT[i]<<endl;
  }
 }
int time(int n,int bt[])
{
 int wt[n],TT[n];
 float avg_wt,avg_tt,totalwt=0,totaltt=0;
 waitingtime(n,bt,wt);
 for(int i=0;i<n;i++)
  totalwt+=wt[i];
 avg_wt=totalwt/n;
 cout<<"The average waiting time is:"<<avg_wt<<"ms"<<endl;
 turnaroundtime(n,bt,wt,TT);
 for(int i=0;i<n;i++)
  totaltt+=TT[i];
 avg_tt=totaltt/n;
 cout<<"the average turnaround time is:"<<avg_tt<<"ms"<<endl;
}
int main()
{
 int n;
 int burstime[100];
 cout<<"Enter the number of process:"<<endl;
 cin>>n;
 for(int i=0;i<n;i++)
  {
   cout<<"Enter the bustime for process"<<i<<":"<<endl;
   cin>>burstime[i];
  }
 time(n,burstime);
}

2)FCFS WITH ARRIVAL TIME

#include<iostream>
#include<stdlib.h>
using namespace std;

class Process {
 public:
 int id, bt, at, tat, wt;
  void input(Process*, int);
  void calc(Process*, int);
  void show(Process*, int);
  void sort(Process*, int);
};
int main() {
 int n;
 cout << "\nEnter the number of processes in your system:\n";
 cin >> n;
 Process *p = new Process[n];
 Process f;
 f.input(p, n);
 f.sort(p, n);
 f.calc(p, n);
 f.show(p, n);
 
// Calculate and display average turnaround time and average waiting time
 float avg_wt = 0, avg_tat = 0;
 for (int i = 0; i < n; i++) {
  avg_wt += p[i].wt;
  avg_tat += p[i].tat;
 }
 avg_wt /= n;
 avg_tat /= n;
 cout << "\nAverage Waiting Time: " << avg_wt << " ms" << endl;
 cout << "Average Turnaround Time: " << avg_tat << " ms" << endl;
 return 0;
}
void Process::input(Process *p, int n) {
 for (int i = 0; i < n; i++) {
   cout << "\nEnter arrival time for process " << i + 1 << ":\n";
   cin >> p[i].at;
   cout << "\nEnter burst time for process " << i + 1 << ":\n";
   cin >> p[i].bt;
   p[i].id = i + 1;
  }
}
void Process::calc(Process* p, int n) {
 int sum = 0;
 sum = sum + p[0].at;
 for (int i = 0; i < n; i++) {
   sum = sum + p[i].bt;
   p[i].tat = sum - p[i].at;
   p[i].wt = p[i].tat - p[i].bt;
   if (i + 1 < n && sum < p[i + 1].at) {
    int t = p[i + 1].at - sum;
    sum = sum + t;
   }
  }
}
void Process::sort(Process* p, int n) {
 for (int i = 0; i < n - 1; i++) {
  for (int j = 0; j < n - i - 1; j++) {
   if (p[j].at > p[j + 1].at) {
    int temp;
    temp = p[j].bt;
    p[j].bt = p[j + 1].bt;
    p[j + 1].bt = temp;
    temp = p[j].at;
    p[j].at = p[j + 1].at;
    p[j + 1].at = temp;
    temp = p[j].id;
    p[j].id = p[j + 1].id;
    p[j + 1].id = temp;
   }
  }
 }
}
void Process::show(Process* p, int n) {
 cout << "Process\tArrival\tBurst\tWaiting\tTurn Around\n";
 for (int i = 0; i < n; i++) {
  cout << " P[" << p[i].id << "]\t " << p[i].at << "\t" << p[i].bt << "\t" << p[i].wt << "\t " << p[i].tat << "\n";
 }
}
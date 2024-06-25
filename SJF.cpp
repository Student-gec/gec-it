Case1) SHORTEST JOB NEXT WITHOUT ARRIVAL TIME

#include<iostream>
using namespace std;
int waitingtime(int n,int bt[],int wt[])
 {
  wt[0]=0;
  cout<<"Waiting time of process 1 is : 0"<<endl;
  for(int i=1;i<n;i++)
   {
    wt[i]=wt[i-1]+bt[i-1];
    cout<<"Waiting time of process "<<i+1<<" is : "<<wt[i]<<endl;
   }
 }
int turnaroundtime(int n,int bt[],int wt[],int TT[])
 {
  for(int i=0;i<n;i++)
   {
    TT[i]=bt[i]+wt[i];
    cout<<"Turnarround time of process "<<i+1<<" is : "<<TT[i]<<endl;
   }
 }
int time(int n,int bt[])
 {
  int wt[n],TT[n];
  float avg_wt,avg_tt,totalwt=0,totaltt=0;
  waitingtime(n,bt,wt);
  turnaroundtime(n,bt,wt,TT);
  for(int i=0;i<n;i++)
   {
    totalwt+=wt[i];
    totaltt+=TT[i];
   }
 avg_wt=totalwt/n;
 avg_tt=totaltt/n;
 cout<<"The average waiting time is:"<<avg_wt<<"ms"<<endl;
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
   cout<<"Enter the bustime for process"<<i+1<<":"<<endl;
   cin>>burstime[i];
  }
 for(int i = 0; i < n - 1; i++)
  {
   for(int j = 0; j < n - i - 1; j++)
    {
     if(burstime[j + 1] < burstime[j])
      {
       int temp = burstime[j + 1];
       burstime[j + 1] = burstime[j];
       burstime[j] = temp;
      }
    }
  }
cout<<endl;
time(n,burstime);
}



Case 2) SHORTEST JOB NEXT WITH ARRIVAL TIME

#include <iostream>
using namespace std;
struct Process {
 int bt; // Burst Time
 int art; // Arrival Time
};
void findWaitingTime(Process proc[], int n, int wt[]) 
{
 int rt[n];
 for (int i = 0; i < n; i++)
 rt[i] = proc[i].bt;
 int complete = 0, t = 0, minm = INT_MAX;
 int shortest = 0, finish_time;
 bool check = false;

 while (complete != n) {
  for (int j = 0; j < n; j++) {
   if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
    minm = rt[j];
    shortest = j;
    check = true;
   }
 }
 if (check == false) {
  t++;
  continue;
 }
 rt[shortest]--;
 minm = rt[shortest];
 if (minm == 0)
   minm = INT_MAX;
 if (rt[shortest] == 0) {
   complete++;
 check = false;
 finish_time = t + 1;
 wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;
 if (wt[shortest] < 0)
   wt[shortest] = 0;
 }
 t++;
 }
}

void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
 for (int i = 0; i < n; i++)
   tat[i] = proc[i].bt + wt[i];
}

void findavgTime(Process proc[], int n) {
 int wt[n], tat[n], total_wt = 0, total_tat = 0;
 findWaitingTime(proc, n, wt);
 findTurnAroundTime(proc, n, wt, tat);
 cout << " BT\t\t" << "WT\t\t" << "TAT\t\t\n";
 for (int i = 0; i < n; i++) {
 total_wt = total_wt + wt[i];
 total_tat = total_tat + tat[i];
 cout << " " << proc[i].bt << "\t\t " << wt[i] << "\t\t " << tat[i] << endl;
 }
 cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
 cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}


int main() {
 int n;
 cout << "Enter the number of processes: ";
 cin >> n;
 Process proc[n];
 for (int i = 0; i < n; i++) {
 cout << "Enter details for process " << i + 1 << ":" << endl;
 cout << "Burst Time: ";
 cin >> proc[i].bt;
 cout << "Arrival Time: ";
 cin >> proc[i].art;
 }
 findavgTime(proc, n);
 return 0;
}
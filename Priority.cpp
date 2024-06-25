Case 1: Without Arrival Time.
#include<iostream>
using namespace std;
int waitingtime(int n,int bt[],int wt[],int priority[])
{
	wt[0]=0;
	cout<<"The waiting time of process is: 0 "<<endl;
	for(int i=1;i<n;i++)
	{   
		wt[i]=wt[i-1]+bt[i-1];
		cout<<"The Waiting time of process is: "<<wt[i]<<endl;
	}
}
int turnaroundtime(int n,int bt[],int wt[],int TT[])
{
	for(int i=0;i<n;i++)
	{
		TT[i]=bt[i]+wt[i];
		cout<<"The turnarround time of process is: "<<TT[i]<<endl;
	}	
}
int time(int n,int bt[],int priority[])
{
	int wt[n],TT[n];
	float avg_wt,avg_tt,totalwt=0,totaltt=0;
	waitingtime(n,bt,wt,priority);
	for(int i=0;i<n;i++)
	{
		totalwt+=wt[i];
	}
	avg_wt=totalwt/n;
	cout<<"The average waiting time is:"<<avg_wt<<"ms"<<endl;
	turnaroundtime(n,bt,wt,TT);
	for(int i=0;i<n;i++)
	{
		totaltt+=TT[i];
	}
	avg_tt=totaltt/n;
	cout<<"the average turnaround time is:"<<avg_tt<<"ms"<<endl;
}
void swap(int &a,int &b)
{
	int temp=a;
	a=b;
	b=temp;
}
int main()
{
	int n,priority[100];
	int burstime[100];
	cout<<"Enter the number of process:"<<endl;
	cin>>n;
	for(int i=0;i<n;i++)
	{
	   cout<<"Enter the bustime for process"<<i+1<<":"<<endl;
	   cin>>burstime[i];
	   cout<<"Enter the priority for process"<<i+1<<":"<<endl;
	   cin>>priority[i];
	}
	for (int i=0;i<n-1;i++)
    {
        for (int j=0;j<n-i-1;j++) 
		{
            if (priority[j]>priority[j+1]) 
			{
                swap(priority[j],priority[j+1]);
                swap(burstime[j],burstime[j+1]);
            }
        }
    }
	cout<<endl;
	time(n,burstime,priority);
}


CASE2: WITH ARRIVAL TIME
#include<iostream>
#include<algorithm>
#include<climits>
using namespace std;
struct Process {
    int burstTime;
    int priority;
    int arrivalTime;
    int processID;
};
bool compareArrivalTime(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;
}
bool comparePriority(Process p1, Process p2) {
    if (p1.priority != p2.priority)
        return p1.priority < p2.priority;
    else
        return p1.arrivalTime < p2.arrivalTime;
}
void findWaitingTime(Process proc[], int n, int wt[]) {
    int service_time[n];
    service_time[0] = proc[0].arrivalTime;
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i - 1] + proc[i - 1].burstTime;
        wt[i] = service_time[i] - proc[i].arrivalTime;
        wt[i] = max(0, wt[i]);
    }
}
void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].burstTime + wt[i];
}
void findavgTime(Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);
    cout << "Process\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << proc[i].processID << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }
    cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turnaround time = " << (float)total_tat / (float)n;
}
int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].processID = i + 1;
        cout << "Enter details for process " << i + 1 << ":" << endl;
        cout << "Burst Time: ";
        cin >> proc[i].burstTime;
        cout << "Arrival Time: ";
        cin >> proc[i].arrivalTime;
        cout << "Priority: ";
        cin >> proc[i].priority;
    }
    sort(proc, proc + n, compareArrivalTime);
    sort(proc, proc + n, comparePriority);
    findavgTime(proc, n);
    return 0;
}

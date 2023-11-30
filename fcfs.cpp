#include <iostream>
#include <algorithm>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void sortProcesses(int p[], int at[], int bt[], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(p[j], p[j + 1]);
            }
        }
    }
}

double calculateAverage(const int arr[], int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum / size;
}

int main()
{
    int N;
    cout << "Enter the number of processes: ";
    cin >> N;

    // Input
    int at[N], bt[N], p[N], wait[N], tat[N], ct[N];
    for (int i = 0; i < N; i++)
    {
        cout << "Enter arrival and burst time for process " << i + 1 << ": ";
        cin >> at[i] >> bt[i];
        p[i] = i + 1;
    }

    sortProcesses(p, at, bt, N);

    // FCFS
    wait[0] = 0;
    ct[0] = at[0] + bt[0];

    for (int i = 0; i < N; i++)
    {
        int idle_time = 0;
        wait[i] = ct[i] - bt[i] - at[i];
        if (at[i + 1] > ct[i])
        {
            idle_time += at[i + 1] - ct[i];
        }
        ct[i + 1] = ct[i] + bt[i + 1] + idle_time;
        tat[i] = wait[i] + bt[i];
    }

    // Display
    cout << "\nProcess\tArrival\tBurst\tWait\tTAT\n";
    for (int i = 0; i < N; i++)
        cout << p[i] << "\t" << at[i] << "\t" << bt[i] << "\t" << wait[i] << "\t" << tat[i] << endl;

    cout << "\nAvg wait time: " << calculateAverage(wait, N);
    cout << "\nAvg turnaround time: " << calculateAverage(tat, N) << endl;

    return 0;
}
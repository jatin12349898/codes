#include <iostream>
using namespace std;
int main()
{
    // Arrays to store information about processes
    int pr[10];
    int at[10];
    int bt[10];
    int rbt[10];
    int tat[10] = {0};
    int wt[10] = {0};
    int completed = 0;
    int elapsed = 0;

    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    // Input details for each process
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the priority of process " << i + 1 << ": ";
        cin >> pr[i];
        cout << "Enter the arrival time of process " << i + 1 << ": ";
        cin >> at[i];
        cout << "Enter the burst time of process " << i + 1 << ": ";
        cin >> bt[i];
        rbt[i] = bt[i]; // Initialize remaining burst time
        tat[i] = 0;     // Initialize turnaround time
        wt[i] = 0;      // Initialize waiting time
    }


    // Loop until all processes are completed
    while (completed != n)
    {
        int selected = 10; // Default value indicating no process is selected

        // Select the process with the highest priority among eligible processes
        for (int i = 0; i < n; i++)
        {
            if (rbt[i] > 0)
            {
                // If no process is selected or the current process has higher priority
                if (selected == 10 && at[i] <= elapsed)
                {
                    selected = i;
                }
                else if (at[i] <= elapsed && pr[i] > pr[selected])
                {
                    selected = i;
                }
            }
        }
        if (selected == 10)
        {
            // If no eligible process is found, increment time
            elapsed++;
        }
        else
        {
            // Execute the selected process
            completed++;
            elapsed += bt[selected];
            rbt[selected] = 0;                           // Set remaining burst time to 0
            tat[selected] = elapsed - at[selected];      // Calculate turnaround time
            wt[selected] = tat[selected] - bt[selected]; // Calculate waiting time
        }
    }
    // Output turnaround time and waiting time for each process
    for (int i = 0; i < n; i++)
    {
        cout << "TAT and WT of process P" << i + 1 << ": ";
        cout << tat[i] << " and ";
        cout << wt[i] << endl;
    }
    return 0;
}

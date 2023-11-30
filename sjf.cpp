#include <iostream>
using namespace std;

// Returns the index of the process with the minimum burst time
int minimumBT(int BT[], int n)
{
    int min = 10000;
    int min_index = -1;
    for (int i = 0; i < n; i++)
    {
        if (BT[i] > 0 && BT[i] < min)
        {
            min = BT[i];
            min_index = i;
        }
    }
    return min_index;
}

// Returns true if all the processes have executed else returns false
bool check(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
        {
            return false;
        }
    }
    return true;
}

// Driver Main
int main()
{
    // Number of processes
    int n = 4;

    // Process details
    int process[] = {1, 2, 3, 4};
    int at[] = {0 , 2 , 4 , 5};
    int bt[] = {7 , 4 , 1 , 4};
    int bto[] = {7 , 4 , 1 , 4};

    // Array to keep track of completed processes
    int is_complete[] = {0, 0, 0, 0};

    // Arrays to store turnaround time, waiting time, and exit time
    int tat[] = {0, 0, 0, 0};
    int wt[] = {0, 0, 0, 0};
    int ct[] = {0, 0, 0, 0};

    // Sorting all the processes according to arrival times
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                // Swap process details if arrival times are not in order
                swap(process[j], process[j + 1]);
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(bto[j], bto[j + 1]);
            }
        }
    }

    // Time variable to keep track of the current time
    int time = at[0];

    // Main loop to execute processes
    while (!check(is_complete, n))
    {
        int j = 0;
        // Checking how many processes have arrival time <= current time and then setting the j pointer accordingly
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time)
            {
                j++;
            }
        }

        // Running the task with the minimum BT
        int running = minimumBT(bt, j);

        // Updating the time variable
        time = time + bt[running];

        // Marking the process as complete and recording exit time
        bt[running] = 0;
        is_complete[running] = 1;
        ct[running] = time;
    }

    // Calculating the TurnAroundTime and Waiting Time for each process
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bto[i];
    }

    // Printing all the data
    cout << "P"
         << "\t"
         << "AT"
         << "\t"
         << "BT"
         << "\t"
         << "WT"
         << "\t"
         << "TAT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << process[i] << "\t" << at[i] << "\t" << bto[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }

    return 0;
}
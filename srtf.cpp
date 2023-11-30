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

int main()
{
    int n = 4;
    int process[] = {1, 2, 3, 4};
    int at[] = {0, 1, 2, 3};
    int bt[] = {6, 4, 2, 3};
    int bto[] = {6, 4, 2, 3};

    // To keep track of the completed processes
    int is_complete[] = {0, 0, 0, 0};
    int tat[] = {0, 0, 0, 0};
    int wt[] = {0, 0, 0, 0};
    int ct[] = {0, 0, 0, 0};

    // Sorting all the processes according to the arrival times
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                swap(process[j], process[j + 1]);
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(bto[j], bto[j + 1]);
            }
        }
    }

    int time = 0;
    while (!check(is_complete, n))
    {
        int j = 0;

        // Checking how many process have arrival time <= current time and then setting the j pointer accordingly
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time)
            {
                j++;
            }
        }

        // Running the task with the minimum BT
        int running = minimumBT(bt, j);

        // Updating the time variable and reducing the time variable by 1
        ++time;
        --bt[running];

        // Check for the process completion
        if (bt[running] == 0)
        {
            is_complete[running] = 1;
            ct[running] = time;
        }
    }

    // Calculating the TurnAroundTime and Waiting Time for (int i = 0; i < n; i++)
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
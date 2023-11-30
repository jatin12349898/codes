#include <iostream>
// Using the inbuid queues in C++
#include <queue>
using namespace std;

// Function to check whether all the processes have executed or not
bool check(bool arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == false)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    // Initializing a Queue to be used as the ready queue of RR
    queue<int> rq;

    // n=Total number of processes
    int n = 4;

    int process[] = {1, 2, 3, 4};
    int at[] = {0, 1, 2, 4};
    int bt[] = {5, 4, 2, 1};
    int bto[] = {5, 4, 2, 1};
    int tat[] = {0, 0, 0, 0};
    int wt[] = {0, 0, 0, 0};
    int ct[] = {0, 0, 0, 0};
    bool is_completed[] = {false, false, false, false, false, false};

    int p_i[n]; // Stores the index of a process
    for (int i = 0; i < n; i++)
    {
        p_i[i] = process[i] - 1;
    }

    // Sorting the given process according to their arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                swap(process[j], process[j + 1]);
                swap(p_i[j], p_i[j + 1]);
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(bto[j], bto[j + 1]);
            }
        }
    }
    // q stores the time Quantum
    int q = 2;
    // Variable running stores the index of the process that is currently executing
    int running = p_i[0];
    // time variable keeps record of the time
    int time = at[0];

    // break_time increases by q everytime a process ends or a time quantum ends
    // Note break_time is necessary because for eg: If q=2 and BT=1 then the new process will run from 1-3 and not 1-2
    int break_time = q;

    while (!check(is_completed, n)) // Executing till all the process have not completed
    {
        --bt[running];
        ++time;

        // Checking and adding to the ready queue if a process has arrivesd at this time
        for (int i = 0; i < n; i++)
        {
            if (at[i] == time)
            {
                rq.push(p_i[i]);
            }
        }

        // Process switching condition
        if (bt[running] == 0 || time == break_time)
        {
            if (bt[running] == 0)
            {
                is_completed[running] = true;
                ct[running] = time;
            }
            else
            {
                // If the process is incomplete, it is pushed back into the ready queue
                rq.push(running);
            }

            // front() gets first element of the queue and pop() removes it from the queue
            running = rq.front();
            rq.pop();

            break_time = time + q;
        }
    }

    // Calculating the TurnAroundTime and Waiting Time
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
         << "TAT"
         << endl;
    for (int i = 0; i < n; i++)
    {
        cout << process[i] << "\t" << at[i] << "\t" << bto[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }
    return 0;
}

// To check for different examples change the data of the required fields
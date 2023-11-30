#include <iostream>
using namespace std;

int main()
{
    int n = 5; // Number of processes
    int m = 3; // Number of resources

    // Allocation Matrix
    int alloc[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};

    // MAX Matrix
    int max[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};

    // Available Resources
    int avail[3] = {3, 3, 2};

    int finished[n] = {0, 0, 0, 0, 0}; // To keep track of the allocated processes

    int ans[n];  // Stores the final safe sequence
    int ind = 0; // Global index for the ans matrix

    // Need = Max - Allocation
    int need[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            // If the process has not finished
            if (finished[i] == 0)
            {
                // flag value 0 indicates that need < available ==> resource will be allocated
                int flag = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++)
                        avail[y] = avail[y] + alloc[i][y];
                    finished[i] = 1;
                }
            }
        }
    }

    int flag = 1;

    // To check if the sequence is safe or not
    for (int i = 0; i < n; i++)
    {
        if (finished[i] == 0)
        {
            flag = 0;
            cout << "The given sequence is not safe";
            break;
        }
    }

    if (flag == 1)
    {
        cout << "Following is the SAFE Sequence" << endl;
        for (int i = 0; i < n - 1; i++)
            cout << " P" << ans[i] << " ->";
        cout << " P" << ans[n - 1] << endl;
    }

    return (0);
}

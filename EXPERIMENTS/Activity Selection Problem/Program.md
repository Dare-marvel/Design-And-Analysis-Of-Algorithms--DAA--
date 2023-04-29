## Code:
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// dynamic approach
struct activity
{
    int start;
    int end;
};

void bubbleSort(struct activity arr[], int n)
{
    int i, j, temp1, temp2;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j].end > arr[j + 1].end)
            { // swap start and end times
                temp1 = arr[j].end;
                arr[j].end = arr[j + 1].end;
                arr[j + 1].end = temp1;
                temp2 = arr[j].start;
                arr[j].start = arr[j + 1].start;
                arr[j + 1].start = temp2;
            }
        }
    }
}

int activitySelectionDP(struct activity arr[], int n, struct activity nonOverlap[], int *nonOverlapCount)
{
    printf("\nDYNAMIC PROGRAMMING:\n");
    // sorting the activities in increasing order of their end time
    bubbleSort(arr, n);

    // dp[i] stores the maximum count of non-conflicting activities till i'th activity
    int *dp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            // when `arr[j].end` is less than equal to `arr[i].start`
            if (arr[j].end <= arr[i].start && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
            }
        }
    }

    // finding the maximum activity count in dp
    int maxCount = dp[0];
    for (int i = 1; i < n; i++)
    {
        if (dp[i] > maxCount)
        {
            maxCount = dp[i];
        }
    }

    // printing non-overlapping activities
    printf("\nNon-overlapping activities using dynamic programming:\n");
    int i, j;
    while (i <= n - 1 && j <= maxCount - 1)
    {
        if (dp[i] == j + 1)
        {
            nonOverlap[j] = arr[i];
            j++;
        }
        i++;
    }

    *nonOverlapCount = maxCount;
    for (int i = 0; i < maxCount; i++)
    {
        printf("Activity from %d to %d\n", nonOverlap[i].start, nonOverlap[i].end);
    }

    // free the allocated memory
    free(dp);
    printf("\n");
    return maxCount;
}

// greedy
void activitySelectionGREEDY(struct activity arr[], int n, struct activity nonOverlap[], int *nonOverlapCount)
{ // Prints a maximum set of activities that can be done by a single person, one at a time.
    // sorting the activities in increasing order of their end time
    printf("\nGREEDY ALGORITHM:\n");
    bubbleSort(arr, n);

    // printing non-overlapping activities
    printf("\nNon-overlapping activities using greedy algorithm:\n");
    int i = 0, j = 1;
    nonOverlap[0] = arr[0];
    *nonOverlapCount = 1;
    printf("Activity from %d to %d\n", nonOverlap[0].start, nonOverlap[0].end);
    for (int i = 1; i < n; i++)
    {
        if (arr[i].start >= nonOverlap[*nonOverlapCount - 1].end)
        {
            nonOverlap[*nonOverlapCount] = arr[i];
            (*nonOverlapCount)++;
            printf("Activity from %d to %d\n", nonOverlap[*nonOverlapCount - 1].start, nonOverlap[*nonOverlapCount - 1].end);
        }
    }
    printf("\n");
}

int main()
{
    // creating random activities
    int n ;
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    struct activity arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i].start = rand() % 100 + 1;
        arr[i].end = arr[i].start + rand() % 100 + 1;
    }

    // finding the maximum count of non-overlapping activities using dynamic programming
    struct activity nonOverlapDP[n];
    int nonOverlapCountDP = 0;
    clock_t start1 = clock();
    activitySelectionDP(arr, n, nonOverlapDP, &nonOverlapCountDP);
    clock_t end1 = clock();
    printf("Maximum count of non-overlapping activities using dynamic programming is: %d\n\n", nonOverlapCountDP);

    // finding the maximum count of non-overlapping activities using greedy algorithm
    struct activity nonOverlapGreedy[n];
    int nonOverlapCountGreedy = 0;
    clock_t start2 = clock();
    activitySelectionGREEDY(arr, n, nonOverlapGreedy, &nonOverlapCountGreedy);
    clock_t end2 = clock();
    printf("Maximum count of non-overlapping activities using greedy algorithm is: %d\n", nonOverlapCountGreedy);
    double time1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    double time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("\n\nDynamic Programming :\nTime taken: %f seconds\n\n", time1); // printing time required for acivity selection using DP
    printf("Greedy Algorithm :\nTime taken: %f seconds", time2);            // printing time required for Greedy algorithm
    return 0;
}
```

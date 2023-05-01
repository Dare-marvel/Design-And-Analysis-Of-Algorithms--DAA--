### [QuickSort](https://www.geeksforgeeks.org/quick-sort/)
### [MergeSort](https://www.geeksforgeeks.org/merge-sort/)
### [Comparison](https://www.geeksforgeeks.org/quick-sort-vs-merge-sort/)

## Explanation of the Code:
Import necessary libraries: The program starts by importing the necessary C standard libraries - stdio.h, stdlib.h, and time.h.

* `Define the partition function`:<br>The partition function implements the partition step of the Quick Sort algorithm. It takes an array, a start index, and an end index as arguments and returns the index of the pivot element. The function selects the pivot element as the last element of the array, and then partitions the array into two subarrays such that all elements less than the pivot element are on the left side of the pivot element and all elements greater than or equal to the pivot element are on the right side.
* `Define the quick function:`<br>The quick function implements the Quick Sort algorithm. It takes an array, a start index, and an end index as arguments and sorts the array in ascending order using the Quick Sort algorithm. The function first partitions the array around the pivot element using the partition function and then recursively applies the same steps to the left and right subarrays.
* `Define the merge function:`<br>The merge function implements the merge step of the Merge Sort algorithm. It takes an array, a left index, a middle index, and a right index as arguments and merges two sorted subarrays into a single sorted array.
* `Define the mergeSort function:`<br>The mergeSort function implements the Merge Sort algorithm. It takes an array, a left index, and a right index as arguments and sorts the array in ascending order using the Merge Sort algorithm. The function first divides the array into two subarrays using the middle index and then recursively applies the same steps to the left and right subarrays. The merge function is used to merge the sorted subarrays.
* `Generate random numbers and write them to a file:`<br>The program generates 100,000 random integers between 100,000 and 1,000,000 using the rand() function and writes them to a file named "randomnum.txt" using the fopen() and fprintf() functions.
* `Sort arrays of increasing sizes and measure execution time:`<br>The program reads the random numbers from the "randomnum.txt" file and initializes two arrays - arr1 and arr2 - with the same set of random integers. The program then measures the execution time of Merge Sort and Quick Sort on each array for increasing sizes of arrays, starting from 100 elements and increasing by 100 for each iteration, up to 10,000 elements.
* `Measure execution time using clock() function:`<br>The execution time is measured using the clock() function from the time.h library. The function returns the number of clock ticks elapsed since the program started. The difference between the clock values before and after the sorting function call is used to compute the execution time.
* `Print the execution time:`<br>The program outputs the execution time for each algorithm for each array size, separated by a tab character. The output is in the format of three columns: iteration count, Merge Sort execution time, and Quick Sort execution time.
* `Close the file and exit the program:`<br>Finally, the program closes the file using the fclose() function and exits with a return value of 0.


## Code:
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int a[], int start, int end)
{
    int pivot = a[end];
    int i = (start - 1);

    for (int j = start; j <= end - 1; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    int t = a[i + 1];
    a[i + 1] = a[end];
    a[end] = t;
    return (i + 1);
}

double quick(int a[], int start, int end)
{
    if (start < end)
    {
        int p = partition(a, start, end);
        quick(a, start, p - 1);
        quick(a, p + 1, end);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;

    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {

        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main()
{
    double qust,mest;
    srand(time(0));
    FILE *fp;
    fp = fopen("randomnum.txt", "w");
    for (int i = 0; i < 100000; i++)
    {
        fprintf(fp, "%d\n", rand() % 900001 + 100000);
    }
    int upper_limit = 100;
    fclose(fp);
    printf("ItCount\tMerSort\tQuickSort\n");
    for (int i = 0; i < 1000; i++)
    {
        fp = fopen("randomnum.txt", "r");
        int arr1[upper_limit], arr2[upper_limit], temp_num;
        for (int j = 0; j < upper_limit; j++)
        {
            fscanf(fp, "%d", &temp_num);
            arr1[j] = temp_num;
            arr2[j] = temp_num;
        }
        fclose(fp);

        clock_t t;
        t = clock();
        mergeSort(arr2,0,upper_limit-1);
        t = clock() - t;
        mest = ((double)t) / CLOCKS_PER_SEC;
        clock_t t1;
        t1 = clock();
        qust=quick(arr1,0,upper_limit-1);
        t1 = clock() - t1;
        qust = ((double)t1) / CLOCKS_PER_SEC;
        printf("%lf\t%lf\n", mest, qust);
        fflush(stdout);
        upper_limit += 100;
    }
    return 0;
}
```
